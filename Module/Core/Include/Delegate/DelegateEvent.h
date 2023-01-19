/*
 * 델리게이트 이벤트들의 복사를 절대 허용해선 안됨.
 * 이벤트들은 각각의 아이디를 들고 있는데 이는 핸들러를 통한 제거를 위함임.
 * 만약 델리게이트 이벤트가 복사가 된다면 한 델리게이트 안에 중복된 아이디를 가진 델리게이트 이벤트가 있을 수도 있음.
 * 또한 델리게이트 이벤트들의 아이디를 관리하는 델리게이트 입장에서도 치명적.
 *
 * 이거 생각해보니까 복사는 막아도 이동은 허용해야 할듯.
 */

#pragma once

#include "TypeDefine.h"

namespace joo
{
	/**
	 * @brief 기본 델리게이트 이벤트 타입입니다.
	 * @tparam TRet 반환 타입.
	 * @tparam TParams 입력 가변 인자 타입.
	 */
	template <typename TRet, typename... TParams>
	class JDelegateEvent
	{
	public:
		JDelegateEvent()
			: mEventId(generateDelegateEventId())
			, mbIsExpired(false)
		{
		}

		/**
		 * @brief 델리게이트 이벤트를 호출합니다.
		 * @warning Invocation 후에 만료 여부를 갱신합니다.
		 * @return Invocation의 결과를 반환. Invocation이 실패하면 기본 생성자를 반환합니다.
		 * @warning TRet의 기본 생성자가 반드시 정의되어 있어야 합니다.
		 */
		virtual TRet Invoke(TParams ... params) = 0;

		/**
		 * @brief 델리게이트 이벤트가 만료되었는지 확인합니다.
		 * @details 만료 여부는 Invocation 후에 알 수 있습니다.
		 * @return 델리게이트 이벤트 만료 여부.
		 */
		bool IsExpired() const
		{
			return mbIsExpired;
		}

		/**
		 * @brief 델리게이트가 부여한 델리게이트 이벤트 아이디를 반환합니다.
		 * @return 델리게이트 이벤트 아이디.
		 */
		DelegateEventId GetEventId() const
		{
			return mEventId;
		}

		bool operator==(const JDelegateEvent& rhs)
		{
			return mEventId == rhs.mEventId;
		}

	protected:
		const DelegateEventId mEventId;
		bool mbIsExpired;

	private:
		DelegateEventId generateDelegateEventId() const
		{
			return reinterpret_cast<DelegateEventId>(this);
		}

	public:
		virtual ~JDelegateEvent() = default;
#pragma region Deleted Default Methods
		JDelegateEvent(const JDelegateEvent& other) = delete;
		JDelegateEvent(JDelegateEvent&& other) = delete;
		JDelegateEvent& operator=(const JDelegateEvent& rhs) = delete;
		JDelegateEvent& operator=(JDelegateEvent&& rhs) = delete;
#pragma endregion
	};
}

namespace std
{
	template <typename TRet, typename... TParams>
	struct hash<joo::JDelegateEvent<TRet, TParams...>>
	{
		size_t operator()(const joo::JDelegateEvent<TRet, TParams...>& event) const
		{
			static_assert(sizeof(size_t) == sizeof(joo::JDelegateEvent<TRet, TParams...>::mEventId));
			return event.GetEventId();
		}
	};
}

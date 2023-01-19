#pragma once

#include <type_traits>
#include <algorithm>
#include "DelegateHandle.h"
#include "DelegateBase.h"
#include "DelegateEvent.h"
#include "DelegateSharedEvent.h"
#include "DelegateRawEvent.h"
#include "DelegateStaticEvent.h"

namespace joo
{
#define INITIAL_EVENT_SET_CAPACITY (16)

	template <typename TRet, typename... TParams>
	class JMultiCastDelegate final : public JDelegateBase<TRet, TParams...>
	{
		using JDelegateBase<TRet, TParams...>::mDelegateId;
		using JDelegateEventPtr = std::unique_ptr<JDelegateEvent<TRet, TParams...>>;

	public:
		template <typename TUser>
		JDelegateHandle AddShared(std::shared_ptr<TUser> user, TRet(TUser::* method)(TParams ...))
		{
			std::function<TRet(TUser*, TParams...)> tmp = method;
			auto itr = mEventSet.emplace(std::make_unique<JDelegateSharedEvent<TRet, TUser, TParams...>>(user, std::move(tmp)));
			
			return JDelegateHandle{ mDelegateId, (*itr.first)->GetEventId() };
		}

		template <typename TUser>
		JDelegateHandle AddShared(std::shared_ptr<TUser> user, TRet(TUser::* method)(TParams ...) const)
		{
			std::function<TRet(TUser*, TParams...)> tmp = method;
			auto itr = mEventSet.emplace(std::make_unique<JDelegateSharedEvent<TRet, TUser, TParams...>>(user, std::move(tmp)));

			return JDelegateHandle{ mDelegateId, (*itr.first)->GetEventId() };
		}

		template <typename TUser>
		JDelegateHandle AddRaw(TUser* user, TRet(TUser::* method)(TParams ...))
		{
			std::function<TRet(TUser*, TParams...)> tmp = method;
			auto itr = mEventSet.emplace(std::make_unique<JDelegateRawEvent<TRet, TUser, TParams...>>(user, std::move(tmp)));

			return JDelegateHandle{ mDelegateId, (*itr.first)->GetEventId() };
		}

		template <typename TUser>
		JDelegateHandle AddRaw(TUser* user, TRet(TUser::* method)(TParams ...) const)
		{
			std::function<TRet(TUser*, TParams...)> tmp = method;
			auto itr = mEventSet.emplace(std::make_unique<JDelegateRawEvent<TRet, TUser, TParams...>>(user, std::move(tmp)));

			return JDelegateHandle{ mDelegateId, (*itr.first)->GetEventId() };
		}

		JDelegateHandle AddStatic(std::function<TRet(TParams...)> method)
		{
			auto itr = mEventSet.emplace(std::make_unique<JDelegateStaticEvent<TRet, TParams...>>(std::move(method)));

			return JDelegateHandle{ mDelegateId, (*itr.first)->GetEventId() };
		}

		JDelegateHandle AddLambda(std::function<TRet(TParams...)> method)
		{
			auto itr = mEventSet.emplace(std::make_unique<JDelegateStaticEvent<TRet, TParams...>>(std::move(method)));

			return JDelegateHandle{ mDelegateId, (*itr.first)->GetEventId() };
		}

		bool Remove(JDelegateHandle& handle)
		{
			auto pred = [handle](const JDelegateEventPtr& event)
			{
				return event->GetEventId() == handle.GetDelegateEventId();
			};

			auto itr = std::find_if(mEventSet.cbegin(), mEventSet.cend(), pred);

			if (itr != mEventSet.cend())
			{
				mEventSet.erase(itr);
				return true;
			}

			return false;
		}

		void RemoveAll()
		{
			mEventSet.clear();
		}

		void Broadcast(TParams... params)
		{
			for (auto itr = mEventSet.begin(); itr != mEventSet.end();)
			{
				(*itr)->Invoke(params...);

				if ((*itr)->IsExpired())
				{
					mEventSet.erase(itr);
				}
				else
				{
					itr++;
				}
			}
		}

		bool IsBound(const JDelegateHandle& handle) const override
		{
			auto pred = [handle](const JDelegateEventPtr& event)
			{
				return event->GetEventId() == handle.GetDelegateEventId();
			};

			auto itr = std::find_if(mEventSet.cbegin(), mEventSet.cend(), pred);
			return itr != mEventSet.cend();
		}

		bool IsBoundAny() const
		{
			return mEventSet.size() != 0;
		}

	private:
		std::unordered_set<JDelegateEventPtr> mEventSet;

	public:
		JMultiCastDelegate()
			: mEventSet()
		{
			static_assert(std::is_void_v<TRet>);

			mEventSet.reserve(INITIAL_EVENT_SET_CAPACITY);
		}

		~JMultiCastDelegate() override = default;
#pragma region Deleted Default Method
		JMultiCastDelegate(const JMultiCastDelegate& other) = delete;
		JMultiCastDelegate(JMultiCastDelegate&& other) = delete;
		JMultiCastDelegate& operator=(const JMultiCastDelegate& rhs) = delete;
		JMultiCastDelegate& operator=(JMultiCastDelegate&& rhs) = delete;
#pragma endregion
	};

#define DECLARE_MULTI_CAST_DELEGATE(DelegateName, ...) \
	using DelegateName = JMultiCastDelegate<void, __VA_ARGS__>;
}

#pragma once

#include <functional>
#include "DelegateEvent.h"

namespace joo
{
	template <typename TRet, typename TUser, typename... TParams>
	class JDelegateRawEvent final : public JDelegateEvent<TRet, TParams...>
	{
		using JDelegateEvent<TRet, TParams...>::mbIsExpired;

	public:
		JDelegateRawEvent(TUser* const user,
		                  std::function<TRet(TUser*, TParams ...)>&& method)
			: mUser(user)
			, mMethod(std::move(method))
		{
		}

		TRet Invoke(TParams ... params) override
		{
			if (mUser != nullptr)
			{
				return mMethod(mUser, params...);
			}

			mbIsExpired = true;
			return TRet();
		}

	private:
		TUser* const mUser;
		std::function<TRet(TUser*, TParams ...)> mMethod;

	public:
		~JDelegateRawEvent() override = default;

#pragma region Deleted Default Methods
		JDelegateRawEvent(const JDelegateRawEvent& other) = delete;
		JDelegateRawEvent(JDelegateRawEvent&& other) = delete;
		JDelegateRawEvent& operator=(const JDelegateRawEvent& rhs) = delete;
		JDelegateRawEvent& operator=(JDelegateRawEvent&& rhs) = delete;
#pragma endregion
	};
}

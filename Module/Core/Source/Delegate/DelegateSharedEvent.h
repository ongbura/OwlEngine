#pragma once

#include <functional>
#include <memory>
#include "DelegateEvent.h"

namespace joo
{
	template <typename TRet, typename TUser, typename... TParams>
	class JDelegateSharedEvent final : public JDelegateEvent<TRet, TParams...>
	{
		using JDelegateEvent<TRet, TParams...>::mbIsExpired;

	public:
		JDelegateSharedEvent(const std::shared_ptr<TUser>& user,
		                     std::function<TRet(TUser*, TParams ...)>&& method)
			: mUser(user)
			, mMethod(std::move(method))
		{
		}

		TRet Invoke(TParams ... params) override
		{
			if (auto userSp = mUser.lock())
			{
				return mMethod(userSp.get(), params...);
			}

			mbIsExpired = true;
			return TRet();
		}

	private:
		std::weak_ptr<TUser> mUser;
		std::function<TRet(TUser*, TParams ...)> mMethod;

	public:
		~JDelegateSharedEvent() override = default;

#pragma region Deleted Default Methods
		JDelegateSharedEvent(const JDelegateSharedEvent& other) = delete;
		JDelegateSharedEvent(JDelegateSharedEvent&& other) = delete;
		JDelegateSharedEvent& operator=(const JDelegateSharedEvent& rhs) = delete;
		JDelegateSharedEvent& operator=(JDelegateSharedEvent&& rhs) = delete;
#pragma endregion
	};
}

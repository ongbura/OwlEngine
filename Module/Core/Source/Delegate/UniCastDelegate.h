#pragma once

#include <type_traits>
#include "DelegateHandle.h"
#include "DelegateBase.h"
#include "DelegateEvent.h"
#include "DelegateSharedEvent.h"
#include "DelegateRawEvent.h"
#include "DelegateStaticEvent.h"

namespace joo
{
	template <typename TRet, typename... TParams>
	class JUniCastDelegate final : public JDelegateBase<TRet, TParams...>
	{
		using JDelegateBase<TRet, TParams...>::mDelegateId;

	public:
		template <typename TUser>
		JDelegateHandle BindShared(std::shared_ptr<TUser> user, TRet (TUser::*method)(TParams ...))
		{
			std::function<TRet(TUser*, TParams ...)> tmp = method;
			mDelegateEvent = std::make_unique<JDelegateSharedEvent<TRet, TUser, TParams...>>(user, std::move(tmp));

			return JDelegateHandle{ mDelegateId, mDelegateEvent->GetEventId() };
		}

		template <typename TUser>
		JDelegateHandle BindShared(std::shared_ptr<TUser> user, TRet (TUser::* method)(TParams ...) const)
		{
			std::function<TRet(TUser*, TParams ...)> tmp = method;
			mDelegateEvent = std::make_unique<JDelegateSharedEvent<TRet, TUser, TParams...>>(user, std::move(tmp));

			return JDelegateHandle{ mDelegateId, mDelegateEvent->GetEventId() };
		}

		template <typename TUser>
		JDelegateHandle BindRaw(TUser* user, TRet (TUser::* method)(TParams ...))
		{
			std::function<TRet(TUser*, TParams ...)> tmp = method;
			mDelegateEvent = std::make_unique<JDelegateRawEvent<TRet, TUser, TParams...>>(user, std::move(tmp));

			return JDelegateHandle{ mDelegateId, mDelegateEvent->GetEventId() };
		}

		template <typename TUser>
		JDelegateHandle BindRaw(TUser* user, TRet (TUser::* method)(TParams ...) const)
		{
			std::function<TRet(TUser*, TParams ...)> tmp = method;
			mDelegateEvent = std::make_unique<JDelegateRawEvent<TRet, TUser, TParams...>>(user, std::move(tmp));

			return JDelegateHandle{ mDelegateId, mDelegateEvent->GetEventId() };
		}
		
		JDelegateHandle BindStatic(std::function<TRet(TParams ...)> method)
		{
			mDelegateEvent = std::make_unique<JDelegateStaticEvent<TRet, TParams...>>(std::move(method));

			return JDelegateHandle{ mDelegateId, mDelegateEvent->GetEventId() };
		}

		JDelegateHandle BindLambda(std::function<TRet(TParams ...)> method)
		{
			mDelegateEvent = std::make_unique<JDelegateStaticEvent<TRet, TParams...>>(std::move(method));
			
			return JDelegateHandle{ mDelegateId, mDelegateEvent->GetEventId() };
		}

		void UnBind(JDelegateHandle& handle)
		{
			if (IsBound())
			{
				UnBind();				
			}

			handle.mBoundedDelegateId = INVALID_ID;
			handle.mDelegateEventId = INVALID_ID;
		}

		void UnBind()
		{
			mDelegateEvent.reset();
		}

		TRet Execute(TParams ... params)
		{
			if constexpr (std::is_void_v<TRet>)
			{
				mDelegateEvent->Invoke(params...);

				if (mDelegateEvent->IsExpired())
				{
					UnBind();
				}

				return;
			}
			else
			{
				TRet ret = mDelegateEvent->Invoke(params...);

				if (mDelegateEvent->IsExpired())
				{
					UnBind();
					return TRet();
				}

				return ret;
			}
		}

		TRet ExecuteIfBound(TParams ... params)
		{
			if constexpr (std::is_void_v<TRet>)
			{
				if (IsBound())
				{
					Execute(params...);
				}

				return;
			}
			else
			{
				if (IsBound())
				{
					return Execute(params...);
				}

				return TRet();
			}
		}

		bool IsBound(const JDelegateHandle& handle) const override
		{
			if (const bool bIsValid = mDelegateEvent.get() != nullptr)
			{
				const bool bIsBound = (handle.mBoundedDelegateId == mDelegateId) && (handle.mDelegateEventId == mDelegateEvent->GetEventId());

				return bIsValid && bIsBound;
			}

			return false;
		}

		bool IsBound() const
		{
			return mDelegateEvent.get() != nullptr;
		}

	private:
		std::unique_ptr<JDelegateEvent<TRet, TParams...>> mDelegateEvent;

	public:
		JUniCastDelegate()
			: mDelegateEvent(nullptr)
		{
		}

		~JUniCastDelegate() override
		{
		}

#pragma region Deleted Default Method
		JUniCastDelegate(const JUniCastDelegate& other) = delete;
		JUniCastDelegate(JUniCastDelegate&& other) = delete;
		JUniCastDelegate& operator=(const JUniCastDelegate& rhs) = delete;
		JUniCastDelegate& operator=(JUniCastDelegate&& rhs) = delete;
#pragma endregion
	};

#define DECLARE_UNI_CAST_DELEGATE(DelegateName, ...) \
	using DelegateName = JUniCastDelegate<void, __VA_ARGS__>;

#define DECLARE_UNI_CAST_DELEGATE_RetVal(RetValType, DelegateName, ...) \
	using DelegateName = JUniCastDelegate<RetValType, __VA_ARGS__>;
}

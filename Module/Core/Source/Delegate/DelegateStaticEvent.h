#pragma once

#include <functional>
#include "DelegateEvent.h"

namespace joo
{
	template <typename TRet, typename... TParams>
	class JDelegateStaticEvent final : public JDelegateEvent<TRet, TParams...>
	{
		using Super = JDelegateEvent<TRet, TParams...>;

	public:
		JDelegateStaticEvent(std::function<TRet(TParams ...)>&& func)
			: mMethod(std::move(func))
		{
		}

		TRet Invoke(TParams ... params) override
		{
			return mMethod(params...);
		}

	private:
		std::function<TRet(TParams ...)> mMethod;

	public:
		~JDelegateStaticEvent() override = default;

#pragma region Deleted Default Methods
		JDelegateStaticEvent(const JDelegateStaticEvent& other) = delete;
		JDelegateStaticEvent(JDelegateStaticEvent&& other) = delete;
		JDelegateStaticEvent& operator=(const JDelegateStaticEvent& rhs) = delete;
		JDelegateStaticEvent& operator=(JDelegateStaticEvent&& rhs) = delete;
#pragma endregion
	};
}

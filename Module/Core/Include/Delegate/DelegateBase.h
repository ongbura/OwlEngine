#pragma once

#include "TypeDefine.h"

namespace joo
{
	template <typename TRet, typename... TParams>
	class JDelegateBase
	{
	public:
		JDelegateBase()
			: mDelegateId(generateDelegateId())
		{}

		virtual ~JDelegateBase() = default;		

		DelegateId GetDelegateId() const
		{
			return mDelegateId;
		}

		virtual bool IsBound(const JDelegateHandle& handle) const = 0;

	protected:
		DelegateId generateDelegateId() const
		{
			return reinterpret_cast<DelegateId>(this);
		}
		
		const DelegateId mDelegateId;
#pragma region Deleted Default Methods
	public:
		JDelegateBase(const JDelegateBase& other) = delete;
		JDelegateBase(JDelegateBase&& other) = delete;
		JDelegateBase& operator=(const JDelegateBase& rhs) = delete;
		JDelegateBase& operator=(JDelegateBase&& rhs) = delete;
#pragma endregion
	};
}

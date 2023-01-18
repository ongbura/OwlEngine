#pragma once

#include <cassert>
#include "TypeDefine.h"

namespace joo
{
#define INVALID_ID (0)

	class JDelegateHandle
	{
		template <typename, typename...>
		friend class JUniCastDelegate;

		template <typename, typename...>
		friend class JMultiCastDelegate;

	public:
		~JDelegateHandle() = default;

		JDelegateHandle(JDelegateHandle&& other) noexcept
			: mBoundedDelegateId(other.mBoundedDelegateId)
			, mDelegateEventId(other.mDelegateEventId)
		{
			other.mBoundedDelegateId = INVALID_ID;
			other.mDelegateEventId = INVALID_ID;
		}

		bool IsValid() const
		{
			return mBoundedDelegateId == INVALID_ID || mDelegateEventId == INVALID_ID;
		}

		void ReAssign(JDelegateHandle&& other)
		{
			assert(!IsValid());

			mBoundedDelegateId = other.mBoundedDelegateId;
			mDelegateEventId = other.mDelegateEventId;

			other.mBoundedDelegateId = INVALID_ID;
			other.mDelegateEventId = INVALID_ID;
		}

		JDelegateHandle& operator=(JDelegateHandle&& rhs) noexcept
		{
			if (this != &rhs)
			{
				ReAssign(std::move(rhs));
			}

			return *this;
		}
		
		DelegateId GetBoundedDelegateId() const
		{
			return mBoundedDelegateId;
		}

		DelegateEventId GetDelegateEventId() const
		{
			return mDelegateEventId;
		}

	private:
		JDelegateHandle(const DelegateId delegateId, const DelegateEventId eventId)
			: mBoundedDelegateId(delegateId)
			, mDelegateEventId(eventId)
		{}

		JDelegateHandle(const JDelegateHandle& other) = default;


		DelegateId mBoundedDelegateId;
		DelegateEventId mDelegateEventId;
#pragma region Deleted Default Methods
	public:
		JDelegateHandle& operator=(const JDelegateHandle& rhs) = delete;
#pragma endregion
	};
}

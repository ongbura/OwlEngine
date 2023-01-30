#pragma once

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

/**
* Makes a type non-copyable and non-movable by deleting copy/move constructors and assignment/move operators.
* The macro should be placed in the public section of the type for better compiler diagnostic messages.
* Example usage:
*
*	class FMyClassName
*	{
*	public:
*		NON_COPYABLE(FMyClassName)
*		FMyClassName() = default;
*	};
*/
#define NON_COPYABLE(TypeName) \
	TypeName(TypeName&&) = delete; \
	TypeName(const TypeName&) = delete; \
	TypeName& operator=(const TypeName&) = delete; \
	TypeName& operator=(TypeName&&) = delete;

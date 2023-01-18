#pragma once

#include <cstdint>

namespace joo
{
#if !defined(ENV64BIT) && !defined(ENV32BIT)
	// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENV64BIT
#else
#define ENV32BIT
#endif
#endif
	// Check windows
	// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENV64BIT
#else
#define ENV32BIT
#endif
#endif
	// Check GCC
#endif

#if defined(ENV32BIT)
	using DelegateId = uint32_t;
	using DelegateEventId = uint32_t;
#elif defined(ENV64BIT)
	using DelegateId = uint64_t;
	using DelegateEventId = uint64_t;
#else
#error "Must define either ENV32BIT or ENV64BIT"
#endif
}

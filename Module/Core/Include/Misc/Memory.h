#pragma once

#include <memory>

template <typename T>
using TUniquePtr = std::unique_ptr<T>;

template <typename T, typename... TArgs>
constexpr TUniquePtr<T> MakeUnique(TArgs... args)
{
	return std::make_unique<T>(std::forward<TArgs>(args)...);
}

template <typename T>
using TSharedPtr = std::shared_ptr<T>;

template <typename T, typename... TArgs>
constexpr TSharedPtr<T> MakeShared(TArgs... args)
{
	return std::make_shared<T>(std::forward<TArgs>(args)...);
}

template <typename T>
using TWeakPtr = std::weak_ptr<T>;

template <typename T>
using TSharedFromThis = std::enable_shared_from_this<T>;

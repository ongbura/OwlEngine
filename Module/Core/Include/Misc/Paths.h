#pragma once

#include "CoreDLL.h"

class CORE_API Paths
{
public:
	Paths() = default;
	explicit Paths(const std::filesystem::path& path);
	Paths(const Paths&) = default;
	Paths(Paths&&) = delete;
	~Paths() = default;

	static std::wstring GetEngineDir();

	static std::wstring GetLogDir();

	static std::wstring GetEngineContentDir();

	static std::wstring GetUserContentDir();

	static std::wstring GetConfigDir();

	static std::wstring GetEngineBinariesDir();

	template <typename... TArgs>
	Paths Combine(TArgs&&... args);

private:
	std::filesystem::path mPath{};
};

template <typename ... TArgs>
Paths Paths::Combine(TArgs&&... args)
{

}


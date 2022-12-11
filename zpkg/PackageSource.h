#pragma once
#include <string>
#include <vector>

#include "cli.h"
#include "PackageSource.h"
#include "PackageSource.h"
#include "util.h"

class PackageSource
{
public:
	__nodiscard std::string name() const
	{
		return m_name;
	}

	virtual std::vector<std::string> list() = 0;
	static std::vector<PackageSource*> all();

protected:
	virtual ~PackageSource() = default;

	const std::string m_name;

	explicit PackageSource(std::string name) : m_name(std::move(name))
	{
	}
};

class ScoopPackageSource final : public PackageSource
{
public:
	ScoopPackageSource() : PackageSource("scoop")
	{
	}

	std::vector<std::string> list() override
	{
		return split(exec(std::format("{} {}", name(), "list").c_str()), ENV_NEWLINE);
	}
};

class PacmanPackageSource final : public PackageSource
{
public:
	PacmanPackageSource() : PackageSource("pacman")
	{
	}

	std::vector<std::string> list() override
	{
		return split(exec(std::format("{} {}", name(), "-Q").c_str()), ENV_NEWLINE);
	}

};

inline std::vector<PackageSource*> PackageSource::all()
{
	return {new ScoopPackageSource(), new PacmanPackageSource()};
}

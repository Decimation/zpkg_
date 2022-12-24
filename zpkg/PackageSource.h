#pragma once
#include <string>
#include <vector>

#include "cli.h"
#include "PackageSource.h"
#include "util.h"

class PackageSource
{
public:
	__nodiscard std::string name() const
	{
		return m_name;
	}

	virtual std::vector<std::string> list()
	{
		return RunCommand(name(), {m_cmd_list});
	}

	virtual std::vector<std::string> search(std::string q)
	{
		return RunCommand(name(), {m_cmd_search, q});
	}

	static std::vector<PackageSource*> all();

protected:
	virtual ~PackageSource() = default;

	const std::string m_name;

	const std::string m_cmd_list;
	const std::string m_cmd_search;

	explicit PackageSource(std::string name, std::string listArgs = "list", std::string searchArgs = "search")
		: m_name(std::move(name)), m_cmd_list(std::move(listArgs)), m_cmd_search(std::move(searchArgs))
	{
	}
};

class ScoopPackageSource final : public PackageSource
{
public:
	ScoopPackageSource() : PackageSource("scoop")
	{
	}
};

class PacmanPackageSource final : public PackageSource
{
public:
	PacmanPackageSource() : PackageSource("pacman", "-Q", "-Q")
	{
	}
};

class WingetPackageSource final : public PackageSource
{
public:
	WingetPackageSource() : PackageSource("winget")
	{
	}
};

inline std::vector<PackageSource*> PackageSource::all()
{
	return {new ScoopPackageSource(), new PacmanPackageSource(), new WingetPackageSource()};
}

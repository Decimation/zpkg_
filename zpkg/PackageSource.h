#pragma once
#include <string>
#include <vector>

#include "cli.h"
#include "util.h"

class PackageSource
{
public:
	__nodiscard std::string name() const { return m_name; }
	virtual std::vector<std::string> list() = 0;

protected:
	virtual ~PackageSource() = default;
	
	const std::string m_name;

	PackageSource(std::string name) : m_name(std::move(name))
	{
		
	};
};

class ScoopPackageSource final : public PackageSource
{
public:
	ScoopPackageSource() : ::PackageSource("scoop")
	{
	}
	std::vector<std::string> list() override
	{
		return split(exec(std::format("{} {}", name(), "list").c_str()), "\r\n");
	}
};

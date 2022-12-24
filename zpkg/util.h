#pragma once

#include <cstdarg>
#include <xutil.h>
#include "Windows.h"

static std::vector<std::string> RunCommand(std::string name, const std::vector<std::string>& args)
{
	std::string buf;
	join(args, SPACE, buf);

	const auto cmd = std::format("{} {}", name, buf);

	dbg_out("#> {}\n", cmd);

	auto output = split(exec(cmd.c_str()), ENV_NEWLINE);

	return output;
}

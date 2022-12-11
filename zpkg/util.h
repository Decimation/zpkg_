#pragma once
#define __nodiscard [[nodiscard]]

constexpr const char* ENV_NEWLINE = "\r\n";

inline std::vector<std::string> split(std::string s, const std::string& delimiter)
{
	size_t pos_start = 0, pos_end;
	const size_t delim_len = delimiter.length();
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		std::string token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

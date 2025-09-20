#include "../../inc/util/IndexParser.h"
#include <cstdlib>
#include <cstring>

uint32_t IndexParser::getLastIndex(const std::string &url) const
{
	const char *p = std::strrchr(url.data(), '/');
	p++;
	return std::atoi(p);
}

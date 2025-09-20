#ifndef __INDEXPARSER_H__
#define __INDEXPARSER_H__

#include <string>
#include <cstdint>

class IndexParser
{
	public:
		IndexParser() = default;
		explicit IndexParser(const IndexParser &) = default;
		IndexParser(IndexParser &&) = default;
		~IndexParser() = default;
	
		uint32_t getLastIndex(const std::string &url) const;
};

#endif

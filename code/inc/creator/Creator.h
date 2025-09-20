#ifndef __CREATOR_H__
#define __CREATOR_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <functional>

class Creator
{
	public:
		Creator() = default;
		explicit Creator(const Creator &) = delete;
		Creator(Creator &&) = delete;
		~Creator() = default;

		template <typename BaseClass, typename ChildClass>
		std::function<BaseClass*()> getCreateFunction() const;

		template <typename BaseClass, typename ChildClass, typename... Args>
		std::function<BaseClass*()> getCreateFunction(Args &...args) const;
};

template <typename BaseClass, typename ChildClass>
std::function<BaseClass*()> Creator::getCreateFunction() const
{
	return [](){ return new ChildClass; };
}

template <typename BaseClass, typename ChildClass, typename... Args>
std::function<BaseClass*()> Creator::getCreateFunction(Args &...args) const
{
	return [&args...](){ return new ChildClass(args...); };
}

#endif

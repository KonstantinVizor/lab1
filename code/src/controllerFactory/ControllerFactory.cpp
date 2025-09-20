#include "../../inc/controllerFactory/ControllerFactory.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <regex>

ControllerFactory::ControllerFactory()
{
	_rMap = {{R"((\d{1,}))", std::regex(R"(\{i\})")}};
}

ControllerFactory& ControllerFactory::registerHandler(const std::string &path,
								const std::string &method,
								const HandlerCreator &creator)
{
	std::string resultPath = path;
	for (RegexMap::value_type &pair : _rMap)
		resultPath = std::regex_replace(resultPath, pair.second, pair.first);
	_hMap.push_back({resultPath, method, creator});
	return *this;
}

ControllerFactory& ControllerFactory::registerDefaultHandler(const HandlerCreator &creator)
{
	_defaultHandlerCreator = creator;
	return *this;
}

ControllerFactory::HandlerPtr ControllerFactory::createRequestHandler([[maybe_unused]] const Poco::Net::HTTPServerRequest &req)
{
	bool found = false;
	HandlerPtr result = nullptr;
	for (HandlerCreatorMap::iterator it = _hMap.begin(); !found && it != _hMap.end(); it++)
		if (std::regex_match(req.getURI(), std::regex(std::get<0>(*it))) &&
			req.getMethod() == std::get<1>(*it))
		{
			found = true;
			result = std::get<2>(*it)();
		}
	if (!found)
		result = _defaultHandlerCreator();
	return result;
}

#ifndef __REQUESTHANDLERFACTORY_H__
#define __REQUESTHANDLERFACTORY_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <functional>
#include <regex>
#include <unordered_map>

class ControllerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
	private:
		using HandlerPtr = Poco::Net::HTTPRequestHandler *;
		using HandlerCreator = std::function<HandlerPtr()>;
		using HandlerCreatorMap = std::vector<std::tuple<std::string,
								std::string,
								HandlerCreator>>;
		using RegexMap = std::unordered_map<std::string, std::regex>;

		HandlerCreator _defaultHandlerCreator;
		HandlerCreatorMap _hMap;	
		RegexMap _rMap;

	public:
		explicit ControllerFactory(const ControllerFactory &) = delete;
		ControllerFactory(ControllerFactory &&) = delete;
		~ControllerFactory() = default;
		ControllerFactory();

		/// Methods: GET, DELETE, PATCH, POST
		/// PathVaribles: {i} - varible int
		ControllerFactory& registerHandler(const std::string &path, const std::string &method, const HandlerCreator &creator);
		ControllerFactory& registerDefaultHandler(const HandlerCreator &creator);

		virtual HandlerPtr createRequestHandler(const Poco::Net::HTTPServerRequest &req) override;
};

#endif

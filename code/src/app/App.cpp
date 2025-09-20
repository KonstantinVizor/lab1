#include "../../inc/app/App.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Util/Application.h>
#include <Poco/Net/HTTPServer.h>
#include <memory>
#include "../../inc/controllerFactory/ControllerFactory.h"
#include "../../inc/creator/Creator.h"
#include "../../inc/controllers/DefaultController.h"
#include "../../inc/controllers/PersonCreateController.h"
#include "../../inc/controllers/PersonGetAllController.h"
#include "../../inc/controllers/PersonGetByIdController.h"
#include "../../inc/controllers/PersonDeleteByIdController.h"
#include "../../inc/controllers/PersonUpdateByIdController.h"
#include "../../inc/repositories/PersonRepository.h"
#include "Poco/Data/PostgreSQL/Connector.h"
#include "Poco/Data/Session.h"

App::App() :
	_port(8080)
{}

App& App::setPort(int port)
{
	_port = port;
	return *this;
}

int App::main([[maybe_unused]] const std::vector<std::string> &args)
{
	Poco::Data::PostgreSQL::Connector::registerConnector();
	std::shared_ptr<Poco::Data::Session> session = std::make_shared<Poco::Data::Session>("postgresql", "host=postgres port=5432 dbname=persons user=program password=test");
	std::shared_ptr<PersonRepository> personRepository = std::make_shared<PersonRepository>();
	personRepository->setSession(session);
	Creator creator;
	ControllerFactory *factory = new ControllerFactory;
	factory->registerHandler("/api/v1/persons", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, PersonGetAllController>(personRepository));
	factory->registerHandler("/api/v1/persons/{i}", "DELETE", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, PersonDeleteByIdController>(personRepository));
	factory->registerHandler("/api/v1/persons/{i}", "PATCH", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, PersonUpdateByIdController>(personRepository));
	factory->registerHandler("/api/v1/persons/{i}", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, PersonGetByIdController>(personRepository));
	factory->registerHandler("/api/v1/persons", "POST", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, PersonCreateController>(personRepository));
	factory->registerDefaultHandler(creator.getCreateFunction<Poco::Net::HTTPRequestHandler, DefaultController>());
	Poco::Net::HTTPServer server(factory, _port, new Poco::Net::HTTPServerParams);
	server.start();
	this->waitForTerminationRequest();
	server.stop();
	return Poco::Util::Application::EXIT_OK;
}

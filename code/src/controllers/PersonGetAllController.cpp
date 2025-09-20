#include "../../inc/controllers/PersonGetAllController.h"
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPResponse.h>

PersonGetAllController::PersonGetAllController(const std::shared_ptr<PersonRepository> &personRepository) :
											Poco::Net::HTTPRequestHandler(),
											_personRepository(personRepository)
{}

void PersonGetAllController::handleRequest([[maybe_unused]] Poco::Net::HTTPServerRequest &req,
					Poco::Net::HTTPServerResponse &resp)
{
	std::vector<PersonModel> models;
	std::string message;
	models = _personRepository->getAll();
	resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	resp.setContentType("application/json");
	message = "[";
	for (int i = 0; i < static_cast<int>(models.size()); i++)
	{
		message += models[i].toJson();
		if (i != static_cast<int>(models.size()) - 1)
			message += ",";
	}
	message += "]";
	std::cout << "Return json on GetAll\n" << message << "\n";
	std::cout.flush();
	resp.sendBuffer(message.data(), message.size());
}

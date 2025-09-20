#include "../../inc/controllers/PersonCreateController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <string>

PersonCreateController::PersonCreateController(const std::shared_ptr<PersonRepository> &personRepository) :
											Poco::Net::HTTPRequestHandler(),
											_personRepository(personRepository)
{}

void PersonCreateController::handleRequest(Poco::Net::HTTPServerRequest &req,
					Poco::Net::HTTPServerResponse &resp)
{
	bool correctJson;
	uint32_t id;
	std::string body;
	PersonModel model;
	req.stream() >> body;
	correctJson = model.fromJson(body, true);
	if (!correctJson)
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
		resp.setReason("Bad Request");
		resp.send() << "{\"message\":\"request's json is invalid\"}";
	}
	else
	{
		id = _personRepository->create(model);
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);
		resp.setReason("Created");
		resp.add("location", "/person/" + std::to_string(id));
		resp.send();
	}
}

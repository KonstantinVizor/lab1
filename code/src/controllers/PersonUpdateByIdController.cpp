#include "../../inc/controllers/PersonUpdateByIdController.h"
#include "../../inc/util/IndexParser.h"
#include "Poco/Net/HTTPResponse.h"
#include <optional>

PersonUpdateByIdController::PersonUpdateByIdController(const std::shared_ptr<PersonRepository> &personRepository) :
											Poco::Net::HTTPRequestHandler(),
											_personRepository(personRepository)
{}

void PersonUpdateByIdController::handleRequest(Poco::Net::HTTPServerRequest &req,
					Poco::Net::HTTPServerResponse &resp)
{
	bool correctJson;
	uint32_t id;
	IndexParser parser;
	std::string body;
	std::optional<PersonModel> model;
	req.stream() >> body;
	id = parser.getLastIndex(req.getURI());
	model = _personRepository->getById(id);
	if (!model.has_value())
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
		resp.setReason("Not Found");
		resp.send() << "{\"message\":\"Cannot find person with id = " << id << "\"}";
	}
	else
	{
		correctJson = model->fromJson(body);
		if (!correctJson)
		{
			resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
			resp.setReason("Bad Request");
			resp.send() << "{\"message\":\"request's json is invalid\"}";
		}
		else
		{
			_personRepository->updateById(id, *model);
			resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
			resp.setContentType("application/json");
			resp.send() << model->toJson();
		}
	}
}

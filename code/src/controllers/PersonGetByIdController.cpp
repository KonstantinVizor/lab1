#include "../../inc/controllers/PersonGetByIdController.h"
#include "../../inc/util/IndexParser.h"

PersonGetByIdController::PersonGetByIdController(const std::shared_ptr<PersonRepository> &personRepository) :
											Poco::Net::HTTPRequestHandler(),
											_personRepository(personRepository)
{}

void PersonGetByIdController::handleRequest(Poco::Net::HTTPServerRequest &req,
					Poco::Net::HTTPServerResponse &resp)
{
	uint32_t id;
	IndexParser parser;
	std::optional<PersonModel> model;
	id = parser.getLastIndex(req.getURI());
	model = _personRepository->getById(id);
	if (model.has_value())
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
		resp.setContentType("application/json");
		resp.send() << model->toJson();
	}
	else
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
		resp.setContentType("application/json");
		resp.setReason("Not Found");
		resp.send() << "{\"message\":\"Cannot find person with id = " << id << "\"}";
	}
}

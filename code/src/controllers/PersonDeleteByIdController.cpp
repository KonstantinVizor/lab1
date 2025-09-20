#include "../../inc/controllers/PersonDeleteByIdController.h"
#include "../../inc/util/IndexParser.h"

PersonDeleteByIdController::PersonDeleteByIdController(const std::shared_ptr<PersonRepository> &personRepository) :
											Poco::Net::HTTPRequestHandler(),
											_personRepository(personRepository)
{}

void PersonDeleteByIdController::handleRequest(Poco::Net::HTTPServerRequest &req,
					Poco::Net::HTTPServerResponse &resp)
{
	uint32_t id;
	IndexParser parser;
	id = parser.getLastIndex(req.getURI());
	_personRepository->deleteById(id);
	resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
	resp.setContentType("application/json");
	resp.setReason("No Content");
	resp.send() << "{\"message\":\"Person was removed with id = " << id << "\"}";
}

#include "../../inc/controllers/DefaultController.h"
#include <Poco/Net/HTTPResponse.h>

void DefaultController::handleRequest([[maybe_unused]] Poco::Net::HTTPServerRequest &req,
					Poco::Net::HTTPServerResponse &resp)
{
	resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
	resp.setReason("Not Found");
	resp.send() << "Page Not Found 404";
}

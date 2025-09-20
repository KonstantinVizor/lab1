#include <cassert>
#include "../../inc/controllers/PersonDeleteByIdController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockPersonRepository.h"

int main(void)
{
	std::shared_ptr<PersonRepository> rep = std::make_shared<MockPersonRepository>();
	MockResponse resp;
	MockRequest req("");
	PersonDeleteByIdController controller(rep);
	req.setURI("/person/13");

	controller.handleRequest(req, resp);
	
	std::cout << resp.getStatus();
	return 0;
}

#include <cassert>
#include "../../inc/controllers/PersonCreateController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockPersonRepository.h"

int main(void)
{
	PersonModel testData;
	testData.setId(0)
		.setName("Kostya")
		.setAge(21)
		.setWork("Student")
		.setAddress("Moscow");
	std::string json = testData.toJson();
	MockResponse resp;
	std::shared_ptr<PersonRepository> rep = std::make_shared<MockPersonRepository>();
	PersonCreateController controller(rep);
	MockRequest req(json);
	static_cast<MockPersonRepository *>(rep.get())->setId(13);

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);
	assert(resp.get("location") == "/person/13");
	return 0;
}

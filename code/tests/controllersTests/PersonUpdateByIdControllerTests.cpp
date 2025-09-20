#include <cassert>
#include "../../inc/controllers/PersonUpdateByIdController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockPersonRepository.h"

int main(void)
{
	std::shared_ptr<PersonRepository> rep = std::make_shared<MockPersonRepository>();
	PersonModel testData, resData;
	testData.setId(0)
		.setName("Kostya")
		.setAge(21)
		.setWork("Student")
		.setAddress("Moscow");
	resData.setId(0)
		.setName("Miha")
		.setAge(21)
		.setWork("Student")
		.setAddress("Moscow");
	std::string updateJson = "{\"name\":\"Miha\"}";
	MockResponse resp;
	PersonUpdateByIdController controller(rep);
	static_cast<MockPersonRepository *>(rep.get())->setTestData(testData);
	MockRequest req(updateJson);

	controller.handleRequest(req, resp);
	
	PersonModel tmp1, tmp2;
	tmp1.fromJson(resp.getStream().str());
	tmp2 = *rep->getById(testData.getId());
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	assert(tmp1 == tmp2);
	assert(tmp1 == resData);
	return 0;
}

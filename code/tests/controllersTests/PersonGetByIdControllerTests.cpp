#include <cassert>
#include "../../inc/controllers/PersonGetByIdController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockPersonRepository.h"
#include <Poco/Net/HTTPResponse.h>

int main(void)
{
	std::shared_ptr<PersonRepository> rep = std::make_shared<MockPersonRepository>();
	PersonModel testData;
	testData.setId(11)
		.setName("Kostya")
		.setAge(21)
		.setWork("Student")
		.setAddress("Moscow");
	MockResponse resp;
	MockRequest req("");
	static_cast<MockPersonRepository *>(rep.get())->setTestData(testData);
	bool flag;
	PersonGetByIdController controller(rep);
	req.setURI("/person/11");

	controller.handleRequest(req, resp);
	
	PersonModel tmp;
	std::string json = resp.getStream().str();
	flag = tmp.fromJson(json);
	assert(flag);
	assert(tmp == testData);

	
	req.setURI("/person/10");

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
	return 0;
}

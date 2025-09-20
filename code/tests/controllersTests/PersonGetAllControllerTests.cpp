#include <cassert>
#include "../../inc/controllers/PersonGetAllController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockPersonRepository.h"
#include "../util/JsonToVectorConverter.h"

int main(void)
{
	std::shared_ptr<PersonRepository> rep = std::make_shared<MockPersonRepository>();
	std::vector<PersonModel> testData;
	testData.push_back(PersonModel().setId(0)
					.setName("Kostya")
					.setAge(21)
					.setWork("Student")
					.setAddress("Moscow"));
	testData.push_back(PersonModel().setId(1)
					.setName("Miha")
					.setAge(20)
					.setWork("Student")
					.setAddress("Zelenograd"));
	JsonVectorConverter converter;
	MockResponse resp;
	MockRequest req("");
	static_cast<MockPersonRepository *>(rep.get())->setTestData(testData);
	PersonGetAllController controller(rep);

	controller.handleRequest(req, resp);
	
	std::string json = resp.getStream().str();
	std::vector<std::string> jsons = converter.jsonToVector(json);
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	assert(jsons.size() == testData.size());
	for (int i = 0; i < static_cast<int>(jsons.size()); i++)
	{
		PersonModel tmp;
		tmp.fromJson(jsons[i]);
		assert(tmp == testData[i]);
	}
	return 0;
}

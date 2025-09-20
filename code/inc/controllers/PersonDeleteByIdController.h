#ifndef __PERSONDELETEBYIDCONTROLLER_H__
#define __PERSONDELETEBYIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <memory>
#include "../repositories/PersonRepository.h"

class PersonDeleteByIdController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<PersonRepository> _personRepository;	

	public:
		PersonDeleteByIdController() = default;
		explicit PersonDeleteByIdController(const PersonDeleteByIdController &) = delete;
		PersonDeleteByIdController(PersonDeleteByIdController &&) = delete;
		~PersonDeleteByIdController() = default;

		PersonDeleteByIdController(const std::shared_ptr<PersonRepository> &personRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif

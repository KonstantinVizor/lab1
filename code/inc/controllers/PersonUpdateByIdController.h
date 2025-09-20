#ifndef __PERSONUPDATEBYIDCONTROLLER_H__
#define __PERSONUPDATEBYIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <memory>
#include "../repositories/PersonRepository.h"

class PersonUpdateByIdController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<PersonRepository> _personRepository;	

	public:
		PersonUpdateByIdController() = default;
		explicit PersonUpdateByIdController(const PersonUpdateByIdController &) = delete;
		PersonUpdateByIdController(PersonUpdateByIdController &&) = delete;
		~PersonUpdateByIdController() = default;

		PersonUpdateByIdController(const std::shared_ptr<PersonRepository> &personRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif

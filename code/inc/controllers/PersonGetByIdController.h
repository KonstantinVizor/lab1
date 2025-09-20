#ifndef __PERSONGETBYIDCONTROLLER_H__
#define __PERSONGETBYIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <memory>
#include "../repositories/PersonRepository.h"

class PersonGetByIdController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<PersonRepository> _personRepository;	

	public:
		PersonGetByIdController() = default;
		explicit PersonGetByIdController(const PersonGetByIdController &) = delete;
		PersonGetByIdController(PersonGetByIdController &&) = delete;
		~PersonGetByIdController() = default;

		PersonGetByIdController(const std::shared_ptr<PersonRepository> &personRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif

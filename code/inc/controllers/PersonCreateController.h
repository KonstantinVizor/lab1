#ifndef __PERSONCREATECONTROLLER_H__
#define __PERSONCREATECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <memory>
#include "../repositories/PersonRepository.h"

class PersonCreateController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<PersonRepository> _personRepository;	

	public:
		PersonCreateController() = delete;
		explicit PersonCreateController(const PersonCreateController &) = delete;
		PersonCreateController(PersonCreateController &&) = delete;
		~PersonCreateController() = default;

		PersonCreateController(const std::shared_ptr<PersonRepository> &personRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif

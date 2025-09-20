#ifndef __PERSONGETALLCONTROLLER_H__
#define __PERSONGETALLCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <memory>
#include "../repositories/PersonRepository.h"

class PersonGetAllController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<PersonRepository> _personRepository;	

	public:
		PersonGetAllController() = default;
		explicit PersonGetAllController(const PersonGetAllController &) = delete;
		PersonGetAllController(PersonGetAllController &&) = delete;
		~PersonGetAllController() = default;

		PersonGetAllController(const std::shared_ptr<PersonRepository> &personRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif

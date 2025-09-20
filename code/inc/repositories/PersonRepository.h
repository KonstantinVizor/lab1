#ifndef __PERSONREPOSITORY_H__
#define __PERSONREPOSITORY_H__

#include "../models/PersonModel.h"
#include <Poco/Data/Session.h>
#include <memory>

class PersonRepository
{
	protected:
		using SessionPtr = std::shared_ptr<Poco::Data::Session>;
		using PersonTuple = Poco::Tuple<int32_t, std::string, int32_t, std::string, std::string>;
		using PersonNoIdTuple = Poco::Tuple<std::string, uint32_t, std::string, std::string>;

		SessionPtr _session;

	public:
		PersonRepository() = default;
		explicit PersonRepository(const PersonRepository &) = delete;
		PersonRepository(PersonRepository &&) = delete;
		~PersonRepository() = default;

		virtual PersonRepository& setSession(const SessionPtr &session);

		virtual std::optional<PersonModel> getById(uint32_t id) const;
		virtual std::vector<PersonModel> getAll() const;
		virtual uint32_t create(const PersonModel &model) const;
		virtual const PersonRepository& updateById(uint32_t id, const PersonModel &model) const;
		virtual const PersonRepository& deleteById(uint32_t id) const;
};

#endif

#ifndef __MOCKPERSONREPOSITORY_H__
#define __MOCKPERSONREPOSITORY_H__

#include "../../inc/repositories/PersonRepository.h"

class MockPersonRepository : public PersonRepository
{
	private:
		std::vector<PersonModel> _data;
		PersonModel _singleData;
		uint32_t _id;

	public:
		void setTestData(const std::vector<PersonModel> &data);
		void setTestData(const PersonModel &data);
		void setId(uint32_t id);
		virtual std::vector<PersonModel> getAll() const override;
		virtual std::optional<PersonModel> getById(uint32_t id) const override;
		virtual const PersonRepository& deleteById(uint32_t id) const override;
		virtual uint32_t create(const PersonModel &model) const override;
		virtual const PersonRepository& updateById(uint32_t id, const PersonModel &model) const override;
};

#endif

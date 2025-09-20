#include "MockPersonRepository.h"
#include <optional>

void MockPersonRepository::setTestData(const std::vector<PersonModel> &data)
{
	_data = data;
}

void MockPersonRepository::setTestData(const PersonModel &data)
{
	_singleData = data;
}

void MockPersonRepository::setId(uint32_t id)
{
	_id = id;
}

std::vector<PersonModel> MockPersonRepository::getAll() const
{
	return _data;
}	

std::optional<PersonModel> MockPersonRepository::getById(uint32_t id) const
{
	if (id == _singleData.getId())
		return std::optional(_singleData);
	return {};
}

const PersonRepository& MockPersonRepository::deleteById([[maybe_unused]] uint32_t id) const
{

	return *this;
}

uint32_t MockPersonRepository::create([[maybe_unused]] const PersonModel &model) const
{
	return _id;
}

const PersonRepository& MockPersonRepository::updateById([[maybe_unused]] uint32_t id, [[maybe_unused]] const PersonModel &model) const
{
	if (id == model.getId() && id == _singleData.getId())
		const_cast<PersonModel &>(_singleData) = model;
	return *this;
}

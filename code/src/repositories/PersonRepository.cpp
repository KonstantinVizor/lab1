#include "../../inc/repositories/PersonRepository.h"
#include <Poco/Data/Binding.h>
#include <Poco/Data/Statement.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Tuple.h>
#include <vector>

PersonRepository& PersonRepository::setSession(const SessionPtr &session)
{
	_session = session;
	return *this;
}

std::optional<PersonModel> PersonRepository::getById(uint32_t id) const
{
	std::vector<PersonTuple> person;
	PersonModel result;
	*_session << "SELECt * FROM persons where id = $1", Poco::Data::Keywords::use(id), 
							Poco::Data::Keywords::into(person),
							Poco::Data::Keywords::now;
	if (person.size() == 0)
		return {};
	result.setId(person[0].get<0>())
		.setName(person[0].get<1>())
		.setAge(person[0].get<2>())
		.setWork(person[0].get<3>())
		.setAddress(person[0].get<4>());
	return result;
}

std::vector<PersonModel> PersonRepository::getAll() const
{
	std::vector<PersonTuple> persons;
	std::vector<PersonModel> result;
	*_session << "SELECT id, name, age, work, address FROM persons", Poco::Data::Keywords::into(persons),
									Poco::Data::Keywords::now;
	result = std::vector<PersonModel>(persons.size());
	for (int i = 0; i < static_cast<int>(persons.size()); i++)
	{
		result[i].setId(persons[i].get<0>())
			.setName(persons[i].get<1>())
			.setAge(persons[i].get<2>())
			.setWork(persons[i].get<3>())
			.setAddress(persons[i].get<4>());
	}
	return result;
}

uint32_t PersonRepository::create(const PersonModel &model) const
{
	uint32_t id;
	PersonNoIdTuple tuple;
	tuple = {
		model.getName(),
		model.getAge(),
		model.getWork(),
		model.getAddress()};
	*_session << "INSERT INTO persons(name, age, work, address) VALUES ($1, $2, $3, $4) RETURNING id", Poco::Data::Keywords::use(tuple),
												Poco::Data::Keywords::into(id),
												Poco::Data::Keywords::now;
	return id;
}

const PersonRepository& PersonRepository::updateById(uint32_t id, const PersonModel &model) const
{
	PersonNoIdTuple tuple;
	tuple = {
		model.getName(),
		model.getAge(),
		model.getWork(),
		model.getAddress()};
	*_session << "UPDATE persons SET name = $1, age = $2, work = $3, address = $4 WHERE id = $5", Poco::Data::Keywords::use(tuple.get<0>()),
												Poco::Data::Keywords::use(tuple.get<1>()),
												Poco::Data::Keywords::use(tuple.get<2>()),
												Poco::Data::Keywords::use(tuple.get<3>()),
												Poco::Data::Keywords::use(id),
												Poco::Data::Keywords::now;
	return *this;
}

const PersonRepository& PersonRepository::deleteById(uint32_t id) const
{
	*_session << "DELETE FROM persons WHERE id = $1", Poco::Data::Keywords::use(id),
							Poco::Data::Keywords::now;
	return *this;
}

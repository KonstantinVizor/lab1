#include "../../inc/models/PersonModel.h"
#include "Poco/Dynamic/Var.h"
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <sstream>

PersonModel::PersonModel(const PersonModel &obj) :
					_id(obj._id),
					_name(obj._name),
					_age(obj._age),
					_work(obj._work),
					_address(obj._address)
{}

PersonModel::PersonModel(PersonModel &&obj) :
					_id(obj._id),
					_name(obj._name),
					_age(obj._age),
					_work(obj._work),
					_address(obj._address)
{}

PersonModel& PersonModel::setId(uint32_t id)
{
	_id = id;
	return *this;
}

PersonModel& PersonModel::setName(const std::string &name)
{
	_name = name;
	return *this;
}

PersonModel& PersonModel::setAge(uint32_t age)
{
	_age = age;
	return *this;
}

PersonModel& PersonModel::setWork(const std::string &work)
{
	_work = work;
	return *this;
}

PersonModel& PersonModel::setAddress(const std::string &address)
{
	_address = address;
	return *this;	
}

const uint32_t& PersonModel::getId() const
{
	return _id;
}

const std::string& PersonModel::getName() const
{
	return _name;
}

const uint32_t& PersonModel::getAge() const
{
	return _age;
}

const std::string& PersonModel::getWork() const
{
	return _work;
}

const std::string& PersonModel::getAddress() const
{
	return _address;
}

bool PersonModel::fromJson(const std::string &json, bool all)
{
	Poco::Dynamic::Var var;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr data;
	try
	{
		data = parser.parse(json).extract<Poco::JSON::Object::Ptr>();
	}
	catch (...)
	{
		return false;
	}
	var = data->get("id");
	if (!var.isEmpty())
		try
		{
			_id = std::stoi(var.toString());
		}
		catch (...)
		{
			return false;
		}
	var = data->get("name");
	if (!var.isEmpty())
		_name = var.toString();
	else if (all)
		return false;
	var = data->get("age");
	if (!var.isEmpty())
		try
		{
			_age = std::stoi(var.toString());
		}
		catch (...)
		{
			return false;
		}
	else if (all)
		return false;
	var = data->get("work");
	if (!var.isEmpty())
		_work = var.toString();
	else if (all)
		return false;
	var = data->get("address");
	if (!var.isEmpty())
		_address = var.toString();
	else if (all)
		return false;
	return true;
}

std::string PersonModel::toJson() const
{
	std::ostringstream stream;
	Poco::JSON::Object data;
	data.set("id", _id);
	data.set("name", _name);
	data.set("age", _age);
	data.set("work", _work);
	data.set("address", _address);
	data.stringify(stream);
	return stream.str();
}

bool PersonModel::operator ==(const PersonModel& obj) const
{
	return obj.getId() == _id &&
		obj.getName() == _name &&
		obj.getAge() == _age &&
		obj.getWork() == _work &&
		obj.getAddress() == _address;
}

const PersonModel& PersonModel::operator =(const PersonModel &obj)
{
	_id = obj._id;
	_name = obj._name;
	_age = obj._age;
	_work = obj._work;
	_address = obj._address;
	return *this;
}

/*
#include "../../inc/models/Person.h"
#include "Poco/UUIDGenerator.h"


using namespace std::string_literals;
using namespace Poco::Data::Keywords;


namespace lab_01 {


Person::Person(ID id):
	Poco::ActiveRecord::ActiveRecord<Poco::UUID>(id)
{
}


Person::Person(const Person& other):
	Poco::ActiveRecord::ActiveRecord<Poco::UUID>(other),
	_name(other._name),
	_age(other._age),
	_work(other._work),
	_address(other._address)
{
}


Person::Ptr Person::find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id)
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(pContext->statementPlaceholderProvider());
	Person::Ptr pObject(new Person);

	pContext->session()
		<< "SELECT id, name, age, work, address"
		<< "  FROM person"
		<< "  WHERE id = " << pSPP->next(),
		into(pObject->mutableID()),
		into(*pObject),
		bind(id),
		now;

	return withContext(pObject, pContext);
}


void Person::insert()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	if (id().isNull())
	{
		mutableID() = Poco::UUIDGenerator().createRandom();
	}

	context()->session()
		<< "INSERT INTO person (id, name, age, work, address)"
		<< "  VALUES (" << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ")",
		bind(id()),
		use(*this),
		now;
}


void Person::update()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "UPDATE person"
		<< "  SET name = " << pSPP->next() << ", age = " << pSPP->next() << ", work = " << pSPP->next() << ", address = " << pSPP->next()
		<< "  WHERE id = " << pSPP->next(),
		use(*this),
		bind(id()),
		now;
}


void Person::remove()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "DELETE FROM person"
		<< "  WHERE id = " << pSPP->next(),
		bind(id()),
		now;
}


const std::vector<std::string>& Person::columns()
{
	static const std::vector<std::string> cols =
	{
		"id"s,
		"name"s,
		"age"s,
		"work"s,
		"address"s,
	};

	return cols;
}


const std::string& Person::table()
{
	static const std::string t = "person";
	return t;
}


} // namespace lab_01
 */

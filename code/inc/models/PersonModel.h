#ifndef __PERSONMODEL_H__
#define __PERSONMODEL_H__

#include <Poco/UUID.h>
#include <string>
class PersonModel
{
	private:
		uint32_t _id;
		std::string _name;
		uint32_t _age;
		std::string _work;
		std::string _address;

	public:
		PersonModel() = default;
		~PersonModel() = default;
		explicit PersonModel(const PersonModel &obj);
		PersonModel(PersonModel &&obj);

		PersonModel& setId(uint32_t id);
		PersonModel& setName(const std::string &name);
		PersonModel& setAge(uint32_t age);
		PersonModel& setWork(const std::string &work);
		PersonModel& setAddress(const std::string &address);

		const uint32_t& getId() const;
		const std::string& getName() const;
		const uint32_t& getAge() const;
		const std::string& getWork() const;
		const std::string& getAddress() const;

		bool fromJson(const std::string &json, bool all = false);
		std::string toJson() const;

		const PersonModel& operator =(const PersonModel &obj);
		bool operator ==(const PersonModel& obj) const;
};

#endif

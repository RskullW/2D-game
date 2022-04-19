#include "ObjectFactory.h"

ObjectFactory* ObjectFactory::s_Instance = nullptr;

void ObjectFactory::RegisterType(std::string className, std::function<GameObject* (Properties* props) > type)
{
	m_TypeReg[className] = type;
}

GameObject* ObjectFactory::CreateObject(std::string type, Properties* props)
{
	GameObject* object = nullptr;

	auto it = m_TypeReg.find(type);

	if (it != m_TypeReg.end())
	{
		object = it->second(props);
	}

	return object;
}
#pragma once

#include <string>
#include <memory>
#include <map>
#include <functional>
#include "GameObject.h"

class ObjectFactory
{
public:
	static ObjectFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectFactory; }
	GameObject* CreateObject(std::string type, Properties* props);
	void RegisterType(std::string className, std::function <GameObject* (Properties* props) > type);

private:
	ObjectFactory() {}
	static ObjectFactory* s_Instance;
	std::map<std::string, std::function<GameObject* (Properties* props)> > m_TypeReg;
};



template <class Type>
class Registrar
{
public:
	Registrar(std::string className)
	{
		ObjectFactory::GetInstance()->RegisterType(className, [](Properties* props)->GameObject* { return new Type(props); });
	}
};
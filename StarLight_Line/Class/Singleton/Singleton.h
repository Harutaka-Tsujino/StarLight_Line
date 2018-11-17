#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

//#include "../../GameLib/GameLib.h"

template <class T>
class Singleton
{
public:
	Singleton() {};
	~Singleton() {};

	inline static T& GetInstance()
	{
		static std::unique_ptr<T> ptr(new T());

		return *ptr;
	}
};

#endif // !SINGLETON_H

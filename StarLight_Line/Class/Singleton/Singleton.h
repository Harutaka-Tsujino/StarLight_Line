#ifndef SINGLETON_H
#define SINGLETON_H
#include <windows.h>
#include <memory>

template <class T>
class Singleton
{
public:

protected:
	Singleton() {};
	~Singleton() {};

private:
	std::unique_ptr<T> ptr;

}

#endif // !SINGLETON_H

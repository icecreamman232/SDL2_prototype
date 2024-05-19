#pragma once
template <typename T> class Singleton
{
public:
	static T& GetInstance();
	Singleton(const Singleton&) = delete;
	Singleton& operator=(cosnt Singleton&) = delete;
protected:
	Singleton() {};
	virtual ~Singleton() {}
};



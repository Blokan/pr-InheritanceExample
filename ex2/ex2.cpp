// ex2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

// класс, описывающий существо
class creature
{
private:
	string title;
	double mass; //kg
protected:
	creature() : mass(0.0) {}
	creature(const creature& obj) : title(obj.title), mass(obj.mass) {}
	creature(const string& _title, double _mass) : title(_title), mass(_mass) {}
	// деструктор (объявлен как виртуальный)
	virtual ~creature() { cout << "creature deleted\n"<< endl; }
	// виртуальная функция для вывода информации об объекте
	virtual void _print() const { cout << "title: "<<title << ", mass: "<<  mass; }
public:

	// открытая функция для вывода информации об объекте
	void print() const
	{
		cout <<typeid(*this).name() << ": ("; // вызов виртуальной функции, т.к. функция _print виртуальная, вызываться она будет не только из текущего класса, но и из производных, в зависимости от того, для какого объекта осуществляется вызов
		_print();
		cout << ")" << endl;
	}
	double get_mass() const
	{
		return mass;
	}
};
// класс animal наследуется от класса creature
class animal : public creature
{
private:
	double speed; //m/s
public:
	animal() : creature() {}
	animal(const animal& obj) : creature(obj), speed(obj.speed) {}
	animal(const string& _title, double _mass, double _speed)
		: creature(_title, _mass), speed(_speed) {}
	~animal() { cout << "animal deleted" << endl; }
protected:
	// виртуальная функция _print переопределяется в производном //классе
	void _print() const
	{
		creature::_print();
		cout <<", speed: " << speed;
	}
public:
	double get_speed() const
	{
		return speed;
	}
};
// класс predator наследуется от animal
class predator : public animal
{
protected:
	predator() {}
public:
	~predator() {}
	// чисто виртуальная функция hunt будет определять
	// посредством производных классов,
	// удастся ли хищнику поохотиться на жертву (obj)
	virtual bool hunt(const animal& obj) = 0;
	// т.к. hunt чисто виртуальная, класс predator является абстрактным
};
// класс bird наследуется от класса animal
class bird : public animal
{
private:
	double topfly; //km
public:
	bird() : animal() {}
	bird(const bird& obj) : animal(obj), topfly(obj.topfly) {}
	bird(const string& _title, double _mass, double _speed, double _topfly)
		: animal(_title, _mass, _speed), topfly(_topfly) {}
	~bird() { cout << "bird deleted" << endl; }
protected:
	// виртуальная функция _print переопределяется в классе bird
	void _print() const
	{
		animal::_print();
		cout << ", topfly: " << topfly;
	}
};
// класс fish наследуется от класса animal
class fish : public animal
{
private:
	double maxdeep; //km
public:
	fish() : animal() {}
	fish(const fish& obj) : animal(obj), maxdeep(obj.maxdeep) {}
	fish(const string& _title, double _mass, double _speed, double _maxdeep)
		: animal(_title, _mass, _speed), maxdeep(_maxdeep) {}
	~fish() { cout << "fish deleted"<<endl; }

protected:
	// виртуальная функция _print переопределяется в классе fish
	void _print() const
	{
		animal::_print();
		cout << ", maxdeep: " << maxdeep;
	}
};
// используется множественное наследование, т.к. орел – и птица, и хищник
class eagle : public bird, public predator
{
public:
	eagle() : bird() {}
	eagle(const eagle& obj) : bird(obj) {}
	eagle(double _mass, double _speed, double _topfly) : bird("Орел", _mass, _speed, _topfly) {}
	// определение тела функции hunt, т.к. hunt определена, класс eagle – НЕабстракный
	bool hunt(const animal& obj)
	{
		// функция get_mass может наследоваться классом eagle из класса animal
		// и через класс bird, и через класс predator
		// нужно указать, что она наследуется через bird
		return obj.get_mass() < bird::get_mass() && obj.get_speed() < bird::get_speed();

	}
};
int main()
{
	setlocale(0, "Rus");
	// создание объектов и вывод информации о них
	animal("Паук", 0.003, 0.05).print();
	bird("Ворона" , 0.3, 10, 0.1).print();
	fish("Рыба-молот", 150, 5, 0.5).print();
	cout << endl;
	return 0;
}
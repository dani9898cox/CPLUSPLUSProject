#pragma once

//clasas abstracta cu metoda update care necesita 
//sa fie implementata de observere
class Observer {

public:

	virtual void update()=0;

};

//subiectu observabilu - classa care notifica schimbarile 

#include <vector>
#include <algorithm>

class Observable 
{

private:
	std::vector<Observer*> observers;

public:

	//functie care adauga un observer
	void addObserver(Observer* obs)
	{
		observers.push_back(obs);
	}

	//functie care sterge un observer
	void removeObserver(Observer* obs)
	{
		observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
	}

	//functie care da update la obseervere
	void notify()
	{
		for (auto obs : observers)
		{
			obs->update();
		}
	}

};

#pragma once
#define _CRTDBG_MAP_ALLOC
#include <string>
#include <crtdbg.h>

using std::string;

//clasa masina
//are param:
//@1: nrdeinmatriculare
//@2: producator
//@3: model
//@4 tip
//toate stringuri
class Masina {
	std::string nrinmatriculare;
	std::string producator;
	std::string model;
	std::string tip;

public:
	//constructoru e default sau custom:)
	Masina() = default;
	Masina(const string nr, const string pr, const string m, const string tip) :nrinmatriculare{ nr }, producator{ pr }, model{ m }, tip{ tip }{}

	//functie care returneaza nr de inmatriculare al unei masini
	string getnrinm() const {
		return nrinmatriculare;
	}

	//functie care returneaza producatorul unei masini
	string getprod() const {
		return producator;
	}

	//functie care returneaza modelul unei masini
	string getmodel() const {
		return model;
	}


	string gettip() const {
		return tip;
	}

	string tostring() const {
		return nrinmatriculare + " " + producator + " " + model + " " + tip;
	}
};

void test_masina();
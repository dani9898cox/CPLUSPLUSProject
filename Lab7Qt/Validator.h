#pragma once
#include "Masina.h"
#include <string>
#include <vector>


using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	vector<string> msgs;
public:
	ValidateException(const vector<string>& errors) : msgs{ errors } {}
	
	string getErrorVali()
	{
		string msg = "";
		for (const string st : msgs)
		{
			msg += st + "\n";
		}
		return msg;
	}

	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);
class Validator {

public:
	//functie cate valideaza o masinuta
	void validare(const Masina& m);
};
void test_validator();
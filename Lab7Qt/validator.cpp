#pragma once
#include "validator.h"
#include "Masina.h"
#include <sstream>
#include <assert.h>

void Validator::validare(const Masina& m)
{
	vector<string> msgs;
	if (m.getmodel().size() == 0)
		msgs.push_back("Model invalid!");
	if (m.getnrinm().size() == 0)
		msgs.push_back("Numar de inmatriculare invalid!");
	if (m.getprod().size() == 0)
		msgs.push_back("Producator invalid!");
	if (m.gettip().size() == 0)
		msgs.push_back("Tip invalid!");
	if (msgs.size() > 0)
		throw  ValidateException(msgs);
}

ostream& operator<<(ostream& out, const ValidateException& ex)
{
	for (const auto& msg : ex.msgs)
	{
		out << msg << " ";
	}
	return out;
}

void test_validator()
{
	Validator v;
	Masina m{ "","","","" };
	try
	{
		v.validare(m);
		assert(false);
	}
	catch (const ValidateException& ex)
	{
		std::stringstream sout;
		sout << ex;
		auto mesaj = sout.str();
		assert(mesaj.find("invalid") >= 0);
	}
}
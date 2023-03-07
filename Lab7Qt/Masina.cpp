#pragma once
#include <assert.h>
#include "Masina.h"

void test_masina()
{
	Masina m{ "MS69EDI","ford","mondeo","sedan" };
	assert(m.getmodel() == "mondeo");
	assert(m.getnrinm() == "MS69EDI");
	assert(m.getprod() == "ford");
	assert(m.gettip() == "sedan");
	assert(m.tostring() == "MS69EDI ford mondeo sedan");
}
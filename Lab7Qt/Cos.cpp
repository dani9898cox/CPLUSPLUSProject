#pragma once
#include "Cos.h"
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

void Cos::addcos(const string nrinm)
{
	Masina m = repo.cauta(nrinm);
	this->cos.push_back(m);
	this->dim++;
}

ostream& operator<<(ostream& out, const CosException& ex) {
	out << ex.msg;
	return out;
}
void Cos::generatecos(const int nr)
{
	vector<Masina> sufle = repo.getall();
	if (sufle.size() < nr)
		throw CosException("Nu exista suficiente masini, introdu un nr mai mic");
	else
	{
		int seed = 69; //std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(sufle.begin(), sufle.end(), std::default_random_engine(seed)); //amesteca vectorul v
		for (auto el : sufle)
		{
			if (this->dim == nr)
				break;
			this->cos.push_back(el);
			this->dim++;

		}

	}
}
vector<Masina> Cos::get_all_cos()
{
	return this->cos;
}
void Cos::clearcos()
{
	this->cos.clear();
	this->dim = 0;
}

void Cos::exportcos(const string expfile)
{
	std::ofstream fout(expfile);
	for (auto el : this->cos)
	{
		fout << el.tostring() << std::endl;

	}
	fout.close();
}
const int Cos::getdim()
{
	return this->dim;
}

void test_cos()
{
	MasinaRepo repo;
	Cos cosulet{ repo };
	assert(cosulet.getdim() == 0);
	repo.adauga(Masina{ "a","a","a","a" });
	repo.adauga(Masina{ "b","a","a","a" });
	repo.adauga(Masina{ "c","a","a","a" });
	repo.adauga(Masina{ "d","a","a","a" });
	repo.adauga(Masina{ "e","a","a","a" });
	cosulet.addcos("a");
	cosulet.addcos("b");
	cosulet.addcos("c");
	cosulet.addcos("d");
	cosulet.addcos("e");
	assert(cosulet.getdim() == 5);
	try
	{
		cosulet.addcos("w");
	}
	catch (RepoException&)
	{
		assert(true);
	}
	cosulet.clearcos();
	assert(cosulet.getdim() == 0);
	try
	{
		cosulet.generatecos(69);
		assert(false);
	}
	catch (CosException&)
	{
		assert(true);
	}
	cosulet.generatecos(4);
	assert(cosulet.getdim() == 4);

}
#pragma once
#include <assert.h>
#include <iostream>
#include <sstream>
#include "MasinaRepo.h"

using std::ostream;
using std::stringstream;

void MasinaRepo::adauga(const Masina& m)
{
	if (exist(m))
	{
		throw RepoException("Exista deja masina cu acest nr de inmatriculare!");

	}
	all.push_back(m);
}

void MasinaRepo::sterge(const Masina& m)
{
	if (!exist(m))
		throw RepoException("Masina nu exista");
	else
	{
		int i = 0;
		for (const auto el : all)
			if (el.getnrinm() == m.getnrinm())
				break;
			else i++;
		all.erase(all.begin() + i);
	}

}
void MasinaRepo::setelem(const Masina& m1, const Masina& m2)
{
	if (!exist(m1))
		throw RepoException("Masina nu exista");
	else
	{
		int i = 0;
		for (const auto el : all)
			if (el.getnrinm() == m1.getnrinm())
				break;
			else i++;
		all.erase(all.begin() + i);
		all.insert(all.begin() + i, m2);
	}
}

bool MasinaRepo::exist(const Masina& m) {
	try
	{
		cauta(m.getnrinm());
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}

const Masina& MasinaRepo::cauta(string nrinm) {
	for (const Masina& m : this->all)
	{
		if (m.getnrinm() == nrinm)
			return m;
	}
	throw RepoException("Nu exista masina cu nr asta de inmatriculare");
}

const vector<Masina>& MasinaRepo::getall() {
	return all;
}

ostream& operator<<(ostream& out, const RepoException& ex) {
	out << ex.msg;
	return out;
}

void MasinaRepoFile::loadfromfile()
{
	std::ifstream fin(this->filename);
	if (!fin.is_open())
		throw RepoException("Nu sa putut citi din fisier " + filename);

	string nrinm, prod, model, tip;
	string item;
	int itemnr = 0;
	while (fin >> item)
	{
		if (itemnr == 0)
		{
			nrinm = item;
		}
		if (itemnr == 1)
		{
			prod = item;
		}
		if (itemnr == 2)
		{
			model = item;
		}
		if (itemnr == 3)
		{
			tip = item;
		}
		itemnr++;
		if (itemnr == 4)
		{
			itemnr = 0;
			Masina m{ nrinm,prod,model,tip };
			MasinaRepo::adauga(m);
		}
	}
	fin.close();

}

void MasinaRepoFile::savetofile()
{
	std::ofstream fout(this->filename);
	if (!fout.is_open())
		throw RepoException("Nu sa putut scrie in fisier " + filename);
	for (auto& m : getall())
	{
		fout << m.tostring() << std::endl;
	}
	fout.close();
}

void MasinaRepoFile::adauga(const Masina& m)
{
	MasinaRepo::adauga(m);
	savetofile();
}

void MasinaRepoFile::sterge(const Masina& m)
{
	MasinaRepo::sterge(m);
	savetofile();
}

void MasinaRepoFile::setelem(const Masina& m1, const Masina& m2)
{
	MasinaRepo::setelem(m1, m2);
	savetofile();
}
void test_adauga()
{
	MasinaRepo repo;
	assert(repo.getall().size() == 0);
	repo.adauga(Masina{ "MS69EDI","ford","mondeo","sedan" });
	assert(repo.getall().size() == 1);

	try {
		repo.adauga(Masina{ "MS69EDI","ford","mondeo","sedan" });
		assert(false);
	}
	catch (const RepoException&)
	{
		assert(true);
	}
}

void test_cauta()
{
	MasinaRepo repo;
	assert(repo.getall().size() == 0);
	repo.adauga(Masina{ "MS69EDI","ford","mondeo","sedan" });

	Masina m = repo.cauta("MS69EDI");
	assert(m.getmodel() == "mondeo");
	try {
		repo.cauta("asfdas");
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
}
void test_sterge()
{
	MasinaRepo repo;
	assert(repo.getall().size() == 0);
	Masina m("MS69EDI", "ford", "mondeo", "sedan");
	repo.adauga(m);
	repo.adauga({ "da","asd","asd","Sdf" });
	assert(repo.getall().size() == 2);
	repo.sterge(m);
	assert(repo.getall().size() == 1);
	Masina r("ca", "dfh", "fgh", "dsfg");
	try
	{
		repo.sterge(r);
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
}
void test_modifica()
{
	MasinaRepo repo;
	assert(repo.getall().size() == 0);
	Masina m("MS69EDI", "ford", "mondeo", "sedan");
	repo.adauga(m);
	repo.adauga({ "da","asd","asd","Sdf" });
	Masina m2("MS69EDI", "cox", "cox", "cox");
	Masina m3("asd", "dg", "dfg", "dfg");
	repo.setelem(m, m2);
	try
	{
		repo.setelem(m3, m2);
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
	vector<Masina> da = repo.getall();
	assert(da[0].getmodel() == "cox");
}

void test_filrepo()
{

	std::ofstream fout;
	fout.open("fisier_test.txt", std::ofstream::out | std::ofstream::trunc);
	fout << "MS23EDI cevamarca cevamodel sedan\n";
	fout << "MS45COX TOYOTA CELLICA sedan\n";
	fout << "CONSTANTA efectiv fain design\n";

	fout.close();
	try {
		MasinaRepoFile testRepoF{ "fisier_test2.txt" };
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	MasinaRepoFile testRepoF{ "fisier_test.txt" };
	assert(testRepoF.getall().size() == 3);


	Masina m{ "a", "a", "a","a" };

	testRepoF.adauga(m);
	assert(testRepoF.getall().size() == 4);
	testRepoF.sterge(m);
	assert(testRepoF.getall().size() == 3);
	try
	{
		testRepoF.sterge(m);
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}

	Masina m2{ "b","b","b","b" };
	try
	{
		testRepoF.setelem(m, m2);
		assert(false);
	}
	catch (RepoException&)
	{
		assert(true);
	}
	testRepoF.adauga(m);
	testRepoF.setelem(m, m2);
	Masina m3 = testRepoF.cauta("b");
	assert(m3.getmodel() == "b");


}

void test_repo()
{
	test_adauga();
	test_cauta();
	test_sterge();
	test_modifica();

}
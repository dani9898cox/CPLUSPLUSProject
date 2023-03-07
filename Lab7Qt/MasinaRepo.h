#pragma once
#include "Masina.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <vector>
#include <string>
#include <ostream>
#include <fstream>

using std::vector;
using std::string;
using std::ostream;

class MasinaRepo {
	vector<Masina> all;

	bool exist(const Masina& m);

public:
	/*
	Facem constructoru sa fie default
	*/
	MasinaRepo() = default;
	/*
	Blocam copierea de masini
	*/
	MasinaRepo(const MasinaRepo& ot) = delete;

	/*
	Adauga masina
	aarunca exceptie daca masina e deja aici
	*/
	virtual void adauga(const Masina& m);

	/*
	* Cauta
	* arunca exceptie daca nu exista masina cu acelasi nr de inmatriculare
	*/
	const Masina& cauta(string nrinmatriculare);

	/*
	* returneaza toate masinile salvate
	*/
	const vector<Masina>& getall();

	//stege o masina din repou asta minunat de masini
	virtual void sterge(const Masina& m);
	//seteaza un element pe pozitia altui element frumos
	virtual void setelem(const Masina& m1, const Masina& m2);
};

//clasa de exceptii din repository
class RepoException {
	string msg;
public:
	RepoException(string m) :msg{ m } {}

	string getErrorRepo()
	{
		return this->msg;
	}

	friend ostream& operator<<(ostream& out, const RepoException& ex);
};
ostream& operator<<(ostream& out, const RepoException& ex);

class MasinaRepoFile : public MasinaRepo {

private:
	string filename;

	//functie care incarca datele din fisier
	void loadfromfile();

	//functie care salveaza datele in fisier
	void savetofile();

public:
	MasinaRepoFile(string filename) : MasinaRepo(), filename{ filename } {
		loadfromfile();
	};

	void adauga(const Masina& m) override;

	void sterge(const Masina& m) override;

	void setelem(const Masina& m1, const Masina& m2) override;

};

void test_repo();
void test_filrepo();
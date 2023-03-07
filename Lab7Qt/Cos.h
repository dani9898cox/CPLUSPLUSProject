
#pragma once
#include <vector>
#include <fstream>
#include <ostream>
#include <string>
#include "Masina.h"
#include "MasinaRepo.h"
#include "Observer.h"

using std::ostream;
using std::string;
using std::vector;
class Cos : public Observable
{
private:
	vector<Masina> cos;
	MasinaRepo& repo;
	int dim = 0;


public:
	//constructor default
	Cos(MasinaRepo& repo) : repo{ repo } {}

	//stergem copycontructoru
	Cos(const Cos& ot) = delete;

	//functie de adaugat o masina in lista pe baza nr de inmatricultare
	//arunca exceptie daca nu exsita masina in repo
	void addcos(const string nrinm);

	//functie care genereaza lista de masini 
	//arunca exceptie dadca nu sunt destule masini pt a genera lista cu nr dat
	void generatecos(const int nr);

	//functie care goleste cosul de masini
	void clearcos();

	//functie care salveaza in fisier cosul
	//arunca exceptie daca fisierul nu  evalid
	void exportcos(const string expfile);

	//returnam dimensiune cosului
	const int getdim();

	vector<Masina> get_all_cos();
};

//clasa de exceptii pentru cos
class CosException {
	string msg;
public:
	CosException(string m) :msg{ m } {}

	friend ostream& operator<<(ostream& out, const CosException& ex);
};
ostream& operator<<(ostream& out, const CosException& ex);

void test_cos();
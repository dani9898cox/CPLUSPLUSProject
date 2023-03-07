#pragma once
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "MasinaRepo.h"
#include <assert.h>
#include <vector>
#include <string>
#include "Validator.h"
#include "undo.h"
#include <memory>

using std::vector;
using std::string;
using std::unique_ptr;

typedef bool(CompareFct)(Masina el1, Masina el2);

//clasa service care gestioneaza masinutele
//parametri:
//@1 repo de masini
//@2 validatorul de masini
class MasinaStore {
	MasinaRepo& repo;
	Validator& vali;

	vector<unique_ptr<ActiuneUndo>> undoactions;

public:
	//constructor custom de masini
	MasinaStore(MasinaRepo& repo, Validator& vali) :repo{ repo }, vali{ vali }{}

	//copy constructorul e sters, nu dorim sa copiem serviceuri
	MasinaStore(const MasinaStore& ot) = delete;

	//functie care returneaza toate mainilie
	const vector<Masina>& getAll() noexcept {
		return repo.getall();
	}

	//functie care creeaza o masina, o valideaza si o adauga in repo si adauga la lista de actiuniundo ultima operatie
	//parametri:
	//@1: nrdeinmatriculare
	//@2: producator
	//@3: model
	//@4: tip
	//arunca exceptie daca masina nu e valida
	void addmasina(const string& nrinmatriculare, const string& producator, const string& model, const string& tip);

	//funcite care sterge o masina din repo dupa nr de inmatriculare
	//parametri:
	//@1: nrdeinmatriculare
	//arunca exceptie daca masina nu se gaseste in repo
	void stergemasina(const string& nrinmatriculare);

	//functie care modifica o masina
	//da
	void modmasina(const string& nrinmatriculare, const string& producatornou, const string& modelnou, const string& tipnou);

	//funcite care returneaza o lista de masini filtrate dupa un anumit criteriu
	//parametri:
	//@1:criteriul
	//@2: nr - int
	vector<Masina> filtraremasini(const string& criteriu, const int nr);

	//funcite de sortasre care returneeaza o lista de masini sortate cresc sau descresc dupa un criteriu
	vector<Masina> sortaremasina(CompareFct cmp, const string direction);

	//functie face undo la ultima operatie efectuata pe repo
	void undo();

	bool checkprod(string prod);
};
//functii de comparare
bool cmpnrinm(const Masina m1, const Masina m2);
bool cmptip(const Masina m1, const Masina m2);
bool cmpprod_model(const Masina m1, const Masina m2);

//funcita de test pt service
void test_service();
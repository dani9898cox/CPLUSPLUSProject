#pragma once
#include "MasinaSrv.h"
#include <iostream>
#include <algorithm>

void MasinaStore::addmasina(const string& nrinmatriculare, const string& producator, const string& model, const string& tip) {
	Masina m(nrinmatriculare, producator, model, tip);
	vali.validare(m);
	repo.adauga(m);
	this->undoactions.push_back(std::make_unique<UndoAdauga>(repo, m));
}

void MasinaStore::stergemasina(const string& nrinmatriculare)
{
	Masina m = repo.cauta(nrinmatriculare);
	repo.sterge(m);
	this->undoactions.push_back(std::make_unique<UndoStergere>(repo, m));
}

void MasinaStore::modmasina(const string& nrinmatriculare, const string& producatornou, const string& modelnou, const string& tipnou)
{
	Masina m2(nrinmatriculare, producatornou, modelnou, tipnou);
	vali.validare(m2);
	Masina m1 = repo.cauta(nrinmatriculare);
	repo.setelem(m1, m2);
	this->undoactions.push_back(std::make_unique<UndoModifica>(repo, m1, m2));
}

void MasinaStore::undo()
{
	if (this->undoactions.empty()) {
		throw RepoException{ "Nu avem ce da undo!\n" };
	}
	undoactions.back()->doundo();
	undoactions.pop_back();
}

vector<Masina> MasinaStore::filtraremasini(const string& criteriu, const int nr)
{
	vector<Masina> all = repo.getall();
	
		vector<Masina> filtrat;

	for (const auto el : all)
	{
		if (nr == 1)
		{
			if (el.getprod() == criteriu)
				filtrat.push_back(el);
		}
		else if (nr == 2)
			if (el.gettip() == criteriu)
				filtrat.push_back(el);
	}
	return filtrat;
}
bool cmpnrinm(const Masina m1, const Masina m2)
{
	return m1.getnrinm() > m2.getnrinm();
}
bool cmptip(const Masina m1, const Masina m2)
{
	return m1.gettip() > m2.gettip();
}
bool cmpprod_model(const Masina m1, const Masina m2)
{
	//if (m1.getprod() > m2.getprod())
	//	return true;
	//else if (m1.getprod() < m2.getprod())
	//	return false;
	//else if (m1.getprod() == m2.getprod())
	//{
	//	if (m1.getmodel() > m2.getmodel())
	//		return true;
	//	else if ((m1.getmodel() <= m2.getmodel()))
	//		return false;
	//}
	if (m1.getprod() != m2.getprod())
		return m1.getprod() > m2.getprod();
	else return m1.getmodel() > m2.getmodel();
}
vector<Masina> MasinaStore::sortaremasina(CompareFct cmp, const string direction)
{
	vector<Masina> all = repo.getall();
	int i, j;
	for (i = 0; i < all.size(); i++)
		for (j = 0; j < all.size(); j++)
			if ((cmp(all[i], all[j]) != true and direction == "ascending") or (cmp(all[i], all[j]) == true and direction == "descending"))
			{
				std::cout << "da";
				Masina m1 = all[i];
				Masina m2 = all[j];
				//all.insert(all.begin() + j, m1);
				//all.insert(all.begin() + i, m2);
				all[i] = m2;
				all[j] = m1;
			}
	return all;
}
bool MasinaStore::checkprod(string prod)
{
	vector<Masina> all = getAll();
	if (std::all_of(all.cbegin(), all.cend(), [prod](Masina el) {
		if (el.getprod() == prod)
			return true;
		}))
	{
		return true ;
	}
	return false ;
}
void test_service() {
	MasinaRepo repo;
	Validator vali;
	MasinaStore store{ repo,vali };

	store.addmasina("a", "a", "a", "a");
	store.addmasina("b", "a", "a", "a");
	store.addmasina("c", "c", "c", "c");
	store.addmasina("d", "d", "d", "d");
	store.addmasina("e", "e", "e", "e");
	store.addmasina("f", "e", "e", "e");
	store.addmasina("g", "e", "e", "e");

	assert(store.getAll().size() == 7);
	store.stergemasina("b");
	assert(store.getAll().size() == 6);
	store.modmasina("a", "x", "x", "x");
	vector<Masina> da = store.getAll();
	assert(da[0].getmodel() == "x");
	store.modmasina("a", "a", "a", "a");
	store.addmasina("b", "a", "a", "a");

	vector<Masina> cox = store.filtraremasini("a", 1);
	assert(cox.size() == 2);
	cox = store.filtraremasini("e", 2);
	assert(cox.size() == 3);

	store.modmasina("b", "b", "b", "b");
	vector<Masina> sorted = store.sortaremasina(cmpnrinm, "ascending");
	assert(sorted[0].getnrinm() == "a");
	sorted = store.sortaremasina(cmpnrinm, "descending");
	assert(sorted[0].getnrinm() == "g");

	sorted = store.sortaremasina(cmptip, "ascending");
	assert(sorted[0].getnrinm() == "a");
	sorted = store.sortaremasina(cmptip, "descending");
	assert(sorted[0].getnrinm() == "e");

	sorted = store.sortaremasina(cmpprod_model, "ascending");
	assert(sorted[0].getnrinm() == "a");
	sorted = store.sortaremasina(cmpprod_model, "descending");
	assert(sorted[0].getnrinm() == "e");

	store.stergemasina("a");
	assert(store.getAll().size() == 6);
	store.undo();
	assert(store.getAll().size() == 7);

	store.addmasina("x", "x", "x", "x");
	assert(store.getAll().size() == 8);

	store.undo();
	assert(store.getAll().size() == 7);

	store.modmasina("a", "x", "x", "x");
	sorted = store.sortaremasina(cmpnrinm, "ascending");
	assert(sorted[0].getmodel() == "x");
	store.undo();
	sorted = store.sortaremasina(cmpnrinm, "ascending");
	assert(sorted[0].getmodel() == "a");

	assert(store.checkprod("a") == true);

}
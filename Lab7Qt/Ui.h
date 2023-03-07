#pragma once
#include "Masina.h"
#include "MasinaSrv.h"
#include "Cos.h"

//aici refuz sa pun specificatii
class CUi {
	MasinaStore& store;
	Cos& cos;
	void adaugaUI();
	void tipareste(const vector<Masina>& masini);
	void stergeUI();
	void modificaUI();
	void printUI();
	void filtrareUI();
	void sortareUI();
	void addcosUI();
	void clearcosUI();
	void gencosUI();
	void exportcosUI();
	void undoUI();

public:

	CUi(MasinaStore& store, Cos& cos) :store{ store }, cos{ cos } {}
	//nu permitem copierea obiectelor
	CUi(const CUi& ot) = delete;
	void run_app();
};
#pragma once
#include "Masina.h"
#include "MasinaRepo.h"

//clasa care are o singura functie,doundo
class ActiuneUndo {
public:
	//functie care faceundo
	virtual void doundo() = 0;
	virtual ~ActiuneUndo() = default;

};

//clasa care mosteneste din clasa undo
//se ocupa cu undo de la adauga
//parametri:
//@1: repo - un repo de masinute
//@2 m - masina pe care o adaugam ultima data in repo
class UndoAdauga : public ActiuneUndo {

private:
	Masina m;
	MasinaRepo& rep;

public:
	UndoAdauga(MasinaRepo& rep, Masina m) :rep{ rep }, m{ m } {}
	void doundo() override {
		rep.sterge(m);
	}
};

//clasa care mosteneste din clasa undo
//se ocupa cu undo de la stergere
//parametri:
//@1: repo - un repo de masinute
//@2 m - masina pe care o stergem ultima data din repo
class UndoStergere : public ActiuneUndo {

private:
	Masina m;
	MasinaRepo& rep;

public:
	UndoStergere(MasinaRepo& rep, Masina m) :rep{ rep }, m{ m } {}
	void doundo() override {
		rep.adauga(m);
	}
};

//clasa care mosteneste din clasa undo
//se ocupa cu undo de la modificare
//parametri:
//@1: repo - un repo de masinute
//@2 m1 - masina pe care o modificam ultima data in repo
//@3 m2 - masina in locul careia am pus masina modificata
class UndoModifica : public ActiuneUndo {

private:
	Masina m1, m2;
	MasinaRepo& rep;

public:
	UndoModifica(MasinaRepo& rep, Masina m1, Masina m2) :rep{ rep }, m1{ m1 }, m2{ m2 } {}
	void doundo() override {
		rep.setelem(m2, m1);
	}
};

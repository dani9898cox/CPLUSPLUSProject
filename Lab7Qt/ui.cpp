#pragma once
#include "Ui.h"
#include "Masina.h"
#include <string>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void CUi::adaugaUI()
{
	string nrmatricol, producator, model, tip;
	cout << "adaugare masina " << endl;
	cout << "Nr matricol:" << endl;
	cin >> nrmatricol;
	cout << "Producatoe :" << endl;
	cin >> producator;
	cout << "Model" << endl;
	cin >> model;
	cout << "Tip:" << endl;
	cin >> tip;
	try {
		store.addmasina(nrmatricol, producator, model, tip);
		cout << "Adaugat cu suuces masina " << endl;
	}
	catch (RepoException& re)
	{
		cout << re;
	}
	catch (ValidateException& ve)
	{
		cout << ve;
	}
}

void CUi::stergeUI()
{
	cout << "Stergere masina " << endl;
	string nrmatricol;
	cin >> nrmatricol;
	try {
		store.stergemasina(nrmatricol);
		cout << "Masina stearsa cu suuces" << endl;
	}
	catch (RepoException& re)
	{
		cout << re;
	}
}

void CUi::modificaUI()
{
	string nrmatricol, producatornou, modelnou, tipnou;
	cout << "modificare masina " << endl;
	cout << "Nr matricol:" << endl;
	cin >> nrmatricol;
	cout << "Producatoe nou :" << endl;
	cin >> producatornou;
	cout << "Model nou" << endl;
	cin >> modelnou;
	cout << "Tip nou:" << endl;
	cin >> tipnou;
	try {
		store.modmasina(nrmatricol, producatornou, modelnou, tipnou);
		cout << "Masina modificata cu succes" << endl;
	}
	catch (RepoException& re)
	{
		cout << re;
	}
	catch (ValidateException& ve)
	{
		cout << ve;
	}

}

void CUi::printUI()
{
	cout << "Numere inmatriculare masini : " << endl;
	vector<Masina> repo = store.getAll();
	for (const Masina& el : repo) {
		cout << el.getnrinm() << " " << el.getmodel() << " " << el.getprod() << " " << el.gettip() << endl;
	}
}

void CUi::filtrareUI()
{
	cout << "Filtrare elemente\n";
	cout << "Alege criteriu\n";
	cout << "1. producator  ||  2. tip\n";
	int nr;
	cin >> nr;
	cout << "introdu criteriu\n";
	string criteriu;
	cin >> criteriu;
	vector<Masina> fil = store.filtraremasini(criteriu, nr);
	for (const auto el : fil)
	{
		cout << el.getnrinm() << " " << el.getmodel() << " " << el.getprod() << " " << el.gettip() << endl;
	}
}

void CUi::sortareUI()
{
	cout << "Sortare masini" << endl;

	string direction;
	cout << "Introdu directia ascending/descending" << endl;
	cin >> direction;
	cout << "Introdu modul de soirtare:" << endl;
	cout << "1 - dupa nr inmatriculare" << endl;
	cout << "2 - dupa tip" << endl;
	cout << "3 - dupa prod + model" << endl;
	int n;
	cin >> n;
	while (n < 1 or n>3)
	{
		cout << "Nu e bun n introdu altu :" << endl;
		cin >> n;
	}
	vector<Masina> all;
	if (n == 1)
		all = store.sortaremasina(cmpnrinm, direction);
	if (n == 2)
		all = store.sortaremasina(cmptip, direction);
	if (n == 3)
		all = store.sortaremasina(cmpprod_model, direction);
	for (const auto el : all)
	{
		cout << el.getnrinm() << " ";
	}
	cout << endl;

}

void CUi::addcosUI()
{
	cout << "Adaugare element in cos..." << endl;
	string nrinm;
	cout << "introdu nr inm:" << endl;
	cin >> nrinm;
	try
	{
		cos.addcos(nrinm);
		cout << cos.getdim() << endl;
		cout << "Adaugare cu succes !" << endl;
	}
	catch (RepoException& re)
	{
		cout << re << endl;
	}
}
void CUi::clearcosUI()
{
	cout << "Curatare cos..." << endl;
	cout << cos.getdim() << endl;
	cos.clearcos();
}
void CUi::gencosUI()
{
	cout << "generare elemente random in cos" << endl;
	cout << "introdu nr de el de generat :" << endl;
	int nr;
	cin >> nr;
	try
	{
		cos.generatecos(nr);
		cout << cos.getdim() << endl;
		cout << "Cos generat cu succes !" << endl;
	}
	catch (CosException& ex)
	{
		cout << ex << endl;
	}
}
void CUi::exportcosUI()
{
	cout << "Salvare cos in fisier html..." << endl;
	cout << "Introdu numele fisierului : " << endl;
	string fisier;
	cin >> fisier;
	cos.exportcos(fisier);
	cout << "Salvare realizata cu succes!" << endl;
}

void CUi::undoUI()
{
	cout << "Se face undo..." << endl;
	try
	{
		store.undo();
		cout << "Undo realizat cu suuces!" << endl;
	}
	catch (RepoException& re)
	{
		cout << re;
	}
}

void meniu()
{
	cout << "Meniu:" << endl;
	cout << "1.  Adauga masina" << endl;
	cout << "2.  Sterge masina " << endl;
	cout << "3.  Modifica masina" << endl;
	cout << "4.  Filtrare masini " << endl;
	cout << "5.  Sortare masini" << endl;
	cout << "6.  Adauga in cos" << endl;
	cout << "7.  Genereaza cos random" << endl;
	cout << "8.  Goleste cos" << endl;
	cout << "9.  Export cos" << endl;
	cout << "10. Undo la ultima operatoe" << endl;
	cout << "57. Tipareste masini" << endl;
	cout << "0. exit" << endl;

}

void CUi::run_app()
{
	while (true)
	{
		meniu();
		int cmd;
		cin >> cmd;
		try {
			switch (cmd) {
			case 1:
				adaugaUI();
				break;
			case 2:
				stergeUI();
				break;
			case 3:
				modificaUI();
				break;
			case 4:
				filtrareUI();
				break;
			case 5:
				sortareUI();
				break;
			case 6:
				addcosUI();
				break;
			case 7:
				gencosUI();
				break;
			case 8:
				clearcosUI();
				break;
			case 9:
				exportcosUI();
				break;
			case 10:
				undoUI();
				break;
			case 57:
				printUI();
				break;

			case 0:
				return;
			default:
				cout << "Comanda invalida\n";
			}
		}
		catch (const RepoException& ex) {
			cout << ex << '\n';
		}
		catch (const ValidateException& ex) {
			cout << ex << '\n';
		}
	}
}

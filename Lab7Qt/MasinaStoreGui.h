#pragma once

#include <vector>
#include <string>
#include <set>

#include <QtWidgets/QApplication>
//#include <QtWidgets/QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QTableWidget>
#include <QGroupBox>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QComboBox>
#include<QHeaderView>
#include <QTableView>


#include "MasinaSrv.h"
#include "Cos.h"
#include "CosuletGui.h"
#include "TabelSmecher.h"

using std::vector;
using std::string;
using std::set;

class MasinaStoreGui : public QWidget {

private:
	MasinaStore& srv;
	Cos& cos;

	CosuletGui cosgui{ srv,cos };	

	//componente pentru adaugare
	QLabel* lbnrinm = new QLabel{ "Nr de inmatriculare:" };
	QLabel* lbprod = new QLabel{ "Producator: " };
	QLabel* lbmodel = new QLabel{ "Model: " };
	QLabel* lbtip = new QLabel{ "Tip: " };

	QLineEdit* editnrinm;
	QLineEdit* editprod;
	QLineEdit* edittip;
	QLineEdit* editmodel;
	QPushButton* addmasina;

	//componente pentru stergere
	QLabel* nrinmdel = new QLabel{ "Introdu nr de inm pt stergere :" };
	QLineEdit* delnrinm;
	QPushButton* delmasina;

	//componente pt modificare

	QLineEdit* modeditnrinm;
	QLineEdit* modeditprod;
	QLineEdit* modedittip;
	QLineEdit* modeditmodel;

	QLabel* lbnrinmmod = new QLabel{ "Nr de inmatriculare:" };
	QLabel* lbprodmod = new QLabel{ "Producator nou: " };
	QLabel* lbmodelmod = new QLabel{ "Model nou: " };
	QLabel* lbtipmod = new QLabel{ "Tip nou: " };

	QPushButton* modmasina;

	//componente pentru filtrare

	QLabel* critfiltru = new QLabel{ "Criteriu de filtrare" };
	QLineEdit* filline;
	QPushButton* btnfiltrare;

	//componentesortare
	QRadioButton* radionrinm = new QRadioButton(QString::fromStdString("Nr inmatriculare"));
	QRadioButton* radiotip = new QRadioButton(QString::fromStdString("Tip"));
	QRadioButton* radiomodel = new QRadioButton(QString::fromStdString("Model"));

	QLabel* radiodirlb = new QLabel("Directie");
	QLineEdit* radiodir = new QLineEdit;
	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QPushButton* btnsort;

	QPushButton* reload;

	TabelSmecher* model;

	//this should be QTableView
	QTableView* tabelmaimute = new QTableView;

	QPushButton* undobtn;

	//compnetnete cos

	//QTableView* cenaiba;
	
	QPushButton* addcos  ;
	QLineEdit* operatiptcos = new QLineEdit;
	QPushButton* clearcos  ;
	QPushButton* generatecos;
	QPushButton* exportbtn;
	QLineEdit* exportedit = new QLineEdit;

	QListWidget* listacos;

	//dinaic btns
	QWidget* dinamicbtn = new QWidget;
	QVBoxLayout* lydin = new QVBoxLayout;

	//componentercos nmou
	QPushButton* coscox;
	QPushButton* cosuinitial;

	QWidget* cosulet;

	QComboBox* combo;
	QComboBox* combo1;


	void initializareGUIcomp();
	void reloadMasini(vector<Masina> cars,string crit);
	void connectSignalsSlots();
	void reloadcos(vector<Masina> cars_cos);
	void clearLayout(QLayout* layout);
public:
	MasinaStoreGui(MasinaStore& srv, Cos& cos) :srv{ srv }, cos{ cos } {
		initializareGUIcomp();
		this->model = new TabelSmecher{this->srv.getAll(),""};
		tabelmaimute->setModel(this->model);
		connectSignalsSlots();
		reloadMasini(srv.getAll(),"");
		reloadcos(cos.get_all_cos());
		//reloaddinbutons();

	}

	void guiAdd();
	void guiDel();
	void guiMod();
	void guiUndo();
	void reloaddinbutons();
	void gui_cos_add();
	void gui_cos_export();
	void gui_cos_generate();
};
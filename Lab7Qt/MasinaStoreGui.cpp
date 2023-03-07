#include "MasinaStoreGui.h"


void MasinaStoreGui::guiAdd()
{
	try {

		string nrinm = editnrinm->text().toStdString();
		string model = editmodel->text().toStdString();
		string prod = editprod->text().toStdString();
		string tip = edittip->text().toStdString();

		editmodel->clear();
		edittip->clear();
		editprod->clear();
		editnrinm->clear();

		this->srv.addmasina(nrinm, model, prod, tip);

		int r = this->model->rowCount(QModelIndex());
		this->model->insertRows(r, 1, QModelIndex());

		this->reloadMasini(srv.getAll(),"");

		QMessageBox::information(this, "Info", QString::fromStdString("Masina adaugata cu succes"));

	}
	catch (RepoException& re)
	{
		QMessageBox::information(this, "Info", QString::fromStdString(re.getErrorRepo()));
	}
	catch (ValidateException& ve)
	{
		QMessageBox::information(this, "Info", QString::fromStdString(ve.getErrorVali()));
	}
}

void MasinaStoreGui::guiDel()
{
	try {

		string nrinm = delnrinm->text().toStdString();
		this->srv.stergemasina(nrinm);
		this->delnrinm->clear();
		QMessageBox::information(this, "Info", QString::fromStdString("Masina steaarsa cu scucces"));

		int r = this->model->rowCount(QModelIndex());
		r--;
		this->model->removeRows(r, 1, QModelIndex());

		this->reloadMasini(srv.getAll(),"");
	}
	catch (RepoException& re)
	{
		QMessageBox::information(this, "Info", QString::fromStdString(re.getErrorRepo()));
	}
}

void MasinaStoreGui::guiUndo()
{
	try
	{
		this->srv.undo();
		this->reloadMasini(srv.getAll(),"");
		QMessageBox::information(this, "Info", QString::fromStdString("Undo realizat cu succes"));
	}
	catch (RepoException& re)
	{
		QMessageBox::information(this, "Info", QString::fromStdString(re.getErrorRepo()));
	}
}

void MasinaStoreGui::guiMod()
{

	try {

		string nrinm = modeditnrinm->text().toStdString();
		string model = modeditmodel->text().toStdString();
		string prod = modeditprod->text().toStdString();
		string tip = modedittip->text().toStdString();

		editmodel->clear();
		edittip->clear();
		editprod->clear();
		editnrinm->clear();

		this->srv.modmasina(nrinm, model, prod, tip);
		this->reloadMasini(srv.getAll(),"");

		QMessageBox::information(this, "Info", QString::fromStdString("Masina modificata cu succes"));

	}
	catch (RepoException& re)
	{
		QMessageBox::information(this, "Info", QString::fromStdString(re.getErrorRepo()));
	}
	catch (ValidateException& ve)
	{
		QMessageBox::information(this, "Info", QString::fromStdString(ve.getErrorVali()));
	}

}

void MasinaStoreGui::connectSignalsSlots() {

	//adauga masina
	QObject::connect(addmasina, &QPushButton::clicked, this, &MasinaStoreGui::guiAdd);

	//conectam butonu de stergere
	QObject::connect(delmasina, &QPushButton::clicked, this, &MasinaStoreGui::guiDel);

	//conectam butonu de modifica
	QObject::connect(modmasina, &QPushButton::clicked, this, &MasinaStoreGui::guiMod);

	//conectam butonu de reload
	QObject::connect(reload, &QPushButton::clicked, [&]() {
		this->reloadMasini(srv.getAll(),"");
		});

	//conecta mfiltrarea
	QObject::connect(btnfiltrare, &QPushButton::clicked, [&]() {
		string filterC = this->filline->text().toStdString();
		this->reloadMasini(srv.filtraremasini(filterC, 1),"");
		});

	//conectam sortarea
	QObject::connect(undobtn, &QPushButton::clicked, this, &MasinaStoreGui::guiUndo);

	QObject::connect(generatecos, &QPushButton::clicked, this, &MasinaStoreGui::gui_cos_generate);

	QObject::connect(addcos, &QPushButton::clicked, this, &MasinaStoreGui::gui_cos_add);

	QObject::connect(clearcos, &QPushButton::clicked, this, [&]() {
		this->listacos->clear(); });

	QObject::connect(exportbtn, &QPushButton::clicked, this, &MasinaStoreGui::gui_cos_export);

	QObject::connect(btnsort, &QPushButton::clicked, [&]() {
		if (this->radionrinm->isChecked())
		{
			QMessageBox::information(this, "Info", QString::fromStdString("1"));
			this->reloadMasini(srv.sortaremasina(cmpnrinm, this->combo->currentText().toStdString()),"");

		}
		else if (this->radiotip->isChecked())
		{

			this->reloadMasini(srv.sortaremasina(cmptip, this->combo->currentText().toStdString()),"");
			QMessageBox::information(this, "Info", QString::fromStdString("2"));
		}
		else if (this->radiomodel->isChecked())
		{

			this->reloadMasini(srv.sortaremasina(cmpprod_model, this->combo->currentText().toStdString()),"");
			QMessageBox::information(this, "Info", QString::fromStdString("3"));
		}
		});

	QObject::connect(coscox,&QPushButton::clicked,[&](){
		this->cosgui.show();
		});



}

void MasinaStoreGui::reloadMasini(vector<Masina> cars,string crit)
{
	/*this->tabel->clearContents();
	this->tabel->setRowCount(cars.size());
	
	int lnr = 0;
	for (auto& car : cars)
	{
		this->tabel->setItem(lnr, 0, new QTableWidgetItem(QString::fromStdString(car.getnrinm())));
		this->tabel->setItem(lnr, 1, new QTableWidgetItem(QString::fromStdString(car.getprod())));
		this->tabel->setItem(lnr, 2, new QTableWidgetItem(QString::fromStdString(car.getmodel())));
		this->tabel->setItem(lnr, 3, new QTableWidgetItem(QString::fromStdString(car.gettip())));
		lnr++;
	}*/
	this->model->setMasinuta(cars);
	this->model->set_criteriu(crit);
	this->reloaddinbutons();
}

void MasinaStoreGui::gui_cos_add()
{
	string nrinm = operatiptcos->text().toStdString();

	try
	{
		this->cos.addcos(nrinm);
		this->reloadcos(cos.get_all_cos());
		QMessageBox::information(this, "Info", QString::fromStdString("Masina adaugata cu succes"));
	}
	catch (RepoException& re)
	{
		QMessageBox::information(this, "Info", QString::fromStdString(re.getErrorRepo()));
	}
}


void MasinaStoreGui::gui_cos_export() {
	string path = exportedit->text().toStdString();
	this->cos.exportcos(path);
	QMessageBox::information(this, "Info", QString::fromStdString("Export realizat cu succes"));
}

void MasinaStoreGui::gui_cos_generate() {
	this->cos.generatecos(5);
	reloadcos(cos.get_all_cos());
	
}


void MasinaStoreGui::reloadcos(vector<Masina> cars_cos)
{
	this->listacos->clear();
	for (const auto el : cars_cos)
	{
		this->listacos->addItem(QString::fromStdString(el.getnrinm()));
	}
}
void MasinaStoreGui::clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}
void MasinaStoreGui::reloaddinbutons()
{
	clearLayout(this->lydin);
	//partea de butoane dealea
	vector<string> butoane;
	for (const auto el : this->srv.getAll())
	{
		int ok = 0;
		for (string cox : butoane)
		{
			if (cox == el.getprod())
			{
				ok++;
			}
		}
		if (ok == 0)
		{
			butoane.push_back(el.getprod());
			QPushButton* btnnou = new QPushButton(QString::fromStdString(el.getprod()));
			lydin->addWidget(btnnou);
			QObject::connect(btnnou, &QPushButton::clicked, [=]() {

				int count = 0;
				for (const Masina masinuta : srv.getAll())
				{
					if (masinuta.getprod() == el.getprod())
						count++;
				}

				QMessageBox::information(this, "Info", QString::number(count));

				});

		}

	}
}
void MasinaStoreGui::initializareGUIcomp()
{
	//facem 2 parti una cu lista tabelasu si alta cu butoanele si labeluri si casute si radiouri si etc
	
	
	//main part
	QVBoxLayout* lymain = new QVBoxLayout;
	this->setLayout(lymain);

	//facem partea stanga
	//le punem pe verticala aici
	QWidget* left = new QWidget;
	QHBoxLayout* lyleft = new QHBoxLayout;
	left->setLayout(lyleft);

	//componente adaugare
	QWidget* formadd = new QWidget;
	QFormLayout* lyformadd = new QFormLayout;

	formadd->setLayout(lyformadd);

	editnrinm = new QLineEdit;
	editprod = new QLineEdit;
	edittip = new QLineEdit;
	editmodel = new QLineEdit;
	lyformadd->addRow(lbnrinm,editnrinm);
	lyformadd->addRow(lbprod,editprod);
	lyformadd->addRow(lbmodel,editmodel);
	lyformadd->addRow(lbtip,edittip);

	addmasina = new QPushButton("Adauga masina");
	
	lyformadd->addWidget(addmasina);
	

	lyleft->addWidget(formadd);

	//stergere
	QWidget* formdel = new QWidget;
	QFormLayout* lyformdel = new QFormLayout;
	delnrinm = new QLineEdit;
	lyformdel->addRow(nrinmdel, delnrinm);
	delmasina = new QPushButton("Sterge masina");
	lyformdel->addWidget(delmasina);
	formdel->setLayout(lyformdel);
	lyleft->addWidget(formdel);
	

	//modficaire

	QWidget* formmod = new QWidget;
	QFormLayout* lyformmod = new QFormLayout;
	formmod->setLayout(lyformmod);

	modeditnrinm = new QLineEdit;
	modeditprod = new QLineEdit;
	modedittip = new QLineEdit;
	modeditmodel = new QLineEdit;

	lyformmod->addRow(lbnrinmmod, modeditnrinm);
	lyformmod->addRow(lbprodmod, modeditprod);
	lyformmod->addRow(lbmodelmod, modeditmodel);
	lyformmod->addRow(lbtipmod, modedittip);

	modmasina = new QPushButton("Modifica masina");
	lyformmod->addWidget(modmasina);

	lyleft->addWidget(formmod);

	//radiobuttons pentru sortare aia nebuna

	//facem ungroupbox

	QVBoxLayout* lyradio = new QVBoxLayout;
	this->groupBox->setLayout(lyradio);
	lyradio->addWidget(radionrinm);
	lyradio->addWidget(radiomodel);
	lyradio->addWidget(radiotip);
	QWidget* raddir = new QWidget;
	QFormLayout* raddirly = new QFormLayout;
	raddir->setLayout(raddirly);
	raddirly->addRow(radiodirlb,radiodir);

	btnsort = new QPushButton("Sortare masinute");
	combo = new QComboBox;
	combo->addItem("ascending");
	combo->addItem("descending");
	lyradio->addWidget(combo);
	lyradio->addWidget(btnsort);
	lyleft->addWidget(groupBox);

	//formatu pentru filtrare 
	QWidget* formfil = new QWidget;
	QFormLayout* lyformfil = new QFormLayout;
	formfil->setLayout(lyformfil);
	filline = new QLineEdit;
	lyformfil->addRow(critfiltru, filline);
	btnfiltrare = new QPushButton("Filtrare masinute");
	lyformfil->addWidget(btnfiltrare);
	lyleft->addWidget(formfil);

	vector<string> tipuri;

	combo1 = new QComboBox;

	for (auto& el : this->srv.getAll())
	{
		int ok = 1;
		for (auto& tip : tipuri)
			if (el.gettip() == tip)
			{
				ok = 0;
				break;
			}
		if (ok == 1)
		{
			tipuri.push_back(el.gettip());
			combo1->addItem(QString::fromStdString(el.gettip()));
			
		}
		QObject::connect(combo1,&QComboBox::currentIndexChanged,[=](){
				this->reloadMasini(srv.getAll(),combo1->currentText().toStdString());
				});

	}
	lyleft->addWidget(combo1);

	
	reload = new QPushButton("Reload la lista");
	undobtn = new QPushButton("Undo");
	//lyleft->addWidget(reload);

	//adaugam partea stranga
	lymain->addWidget(left);


	//layoutu de jos
	
	QWidget* bottom = new QWidget;
	QHBoxLayout* lybottom = new QHBoxLayout;
	bottom->setLayout(lybottom);
	//facem partea dreapta aioa cu tabelu, mai mult partea de jkos la mine da se intelege

	QWidget* right = new QWidget;
	QVBoxLayout* lyright = new QVBoxLayout;
	right->setLayout(lyright);

	int nrlin = 10;
	int nrcol = 5;
	//this->tabel = new QTableWidget{ nrlin,nrcol };

	//setam headeru tabeluli
	QStringList tbheader;
	tbheader << "Nr Inmatriculare" << "Producator" << "Model" << "Tip";
	//this->tabel->setHorizontalHeaderLabels(tbheader);

	//this->tabel->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//QObject::connect();

	lyright->addWidget(tabelmaimute);
	lyright->addWidget(reload);
	lyright->addWidget(undobtn);
	lybottom->addWidget(right);


	QWidget* chesticos = new QWidget;
	QHBoxLayout* lychesticos = new QHBoxLayout;
	chesticos->setLayout(lychesticos);

	coscox = new QPushButton("Cosuletu smecher");
	lychesticos->addWidget(coscox);
	lyright->addWidget(chesticos);

	//cos 
	cosulet = new QWidget;
	QVBoxLayout* lycos = new QVBoxLayout;
	cosulet->setLayout(lycos);

	QWidget* formcos = new QWidget;
	QFormLayout* lyformcos = new QFormLayout;
	formcos->setLayout(lyformcos);


	 addcos = new QPushButton("Adauga cos");

	 clearcos = new QPushButton("Clear");
	 generatecos = new QPushButton("Generate");
	 exportbtn = new QPushButton("Export");
	
	 QLabel* itemcos = new QLabel("Item pe care lucram:");
	 QLabel* filepathexport = new QLabel("Filepath pentru export");

	lyformcos->addRow(itemcos,operatiptcos);
	lyformcos->addRow(filepathexport,exportedit);
	lycos->addWidget(formcos);
	lycos->addWidget(addcos);
	lycos->addWidget(clearcos);
	lycos->addWidget(generatecos);

	lycos->addWidget(exportbtn);

	listacos = new QListWidget();
	lycos->addWidget(listacos);
	cosuinitial = new QPushButton("Dc am 3 cosuri");
	lychesticos->addWidget(cosuinitial);

	QObject::connect(cosuinitial, &QPushButton::clicked, [&]() {
		cosulet->show(); });

	//QWidget* dinamicbtn = new QWidget;
	//QVBoxLayout* lydin = new QVBoxLayout;
	dinamicbtn->setLayout(lydin);

	lybottom->addWidget(dinamicbtn);
	lymain->addWidget(bottom);

}

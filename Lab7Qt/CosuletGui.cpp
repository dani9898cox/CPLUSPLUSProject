#include "CosuletGui.h"

void CosuletGui::initGui()
{
	lymain = new QHBoxLayout;
	this->setLayout(lymain);

	QWidget* leftSide = new QWidget{};
	QVBoxLayout* lyLeft = new QVBoxLayout{};
	leftSide->setLayout(lyLeft);

	QWidget* formW = new QWidget{};
	QFormLayout* lyEdits = new QFormLayout{};

	lblslider = new QLabel{ "Nr. melodii de generat" };
	editslider = new QLineEdit{};
	lyEdits->addRow(lblslider, editslider);
	formW->setLayout(lyEdits);


	btngenerate = new QPushButton{ "Genereaza random" };
	empty = new QPushButton{ "Goleste cos" };

	btnclose = new QPushButton{ "Close" };

	btnLabelWindow = new QPushButton{ "Fereastra label" };
	btnLabelWindow->setStyleSheet("background-color: cyan");


	btnDrawWindow = new QPushButton{ "Fereastra desen" };
	btnDrawWindow->setStyleSheet("background-color: yellow");


	sliderentiu = new QSlider{};
	sliderentiu->setMinimum(1);
	sliderentiu->setMaximum(srv.getAll().size());

	lyLeft->addWidget(formW);
	lyLeft->addWidget(btngenerate);
	lyLeft->addWidget(empty);

	lyLeft->addWidget(btnclose);
	lyLeft->addWidget(btnLabelWindow);
	lyLeft->addWidget(btnDrawWindow);

	QWidget* rightSide = new QWidget{};
	QVBoxLayout* lyRight = new QVBoxLayout{};
	rightSide->setLayout(lyRight);

	listamasini = new QListWidget{};
	listamasini->setFixedWidth(320);
	listamasini->setSelectionMode(QAbstractItemView::SingleSelection);

	lyRight->addWidget(listamasini);


	lymain->addWidget(leftSide);
	lymain->addWidget(sliderentiu);
	lymain->addWidget(rightSide);



}

void CosuletGui::connectSignalSlots()
{
	QObject::connect(btngenerate, &QPushButton::clicked, this, [&](){
		
		int nrmasini = this->sliderentiu->value();
		editslider->setText(QString::number(nrmasini));
		this->cos.generatecos(nrmasini);
		reloadCos();
		}
	);

	QObject::connect(btnclose,&QPushButton::clicked,this,[&](){
		this->close();
		});

	QObject::connect(empty, &QPushButton::clicked,this, [&]() {
		this->cos.clearcos();
		reloadCos();
		//QMessageBox::information(this,"Info",QString::fromStdString("cenaibanumerge"));
		});

	QObject::connect(btnDrawWindow, &QPushButton::clicked, [&]() {
		auto desenmasinuta = new DesenatoruldeMasini(this->cos);
		desenmasinuta->show();
		});

	QObject::connect(listamasini, &QListWidget::itemSelectionChanged, [&]() {
		auto selItms = listamasini->selectedItems();
		for (auto item : selItms) {
			qDebug() << item->text();
			item->setBackground(Qt::green); // sets green background
		}

		});

}

void CosuletGui::reloadCos()
{
	this->listamasini->clear();

	const vector<Masina>& cars = cos.get_all_cos();
	for (auto& masina : cars) {
		QString currentItem = QString::fromStdString(masina.tostring());
		this->listamasini->addItem(currentItem);
	}
	this->listamasini->setAlternatingRowColors (Qt::red);

}

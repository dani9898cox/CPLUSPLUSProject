#pragma once

#include <QtWidgets/QApplication>
#include <QWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>

#include <QMessageBox>
#include <string>
#include <set>
#include <vector>
#include <QDebug>
#include <QPainter>
#include <cstdlib>

#include "Cos.h"
#include "MasinaSrv.h"
#include "Observer.h"


using std::vector;
using std::string;
using std::set;

class NumaratoruldeMasini;

class CosuletGui : public QWidget
{
private:
	MasinaStore& srv;
	Cos& cos;

	QHBoxLayout* lymain;
	QListWidget* listamasini;

	QPushButton* clearlist;

	QLineEdit* editslider;
	QLabel* lblslider;
	QSlider* sliderentiu;

	QPushButton* btngenerate;
	QPushButton* empty;
	QPushButton* btnclose;

	QPushButton* btnLabelWindow;
	QPushButton* btnDrawWindow;

	void initGui();
	void connectSignalSlots();
	void reloadCos();

public :
	CosuletGui(MasinaStore& srv, Cos& cos) : srv{ srv }, cos{cos} {
		initGui();
		connectSignalSlots();
	}
};

class NumaratoruldeMasini : public QWidget, public Observer
{
private:
	QLineEdit* textbox;
	Cos& cos;

public:

	NumaratoruldeMasini(Cos& cosulet) : cos{ cosulet } {

		textbox = new QLineEdit;
		QHBoxLayout* layout = new QHBoxLayout;
		this->setLayout(layout);
		layout->addWidget(textbox);
		cos.addObserver(this);
		update();
	}

	void update() override
	{
		textbox->setText(std::to_string(cos.get_all_cos().size()).c_str());
	}

	~NumaratoruldeMasini()
	{
		cos.removeObserver(this);
	}
	

};

class DesenatoruldeMasini : public QWidget, public Observer {
		
private: 
	Cos& cos;

protected:
	void paintEvent(QPaintEvent* ev) override {

		int x = 10, y = 10, w = 10, h = 10;
		QPainter g{ this };
		g.setPen(Qt::blue);
		for (auto masina : cos.get_all_cos())
		{
			g.drawRect(x, y, w, h);
			x += 40;
		}

	}

public:

	DesenatoruldeMasini(Cos& cosulet) : cos{ cosulet } {
		update();
	}

	void update() override
	{
		this->repaint();
	}

};
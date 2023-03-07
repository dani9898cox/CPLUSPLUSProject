#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <vector>
#include <qdebug.h>
#include <QFont>

#include "Masina.h"

using std::vector;

class TabelSmecher : public QAbstractTableModel {

	std::vector<Masina> masinute;
	std::string crit="";

public :

	void set_criteriu(string criteriu)
	{
		this->crit = criteriu;
	}

	TabelSmecher(const vector<Masina>& masinute, string crit) : masinute{ masinute }, crit{ crit } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override 
	{
		return masinute.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	//Returns the data stored under the given role for the item referred to by the index.
	//nu stiu ce i asta sper ca nu pica la examen 

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			auto masinuta = this->masinute[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(masinuta.getnrinm());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(masinuta.getprod());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(masinuta.getmodel());
			}
			else if(index.column()==3) {
				return QString::fromStdString(masinuta.gettip());
			}
			else
			{
				int nrtr=0;
				for (auto& el : this->masinute)
				{
					if (el.gettip() == masinuta.gettip())
						nrtr++;
					

				}
				return QString::number(nrtr);

			}
		}
		else if (role == Qt::BackgroundRole) {
			auto maimuta = this->masinute[index.row()];
			if (maimuta.getprod() == "Ford") {
				return QBrush(Qt::blue);
			}
		}
		else if (role == Qt::FontRole) {
			auto maimuta = this->masinute[index.row()];
			if (maimuta.gettip() == this->crit) {
				auto font = QFont();
				font.setBold(true);
				return font;
			}
		}
		/*else if (role == Qt::ForegroundRole) {
			auto maimuta = this->masinute[index.row()];
			if (maimuta.getnrinm() =="MS69EDI") {
				return QBrush(Qt::red);
			}*/
			
		//}
		else if(role==Qt::ForegroundRole)
		{
			auto maimuta = this->masinute[index.row()];
			if (maimuta.gettip() == this->crit) {
				return QBrush(Qt::red);
			}

		}

		return QVariant{};
	}

	void setMasinuta(const vector<Masina> masini) {
		this->masinute = masini;
		auto topIndex = createIndex(0, 0);
		auto bottomIndex = createIndex(masinute.size(), 4);
		emit dataChanged(topIndex, bottomIndex);
		emit layoutChanged();
	}

	Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}

	//bool insertRows(int row, int count, const QModelIndex& parent) override
	//{
	//	beginInsertRows(parent, row, row + count - 1);
	//	endInsertRows();
	//	return true;
	//}

	//bool removeRows(int row, int count, const QModelIndex& parent) override
	//{
	//	beginRemoveRows(parent, row, row + count - 1);
	//	endRemoveRows();
	//	return true;
	//}


};

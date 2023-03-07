#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab7Qt.h"

class Lab7Qt : public QMainWindow
{
    Q_OBJECT

public:
    Lab7Qt(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lab7QtClass ui;
};

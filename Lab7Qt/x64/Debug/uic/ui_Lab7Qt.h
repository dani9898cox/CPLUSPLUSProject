/********************************************************************************
** Form generated from reading UI file 'Lab7Qt.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB7QT_H
#define UI_LAB7QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab7QtClass
{
public:

    void setupUi(QWidget *Lab7QtClass)
    {
        if (Lab7QtClass->objectName().isEmpty())
            Lab7QtClass->setObjectName(QString::fromUtf8("Lab7QtClass"));
        Lab7QtClass->resize(600, 400);

        retranslateUi(Lab7QtClass);

        QMetaObject::connectSlotsByName(Lab7QtClass);
    } // setupUi

    void retranslateUi(QWidget *Lab7QtClass)
    {
        Lab7QtClass->setWindowTitle(QCoreApplication::translate("Lab7QtClass", "Lab7Qt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab7QtClass: public Ui_Lab7QtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB7QT_H

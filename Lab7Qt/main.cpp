
#include <iostream>
#include "Masina.h"
#include "Validator.h"
#include "MasinaRepo.h"
#include "MasinaSrv.h"
#include "Ui.h"
#include "Cos.h"
#include "MasinaStoreGui.h"

using namespace std;

void test_all()
{
    test_masina();
    test_validator();
    test_repo();
    test_filrepo();
    test_service();
    test_cos();
}
#include "Lab7Qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    test_all();
    QApplication a(argc, argv);

     MasinaRepoFile repo{"fisier.txt"};
     Validator vali;
     MasinaStore store{ repo,vali };
     Cos cos{ repo };
     MasinaStoreGui gui{store,cos};

    
    
    gui.setWindowState(Qt::WindowMaximized);
    gui.show();

    return a.exec();
}

//int main()
//{
//    cout << "***************************************\n";
//    cout << "Program minuant de inchiriere de masini\n";
//    cout << "Developement team : Daniel \n";
//    cout << "Version: beta 0.8\n";
//    cout << "***************************************\n";
//
//    cout << endl;
//    cout << "Start teste...\n";
//    test_all();
//    cout << "Teste gata cu suuces !...\n";
//
//     MasinaRepoFile repo{"fisier.txt"};
//     Validator vali;
//     MasinaStore store{ repo,vali };
//     Cos cos{ repo };
//     CUi ui{ store,cos };
//     ui.run_app();
//    
//    return 0;
//}

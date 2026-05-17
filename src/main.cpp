#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Set application information
    QCoreApplication::setApplicationName("TicTacToePremium");
    QCoreApplication::setOrganizationName("Student Project");
    
    MainWindow w;
    w.show();
    
    return app.exec();
}

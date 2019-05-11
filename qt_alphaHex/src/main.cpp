#include "inc/gui/window/mainWindow.h"
#include "inc/policy/aiPolicy.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QObject::connect(w.m_setWidget,SIGNAL(signals_on_exit()),
                     &a,SLOT(quit()));
    //w.show();
    return a.exec();
}

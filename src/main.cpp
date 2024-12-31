#include "NekoSource.h"
#include "buttons.h"
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QSize>
#include <QLayout>
#include <QWidget>
#include <QStyleFactory>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget* pizdadeda = new QWidget();
    pizdadeda->setMinimumSize(1000, 650);

    butts(pizdadeda, a);

    //pizdadeda->setWindowIcon(QIcon(":/NekoSource/icon.png"));
    pizdadeda->show();

    a.setStyle(QStyleFactory::create("Fusion"));
    QPalette p = a.palette();
    //p.setColor(QPalette::Window, QColor(53, 53, 53));
    //p.setColor(QPalette::Button, QColor(53, 53, 53));
    //p.setColor(QPalette::Highlight, QColor(255, 92, 119));
    //p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    //p.setColor(QPalette::WindowText, QColor(255, 255, 255));
    //a.setPalette(p); //dark theme

    p.setColor(QPalette::Window, QColor(54, 33, 52));
    p.setColor(QPalette::Button, QColor(88, 48, 72));
    p.setColor(QPalette::Highlight, QColor(138, 43, 91));
    p.setColor(QPalette::ButtonText, QColor(255, 220, 240));
    p.setColor(QPalette::WindowText, QColor(240, 190, 215));
    a.setPalette(p); //dark pink theme

    return a.exec();
    //run in Qt cmd after compile: windeployqt "path-to-nekosource.exe"
}

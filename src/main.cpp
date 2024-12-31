#include "NekoSource.h"
#include <clocale>
#include <cstdio>
#include "buttons.h"
#include "settings.h"
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QSize>
#include <QLayout>
#include <QWidget>
#include <QStyleFactory>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "en_US.UTF-8");
    QCoreApplication::setOrganizationName("TolyaGosuslugi");
    QCoreApplication::setOrganizationDomain("https://github.com/TolyaGosuslugi");
    QCoreApplication::setApplicationName("NekoSource");

    QApplication a(argc, argv);
    QWidget* pizdadeda = new QWidget();
    pizdadeda->setMinimumSize(1000, 650);

    butts(pizdadeda, a);

    //pizdadeda->setWindowIcon(QIcon(":/NekoSource/icon.png"));
    pizdadeda->show();

    a.setStyle(QStyleFactory::create("Fusion"));
    loadSettings(a);
    //QPalette p = a.palette();
    //p.setColor(QPalette::Window, QColor(54, 33, 52));
    //p.setColor(QPalette::Button, QColor(88, 48, 72));
    //p.setColor(QPalette::Highlight, QColor(138, 43, 91));
    //p.setColor(QPalette::ButtonText, QColor(255, 220, 240));
    //p.setColor(QPalette::WindowText, QColor(240, 190, 215));
    //a.setPalette(p); //dark pink theme

    return a.exec();
    //run in Qt cmd after compile: windeployqt "path-to-nekosource.exe"
}

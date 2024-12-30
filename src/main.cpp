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

    butts(pizdadeda);

    //pizdadeda->setWindowIcon(QIcon(":/NekoSource/icontest.png"));
    pizdadeda->show();

    a.setStyle(QStyleFactory::create("Fusion"));
    QPalette p = a.palette();
    p.setColor(QPalette::Window, QColor(53, 53, 53));
    p.setColor(QPalette::Button, QColor(53, 53, 53));
    p.setColor(QPalette::Highlight, QColor(142, 45, 197));
    p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    p.setColor(QPalette::WindowText, QColor(255, 255, 255));
    a.setPalette(p);

    //QPushButton button("Hello, Qt!");
    //button.resize(200, 100);
    //button.show();

    //NekoSource w;
    //w.show();

    return a.exec();
}

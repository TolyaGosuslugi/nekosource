#include "src/NekoSource.h"
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QSize>
#include <QLayout>
#include <QWidget>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *pizdadeda = new QWidget();
    pizdadeda->setFixedSize(1000, 650);
    QPushButton* butt = new QPushButton(pizdadeda);
    butt->resize(200, 100);
    butt->setText("pizda");
    pizdadeda->show();

    a.setStyle(QStyleFactory::create("Fusion"));

    //QPushButton button("Hello, Qt!");
    //button.resize(200, 100);
    //button.show();

    //NekoSource w;
    //w.show();

    return a.exec();
}

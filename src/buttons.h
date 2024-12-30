#pragma once
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QSize>
#include <QLayout>
#include <QWidget>
#include <QStyleFactory>
#include <QLineEdit>
#include <QAction>
#include <QToolButton>

void butts(QWidget *pizdadeda) {

    QToolButton *toolButton1 = new QToolButton(pizdadeda);
    toolButton1->setText("Pizda Deda Flac");
    toolButton1->setIcon(QIcon(":/NekoSource/bomzi.png"));
    toolButton1->setIconSize(QSize(50, 50));
    toolButton1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolButton1->show();

    QToolButton* toolButton2 = new QToolButton(pizdadeda);
    toolButton2->setText("Ebat Ochko Nigers");
    toolButton2->setIcon(QIcon(":/NekoSource/gena.png"));
    toolButton2->setIconSize(QSize(50, 50));
    toolButton2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolButton2->move(90, 0);
    toolButton2->show();
}
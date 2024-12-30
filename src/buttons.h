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
    //toolButton->resize(100, 100);
    toolButton1->show();

}
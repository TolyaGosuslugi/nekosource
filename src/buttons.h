#pragma once
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QSize>
#include <QLayout>
#include <QWidget>
#include <QStyleFactory>
#include <QLineEdit>

void butts(QWidget *pizdadeda) {
	pizdadeda->setMinimumSize(1000, 650);
	QPushButton* butt1 = new QPushButton(pizdadeda);
	butt1->resize(100, 100);
	butt1->setText("kesha lox");
	QPixmap pixmap(":/NekoSource/kesha.png");
	QIcon ButtonIcon(pixmap);
	butt1->setIcon(ButtonIcon);
	butt1->setIconSize(QSize(50, 50));

	QPushButton* butt2 = new QPushButton(pizdadeda);
	butt2->resize(100, 100);
	butt2->setText("pizda");
	QPixmap pixmap2(":/NekoSource/bomzi.png");
	QIcon ButtonIcon2(pixmap2);
	butt2->setIcon(ButtonIcon2);
	butt2->setIconSize(QSize(50, 50));
	butt2->move(100, 0);
}
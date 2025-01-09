#pragma once
#include <QLabel>
#include <QWidget>
#include <QFont>
#include <QObject>

void showAboutWindow() {
	QWidget* aboutWind = new QWidget();
	aboutWind->setMinimumSize(500, 350);
	aboutWind->setWindowTitle(QObject::tr("Thanks for using NekoSource! ^^ || 2024-2025 TolyaGosuslugi"));

	QLabel* mainLabel = new QLabel(aboutWind);
	mainLabel->setText(QObject::tr("About"));
	mainLabel->setStyleSheet(QString("font-size: 30px; color: #A0A0A0").arg(32));
	mainLabel->show();

///////////////////    Authors    ///////////////////

	QVBoxLayout* mainBox = new QVBoxLayout();

	QLabel* tolyagosuslugi = new QLabel(aboutWind);
	tolyagosuslugi->setText("<a href=\"https://github.com/tolyagosuslugi\">tolyagosuslugi</a> - " + QObject::tr("main code, russian translation"));
	tolyagosuslugi->setStyleSheet(QString("font-size: 14px").arg(32));
	tolyagosuslugi->setTextFormat(Qt::RichText);
	tolyagosuslugi->setTextInteractionFlags(Qt::TextBrowserInteraction);
	tolyagosuslugi->setOpenExternalLinks(true);
	tolyagosuslugi->show();
	QLabel* shadowcj = new QLabel(aboutWind);
	shadowcj->setText("<a href=\"https://github.com/bluzetX\">shadowcj</a> - " + QObject::tr("ukrainian translation"));
	shadowcj->setStyleSheet(QString("font-size: 14px").arg(32));
	shadowcj->setTextFormat(Qt::RichText);
	shadowcj->setTextInteractionFlags(Qt::TextBrowserInteraction);
	shadowcj->setOpenExternalLinks(true);
	shadowcj->show();
	/* QLabel* semkapc = new QLabel(aboutWind);
	semkapc->setText("<a href=\"https://github.com/semkapc\">semkapc</a> - " + QObject::tr("belarusian translation"));
	semkapc->setStyleSheet(QString("font-size: 14px").arg(32));
	semkapc->setTextFormat(Qt::RichText);
	semkapc->setTextInteractionFlags(Qt::TextBrowserInteraction);
	semkapc->setOpenExternalLinks(true);
	semkapc->show(); */

	QLabel* iconsSource = new QLabel(aboutWind);
	iconsSource->setText("<a href=\"https://feathericons.com/\">feathericons.com</a> - " + QObject::tr("thanks for icons"));
	iconsSource->setStyleSheet(QString("font-size: 14px").arg(32));
	iconsSource->setTextFormat(Qt::RichText);
	iconsSource->setTextInteractionFlags(Qt::TextBrowserInteraction);
	iconsSource->setOpenExternalLinks(true);
	iconsSource->show();

	mainBox->addWidget(mainLabel);
	mainBox->addWidget(tolyagosuslugi);
	mainBox->addWidget(shadowcj);
	//mainBox->addWidget(semkapc);
	mainBox->addWidget(iconsSource);
	mainBox->setAlignment(Qt::AlignTop);

	aboutWind->setLayout(mainBox);
	aboutWind->show();
}
#pragma once
#include <QComboBox>
#include <QSettings>
#include <QToolButton>
#include <QMessageBox>
QSettings sysSetts("TolyaGosuslugi", "NekoSource");
QString thm = sysSetts.value("theme", "dark").toString();
QString lng = sysSetts.value("lang", "en_US").toString();
QString newLng;

void createSettingsWindow(QWidget *mainWindow) {
	QWidget* settsWind = new QWidget();
	settsWind->setAttribute(Qt::WA_DeleteOnClose);
	settsWind->setMinimumSize(QSize(200, 100));

	QToolButton* themeButton = new QToolButton(settsWind);
	themeButton->setText(lng);

	// Create list
	QMenu* menu = new QMenu(themeButton);
	QAction* en = menu->addAction("en_US");
	QAction* ru = menu->addAction("ru_RU");

	// Create connects for all actions
	QObject::connect(en, &QAction::triggered, [=]() {
		newLng = "en_US";
	});
	QObject::connect(ru, &QAction::triggered, [=]() {
		newLng = "ru_RU";
	});

	themeButton->setMenu(menu);
	themeButton->setPopupMode(QToolButton::InstantPopup);
	settsWind->show();
}
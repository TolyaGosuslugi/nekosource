#pragma once
#include "settsButtons.h"
#include <QComboBox>
#include <QSettings>
#include <QToolButton>
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

void createSettingsWindow(QApplication& a) {
	QWidget* settsWind = new QWidget();
	settsWind->setWindowTitle(QObject::tr("Settings"));
	settsWind->setAttribute(Qt::WA_DeleteOnClose);
	settsWind->setFixedSize(QSize(400, 120));
	settsbutts(settsWind, a);
}
#pragma once
#include <filesystem>
#include <QWidget>
#include <QtWidgets/QApplication>
#include <QList>
#include <QListWidget>
#include <QString>

void showListWidget(QWidget* mainWindow) {
	QListWidget* mainList = new QListWidget(mainWindow);
	mainList->setMinimumSize(300, 600);

	for (const auto& entry : std::filesystem::recursive_directory_iterator("repos")) {
		if (entry.is_directory()) {
			QString partsStr = QString::fromStdString(entry.path().string());
			QStringList parts = partsStr.split("\\");
			if (parts.size() == 3) {
				mainList->addItem(partsStr);
			}
		}
	}

	mainList->show();
}
#pragma once
#include <filesystem>
#include <fstream>
#include <QWidget>
#include <QVBoxLayout>
#include <QtWidgets/QApplication>
#include <QList>
#include <QListWidget>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QTableWidget>
#include <QTime>

QWidget* showTableWidget(QTableWidget* mainList) {
    mainList->setRowCount(0);
    int row = 0;
    for (const auto& entry : std::filesystem::recursive_directory_iterator("repos")) {
        if (entry.is_directory()) {
            QString partsStr = QString::fromStdString(entry.path().string());
            QStringList parts = partsStr.split("\\");
            if (parts.size() == 3) {
                mainList->insertRow(row);

                QTableWidgetItem* pathItem = new QTableWidgetItem(partsStr);
                mainList->setItem(row, 0, pathItem);

                std::string substrUrl;
                QString cfgPath = partsStr + "\\.git\\config";
                QString linkResult;
                std::ifstream config(cfgPath.toStdString());
                if (config.is_open()) {
                    while (std::getline(config, substrUrl)) {
                        if (QString::fromStdString(substrUrl).contains("url")) {
                            linkResult = QString::fromStdString(substrUrl).mid(7);
                        }
                    }
                }

                QTableWidgetItem* linkItem = new QTableWidgetItem(linkResult);
                mainList->setItem(row, 1, linkItem);

                row++;
            }
        }
    }
}

void updateReposTable(QTableWidget* mainList) {
    mainList->clear();
    showTableWidget(mainList);
    mainList->setHorizontalHeaderLabels(QStringList() << QObject::tr("Path") << QObject::tr("Link"));
}

void delay(int secs)
{
    QTime dieTime = QTime::currentTime().addSecs(secs);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
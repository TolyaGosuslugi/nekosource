#pragma once
#include <QItemSelectionModel>
#include <QTableWidgetItem>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <QTableWidget>

void inExplorer(QTableWidget* mainList) {
    QItemSelectionModel* selectionModel = mainList->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row();
        int column = 0;
        QTableWidgetItem* pathItem = mainList->item(row, column);
        QDir baseDir = QDir::current();
        QString fullPath = baseDir.absoluteFilePath(pathItem->text());
        fullPath.replace("/", "\\");

        QProcess* process = new QProcess();
        QString command = "explorer " + fullPath;
        process->startDetached(command);
    }
    else {
        QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("No row selected!"));
    }
}

void inCMD(QTableWidget* mainList) {
    QItemSelectionModel* selectionModel = mainList->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row();
        int column = 0;
        QTableWidgetItem* pathItem = mainList->item(row, column);
        QDir baseDir = QDir::current();
        QString fullPath = baseDir.absoluteFilePath(pathItem->text());
        fullPath.replace("/", "\\");

        //QProcess* process = new QProcess();
        //QString command = "start cmd / k \"cd " + fullPath + "\"";
        //process->execute(command);

        std::string command = "start cmd /k \"cd " + fullPath.toStdString() + "\"";
        std::system(command.c_str());
    }
    else {
        QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("No row selected!"));
    }
}
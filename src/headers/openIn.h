#pragma once
#include <QItemSelectionModel>
#include <QTableWidgetItem>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <QTableWidget>
#include <QDesktopServices>
#include <QUrl>

void inExplorer(QTableWidget* mainList) {
    QItemSelectionModel* selectionModel = mainList->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row(); // Get selected row
        int column = 0; // From "Path" column
        QTableWidgetItem* pathItem = mainList->item(row, column); //get item
        QDir baseDir = QDir::current(); // Get current dir(where is nekosource.exe)
        QString fullPath = baseDir.absoluteFilePath(pathItem->text()); // Get full path to nekosource.exe
        fullPath.replace("/", "\\"); // replace fucking / to \\

        QProcess* process = new QProcess();
        QString command = "explorer " + fullPath;
        process->startDetached(command); // open explorer in repository directory
    }
    else {
        QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("No row selected!"));
    }
}

void inCMD(QTableWidget* mainList) {
    QItemSelectionModel* selectionModel = mainList->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row(); // Get selected row
        int column = 0; // From "Path" column
        QTableWidgetItem* pathItem = mainList->item(row, column); //get item
        QDir baseDir = QDir::current(); // Get current dir(where is nekosource.exe)
        QString fullPath = baseDir.absoluteFilePath(pathItem->text()); // Get full path to nekosource.exe
        fullPath.replace("/", "\\"); // replace fucking / to \\

        std::string command = "start cmd /k \"cd " + fullPath.toStdString() + "\"";
        std::system(command.c_str()); // run cmd in repository directory
    }
    else {
        QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("No row selected!"));
    }
}

void inBrowser(QTableWidget* mainList) {
    QItemSelectionModel* selectionModel = mainList->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row(); // Get selected row
        int column = 1; // From "Link" column
        QTableWidgetItem* pathItem = mainList->item(row, column); // get item

        QDesktopServices::openUrl(QUrl(pathItem->text())); // Get url from selected row and Link column and open it in browser
    }
    else {
        QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("No row selected!"));
    }
}
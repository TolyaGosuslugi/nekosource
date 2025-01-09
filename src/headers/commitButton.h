#pragma once
#include <QDir>
#include <QTableWidget>

void commitChanges(QTableWidget* mainList) {
    QItemSelectionModel* selectionModel = mainList->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row();
        int column = 0; // Из колонки "Путь"
        QTableWidgetItem* pathItem = mainList->item(row, column); // Получаем (блять как переводиться)
        QDir baseDir = QDir::current(); //Получаем директорию(where is nekosource.exe)
        QString fullPath = baseDir.absoluteFilePath(pathItem->text()); // Получаем полный путь к nekosource.exe
        fullPath.replace("/", "\\"); // замена ебанных / на \\

        //QProcess* process = new QProcess();
        //process->setWorkingDirectory(fullPath);
        //QString command = "explorer " + fullPath;
        //process->startDetached(command);
        // TODO: доделать "git add -A", "git commit -m"(окно с вводом сообщением коммита) и "git push"
    }
    else {
        QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("No row selected!"));
    }
}
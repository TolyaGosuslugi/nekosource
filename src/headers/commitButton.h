#pragma once
#include <QDir>
#include <QTableWidget>

void commitChanges(QTableWidget* mainList) {
    QItemSelectionModel* selectionModel = mainList->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row();
        int column = 0; // Из колонки "Путь"
        QTableWidgetItem* pathItem = mainList->item(row, column); // Получаем (блять как переводится item)
        QDir baseDir = QDir::current(); //Получаем директорию(откуда запущен nekosource.exe)
        QString fullPath = baseDir.absoluteFilePath(pathItem->text()); // получаем полный путь к выбранному объекту-репозиторию
        fullPath.replace("/", "\\"); // замена ебанных / на \\

        QString gitPath = "git";
        if (std::filesystem::exists("PortableGit")) {
            gitPath = baseDir.absolutePath() + "/PortableGit/bin/git.exe";
        }

        QProcess* process = new QProcess();
        process->setWorkingDirectory(fullPath);
        process->start(gitPath, QStringList() << "add" << "-A");
        // добавление новых элементов
        
        QWidget* commitMessageWidget = new QWidget();
        QString commitMessageText;
        QInputDialog inputDialog;
        bool ok;
        QString text = inputDialog.getText(commitMessageWidget,
            QObject::tr("Commit message"),
            QObject::tr("Enter commit message:"),
            QLineEdit::Normal,
            "",
            &ok);
        if (ok) {
            if (!text.isEmpty()) {
                commitMessageText = text;
                QProcess commitProcess;
                commitProcess.setWorkingDirectory(fullPath);
                commitProcess.start(gitPath, QStringList() << "commit" << "-m" << commitMessageText);
                commitProcess.waitForFinished();

                QProcess pushProcess;
                pushProcess.setWorkingDirectory(fullPath);
                pushProcess.start(gitPath, QStringList() << "push");
                pushProcess.waitForFinished();
            }
            else {
                QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("Commit message cannot be empty!"));
            }
        }
    }
    else {
        QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("No row selected!"));
    }
}
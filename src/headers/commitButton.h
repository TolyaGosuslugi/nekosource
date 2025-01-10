#pragma once
#include <QDir>
#include <QTableWidget>

void commitChanges(QTableWidget* mainList) {
    QItemSelectionModel* selectionModel = mainList->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        int row = selectedIndexes.first().row();
        int column = 0; // �� ������� "����"
        QTableWidgetItem* pathItem = mainList->item(row, column); // �������� (����� ��� ������������)
        QDir baseDir = QDir::current(); //�������� ����������(where is nekosource.exe)
        QString fullPath = baseDir.absoluteFilePath(pathItem->text()); // �������� ������ ���� � nekosource.exe
        fullPath.replace("/", "\\"); // ������ ������� / �� \\

        QString gitPath = "git";
        if (std::filesystem::exists("PortableGit")) {
            gitPath = baseDir.absolutePath() + "/PortableGit/bin/git.exe";
        }

        QProcess* process = new QProcess();
        process->setWorkingDirectory(fullPath);
        process->start(gitPath, QStringList() << "add" << "-A");
        // ���������� ����� ���������
        
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
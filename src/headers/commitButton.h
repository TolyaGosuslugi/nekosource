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

        //QProcess* process = new QProcess();
        //process->setWorkingDirectory(fullPath);
        //QString command = "explorer " + fullPath;
        //process->startDetached(command);
        // TODO: �������� "git add -A", "git commit -m"(���� � ������ ���������� �������) � "git push"
    }
    else {
        QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("No row selected!"));
    }
}
#pragma once
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QSize>
#include <QLayout>
#include <QWidget>
#include <string>
#include <QStyleFactory>
#include <QLineEdit>
#include <QAction>
#include <QToolButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QProcess>

void butts(QWidget *pizdadeda) {

    QToolButton *toolButton1 = new QToolButton(pizdadeda);
    toolButton1->setText("Clone Repository");
    toolButton1->setIcon(QIcon(":/NekoSource/bomzi.png"));
    toolButton1->setIconSize(QSize(50, 50));
    toolButton1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QObject::connect(toolButton1, &QToolButton::clicked, [&]() {
        QWidget *newWindow = new QWidget();
        newWindow->setAttribute(Qt::WA_DeleteOnClose);

        QInputDialog inputDialog;
        bool ok;
        inputDialog.resize(QSize(300, 200));
        QString text = inputDialog.getText(newWindow,
            "Clone Repository",
            "Enter repository link:",
            QLineEdit::Normal,
            "",
            &ok);
        if (ok && !text.isEmpty()) {
            QStringList parts = text.split('/');
            QString repoName = parts.last().section('.', 0, 0);

            QString command = "git clone " + text + " repos/" + repoName;
            QProcess* process = new QProcess(newWindow);
            process->startDetached(command);
        }
    });

    toolButton1->show();
}
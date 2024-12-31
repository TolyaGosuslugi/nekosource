#pragma once
#include "settings.h"
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QSize>
#include <QLayout>
#include <QLabel>
#include <QWidget>
#include <string>
#include <QStyleFactory>
#include <QLineEdit>
#include <QAction>
#include <QToolButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QProcess>
#include <QSet>
#include <QString>

void butts(QWidget *pizdadeda, QApplication &a) {

    QToolButton *cloneButton = new QToolButton(pizdadeda);
    cloneButton->setText(textLocal("clone"));
    cloneButton->setIcon(QIcon(":/NekoSource/tuka.png"));
    cloneButton->setIconSize(QSize(50, 50));
    cloneButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QObject::connect(cloneButton, &QToolButton::clicked, [&]() {
        QWidget *newWindow = new QWidget();
        newWindow->setAttribute(Qt::WA_DeleteOnClose);

        QInputDialog inputDialog;
        bool ok;
        QString text = inputDialog.getText(newWindow,
            textLocal("clone"),
            "Enter repository link:",
            QLineEdit::Normal,
            "",
            &ok);
        if (ok && !text.isEmpty()) {
            QString repoAuthor;
            QString repoName;
            QSet<QString> gitDomains = {"github.com", "gitlab.com", "codeberg.org", "gitea.com"};
            if (!text.startsWith("https://")) {
                text = "https://" + text;
            }
            QStringList parts = text.split('/');
            if (parts.size() >= 5 && gitDomains.contains(parts[2])) {
                QString repoAuthor = parts[3];
                QString repoName = parts[4];

                QString command = "git clone " + text + " repos/" + repoAuthor + "/" + repoName;
                QProcess* process = new QProcess(newWindow);
                process->startDetached(command);
            }
            else {
                QMessageBox::warning(nullptr, "Warning", "Incorrect link!");
            }
        }
    });
    cloneButton->show();
}
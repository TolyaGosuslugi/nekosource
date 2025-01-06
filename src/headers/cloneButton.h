#pragma once
#include "reposList.h"
#include <iostream>
#include <filesystem>
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
#include <QTranslator>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QModelIndexList>
#include <QClipboard>


void urlManually(QTableWidget* mainList) {
    QWidget* newWindow = new QWidget();
    newWindow->setAttribute(Qt::WA_DeleteOnClose);

    QInputDialog inputDialog;
    bool ok;
    QString text = inputDialog.getText(newWindow,
        QObject::tr("Clone Repository"),
        QObject::tr("Enter repository link:"),
        QLineEdit::Normal,
        "",
        &ok);
    if (ok && !text.isEmpty()) {
        QString repoAuthor;
        QString repoName;
        QSet<QString> gitDomains = { "github.com", "gitlab.com", "codeberg.org", "gitea.com" };
        if (!text.startsWith("https://")) {
            text = "https://" + text;
        }
        QStringList parts = text.split('/');
        if (parts.size() >= 5 && gitDomains.contains(parts[2])) {
            QString repoAuthor = parts[3];
            QString repoName = parts[4];
            QString command;

            if (std::filesystem::exists("PortableGit")) {
                command = "PortableGit/bin/git.exe clone " + text + " repos/" + repoAuthor + "/" + repoName;
            }
            else {
                command = "git clone " + text + " repos/" + repoAuthor + "/" + repoName;
            }

            QProcess* process = new QProcess(newWindow);
            process->startDetached(command);
        }
        else {
            QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("Incorrect link!"));
        }
        delay(1);
        QProcess* process = new QProcess(newWindow);
        QString command = "attrib - r /s /d repos\\" + repoAuthor + "\\" + repoName;
        process->startDetached(command);
        updateReposTable(mainList);
    }
}

void urlFromClipboard(QTableWidget* mainList) {
    QInputDialog inputDialog;
    QString text = QGuiApplication::clipboard()->text();
    if (!text.isEmpty()) {
        QString repoAuthor;
        QString repoName;
        QSet<QString> gitDomains = { "github.com", "gitlab.com", "codeberg.org", "gitea.com" };
        if (!text.startsWith("https://")) {
            text = "https://" + text;
        }
        QStringList parts = text.split('/');
        if (parts.size() >= 5 && gitDomains.contains(parts[2])) {
            QString repoAuthor = parts[3];
            QString repoName = parts[4];
            QString command;

            if (std::filesystem::exists("PortableGit")) {
                command = "PortableGit/bin/git.exe clone " + text + " repos/" + repoAuthor + "/" + repoName;
            }
            else {
                command = "git clone " + text + " repos/" + repoAuthor + "/" + repoName;
            }

            QProcess* process = new QProcess();
            process->startDetached(command);
        }
        else {
            QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("There is no link in the clipboard!"));
        }
        delay(1);
        updateReposTable(mainList);
    }
}
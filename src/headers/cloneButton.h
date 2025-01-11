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
#include <QDir>
#include <QString>
#include <QTranslator>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QModelIndexList>
#include <QClipboard>
#include <QMimeData>
#include <qDebug>

///////////    Гит    ///////////

QString gitPath() {
    QDir baseDir = QDir::current();
    QString fullPath = baseDir.absoluteFilePath("PortableGit");
    if (std::filesystem::exists(fullPath.toStdString())) {
        return fullPath + "/bin/git.exe";
    }
    else {
        return "git";
    }
}

///////////    Функция клона    ///////////

void clone(QString& command, QString& fullPath) {
    QMessageBox* notification = new QMessageBox();
    notification->setWindowTitle(QObject::tr("Process Running"));
    notification->setText(QObject::tr("The process is running..."));
    notification->setStandardButtons(QMessageBox::NoButton);
    notification->setModal(true);
    notification->show();

    QProcess* process = new QProcess();
    QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [notification, process, fullPath](int exitCode, QProcess::ExitStatus exitStatus) {
        notification->close();
        notification->deleteLater();

        QByteArray errorOutput = process->readAllStandardError();
        QString errorMessage = QString::fromUtf8(errorOutput).trimmed();

        if (exitStatus == QProcess::NormalExit && exitCode == 0) {
            QMessageBox::information(nullptr, QObject::tr("Cloning Finished"), QObject::tr("The repository has been successfully cloned."));
        }
        else if (errorMessage.contains("repository not found", Qt::CaseInsensitive)) {
            QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("The repository was not found. Please check the link."));
        }
        else if (errorMessage.contains("already exists and is not an empty directory.", Qt::CaseInsensitive)) {
            QProcess* gitPull = new QProcess();
            gitPull->setWorkingDirectory(fullPath);
            gitPull->start(gitPath(), QStringList() << "pull");
            gitPull->waitForFinished();

            QMessageBox::information(nullptr, QObject::tr("Cloning Finished"), QObject::tr("The repository has been successfully cloned."));
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Oops"), QObject::tr("Cloning the repository failed with an error:\n%1").arg(errorMessage));
        }

        process->deleteLater();
        });

    process->start(command);
}

///////////    Основные фукнции    ///////////

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

            command = gitPath() + " clone " + text + " repos/" + repoAuthor + "/" + repoName;

            QDir baseDir = QDir::current();
            QString fullPath = baseDir.absoluteFilePath("repos/"+repoAuthor + "/" + repoName);

            clone(command, fullPath);
        }
        else {
            QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("Incorrect link!"));
        }
        delay(1);
        updateReposTable(mainList);
    }
}

void urlFromClipboard(QTableWidget* mainList) {
    QInputDialog inputDialog;
    QString text = QGuiApplication::clipboard()->text().trimmed();
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

            command = gitPath() + " clone " + text + " repos/" + repoAuthor + "/" + repoName;

            QDir baseDir = QDir::current();
            QString fullPath = baseDir.absoluteFilePath("repos/"+repoAuthor + "/" + repoName);

            clone(command, fullPath);
        }
        else {
            QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("There is no link in the clipboard!"));
        }
        delay(1);
        updateReposTable(mainList);
    }
    else {
        QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("There is no link in the clipboard!"));
    }
}
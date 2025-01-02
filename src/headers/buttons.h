#pragma once
#include "settings.h"
#include "settsWindow.h"
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
QSize iconSize = QSize(25, 25);

void butts(QWidget* mainWindow, QApplication& a) {
    QTableWidget* mainList = new QTableWidget(0, 2, mainWindow);
    mainList->setHorizontalHeaderLabels(QStringList() << QObject::tr("Path") << QObject::tr("Link"));
    mainList->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    mainList->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    mainList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showTableWidget(mainList);

    QVBoxLayout* mainLayout = new QVBoxLayout(mainWindow);

    QHBoxLayout* hLayout = new QHBoxLayout();

    QToolButton* refreshButton = new QToolButton(mainWindow);
    refreshButton->setText(QObject::tr("Refresh"));
    refreshButton->setIcon(QIcon(":/NekoSource/img/refresh-uni.svg"));
    refreshButton->setIconSize(iconSize);
    refreshButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QObject::connect(refreshButton, &QToolButton::clicked, [&, mainList]() {
        updateReposTable(mainList);
    });
    refreshButton->show();

    QLabel* between = new QLabel("|");

    QToolButton* cloneButton = new QToolButton(mainWindow);
    cloneButton->setText(QObject::tr("Clone Repository"));
    cloneButton->setIcon(QIcon(":/NekoSource/img/plus-uni.svg"));
    cloneButton->setIconSize(iconSize);
    cloneButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QObject::connect(cloneButton, &QToolButton::clicked, [&, mainList]() {
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
            updateReposTable(mainList);
        }
        });
    cloneButton->show();

    QToolButton* settingsButton = new QToolButton(mainWindow);
    settingsButton->setText(QObject::tr("Settings"));
    settingsButton->setIcon(QIcon(":/NekoSource/img/settings-uni.svg"));
    settingsButton->setIconSize(iconSize);
    settingsButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QObject::connect(settingsButton, &QToolButton::clicked, [&]() {
        createSettingsWindow(a);
        });
    settingsButton->show();

    hLayout->addWidget(refreshButton);
    hLayout->addWidget(between);
    hLayout->addWidget(cloneButton);
    hLayout->addWidget(settingsButton);
    hLayout->setAlignment(Qt::AlignLeft);

    mainLayout->addLayout(hLayout);

    /* QTableWidget* mainList = new QTableWidget(0, 2, mainWindow);
    mainList->setHorizontalHeaderLabels(QStringList() << QObject::tr("Path") << QObject::tr("Link"));
    mainList->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    mainList->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    mainList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showTableWidget(mainList); */

    mainLayout->addWidget(mainList);
    mainLayout->setAlignment(Qt::AlignTop);

    mainWindow->setLayout(mainLayout);
}

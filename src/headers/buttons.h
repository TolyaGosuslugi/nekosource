#pragma once
#include "settings.h"
#include "settsWindow.h"
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
QSize iconSize = QSize(25, 25);

void butts(QWidget* mainWindow, QApplication& a) {
    QHBoxLayout* hLayout = new QHBoxLayout();

    QToolButton* cloneButton = new QToolButton(mainWindow); // Create new Tool Button in Main Window
    cloneButton->setText(QObject::tr("Clone Repository")); // Button text
    cloneButton->setIcon(QIcon(":/NekoSource/img/plus-uni.svg"));// + iconTheme + ".svg")); // Button icon
    cloneButton->setIconSize(iconSize); // Button size
    cloneButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // Text under icon
    QObject::connect(cloneButton, &QToolButton::clicked, [&]() { // Create action on click
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
                QMessageBox::warning(nullptr, QObject::tr("Warning"), QObject::tr("Incorrect link!"));
            }
        }
        });
    cloneButton->setProperty("iconName", "settings");
    cloneButton->show(); // Show button

    QToolButton* settingsButton = new QToolButton(mainWindow); // Create new Tool Button in Main Window
    settingsButton->setText(QObject::tr("Settings")); // Button text
    settingsButton->setIcon(QIcon(":/NekoSource/img/settings-uni.svg"));// + iconTheme + ".svg")); // Button icon
    settingsButton->setIconSize(iconSize); // Button size
    settingsButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // Text under icon
    QObject::connect(settingsButton, &QToolButton::clicked, [&]() {
        createSettingsWindow(a); // settsWindow.h
    });
    settingsButton->setProperty("iconName", "settings");
    settingsButton->show(); // Show button

    hLayout->addWidget(cloneButton);
    hLayout->addWidget(settingsButton);
    hLayout->setAlignment(Qt::AlignLeft);
    hLayout->setAlignment(Qt::AlignTop);
    mainWindow->setLayout(hLayout);
}
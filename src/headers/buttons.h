#pragma once
#include "settings.h"
#include "settsWindow.h"
#include "reposList.h"
#include "about.h"
#include "cloneButton.h"
#include "openIn.h"
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
    refreshButton->setIcon(QIcon(":/img/refresh-uni.svg"));
    refreshButton->setIconSize(iconSize);
    refreshButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QObject::connect(refreshButton, &QToolButton::clicked, [&, mainList]() {
        updateReposTable(mainList);
    });
    refreshButton->show();

    QLabel* between = new QLabel("|");

    QToolButton* cloneButton = new QToolButton(mainWindow);
    cloneButton->setText(QObject::tr("Clone Repository"));
    cloneButton->setIcon(QIcon(":/img/download-uni.svg"));
    cloneButton->setIconSize(iconSize);
    cloneButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QMenu* cloneMenu = new QMenu(cloneButton);
    QAction* enterManually = cloneMenu->addAction(QObject::tr("Enter Manually"));
    QAction* fromClipboard = cloneMenu->addAction(QObject::tr("Paste from Clipboard"));
    QObject::connect(enterManually, &QAction::triggered, [&, mainList]() {
        urlManually(mainList); // [cloneButton.h]
    });
    QObject::connect(fromClipboard, &QAction::triggered, [&, mainList]() {
        urlFromClipboard(mainList); // [cloneButton.h]
    });
    cloneButton->setMenu(cloneMenu);
    cloneButton->setPopupMode(QToolButton::InstantPopup);

    QToolButton* openInButton = new QToolButton(mainWindow);
    openInButton->setText(QObject::tr("Open in"));
    openInButton->setIcon(QIcon(":/img/external-link-uni.svg"));
    openInButton->setIconSize(iconSize);
    openInButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QMenu* openInMenu = new QMenu(openInButton);
    QAction* explorer = openInMenu->addAction(QObject::tr("Explorer"));
    explorer->setIcon(QIcon(":/img/folder-uni.svg"));
    QAction* cmd = openInMenu->addAction(QObject::tr("CMD"));
    cmd->setIcon(QIcon(":/img/terminal-uni.svg"));
    QObject::connect(explorer, &QAction::triggered, [&, mainList]() {
        inExplorer(mainList); // [openIn.h]
    });
    QObject::connect(cmd, &QAction::triggered, [&, mainList]() {
        inCMD(mainList); // [openIn.h]
    });
    openInButton->setMenu(openInMenu);
    openInButton->setPopupMode(QToolButton::InstantPopup);

    QToolButton* removeButton = new QToolButton(mainWindow);
    removeButton->setText(QObject::tr("Remove Selected"));
    removeButton->setIcon(QIcon(":/img/trash-uni.svg"));
    removeButton->setIconSize(iconSize);
    removeButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QObject::connect(removeButton, &QToolButton::clicked, [&, mainList, mainWindow]() {
        QItemSelectionModel* selectionModel = mainList->selectionModel();
        QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

        if (!selectedIndexes.isEmpty()) {
            int row = selectedIndexes.first().row();
            int column = 0;
            QTableWidgetItem* pathItem = mainList->item(row, column);

            QMessageBox::StandardButton areYouSure = QMessageBox::information(nullptr, QObject::tr("Wait"), QObject::tr("Are you sure?"), QMessageBox::Yes | QMessageBox::No);
            if (areYouSure == QMessageBox::Yes) {
                QString path = pathItem->text();
                QString command = "rmdir /s /q " + path;
                std::system(command.toStdString().c_str());

                delay(1);
                updateReposTable(mainList);
            }
        }
        else {
            QMessageBox::warning(nullptr, QObject::tr("Oops"), QObject::tr("No row selected!"));
        }

    });
    removeButton->show();

    QLabel* between2 = new QLabel("|");

    QToolButton* settingsButton = new QToolButton(mainWindow);
    settingsButton->setText(QObject::tr("Settings"));
    settingsButton->setIcon(QIcon(":/img/settings-uni.svg"));
    settingsButton->setIconSize(iconSize);
    settingsButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QObject::connect(settingsButton, &QToolButton::clicked, [&]() {
        createSettingsWindow(a);
    });
    settingsButton->show();

    QToolButton* aboutButton = new QToolButton(mainWindow);
    aboutButton->setText(QObject::tr("About"));
    aboutButton->setIcon(QIcon(":/img/info-uni.svg"));
    aboutButton->setIconSize(iconSize);
    aboutButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QObject::connect(aboutButton, &QToolButton::clicked, [&]() {
        showAboutWindow();
    });
    aboutButton->show();

    hLayout->addWidget(refreshButton);
    hLayout->addWidget(between);
    hLayout->addWidget(cloneButton);
    hLayout->addWidget(openInButton);
    hLayout->addWidget(removeButton);
    hLayout->addWidget(between2);
    hLayout->addWidget(settingsButton);
    hLayout->addWidget(aboutButton);
    hLayout->setAlignment(Qt::AlignLeft);

    mainLayout->addLayout(hLayout);

    mainLayout->addWidget(mainList);
    mainLayout->setAlignment(Qt::AlignTop);

    mainWindow->setLayout(mainLayout);
}

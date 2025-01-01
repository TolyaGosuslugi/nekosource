#pragma once
#include "settings.h"
#include <QComboBox>
#include <QSettings>
#include <QToolButton>
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QProcess>
QSettings sysSetts("TolyaGosuslugi", "NekoSource");
QString newLng;

void settsbutts(QWidget* settsWind, QApplication& a) {
    QString thm = sysSetts.value("theme", "dark").toString();
    QString lng = sysSetts.value("lang", "en_US").toString();
    QVBoxLayout* mainLayout = new QVBoxLayout(settsWind);

    // Language
    QHBoxLayout* langLayout = new QHBoxLayout();
    QLabel* langLabel = new QLabel(QObject::tr("Language"), settsWind);
    QToolButton* langButton = new QToolButton(settsWind);
    langButton->setText(lng);

    QMenu* lngMenu = new QMenu(langButton);
    QAction* en = lngMenu->addAction("en_US");
    QAction* ru = lngMenu->addAction("ru_RU");
    QObject::connect(en, &QAction::triggered, [&, langButton, lng]() {
        settings.setValue("lang", "en_US");
        langButton->setText(sysSetts.value("lang", "en_US").toString());
        QMessageBox::StandardButton reply = QMessageBox::information(nullptr, QObject::tr("Settings"), QObject::tr("Restart the program to take effect."), QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }
        });
    QObject::connect(ru, &QAction::triggered, [&, langButton, lng]() {
        settings.setValue("lang", "ru_RU");
        langButton->setText(sysSetts.value("lang", "en_US").toString());
        QMessageBox::StandardButton reply = QMessageBox::information(nullptr, QObject::tr("Settings"), QObject::tr("Restart the program to take effect."), QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }
        });

    langButton->setMenu(lngMenu);
    langButton->setPopupMode(QToolButton::InstantPopup);

    langLayout->addWidget(langLabel);
    langLayout->addWidget(langButton);
    langLayout->setSpacing(5);
    langLayout->setAlignment(Qt::AlignLeft);

    // Theme
    QHBoxLayout* thmLayout = new QHBoxLayout();
    QLabel* thmLabel = new QLabel(QObject::tr("Theme"), settsWind);
    QToolButton* thmButton = new QToolButton(settsWind);
    thmButton->setText(thm);

    QMenu* thmMenu = new QMenu(thmButton);
    QAction* light = thmMenu->addAction("light");
    QAction* dark = thmMenu->addAction("dark");
    QAction* darkpink = thmMenu->addAction("darkpink");
    QObject::connect(light, &QAction::triggered, [&, thmButton, thm]() {
        setLightTheme(a);
        settings.setValue("theme", "light");
        thmButton->setText(sysSetts.value("theme", "dark").toString());
        });
    QObject::connect(dark, &QAction::triggered, [&, thmButton, thm]() {
        setDarkTheme(a);
        settings.setValue("theme", "dark");
        thmButton->setText(sysSetts.value("theme", "dark").toString());
        });
    QObject::connect(darkpink, &QAction::triggered, [&, thmButton, thm]() {
        setDarkPinkTheme(a);
        settings.setValue("theme", "darkpink");
        thmButton->setText(sysSetts.value("theme", "dark").toString());
        });

    thmButton->setMenu(thmMenu);
    thmButton->setPopupMode(QToolButton::InstantPopup);

    thmLayout->addWidget(thmLabel);
    thmLayout->addWidget(thmButton);
    thmLayout->setSpacing(5);
    thmLayout->setAlignment(Qt::AlignLeft);



    mainLayout->addLayout(langLayout);
    mainLayout->addLayout(thmLayout);
    mainLayout->setAlignment(Qt::AlignTop);

    settsWind->setLayout(mainLayout);
    settsWind->show();
}

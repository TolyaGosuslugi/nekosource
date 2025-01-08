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
//QsysSetts sysSetts("TolyaGosuslugi", "NekoSource");
QString newLng;
QString newThm;
QString newColor;

void settsbutts(QWidget* settsWind, QApplication& a) {
    QSettings sysSetts("TolyaGosuslugi", "NekoSource");
    QString lng = sysSetts.value("lang", "en_US").toString();
    QString thm = sysSetts.value("theme", "dark").toString();
    QString color = settings.value("color", "default").toString();
    newLng = lng;
    newThm = thm;
    newColor = color;
    QVBoxLayout* mainLayout = new QVBoxLayout(settsWind);

    // Язык
    QHBoxLayout* langLayout = new QHBoxLayout();
    QLabel* langLabel = new QLabel(QObject::tr("Language"), settsWind);
    QToolButton* langButton = new QToolButton(settsWind);
    langButton->setText(lng);

    QMenu* lngMenu = new QMenu(langButton);
    QStringList languages = {"en_US", "ru_RU"};
    for (const QString& lang : languages) {
        QAction* action = lngMenu->addAction(lang);
        QObject::connect(action, &QAction::triggered, [lang, langButton]() {
            newLng = lang;
            langButton->setText(lang);
        });
    }
    langButton->setMenu(lngMenu);
    langButton->setPopupMode(QToolButton::InstantPopup);
    langLayout->addWidget(langLabel);
    langLayout->addWidget(langButton);
    langLayout->setSpacing(5);
    langLayout->setAlignment(Qt::AlignLeft);

    // Тема
    QHBoxLayout* thmLayout = new QHBoxLayout();
    QLabel* thmLabel = new QLabel(QObject::tr("Theme"), settsWind);
    QToolButton* thmButton = new QToolButton(settsWind);
    thmButton->setText(thm);

    QMenu* thmMenu = new QMenu(thmButton);
    QStringList themes = { "light", "dark" };
    for (const QString& theme : themes) {
        QAction* action = thmMenu->addAction(theme);
        QObject::connect(action, &QAction::triggered, [thmButton, theme]()  {
            newThm = theme;
            thmButton->setText(theme);
        });
    }
    thmButton->setMenu(thmMenu);
    thmButton->setPopupMode(QToolButton::InstantPopup);
    thmLayout->addWidget(thmLabel);
    thmLayout->addWidget(thmButton);
    thmLayout->setSpacing(5);
    thmLayout->setAlignment(Qt::AlignLeft);

    // Цветовая схема
    QHBoxLayout* colorLayout = new QHBoxLayout();
    QLabel* colorLabel = new QLabel(QObject::tr("Color"), settsWind);
    QToolButton* colorButton = new QToolButton(settsWind);
    colorButton->setText(color);

    QMenu* colorMenu = new QMenu(colorButton);
    QStringList colors = { "default", "pink", "blue", "green" };
    for (const QString& color : colors) {
        QAction* action = colorMenu->addAction(color);
        QObject::connect(action, &QAction::triggered, [color, colorButton]() {
            newColor = color;
            colorButton->setText(color);
        });
    }
    colorButton->setMenu(colorMenu);
    colorButton->setPopupMode(QToolButton::InstantPopup);
    colorLayout->addWidget(colorLabel);
    colorLayout->addWidget(colorButton);
    colorLayout->setSpacing(5);
    colorLayout->setAlignment(Qt::AlignLeft);

    // Нижние кнопки
    QVBoxLayout* buttsMain = new QVBoxLayout();
    QHBoxLayout* hButtons = new QHBoxLayout();
    QPushButton* ok = new QPushButton();
    ok->setText(QObject::tr("OK"));
    QObject::connect(ok, &QPushButton::clicked, [color, thm, lng]() {
        settings.setValue("lang", newLng);
        settings.setValue("theme", newThm);
        settings.setValue("color", newColor);


        QMessageBox::StandardButton reply = QMessageBox::information(
        nullptr, QObject::tr("Settings"), QObject::tr("Restart the program to take effect."),
        QMessageBox::Yes | QMessageBox::No
        );
        if (reply == QMessageBox::Yes) {
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }
    });
    QPushButton* cancel = new QPushButton();
    cancel->setText(QObject::tr("Cancel"));
    QObject::connect(cancel, &QPushButton::clicked, [settsWind]() {
        settsWind->close();
    });

    hButtons->addWidget(ok);
    hButtons->addWidget(cancel);
    buttsMain->addLayout(hButtons);
    buttsMain->setAlignment(Qt::AlignRight);

    mainLayout->addLayout(langLayout);
    mainLayout->addLayout(thmLayout);
    mainLayout->addLayout(colorLayout);
    mainLayout->addLayout(hButtons);
    mainLayout->addLayout(buttsMain);
    mainLayout->setAlignment(Qt::AlignTop);

    settsWind->setLayout(mainLayout);
    settsWind->show();
}

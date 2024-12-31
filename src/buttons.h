#pragma once
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

void butts(QWidget *pizdadeda, QApplication &a) {

    QToolButton *toolButton1 = new QToolButton(pizdadeda);
    toolButton1->setText("Clone Repository");
    toolButton1->setIcon(QIcon(":/NekoSource/tuka.png"));
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
            QString repoAuthor;
            QString repoName;
            if (parts.first() == "github.com" || parts.first() == "gitlab.com" || parts.first() == "codeberg.org" || parts.first() == "gitea.com") {
                text = "https://" + text;
                parts = text.split('/');
                repoAuthor = parts[3];
                repoName = parts[4];
            }
            else {
                QMessageBox::warning(nullptr, "Warning", "Incorrect link!");
            }
            if (parts.first() == "https:" && parts[1] == "github.com") {
                QString command = "git clone " + text + " repos/" + repoAuthor + "/" + repoName;
                QProcess* process = new QProcess(newWindow);
                process->startDetached(command);
            }
        }
    });
    toolButton1->show();


    QToolButton* toolButton2 = new QToolButton(pizdadeda);
    toolButton2->setText("Dark Theme");
    toolButton2->setIcon(QIcon(":/NekoSource/kesha.png"));
    toolButton2->setIconSize(QSize(50, 50));
    toolButton2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QObject::connect(toolButton2, &QToolButton::clicked, [&]() {
        QPalette p = a.palette();
        p.setColor(QPalette::Window, QColor(53, 53, 53));
        p.setColor(QPalette::Button, QColor(53, 53, 53));
        p.setColor(QPalette::Highlight, QColor(51, 150, 255));
        p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
        p.setColor(QPalette::WindowText, QColor(255, 255, 255));
        a.setPalette(p); //dark theme
    });
    toolButton2->move(100, 0);
    toolButton2->show();
}
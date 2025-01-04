#include "NekoSource.h"
#include "headers/buttons.h"
#include "headers/settings.h"
#include "headers/reposList.h"
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QSize>
#include <QLayout>
#include <QWidget>
#include <QStyleFactory>
#include <QLineEdit>
#include <QTextCodec>
#include <QSettings>
#include <QList>
#include <QLabel>
#include <QListWidget>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("TolyaGosuslugi");
    QCoreApplication::setOrganizationDomain("https://github.com/TolyaGosuslugi");
    QCoreApplication::setApplicationName("NekoSource");

    QApplication a(argc, argv);
    QWidget* mainWindw = new QWidget(); // Create main window
    mainWindw->setMinimumSize(1000, 650); // Set minimum window size 1000x650

    loadSettings(a); // [settings.h] Load Settings from redegit

    QSettings settings("TolyaGosuslugi", "NekoSource");
    QString lang = settings.value("lang", "en_US").toString();
    QTranslator translator;
    a.removeTranslator(&translator);
    translator.load(":/NekoSource/translations/" + lang + ".qm");
    a.installTranslator(&translator);

    butts(mainWindw, a); // [buttons.h] Create Buttons in Main Window || [reposList.h] Show List of repos

    //mainWindw->setWindowIcon(QIcon(":/NekoSource/img/icon.jpg")); // Set app icon
    mainWindw->show(); // Show Main Window

    a.setStyle(QStyleFactory::create("Fusion")); // Set theme style Fusion

    return a.exec();

    //run in Qt cmd after compile: windeployqt "path-to-nekosource.exe"

    //to generate lang: 
    // 1. lupdate main.cpp headers\buttons.h headers\settings.h headers\settsButtons.h headers\settsWindow.h headers\reposList.h headers\about.h -ts translations/ru_RU.ts
    // 2. linguist translations/ru_RU.ts
    // 3. lrelease translations/ru_RU.ts
}

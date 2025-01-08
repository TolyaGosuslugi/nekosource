#include "NekoSource.h"
#include "headers/buttons.h"
#include "headers/settings.h"
#include "headers/reposList.h"
#include "headers/monthCheck.h"
//#include "headers/snowParticles.h"
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
#include <QMediaPlayer>
#include <QMediaPlaylist>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("TolyaGosuslugi");
    QCoreApplication::setOrganizationDomain("https://github.com/TolyaGosuslugi");
    QCoreApplication::setApplicationName("NekoSource");

    QApplication a(argc, argv);
    QWidget* mainWindw = new QWidget(); // Основное окно
    mainWindw->setMinimumSize(1000, 650); // Установка минимального разрешения: 1000х650

    loadSettings(a); // [settings.h] Загрузка настроек из реестра

    QSettings settings("TolyaGosuslugi", "NekoSource");
    QString lang = settings.value("lang", "en_US").toString();
    QTranslator translator;
    a.removeTranslator(&translator);
    translator.load(":/translations/" + lang + ".qm");
    a.installTranslator(&translator);

    //QString month = getMonthTheme();
    //if (month == "Winter") {
    //    SnowParticles* snowEffect = new SnowParticles(mainWindw);
    //    snowEffect->setGeometry(0, 0, mainWindw->width(), mainWindw->height());
    //    snowEffect->startSnowfall();
    //}
    // код на снег, сгенерированный ChatGPT. надеюсь, перепишу

    // фоновая музычка
    QMediaPlaylist* playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/audio/bgm.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer* music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(15);
    music->play();

    butts(mainWindw, a); // [buttons.h] Создание кнопок в основном || [reposList.h] Список репозиторий

    //mainWindw->setWindowIcon(QIcon(":/NekoSource/img/icon.jpg")); // Иконка основного окна
    mainWindw->show(); // Показ основного окна

    a.setStyle(QStyleFactory::create("Fusion")); // Стиль темы: Fusion

    return a.exec();

    //после компиля основного exe'шника запустить в Qt терминале: windeployqt "path-to-nekosource.exe"

    //для обновы языка: 
    // 1. cd C:\Users\User\source\repos\NekoSource\NekoSource\src
    // 2. lupdate main.cpp headers\buttons.h headers\settings.h headers\settsButtons.h headers\settsWindow.h headers\reposList.h headers\about.h headers\cloneButton.h headers\openIn.h -ts translations/ru_RU.ts
    // 3. linguist translations/ru_RU.ts
    // 4. lrelease translations/ru_RU.ts
}

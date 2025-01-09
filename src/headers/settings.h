#pragma once
#include <QSettings>
#include <QToolButton>
#include <QTranslator>
#include <QMessageBox>
#include <filesystem>
#include <QList>
QSettings settings("TolyaGosuslugi", "NekoSource");
QString theme = settings.value("theme", "dark").toString();
QString color = settings.value("color", "default").toString();
QString lang = settings.value("lang", "en_US").toString();
QString iconTheme;

/* void updateIcons(QWidget* mainWindow) {
	QList<QToolButton*> buttons = mainWindow->findChildren<QToolButton*>();
	for (QToolButton* button : buttons) {
		QString iconPath = button->property("iconName").toString();
		if (!iconPath.isEmpty()) {
			button->setIcon(QIcon(":/NekoSource/img/" + iconPath + "-" + iconTheme + ".svg"));
		}
	}
} */
// TODO: icon color update
// 08.01.2025 18:18 - now the theme changes after restart, the icon color can be changed according to the theme

void loadSettings(QApplication &a) {
	// проверка имеется ли папка для реп
	if (!std::filesystem::exists("repos")) {
		std::filesystem::create_directory("repos");
	}

	// set theme from regedit
    if (theme == "dark") {
	iconTheme = "light";
        if (color == "default") {
            QPalette p = a.palette();
            p.setColor(QPalette::Window, QColor(53, 53, 53));
            p.setColor(QPalette::Button, QColor(53, 53, 53));
            p.setColor(QPalette::Highlight, QColor(0, 120, 215));
            p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
            p.setColor(QPalette::WindowText, QColor(255, 255, 255));
            p.setColor(QPalette::Text, QColor(255, 255, 255));
            p.setColor(QPalette::Base, QColor(53, 53, 53));
            p.setColor(QPalette::Link, QColor(0, 150, 255));
            a.setPalette(p);
        }
        else if (color == "pink") {
            QPalette p = a.palette();
            p.setColor(QPalette::Window, QColor(54, 33, 52));
            p.setColor(QPalette::Button, QColor(88, 48, 72));
            p.setColor(QPalette::Highlight, QColor(138, 43, 91));
            p.setColor(QPalette::ButtonText, QColor(255, 220, 240));
            p.setColor(QPalette::WindowText, QColor(240, 190, 215));
            p.setColor(QPalette::Text, QColor(255, 220, 240));
            p.setColor(QPalette::Base, QColor(54, 33, 52));
            p.setColor(QPalette::Link, QColor(200, 80, 120));
            a.setPalette(p);
        }
        else if (color == "blue") {
            QPalette p = a.palette();
            p.setColor(QPalette::Window, QColor(30, 34, 58));
            p.setColor(QPalette::Button, QColor(45, 50, 80));
            p.setColor(QPalette::Highlight, QColor(70, 80, 130));
            p.setColor(QPalette::ButtonText, QColor(200, 220, 255));
            p.setColor(QPalette::WindowText, QColor(180, 200, 240));
            p.setColor(QPalette::Text, QColor(200, 220, 255));
            p.setColor(QPalette::Base, QColor(30, 34, 58));
            p.setColor(QPalette::Link, QColor(90, 150, 250));
            a.setPalette(p);
        }
        else if (color == "green") {
            QPalette p = a.palette();
            p.setColor(QPalette::Window, QColor(25, 45, 35));
            p.setColor(QPalette::Button, QColor(40, 60, 50));
            p.setColor(QPalette::Highlight, QColor(70, 120, 90));
            p.setColor(QPalette::ButtonText, QColor(200, 250, 220));
            p.setColor(QPalette::WindowText, QColor(180, 240, 200));
            p.setColor(QPalette::Text, QColor(200, 250, 220));
            p.setColor(QPalette::Base, QColor(25, 45, 35));
            p.setColor(QPalette::Link, QColor(90, 200, 120));
            a.setPalette(p);
        }
    }
    else if (theme == "light") {
	iconTheme = "dark";
        if (color == "default") {
            QPalette p = a.palette();
            p.setColor(QPalette::Window, QColor(240, 240, 240));
            p.setColor(QPalette::Button, QColor(246, 246, 246));
            p.setColor(QPalette::Highlight, QColor(0, 120, 215));
            p.setColor(QPalette::ButtonText, QColor(0, 0, 0));
            p.setColor(QPalette::WindowText, QColor(0, 0, 0));
            p.setColor(QPalette::Text, QColor(0, 0, 0));
            p.setColor(QPalette::Base, QColor(240, 240, 240));
            p.setColor(QPalette::Link, QColor(0, 0, 255));
            a.setPalette(p);
        }
        else if (color == "pink") {
            QPalette p = a.palette();
            p.setColor(QPalette::Window, QColor(255, 230, 240));
            p.setColor(QPalette::Button, QColor(255, 210, 225));
            p.setColor(QPalette::Highlight, QColor(255, 182, 193));
            p.setColor(QPalette::ButtonText, QColor(120, 40, 70));
            p.setColor(QPalette::WindowText, QColor(100, 50, 80));
            p.setColor(QPalette::Text, QColor(100, 50, 80));
            p.setColor(QPalette::Base, QColor(255, 225, 235));
            p.setColor(QPalette::Link, QColor(255, 105, 180));
            a.setPalette(p);
        }
        else if (color == "blue") {
            QPalette p = a.palette();
            p.setColor(QPalette::Window, QColor(220, 230, 255));
            p.setColor(QPalette::Button, QColor(190, 210, 250));
            p.setColor(QPalette::Highlight, QColor(130, 170, 255));
            p.setColor(QPalette::ButtonText, QColor(40, 60, 100));
            p.setColor(QPalette::WindowText, QColor(30, 50, 80));
            p.setColor(QPalette::Text, QColor(30, 50, 80));
            p.setColor(QPalette::Base, QColor(210, 230, 255));
            p.setColor(QPalette::Link, QColor(60, 120, 240));
            a.setPalette(p);
        }
        else if (color == "green") {
            QPalette p = a.palette();
            p.setColor(QPalette::Window, QColor(220, 255, 240));
            p.setColor(QPalette::Button, QColor(190, 240, 210));
            p.setColor(QPalette::Highlight, QColor(130, 220, 170));
            p.setColor(QPalette::ButtonText, QColor(30, 70, 50));
            p.setColor(QPalette::WindowText, QColor(20, 60, 40));
            p.setColor(QPalette::Text, QColor(20, 60, 40));
            p.setColor(QPalette::Base, QColor(210, 255, 230));
            p.setColor(QPalette::Link, QColor(80, 180, 100));
            a.setPalette(p);
        }
    }
}
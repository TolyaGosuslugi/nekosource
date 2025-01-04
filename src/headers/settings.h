#pragma once
#include <QSettings>
#include <QToolButton>
#include <QTranslator>
#include <QMessageBox>
#include <filesystem>
#include <QList>
QSettings settings("TolyaGosuslugi", "NekoSource");
QString theme = settings.value("theme", "dark").toString();
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

void setDarkTheme(QApplication& a) {
    iconTheme = "light";
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

void setDarkPinkTheme(QApplication& a) {
    iconTheme = "light";
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

void setLightTheme(QApplication& a) {
    iconTheme = "dark";
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




void loadSettings(QApplication &a) {
	// check repos folder
	if (!std::filesystem::exists("repos")) {
		std::filesystem::create_directory("repos");
	}

	// set theme from regedit
	if (theme == "dark") {
		setDarkTheme(a);
	}
	else if (theme == "darkpink") {
		setDarkPinkTheme(a);
	}
	else if (theme == "light") {
		setLightTheme(a);
	}
}
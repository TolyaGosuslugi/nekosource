#pragma once
#include <QSettings>
#include <QTranslator>
QSettings settings("TolyaGosuslugi", "NekoSource");
QString theme = settings.value("theme", "dark").toString();
QString lang = settings.value("lang", "en_US").toString();
QString iconTheme;

void setDarkTheme(QApplication& a) {
	iconTheme = "light";
	QPalette p = a.palette();
	p.setColor(QPalette::Window, QColor(53, 53, 53));
	p.setColor(QPalette::Button, QColor(53, 53, 53));
	p.setColor(QPalette::Highlight, QColor(0, 120, 215));
	p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
	p.setColor(QPalette::WindowText, QColor(255, 255, 255));
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
	a.setPalette(p);
}


void loadSettings(QApplication &a) {
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
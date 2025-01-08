#include <QDate>

QString getMonthTheme() {
    QDate currentDate = QDate::currentDate();
    int month = currentDate.month();

    switch (month) {
    case 12:
    case 1:
    case 2:
        return "Winter";
    default:
        return "No bg effect";
    }
}

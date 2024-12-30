#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_NekoSource.h"

class NekoSource : public QMainWindow
{
    Q_OBJECT

public:
    NekoSource(QWidget *parent = nullptr);
    ~NekoSource();

private:
    Ui::NekoSourceClass ui;
};

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MiaInterface.h"

class MiaInterface : public QMainWindow
{
	Q_OBJECT

public:
	MiaInterface(QWidget* parent = Q_NULLPTR);

private:
	Ui::MiaInterfaceClass ui;
};

#pragma once

#include <array>
#include <vector>

#include <QtWidgets/QMainWindow>
#include "ui_MiaInterface.h"

#include "DigitViewer.h"

class MiaInterface : public QMainWindow
{
	Q_OBJECT

public:
	MiaInterface(QWidget* parent = Q_NULLPTR);
	virtual ~MiaInterface();

private:
	void ChangeDigit(int value);

	Ui::MiaInterfaceClass ui;

	DigitViewer* m_pDigitViewer;

	std::vector<std::array<std::vector<double>, 2>> m_vavdTrainData;
	std::vector<std::array<std::vector<double>, 2>> m_vavdEvaluationData;
	std::vector<std::array<std::vector<double>, 2>> m_vavdTestData;

	std::vector<std::vector<double>> m_vvdDigits;
};

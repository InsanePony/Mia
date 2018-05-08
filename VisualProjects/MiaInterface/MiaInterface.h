#pragma once

#include <array>
#include <vector>

#include <QtWidgets/QMainWindow>
#include "ui_MiaInterface.h"

#include "DigitDrawer.h"
#include "DigitViewer.h"
#include "Network.h"

class MiaInterface : public QMainWindow
{
	Q_OBJECT

public:
	MiaInterface(QWidget* parent = Q_NULLPTR);
	virtual ~MiaInterface();

private:
	void CreateNetwork();
	void LoadNetwork();

	void NewEntry();
	void TestNewEntry(QImage* image);

	void ChangeDigit(int value);
	void AskMia();

	Ui::MiaInterfaceClass ui;

	Network* m_pNetwork;

	DigitDrawer* m_pDigitDrawer;

	DigitViewer* m_pDigitViewer;
	DigitViewer* m_pMiaResponse;

	QPushButton* m_pAskMiaButton;

	int currDigitIndex;

	std::vector<std::array<std::vector<double>, 2>> m_vavdTrainData;
	std::vector<std::array<std::vector<double>, 2>> m_vavdEvaluationData;
	std::vector<std::array<std::vector<double>, 2>> m_vavdTestData;

	std::vector<std::vector<double>> m_vvdDigits;
};

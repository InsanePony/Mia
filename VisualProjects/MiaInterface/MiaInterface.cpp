#include "MiaInterface.h"
#include "DataLoader.h"

MiaInterface::MiaInterface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	DataLoader* loader = new DataLoader();

	std::vector<std::array<std::vector<double>, 2>> data = loader->LoadData("../../MNIST data/train-data-pixels-value", "../../MNIST data/train-data-numbers", 60000);

	m_vavdTrainData = std::vector<std::array<std::vector<double>, 2>>(data.begin(), data.begin() + 50000);
	m_vavdEvaluationData =  std::vector<std::array<std::vector<double>, 2>>(data.begin() + 50000, data.end());
	m_vavdTestData = loader->LoadData("../../MNIST data/test-data-pixels-value", "../../MNIST data/test-data-numbers", 10000);

	for (int idx = 0; idx < 60000; ++idx)
		m_vvdDigits.push_back(data[idx][0]);
	for (int idx = 0; idx < 10000; ++idx)
		m_vvdDigits.push_back(m_vavdTestData[idx][0]);

	m_pDigitViewer = new DigitViewer(ui.digit, ui.digitSpinBox);
	m_pDigitViewer->ShowDigit(m_vavdTrainData[0][0]);

	QObject::connect(ui.digitSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MiaInterface::ChangeDigit);
}
MiaInterface::~MiaInterface()
{
	delete m_pDigitViewer;
}

void MiaInterface::ChangeDigit(int value)
{
	m_pDigitViewer->ShowDigit(m_vvdDigits[value]);
}

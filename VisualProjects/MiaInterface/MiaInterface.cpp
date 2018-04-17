#include "MiaInterface.h"
#include "DataLoader.h"
#include "qfiledialog.h"

MiaInterface::MiaInterface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_pNetwork = nullptr;

	DataLoader* loader = new DataLoader();

	std::vector<std::array<std::vector<double>, 2>> data = loader->LoadData("../../MNIST data/train-data-pixels-value", "../../MNIST data/train-data-numbers", 60000);

	m_vavdTrainData = std::vector<std::array<std::vector<double>, 2>>(data.begin(), data.begin() + 50000);
	m_vavdEvaluationData =  std::vector<std::array<std::vector<double>, 2>>(data.begin() + 50000, data.end());
	m_vavdTestData = loader->LoadData("../../MNIST data/test-data-pixels-value", "../../MNIST data/test-data-numbers", 10000);

	for (int idx = 0; idx < 60000; ++idx)
		m_vvdDigits.push_back(data[idx][0]);
	for (int idx = 0; idx < 10000; ++idx)
		m_vvdDigits.push_back(m_vavdTestData[idx][0]);

	m_pDigitViewer = new DigitViewer(ui.digit);
	m_pDigitViewer->ShowDigit(m_vavdTrainData[0][0]);

	m_pMiaResponse = new DigitViewer(ui.miaResponse);

	m_pAskMiaButton = ui.askMiaButton;

	QObject::connect(ui.digitSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MiaInterface::ChangeDigit);
	QObject::connect(ui.actionNewNetwork, &QAction::triggered, this, &MiaInterface::CreateNetwork);
	QObject::connect(ui.actionLoadNetwork, &QAction::triggered, this, &MiaInterface::LoadNetwork);
	QObject::connect(ui.askMiaButton, &QPushButton::pressed, this, &MiaInterface::AskMia);
}
MiaInterface::~MiaInterface()
{
	if (m_pNetwork)
		delete m_pNetwork;

	delete m_pDigitViewer;
	delete m_pMiaResponse;
}

void MiaInterface::CreateNetwork()
{

}
void MiaInterface::LoadNetwork()
{
	QString filePath = QFileDialog::getOpenFileName(this, "Open Network file", QDir::homePath(), "Network file (*.mia)");

	if (filePath.size() > 0)
	{
		m_pNetwork = new Network(new NetworkLoader(filePath.toLatin1().constData()));
		m_pAskMiaButton->setEnabled(true);
	}
}

void MiaInterface::ChangeDigit(int value)
{
	m_pDigitViewer->ShowDigit(m_vvdDigits[value]);
	currDigitIndex = value;
}
void MiaInterface::AskMia()
{
	m_pMiaResponse->ShowDigit(m_pNetwork->GetResponse(m_vvdDigits[currDigitIndex]));
}

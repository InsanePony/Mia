#include <functional>

#include "MiaInterface.h"
#include "DataLoader.h"
#include "DialogNetworkCreation.h"
#include "Utils.h"

#include "qfiledialog.h"
#include "qmessagebox.h"


MiaInterface::MiaInterface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_pNetwork = nullptr;

	m_pDigitDrawer = new DigitDrawer(this);

	DataLoader* loader = new DataLoader();

	std::string path;

	if (Utils::IsInVisual())
		path = "../..";
	else
		path = Utils::GetExePath();

	std::vector<std::array<std::vector<double>, 2>> data = loader->LoadData(path + "/MNIST data/train-data-pixels-value", path + "/MNIST data/train-data-numbers", 60000);

	m_vavdTrainData = std::vector<std::array<std::vector<double>, 2>>(data.begin(), data.begin() + 50000);
	m_vavdEvaluationData =  std::vector<std::array<std::vector<double>, 2>>(data.begin() + 50000, data.end());
	m_vavdTestData = loader->LoadData(path + "/MNIST data/test-data-pixels-value", path + "/MNIST data/test-data-numbers", 10000);

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
	QObject::connect(ui.actionNewEntry, &QAction::triggered, this, &MiaInterface::NewEntry);
	QObject::connect(ui.askMiaButton, &QPushButton::pressed, this, &MiaInterface::AskMia);
	QObject::connect(m_pDigitDrawer, &DigitDrawer::EntryFinished, this, &MiaInterface::TestNewEntry);
}
MiaInterface::~MiaInterface()
{
	if (m_pNetwork)
		delete m_pNetwork;

	delete m_pDigitDrawer;
	delete m_pDigitViewer;
	delete m_pMiaResponse;
}

void MiaInterface::CreateNetwork()
{
	QMessageBox::StandardButton saveFileQuestion = QMessageBox::question(this, "Mia Interface", "Save Network after ?", QMessageBox::Yes | QMessageBox::No);

	DialogNetworkCreation dialog(this, saveFileQuestion == QMessageBox::Yes);

	if (dialog.exec() == QDialog::Accepted)
	{
		dialog.hide();
		m_pAskMiaButton->setEnabled(false);

#undef GetForm
		m_pNetwork = new Network(dialog.GetForm(), dialog.GetFileName());
		m_pNetwork->OnLearningEnd(std::bind(&MiaInterface::NetworkFinishLearningPhase, this));
		m_pNetwork->StartLearning(m_vavdTrainData, dialog.GetNumberGenerations(), dialog.GetLearningRate(), dialog.GetBatchSize(), (dialog.GetTrackProgress()) ? m_vavdTestData : std::vector<std::array<std::vector<double>, 2>>());
	}
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

void MiaInterface::NewEntry()
{
	m_pDigitDrawer->Show();
}
void MiaInterface::TestNewEntry(QImage* image)
{
	if (m_pAskMiaButton->isEnabled())
	{
		QImage forMiaImage = image->scaled(28, 28, Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::FastTransformation);

		std::vector<double> imageAsData;
		imageAsData.resize(784);
		for (int idx = 0; idx < 784; ++idx)
		{
			int rowIdx = idx / 28;
			int columnIdx = idx % 28;

			imageAsData[idx] = (255 - forMiaImage.pixelColor(columnIdx, rowIdx).red()) / 255.0;
		}

		m_pMiaResponse->ShowDigit(m_pNetwork->GetResponse(imageAsData));
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

void MiaInterface::NetworkFinishLearningPhase()
{
	QMessageBox::StandardButton networkFinishInformation = QMessageBox::information(this, "Mia Interface", "Learning phase finished", QMessageBox::Ok);
	m_pAskMiaButton->setEnabled(true);
}

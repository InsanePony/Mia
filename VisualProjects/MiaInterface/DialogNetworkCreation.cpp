#include "DialogNetworkCreation.h"

#include "qmessagebox.h"
#include "qlabel.h"
#include "qdialogbuttonbox.h"
#include "qspinbox.h"
#include "qcheckbox.h"


DialogNetworkCreation::DialogNetworkCreation(QWidget* parent, bool withFileSave)
	: QDialog(parent)
{
	m_pForm = new QFormLayout(this);
	m_pForm->addRow(new QLabel("Network"));

	if (withFileSave)
	{
		QLineEdit* lineEdit = new QLineEdit(this);
		m_pForm->addRow("Filename", lineEdit);
		m_vpFields.push_back(lineEdit);

		m_uiNewFieldRow = 4;
	}
	else
		m_uiNewFieldRow = 3;

	QSpinBox* layerNumber = new QSpinBox(this);
	layerNumber->setValue(0);
	layerNumber->setRange(0, 5);
	QObject::connect(layerNumber, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &DialogNetworkCreation::LayerChange);
	m_pForm->addRow("Layer Number", layerNumber);
	m_vpFields.push_back(layerNumber);

	QLineEdit* inputLayerLine = new QLineEdit(this);
	inputLayerLine->setText("784");
	inputLayerLine->setDisabled(true);
	m_pForm->addRow("Input Layer", inputLayerLine);
	m_vpFields.push_back(inputLayerLine);

	QLineEdit* outputLayerLine = new QLineEdit(this);
	outputLayerLine->setText("10");
	outputLayerLine->setDisabled(true);
	m_pForm->addRow("Output Layer", outputLayerLine);
	m_vpFields.push_back(outputLayerLine);

	QSpinBox* numberGenerationsLine = new QSpinBox(this);
	numberGenerationsLine->setValue(0);
	numberGenerationsLine->setRange(1, 1000);
	m_pForm->addRow("Number of generations", numberGenerationsLine);
	m_vpFields.push_back(numberGenerationsLine);

	QSpinBox* batchSizeLine = new QSpinBox(this);
	batchSizeLine->setValue(0);
	batchSizeLine->setRange(1, 30000);
	m_pForm->addRow("Batch size", batchSizeLine);
	m_vpFields.push_back(batchSizeLine);

	QDoubleSpinBox* learningRateLine = new QDoubleSpinBox(this);
	learningRateLine->setValue(1.0);
	learningRateLine->setRange(0.1, 10.0);
	m_pForm->addRow("Learning rate", learningRateLine);
	m_vpFields.push_back(learningRateLine);

	QCheckBox* trackProgressCheckBox = new QCheckBox(this);
	m_pForm->addRow("Track Progress", trackProgressCheckBox);
	m_vpFields.push_back(trackProgressCheckBox);

	m_pDialogButton = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
	m_pForm->addRow(m_pDialogButton);

	QObject::connect(m_pDialogButton, SIGNAL(accepted()), this, SLOT(accept()));
	QObject::connect(m_pDialogButton, SIGNAL(rejected()), this, SLOT(reject()));

	m_uiLayerNumber = 0;
	m_bSave = withFileSave;
}
DialogNetworkCreation::~DialogNetworkCreation()
{
	delete m_pForm;

	for (int fieldIdx = 0; fieldIdx < m_vpFields.size(); ++fieldIdx)
	{
		if (m_vpFields[fieldIdx] != nullptr)
			delete m_vpFields[fieldIdx];
	}

	m_vpFields.clear();

	delete m_pDialogButton;
}

std::vector<unsigned int> DialogNetworkCreation::GetForm()
{
	std::vector<unsigned int> networkForm = std::vector<unsigned int>();

	networkForm.push_back(784);

	for (int idx = m_uiLayerNumber; idx > 0; --idx)
		networkForm.push_back(((QSpinBox*)m_vpFields[m_vpFields.size() - idx - 4])->value());

	networkForm.push_back(10);

	return networkForm;
}
std::string DialogNetworkCreation::GetFileName()
{
	return (m_bSave) ? ((QLineEdit*)m_vpFields[0])->text().toLatin1().toStdString() : "";
}
bool DialogNetworkCreation::GetTrackProgress()
{
	return ((QCheckBox*)m_vpFields[(m_bSave) ? 7 : 6])->isChecked();
}
unsigned int DialogNetworkCreation::GetNumberGenerations()
{
	return ((QSpinBox*)m_vpFields[(m_bSave) ? 4 : 3])->value();
}
unsigned int DialogNetworkCreation::GetBatchSize()
{
	return ((QSpinBox*)m_vpFields[(m_bSave) ? 5 : 4])->value();
}
double DialogNetworkCreation::GetLearningRate()
{
	return ((QDoubleSpinBox*)m_vpFields[(m_bSave) ? 6 : 5])->value();
}

void DialogNetworkCreation::LayerChange(int value)
{
	if (value > m_uiLayerNumber)
	{
		int toAdd = value - m_uiLayerNumber;
		for (int idx = 0; idx < toAdd; ++idx)
			AddLayer();
	}
	else
	{
		int toRemove = m_uiLayerNumber - value;
		for (int idx = 0; idx < toRemove; ++idx)
			RemoveLayer();
	}
}

void DialogNetworkCreation::AddLayer()
{
	QSpinBox* layerNumber = new QSpinBox(this);
	layerNumber->setValue(0);
	layerNumber->setRange(1, 1000);
	m_pForm->insertRow(m_uiNewFieldRow, QString("Layer %1").arg(m_uiLayerNumber + 1), layerNumber);
	m_vpFields.push_back(layerNumber);

	++m_uiNewFieldRow;
	++m_uiLayerNumber;
}
void DialogNetworkCreation::RemoveLayer()
{
	m_pForm->removeRow(m_pForm->count() - 2);
	m_vpFields.pop_back();
	--m_uiNewFieldRow;
	--m_uiLayerNumber;
}

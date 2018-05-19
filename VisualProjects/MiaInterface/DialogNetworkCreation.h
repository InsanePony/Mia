#pragma once

#include <vector>

#include "qdialog.h"
#include "qformlayout.h"
#include "qlineedit.h"
#include "qdialogbuttonbox.h"

class DialogNetworkCreation : public QDialog
{
	Q_OBJECT

public:
	DialogNetworkCreation() = delete;
	DialogNetworkCreation(DialogNetworkCreation const&) = delete;
	DialogNetworkCreation(QWidget* parent, bool withFileSave = false);
	virtual ~DialogNetworkCreation();

	std::vector<unsigned int> GetForm();
	std::string GetFileName();
	unsigned int GetNumberGenerations();
	unsigned int GetBatchSize();
	double GetLearningRate();
	bool GetTrackProgress();

private:
	void LayerChange(int value);

	void AddLayer();
	void RemoveLayer();

	QFormLayout* m_pForm;
	std::vector<QWidget*> m_vpFields;
	QDialogButtonBox* m_pDialogButton;

	unsigned int m_uiNewFieldRow;
	unsigned int m_uiLayerNumber;

	bool m_bSave;
};

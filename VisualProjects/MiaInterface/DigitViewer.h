#pragma once

#include "qobject.h"
#include "ui_MiaInterface.h"

class DigitViewer : public QObject
{
	Q_OBJECT

public:
	DigitViewer() = delete;
	DigitViewer(DigitViewer const&) = delete;
	DigitViewer(QGraphicsView* digitGraphicsView, QSpinBox* choiceSpinBox = nullptr);
	virtual ~DigitViewer();

	void ShowDigit(std::vector<double> digitAsData);

private:
	QGraphicsView* m_pDigitGraphicsView;
	QGraphicsScene* m_pDigitScene;

	QSpinBox* m_pDigitSpinBox;
};

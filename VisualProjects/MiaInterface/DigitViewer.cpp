#include "DigitViewer.h"

DigitViewer::DigitViewer(QGraphicsView* digitGraphicsView)
	: QObject()
{
	m_pDigitGraphicsView = digitGraphicsView;
	m_pDigitScene = nullptr;
}
DigitViewer::~DigitViewer()
{
	delete m_pDigitScene;
}

void DigitViewer::ShowDigit(std::vector<double> digitAsData)
{
	QImage digitAsImage = QImage(28, 28, QImage::Format::Format_ARGB32_Premultiplied);

	int digitSize = (int)digitAsData.size();
	for (int idx = 0; idx < digitSize; ++idx)
	{
		int rowIdx = idx / 28;
		int columnIdx = idx % 28;

		int color = (1.f - digitAsData[idx]) * 255;

		digitAsImage.setPixelColor(columnIdx, rowIdx, QColor(color, color, color));
	}

	int imageSize = m_pDigitGraphicsView->size().width() - 10;
	digitAsImage = digitAsImage.scaled(imageSize, imageSize, Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);

	if (m_pDigitScene)
		delete m_pDigitScene;

	m_pDigitScene = new QGraphicsScene(this);
	m_pDigitScene->addPixmap(QPixmap::fromImage(digitAsImage));
	m_pDigitScene->setSceneRect(digitAsImage.rect());

	m_pDigitGraphicsView->setScene(m_pDigitScene);
}
void DigitViewer::ShowDigit(int number)
{
	if (m_pDigitScene)
		delete m_pDigitScene;

	m_pDigitScene = new QGraphicsScene(this);

	std::string path = "../../Digits/";
	path.push_back('0' + number);
	path.append(".png");
	QImage digit = QImage(path.c_str());

	if (number == 4)
	{
		int imageSize = m_pDigitGraphicsView->size().width() - 10;
		digit = digit.scaled(imageSize, imageSize, Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::SmoothTransformation);
	}

	m_pDigitScene->addPixmap(QPixmap::fromImage(digit));
	m_pDigitScene->setSceneRect(digit.rect());

	m_pDigitGraphicsView->setScene(m_pDigitScene);
}

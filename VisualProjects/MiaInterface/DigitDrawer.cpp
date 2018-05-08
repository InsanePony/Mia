#include <QCloseEvent>

#include "DigitDrawer.h"
#include "qpainter.h"

DigitDrawer::DigitDrawer(QWidget* parent)
	: QWidget(parent, Qt::Window)
{
	m_pImage = new QImage(360, 360, QImage::Format::Format_ARGB32_Premultiplied);
	resize(360, 360);

	m_bDrawing = false;
	m_bEnterPressed = false;
	m_bEscapePressed = false;
}
DigitDrawer::~DigitDrawer()
{
	delete m_pImage;
}

void DigitDrawer::Show()
{
	m_pImage->fill(QColor(255, 255, 255));
	update();
	show();
}

void DigitDrawer::DrawLine(QPoint const& endPos)
{
	QPainter painter(m_pImage);

	/*QLinearGradient linearGrad = QLinearGradient(m_StartPos.x() - 10, m_StartPos.y(), endPos.x() + 10, m_StartPos.y());
	linearGrad.setColorAt(0, QColor(255, 255, 255));
	linearGrad.setColorAt(0.2f, QColor(0, 0, 0));
	linearGrad.setColorAt(0.8f, QColor(0, 0, 0));
	linearGrad.setColorAt(1.f, QColor(255, 255, 255));
	QBrush brush(linearGrad);
	painter.setPen(QPen(brush,
		20,
		Qt::PenStyle::SolidLine,
		Qt::PenCapStyle::RoundCap,
		Qt::PenJoinStyle::RoundJoin));*/

	painter.setPen(QPen(QBrush(QColor(0, 0, 0), Qt::BrushStyle::SolidPattern),
						20,
						Qt::PenStyle::SolidLine,
						Qt::PenCapStyle::RoundCap,
						Qt::PenJoinStyle::RoundJoin));
	painter.drawLine(m_StartPos, endPos);

	update(QRect(m_StartPos, endPos).normalized().adjusted(-10, -10, 10, 10));
	m_StartPos = endPos;
}

void DigitDrawer::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_StartPos = event->pos();
		m_bDrawing = true;
	}
}
void DigitDrawer::mouseMoveEvent(QMouseEvent* event)
{
	if ((event->buttons() & Qt::LeftButton) && m_bDrawing)
	{
		DrawLine(event->pos());
	}
}
void DigitDrawer::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && m_bDrawing)
	{
		DrawLine(event->pos());
		m_bDrawing = false;
	}
}

void DigitDrawer::keyPressEvent(QKeyEvent* event)
{
	if ((event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) && !m_bEnterPressed)
	{
		m_bEnterPressed = true;
		emit EntryFinished(m_pImage);
	}

	if (event->key() == Qt::Key_Escape && !m_bEscapePressed)
	{
		m_bEscapePressed = true;
		m_pImage->fill(QColor(255, 255, 255));
		update();
	}
}
void DigitDrawer::keyReleaseEvent(QKeyEvent* event)
{
	if ((event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) && m_bEnterPressed)
	{
		m_bEnterPressed = false;
	}

	if (event->key() == Qt::Key_Escape && m_bEscapePressed)
	{
		m_bEscapePressed = false;
	}
}

void DigitDrawer::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QRect rect = event->rect();
	painter.drawImage(rect, *m_pImage, rect);
}

void DigitDrawer::resizeEvent(QResizeEvent* event)
{

}
void DigitDrawer::closeEvent(QCloseEvent* event)
{
	event->ignore();

	hide();
}

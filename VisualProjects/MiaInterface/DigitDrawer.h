#pragma once

#include "qwidget.h"

class DigitDrawer : public QWidget
{
	Q_OBJECT

public:
	DigitDrawer(QWidget* parent = nullptr);
	DigitDrawer(DigitDrawer const&) = delete;
	virtual ~DigitDrawer();

	void Show();

signals:
	void EntryFinished(QImage* image);

private:
	void DrawLine(QPoint const& endPos);

	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

	void resizeEvent(QResizeEvent* event) override;
	void closeEvent(QCloseEvent* event) override;

	QImage* m_pImage;

	QPoint m_StartPos;
	bool m_bDrawing;

	bool m_bEnterPressed;
	bool m_bEscapePressed;
};

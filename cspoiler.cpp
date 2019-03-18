/*!
 \file cspoiler.cpp

*/

#include "cspoiler.h"

#include <QPropertyAnimation>


cSpoiler::cSpoiler(QWidget *parent) :
	QWidget(parent),
	m_animationDuration(300)
{
	m_toggleButton.setStyleSheet("QToolButton { border: none; }");
	m_toggleButton.setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	m_toggleButton.setArrowType(Qt::ArrowType::RightArrow);
	m_toggleButton.setText("");
	m_toggleButton.setCheckable(true);
	m_toggleButton.setChecked(false);

	m_headerLine.setFrameShape(QFrame::HLine);
	m_headerLine.setFrameShadow(QFrame::Sunken);
	m_headerLine.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

	m_contentArea.setStyleSheet("QScrollArea { border: none; }");
	m_contentArea.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	// start out collapsed
	m_contentArea.setMaximumHeight(0);
	m_contentArea.setMinimumHeight(0);
	// let the entire widget grow and shrink with its content
	m_toggleAnimation.addAnimation(new QPropertyAnimation(this, "minimumHeight"));
	m_toggleAnimation.addAnimation(new QPropertyAnimation(this, "maximumHeight"));
	m_toggleAnimation.addAnimation(new QPropertyAnimation(&m_contentArea, "maximumHeight"));
	// don't waste space
	m_mainLayout.setVerticalSpacing(0);
	m_mainLayout.setContentsMargins(0, 0, 0, 0);
	int row = 0;
	m_mainLayout.addWidget(&m_toggleButton, row, 0, 1, 1, Qt::AlignLeft);
	m_mainLayout.addWidget(&m_headerLine, row++, 2, 1, 1);
	m_mainLayout.addWidget(&m_contentArea, row, 0, 1, 3);
	setLayout(&m_mainLayout);
	QObject::connect(&m_toggleButton, &QToolButton::clicked, [this](const bool checked)
		{
			m_toggleButton.setArrowType(checked ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
			m_toggleAnimation.setDirection(checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
			m_toggleAnimation.start();
		});
}

void cSpoiler::setTitle(const QString& title)
{
	m_toggleButton.setText(title);
}

void cSpoiler::setContentLayout(QLayout& contentLayout)
{
	delete m_contentArea.layout();
	m_contentArea.setLayout(&contentLayout);
	const auto collapsedHeight = sizeHint().height() - m_contentArea.maximumHeight();
	auto contentHeight = contentLayout.sizeHint().height();
	for (int i = 0; i < m_toggleAnimation.animationCount() - 1; ++i)
	{
		QPropertyAnimation * spoilerAnimation = static_cast<QPropertyAnimation *>(m_toggleAnimation.animationAt(i));
		spoilerAnimation->setDuration(m_animationDuration);
		spoilerAnimation->setStartValue(collapsedHeight);
		spoilerAnimation->setEndValue(collapsedHeight + contentHeight);
	}
	QPropertyAnimation * contentAnimation = static_cast<QPropertyAnimation *>(m_toggleAnimation.animationAt(m_toggleAnimation.animationCount() - 1));
	contentAnimation->setDuration(m_animationDuration);
	contentAnimation->setStartValue(0);
	contentAnimation->setEndValue(contentHeight);
}

void cSpoiler::setContentWidget(QWidget* contentWidget)
{
	auto*	lpLayout = new QVBoxLayout();
	lpLayout->addWidget(contentWidget);
	setContentLayout(*lpLayout);
}

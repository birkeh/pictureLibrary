#include "csplashscreen.h"
#include "common.h"


cSplashScreen::cSplashScreen(const QPixmap& pixmap, QFont& font) :
	QSplashScreen(pixmap)
{
	setFont(font);
	m_textDocument.setDefaultFont(font);
}

void cSplashScreen::drawContents(QPainter *painter)
{
	painter->translate(m_rect.topLeft());
	m_textDocument.setHtml(m_szMessage);
	m_textDocument.drawContents(painter);
}

void cSplashScreen::showStatusMessage(const QString& message)
{
	m_szMessage	= message;
	showMessage(m_szMessage);
}

void cSplashScreen::addStatusMessage(const QString& message)
{
	m_szMessage.append(message);
	showMessage(m_szMessage);
}

void cSplashScreen::setMessageRect(QRect rect)
{
	m_rect			= rect;
	m_textDocument.setTextWidth(rect.width());
}

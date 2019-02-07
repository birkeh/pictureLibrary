#ifndef CSPLASHSCREEN_H
#define CSPLASHSCREEN_H


#include <QSplashScreen>
#include <QPainter>
#include <QTextDocument>


class cSplashScreen : public QSplashScreen
{
public:
	cSplashScreen(const QPixmap& pixmap, QFont &font);

	virtual void	drawContents(QPainter *painter);
	void			showStatusMessage(const QString &message);
	void			addStatusMessage(const QString &message);
	void			setMessageRect(QRect rect);

private:
	QTextDocument	m_textDocument;
	QString			m_szMessage;
	QRect			m_rect;
};

#endif // CSPLASHSCREEN_H

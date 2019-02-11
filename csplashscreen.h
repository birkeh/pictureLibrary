#ifndef CSPLASHSCREEN_H
#define CSPLASHSCREEN_H


#include <QSplashScreen>
#include <QPainter>
#include <QTextDocument>


/**
 * @brief
 *
 */
class cSplashScreen : public QSplashScreen
{
public:
	cSplashScreen(const QPixmap& pixmap, QFont &font);

	/**
	 * @brief
	 *
	 * @param painter
	 */
	virtual void	drawContents(QPainter *painter);
	/**
	 * @brief
	 *
	 * @param message
	 */
	void			showStatusMessage(const QString &message);
	/**
	 * @brief
	 *
	 * @param message
	 */
	void			addStatusMessage(const QString &message);
	/**
	 * @brief
	 *
	 * @param rect
	 */
	void			setMessageRect(QRect rect);

private:
	QTextDocument	m_textDocument;	/**< TODO: describe */
	QString			m_szMessage;	/**< TODO: describe */
	QRect			m_rect;			/**< TODO: describe */
};

#endif // CSPLASHSCREEN_H

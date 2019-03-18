/*!
 \file cspoiler.h

*/

#ifndef CSPOILER_H
#define CSPOILER_H


#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>


/*!
 \brief

 \class cSpoiler cspoiler.h "cspoiler.h"
*/
class cSpoiler : public QWidget
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cSpoiler
	 \param parent
	*/
	explicit cSpoiler(QWidget *parent = nullptr);

	/*!
	 \brief

	 \fn setTitle
	 \param title
	*/
	void					setTitle(const QString& title);
	/*!
	 \brief

	 \fn setContentLayout
	 \param contentLayout
	*/
	void					setContentLayout(QLayout& contentLayout);
	/*!
	 \brief

	 \fn setContentWidget
	 \param contentWidget
	*/
	void					setContentWidget(QWidget* contentWidget);

signals:

public slots:

private:
	QGridLayout				m_mainLayout;				/*!< TODO: describe */
	QToolButton				m_toggleButton;				/*!< TODO: describe */
	QFrame					m_headerLine;				/*!< TODO: describe */
	QParallelAnimationGroup	m_toggleAnimation;			/*!< TODO: describe */
	QScrollArea				m_contentArea;				/*!< TODO: describe */
	int						m_animationDuration{300};	/*!< TODO: describe */
};

#endif // CSPOILER_H

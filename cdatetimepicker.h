/*!
 \file cdatetimepicker.h

*/

#ifndef CDATETIMEPICKER_H
#define CDATETIMEPICKER_H


#include <QDialog>
#include <QImage>


namespace Ui {
class cDateTimePicker;
}

/*!
 \brief

 \class cDateTimePicker cdatetimepicker.h "cdatetimepicker.h"
*/
class cDateTimePicker : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cDateTimePicker
	 \param parent
	*/
	explicit cDateTimePicker(QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cDateTimePicker
	*/
	~cDateTimePicker();

	/*!
	 \brief

	 \fn setText
	 \param szText
	*/
	void					setText(const QString& szText);
	/*!
	 \brief

	 \fn setImage
	 \param image
	*/
	void					setImage(const QImage& image);
	/*!
	 \brief

	 \fn setDateTime
	 \param dateTime
	*/
	void					setDateTime(const QDateTime dateTime);
	/*!
	 \brief

	 \fn dateTime
	 \return QDateTime
	*/
	QDateTime				dateTime();
private:
	Ui::cDateTimePicker*	ui;					/*!< TODO: describe */
};

#endif // CDATETIMEPICKER_H

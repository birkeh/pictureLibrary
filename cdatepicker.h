/*!
 \file cdatepicker.h

*/

#ifndef CDATEPICKER_H
#define CDATEPICKER_H


#include <QDialog>
#include <QImage>


namespace Ui {
class cDatePicker;
}

/*!
 \brief

 \class cDatePicker cdatepicker.h "cdatepicker.h"
*/
class cDatePicker : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cDatePicker
	 \param parent
	*/
	explicit cDatePicker(QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cDatePicker
	*/
	~cDatePicker();

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

	 \fn setDate
	 \param date
	*/
	void					setDate(const QDate date);
	/*!
	 \brief

	 \fn date
	 \return QDate
	*/
	QDate				date();

private:
	Ui::cDatePicker *ui; /*!< TODO: describe */
};

#endif // CDATEPICKER_H

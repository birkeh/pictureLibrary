/*!
 \file ccombopicker.h

*/

#ifndef CCOMBOPICKER_H
#define CCOMBOPICKER_H

#include <QDialog>

namespace Ui {
class cComboPicker;
}

/*!
 \brief

 \class cComboPicker ccombopicker.h "ccombopicker.h"
*/
class cComboPicker : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cComboPicker
	 \param parent
	*/
	explicit cComboPicker(QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cComboPicker
	*/
	~cComboPicker();

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

	 \fn setList
	 \param list
	*/
	void					setList(const QStringList& list);
	/*!
	 \brief

	 \fn setEditable
	 \param editable
	*/
	void					setEditable(bool editable);
	/*!
	 \brief

	 \fn setSelection
	 \param image
	*/
	void					setSelection(const QString& selection);
	/*!
	 \brief

	 \fn selection
	 \return QString
	*/
	QString					selection();

private:
	Ui::cComboPicker *ui; /*!< TODO: describe */
};

#endif // CCOMBOPICKER_H

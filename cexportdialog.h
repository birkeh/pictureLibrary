/*!
 \file cexportdialog.h

*/

#ifndef CEXPORTDIALOG_H
#define CEXPORTDIALOG_H


#include <QDialog>
#include <QCloseEvent>


namespace Ui {
class cExportDialog;
}

/*!
 \brief

 \class cExportDialog cexportdialog.h "cexportdialog.h"
*/
class cExportDialog : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cExportDialog
	 \param parent
	*/
	explicit cExportDialog(QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cExportDialog
	*/
	~cExportDialog();

private slots:
	/*!
	 \brief

	 \fn onPathSelect
	*/
	void							onPathSelect();

private:
	Ui::cExportDialog*			ui; /*!< TODO: describe */

	/*!
	 \brief

	 \fn initUI
	*/
	void							initUI();
	/*!
	 \brief

	 \fn createActions
	*/
	void							createActions();

	/*!
	 \brief

	 \fn accept
	*/
	void							accept();
	/*!
	 \brief

	 \fn reject
	*/
	void							reject();

	/*!
	 \brief

	 \fn savePosition
	*/
	void							savePosition();
};

#endif // CEXPORTDIALOG_H

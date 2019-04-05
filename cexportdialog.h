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
	enum EXPORT_TYPE
	{
		EXPORT_TYPE_ALL			= 1,
		EXPORT_TYPE_SELECTION	= 2,
		EXPORT_TYPE_FILTER		= 3,
	};

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

	/*!
	 \brief

	 \fn path
	*/
	QString							path();
	/*!
	 \brief

	 \fn exportType
	*/
	EXPORT_TYPE						exportType();
	/*!
	 \brief

	 \fn filePattern
	*/
	QString							filePattern();
	/*!
	 \brief

	 \fn structurePattern
	*/
	QString							structurePattern();

private slots:
	/*!
	 \brief

	 \fn onPathSelect
	*/
	void							onPathSelect();
	/*!
	 \brief

	 \param text
	 \fn onFilePathChanged
	*/
	void							onPathChanged(const QString& text);
	/*!
	 \brief

	 \param selected
	 \fn onFileOriginalClicked
	*/
	void							onFileOriginalClicked(bool selected);
	/*!
	 \brief

	 \param selected
	 \fn onFilePatternClicked
	*/
	void							onFilePatternClicked(bool selected);
	/*!
	 \brief

	 \param text
	 \fn onFilePatternChanged
	*/
	void							onFilePatternChanged(const QString& text);
	/*!
	 \brief

	 \param selected
	 \fn onStructureOriginalClicked
	*/
	void							onStructureOriginalClicked(bool selected);
	/*!
	 \brief

	 \param selected
	 \fn onStructurePatternClicked
	*/
	void							onStructurePatternClicked(bool selected);
	/*!
	 \brief

	 \param text
	 \fn onStructurePatternChanged
	*/
	void							onStructurePatternChanged(const QString& text);

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

	 \fn checkAccept
	*/
	void							checkAccept();

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

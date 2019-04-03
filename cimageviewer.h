#ifndef CIMAGEVIEWER_H
#define CIMAGEVIEWER_H


#include "cpicture.h"
#include "cimage.h"

#include <QDialog>


namespace Ui {
class cImageViewer;
}

class cImageViewer : public QDialog
{
	Q_OBJECT

public:
	explicit cImageViewer(QWidget *parent = nullptr);
	~cImageViewer();

	void					setPicture(QString szNumber, QString szRootPath, cPicture* lpPicture);
private:
	Ui::cImageViewer*		ui;
	cImage*					m_lpImage;

protected:

private slots:
	/*!
	 \brief

	 \fn onImageNext
	*/
	void					onImageNext();
	/*!
	 \brief

	 \fn onImagePrev
	*/
	void					onImagePrev();
	/*!
	 \brief

	 \fn onImageLast
	*/
	void					onImageLast();
	/*!
	 \brief

	 \fn onImageFirst
	*/
	void					onImageFirst();

signals:
	/*!
	 \brief

	 \fn imageNext
	*/
	void					imageNext();
	/*!
	 \brief

	 \fn imagePrev
	*/
	void					imagePrev();
	/*!
	 \brief

	 \fn imageLast
	*/
	void					imageLast();
	/*!
	 \brief

	 \fn imageFirst
	*/
	void					imageFirst();
};

#endif // CIMAGEVIEWER_H

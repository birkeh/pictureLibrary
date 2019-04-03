#ifndef CIMAGEVIEWER_H
#define CIMAGEVIEWER_H


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

	void					setImage(cImage* lpImage);
private:
	Ui::cImageViewer*		ui;

protected:
	void					keyPressEvent(QKeyEvent* e);

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

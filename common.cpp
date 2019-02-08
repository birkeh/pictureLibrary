/*!
 \file common.cpp

*/

#include "common.h"

#include <QBuffer>


QImage blob2Image(const QByteArray& ba)
{
	QImage		image;

	if(!ba.isEmpty())
	{
		if(!image.loadFromData(ba))
			myDebug << "image load error.";
	}

	return(image);
}

QByteArray image2Blob(const QImage &image)
{
	QByteArray	ba;
	QBuffer		buffer(&ba);
	buffer.open(QIODevice::WriteOnly);
	image.save(&buffer, "JPG");
	buffer.close();

	return(ba);
}

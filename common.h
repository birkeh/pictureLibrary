/*!
 \file common.h

*/

#ifndef COMMON_H
#define COMMON_H


#include <QImage>
#include <QByteArray>
#include <QStandardItem>

#include <QDebug>


#define THUMBNAIL_WIDTH		160
#define THUMBNAIL_HEIGHT	120


#ifdef __GNUC__
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __PRETTY_FUNCTION__ << ":"
#elif __MINGW32__
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __PRETTY_FUNCTION__ << ":"
#else
	#define myDebug qDebug() << __FILE__ << "(" << __LINE__ << ") - " << __FUNCTION__ << ":"
#endif

/**
 * @brief
 *
 * @param ba
 * @return QImage
 */
QImage			blob2Image(const QByteArray& ba);
/**
 * @brief
 *
 * @param image
 * @return QByteArray
 */
QByteArray		image2Blob(const QImage& image);

void			insertPath(QString szPath, QStandardItem* lpRootItem);


#endif // COMMON_H

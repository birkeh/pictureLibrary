/*!
 \file common.h

*/

#ifndef COMMON_H
#define COMMON_H


#include <QImage>
#include <QByteArray>
#include <QStandardItem>
#include <QTreeView>

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

/*!
 \brief

 \fn blob2Image
 \param ba
 \return QImage
*/
QImage			blob2Image(const QByteArray& ba);
/*!
 \brief

 \fn image2Blob
 \param image
 \return QByteArray
*/
QByteArray		image2Blob(const QImage& image);

/*!
 \brief

 \fn insertPath
 \param szPath
 \param lpRootItem
 \return QStandardItem
*/
QStandardItem* insertPath(QString szPath, QStandardItem* lpRootItem);

/*!
 \brief

 \fn copyFile
 \param szSource
 \param szDest
 \param bDelete
 \return bool
*/
bool copyFile(const QString& szSource, const QString& szDest, bool bDelete = false);

#endif // COMMON_H

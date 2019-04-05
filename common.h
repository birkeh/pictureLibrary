/*!
 \file common.h

*/

#ifndef COMMON_H
#define COMMON_H


#include "cimportdialog.h"

#include <QImage>
#include "cpicture.h"

#include <QByteArray>
#include <QStandardItem>
#include <QTreeView>

#include <QProgressBar>

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

 \fn picture2Path
 \param lpPicture
 \param newDate
 \param szNewTitle
 \param newHDR
 \return QString
*/
QString			picture2Path(cPicture* lpPicture, const QDateTime& newDate = QDateTime(), const QString& szNewTitle = QString(), const qint8& newHDR = -1);
/*!
 \brief

 \fn pattern2Text
 \param lpPicture
 \param szPattern
 \return QString
*/
QString			pattern2Text(cPicture* lpPicture, const QString& szPattern);
/*!
 \brief

 \fn pattern2Path
 \param lpPicture
 \param szPattern
 \return QString
*/
QString			pattern2Path(cPicture* lpPicture, const QString& szPattern);
/*!
 \brief

 \fn pattern2File
 \param lpPicture
 \param szPattern
 \return QString
*/
QString			pattern2File(cPicture* lpPicture, const QString& szPattern);

/*!
 \brief

 \fn ms2String
 \param ms
 \return QString
*/
QString			ms2String(qint64 ms);

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
bool copyFile(QProgressBar* lpProgressBar, const QString& szSource, const QString& szDest, bool bDelete = false);

#endif // COMMON_H

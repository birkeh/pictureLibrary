/*!
 \file common.cpp

*/

/*!
 \file common.cpp

*/

#include "common.h"

#include "ccopier.h"

#include <QBuffer>
#include <QDir>
#include <QEventLoop>


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

QString picture2Path(cPicture* lpPicture, const QDateTime& newDate, const QString& szNewTitle, const qint8& newHDR)
{
	QString	szPath("");

	if(newDate.isValid())
		szPath	= newDate.toString("yyyy/yyyy-MM-dd");
	else if(lpPicture->dateTime().isValid())
		szPath	= lpPicture->dateTime().toString("yyyy/yyyy-MM-dd");

	if(!szNewTitle.isNull() && !szNewTitle.isEmpty())
	{
		if(szPath.isEmpty())
			szPath	= szNewTitle;
		else
			szPath.append(" - " + szNewTitle);
	}
	else if(szNewTitle.isNull() && !lpPicture->title().isEmpty())
	{
		if(szPath.isEmpty())
			szPath	= lpPicture->title();
		else
			szPath.append(" - " + lpPicture->title());
	}

	if(!lpPicture->cameraModel().isEmpty())
		szPath.append("/" + lpPicture->cameraModel().replace("/", "_").replace("\\", "_"));

	if((newHDR == -1 &&lpPicture->hdr()) || newHDR == 1)
		szPath.append("/HDR");

	return(szPath);
}

QString ms2String(qint64 ms)
{
	qint64	h	= ms/3600000;
	qint64	m	= (ms-h*3600000)/60000;
	qint64	s	= (ms-h*3600000-m*60000)/1000;

	return(QString("%1:%2:%3").arg(static_cast<int>(h)).arg(static_cast<int>(h), 2, 10, QChar('0')).arg(static_cast<int>(s), 2, 10, QChar('0')));
}

QStandardItem* insertPath(QString szPath, QStandardItem* lpRootItem)
{
	if(!lpRootItem)
		return(nullptr);

	QString				szPath1		= szPath.replace("\\", "/");
	QStringList			szPathList	= szPath1.split("/");
	QStandardItem*		lpCurRoot	= lpRootItem;
	int					path;
	bool				bFound;

	szPath1	= "";

	for(path = 0;path < szPathList.count();path++)
	{
		bFound	= false;
		for(int x = 0;x < lpCurRoot->rowCount();x++)
		{
			QStandardItem*	lpCurItem	= lpCurRoot->child(x, 0);

			if(!lpCurItem->text().compare(szPathList[path], Qt::CaseInsensitive))
			{
				lpCurRoot	= lpCurItem;
				bFound		= true;
				break;
			}
		}

		if(!bFound)
			break;

		szPath1.append(szPathList[path]+"/");
	}

	for(;path < szPathList.count();path++)
	{
		szPath1.append(szPathList[path]);
		QStandardItem*	lpNewItem	= new QStandardItem(szPathList[path]);
		lpCurRoot->appendRow(lpNewItem);
		lpNewItem->setData(QVariant::fromValue(szPath1), Qt::UserRole+1);
		szPath1.append("/");

		lpCurRoot	= lpNewItem;
	}

	return(lpCurRoot);
}

bool copyFile(QProgressBar* lpProgressBar, const QString& szSource, const QString& szDest, bool bDelete)
{
	QString	szDestPath;
	QString	szDestFilePath	= szDest;
	QDir	dir;
	QFile	file;

	szDestFilePath.replace("\\", "/");

	szDestPath	= szDestFilePath.left(szDestFilePath.lastIndexOf("/"));

	dir.mkpath(szDestPath);

	if(file.exists(szDestFilePath))
		file.remove(szDestFilePath);

	if(szSource[1] == ':' && szDest[1] == ':' && szSource[0] == szDest[0] && bDelete) // move
	{
		if(dir.rename(szSource, szDest))
			return(true);
	}

	cCopier*	lpCopier	= new cCopier(szSource, szDest);

	if(lpProgressBar)
		QObject::connect(lpCopier, SIGNAL(newStatus(int)), lpProgressBar, SLOT(setValue(int)));

	QEventLoop				loop;

	lpCopier->copy();

	QObject::connect(lpCopier, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if(bDelete)
		file.remove(szSource);

	return(true);
}

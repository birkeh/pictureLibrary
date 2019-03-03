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

		szPath1.append(szPathList[path]+QDir::separator());
	}

	for(;path < szPathList.count();path++)
	{
		szPath1.append(szPathList[path]);
		QStandardItem*	lpNewItem	= new QStandardItem(szPathList[path]);
		lpCurRoot->appendRow(lpNewItem);
		lpNewItem->setData(QVariant::fromValue(szPath1), Qt::UserRole+2);
		szPath1.append(QDir::separator());

		lpCurRoot	= lpNewItem;
	}

	return(lpCurRoot);
}

//bool copyFile(cImportDialog* lpImportDialog, const QString& szSource, const QString& szDest, bool bDelete)
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

	cCopier*	lpCopier	= new cCopier(szSource, szDest);

	if(lpProgressBar)
		QObject::connect(lpCopier, SIGNAL(newStatus(int)), lpProgressBar, SLOT(setValue(int)));
//	connect(copier, SIGNAL(newStatus(QString)), this, SLOT(newStatus(QString)));
//				connect(copier, SIGNAL(finished()), SIGNAL(copyFinished()));
//				connect(copier, SIGNAL(finished()), copier, SLOT(deleteLater()));
//				connect(this, SIGNAL(stopCopy()), copier, SLOT(stop()));

	QEventLoop				loop;

	lpCopier->copy();

	QObject::connect(lpCopier, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if(bDelete)
		file.remove(szSource);

	return(true);
}

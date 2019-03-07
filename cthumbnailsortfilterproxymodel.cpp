/*!
 \file cthumbnailfilterproxymodel.cpp

*/

#include "cthumbnailsortfilterproxymodel.h"
#include "cpicture.h"


cThumbnailSortFilterProxyModel::cThumbnailSortFilterProxyModel(QObject* parent) :
	QSortFilterProxyModel (parent)
{
}

void cThumbnailSortFilterProxyModel::setFilterPath(const QString &szPath)
{
	m_szPath	= szPath;
	m_szPath.replace("\\", "/");

	invalidateFilter();
}

QString cThumbnailSortFilterProxyModel::filterPath()
{
	return(m_szPath);
}

bool cThumbnailSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
	if(m_szPath.isEmpty())
		return(true);

	QModelIndex	index0		= sourceModel()->index(sourceRow, 0, sourceParent);
	cPicture*	lpPicture	= sourceModel()->data(index0, Qt::UserRole+1).value<cPicture*>();

	if(!lpPicture)
		return(false);

	QString		szPath		= lpPicture->filePath();

	if(!szPath.startsWith(m_szPath))
		return(false);

	if(szPath.length() == m_szPath.length())
		return(true);

	if(szPath.mid(m_szPath.length(), 1) == "/")
		return(true);

	return(false);
}
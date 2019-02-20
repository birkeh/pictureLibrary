/*!
 \file cthumbnailfilterproxymodel.h

*/

#ifndef CTHUMBNAILFILTERPROXYMODEL_H
#define CTHUMBNAILFILTERPROXYMODEL_H


#include <QSortFilterProxyModel>


/*!
 \brief

 \class cThumbnailFilterProxyModel cthumbnailfilterproxymodel.h "cthumbnailfilterproxymodel.h"
*/
class cThumbnailSortFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	cThumbnailSortFilterProxyModel(QObject* parent = nullptr);

	/*!
	 \brief

	 \fn filterPath
	*/
	QString					filterPath();
	/*!
	 \brief

	 \fn setFilterPath
	 \param szPath
	*/
	void					setFilterPath(const QString& szPath);

protected:
	/*!
	 \brief

	 \fn filterAcceptsRow
	 \param sourceRow
	 \param sourceParent
	 \return bool
	*/
	bool					filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
	QString					m_szPath;					/*!< TODO: describe */
};

#endif // CTHUMBNAILFILTERPROXYMODEL_H

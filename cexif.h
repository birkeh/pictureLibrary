#ifndef CEXIF_H
#define CEXIF_H

#include <QString>


class cEXIF
{
public:
	cEXIF();

	bool			fromFile(const QString& szFileName);
};

#endif // CEXIF_H

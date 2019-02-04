#include "cexif.h"

#include <QDebug>

#include <exiv2/exiv2.hpp>


cEXIF::cEXIF()
{
}

bool cEXIF::fromFile(const QString& szFileName)
{
	Exiv2::Image::AutoPtr			image		= Exiv2::ImageFactory::open(szFileName.toStdString());
	if(!image.get())
		return(false);

	image->readMetadata();

	Exiv2::ExifData&				exifData	= image->exifData();
	if(exifData.empty())
		return(false);

	Exiv2::ExifData::const_iterator	end			= exifData.end();
	for(Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i)
	{
		const char*	tn	= i->typeName();
		std::string	str;
		std::stringstream	strBuffer;

		strBuffer << std::setw(44) << std::setfill(' ') << std::left
		<< i->key() << " "
		<< "0x" << std::setw(4) << std::setfill('0') << std::right
		<< std::hex << i->tag() << " "
		<< std::setw(9) << std::setfill(' ') << std::left
		<< (tn ? tn : "Unknown") << " "
		<< std::dec << std::setw(3)
		<< std::setfill(' ') << std::right
		<< i->count() << "  "
		<< std::dec << i->value();

		str	= strBuffer.str();

		qDebug() << str.data();
	}

	return(true);
}

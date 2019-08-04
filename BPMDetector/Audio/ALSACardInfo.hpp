#ifndef _ALSACARDINFO_H
#define _ALSACARDINFO_H

#include "../globals.hpp"

#include <string>


//Soundcard data
struct ALSACardInfo_t
{
	unsigned int ID 	= 0;		//Number of soundcard
	std::string  name	= "";		//Name of soundcard
	std::string  hw_ID	= "";		//Hardware identifier - used for open call
	std::string  subdev = "";		//Subdevice string
};

#endif

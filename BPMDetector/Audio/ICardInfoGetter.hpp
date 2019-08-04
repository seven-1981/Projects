#ifndef _ICARDINFOGETTER_H
#define _ICARDINFOGETTER_H

#include <string>


//Interface for sound card info getter
class ICardInfoGetter
{
public:
	virtual ~ICardInfoGetter() { };
	
	//Abstract functions - always required
	virtual int next(int& num) = 0;
	virtual int open(std::string hw_id) = 0;
	virtual int get_name(std::string& name) = 0;
	//Those are only API calls - not required for testing
	virtual void close() { }
	virtual void free() const { }
};

#endif

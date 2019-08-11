#ifndef _ICARDLISTER_H
#define _ICARDLISTER_H

#include <vector>


//Forward declarations
class ICardInfoGetter;


template <typename CARD_INFO_TYPE>
class ICardLister
{
public:
	virtual ~ICardLister() { }
	
	//Init method
	virtual void init(ICardInfoGetter* info_getter) = 0;
	//Returns vector with card info
	virtual std::vector<CARD_INFO_TYPE> get_cardInfos() const = 0;
};

#endif

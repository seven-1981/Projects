#ifndef _ICARDLISTER_H
#define _ICARDLISTER_H

#include <vector>


//Forward declarations
class ICardInfoGetter;


//Normally, templates and inheritance don't go well with each other. In this case,
//we use the template to delegate the type definition to the inheritor. Otherwise,
//for the vector elements we'd have to use dynamic memory allocation to hold polymorphic
//vector elements.
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

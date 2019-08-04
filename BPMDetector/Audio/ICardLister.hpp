#ifndef _ICARDLISTER_H
#define _ICARDLISTER_H

#include <vector>


//Forward declaration for card info getter
class ICardInfoGetter;
//Forward declaration of error enum class
enum class Errors_e;


//Base class for soundcard lister. Since it is platform 
//dependent, we use an interface class. The template parameter
//defines the card info type used
template <typename T>
class ICardLister
{
public:
	virtual ~ICardLister() { }
	
	//Init method
	virtual void init(ICardInfoGetter* info_getter) = 0;
	//Returns vector with card info
	virtual std::vector<T> get_cardInfos() const = 0;
};

#endif

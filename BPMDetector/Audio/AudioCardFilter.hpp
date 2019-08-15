#ifndef _AUDIOCARDFILTER_H
#define _AUDIOCARDFILTER_H

#include "ALSACardInfo.hpp"

#include <functional>
#include <algorithm>
#include <string>


//Used to select soundcard
const std::string USB_CARD_TAG = "USB";

//Typename simplification
using CARD_INFO_TYPE = ALSACardInfo_t;


template <typename FILTER_FUNC>
class AudioCardFilter
{
public:
    AudioCardFilter() 
    {
        m_filter = [] (const CARD_INFO_TYPE& card) { return card.name.find(USB_CARD_TAG) != std::string::npos; };
    }
    ~AudioCardFilter() { }

	void set_filter(FILTER_FUNC func)
    {
        m_filter = func;
    }

    template <typename CARD_LIST>
    CARD_LIST apply_filter(CARD_LIST& list)
    {
        return perform_filtering(list, m_filter);
    }

private:
	//Filter function for selecting USB card
	FILTER_FUNC m_filter;

	//Filter function - for usage with lambda
	template <typename CONT, typename PRED>
	CONT perform_filtering(const CONT& container, PRED predicate) 
	{
		CONT result;
		std::copy_if(container.begin(), container.end(), std::back_inserter(result), predicate);
		return result;
	}
};

#endif
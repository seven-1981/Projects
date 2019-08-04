#ifndef _ICARDMANAGER_H
#define _ICARDMANAGER_H


//Forward declaration of error enum class
enum class Errors_e;


//Base class for soundcard manager
template <typename CONFIGURATOR_TYPE, typename LISTER_TYPE, typename CARD_CONFIG_TYPE>
class ICardManager
{
public:
	virtual ~ICardManager() { }
	
	//Init methods
	virtual void init_configurator(CONFIGURATOR_TYPE* configurator) = 0;
	virtual void init_lister(LISTER_TYPE* lister) = 0;
	virtual void set_configuration(CARD_CONFIG_TYPE& configuration) = 0;
	//Start card configuration process
	virtual Errors_e select_and_configure() = 0;
};

#endif

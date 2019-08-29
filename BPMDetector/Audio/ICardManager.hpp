#ifndef _ICARDMANAGER_H
#define _ICARDMANAGER_H


//Forward declarations
enum class Errors_e;
struct ICardConfiguration_t;
class ICardConfigurator;


//Base class for soundcard manager
template <typename LISTER_TYPE>
class ICardManager
{
public:
	virtual ~ICardManager() { }
	
	//Init methods
	virtual void init_configurator(ICardConfigurator* configurator) = 0;
	virtual void init_lister(LISTER_TYPE* lister) = 0;
	//Start card configuration process 
	virtual Errors_e select_and_configure(ICardConfiguration_t& configuration) = 0;
	virtual Errors_e configure(ICardConfiguration_t& configuration) = 0;
};

#endif

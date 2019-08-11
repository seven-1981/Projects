#ifndef _ICARDCONFIGURATOR_H
#define _ICARDCONFIGURATOR_H

#include <string>


//Forward declarations
enum class Errors_e;
struct ICardConfiguration_t;


class ICardConfigurator
{
public:
	virtual ~ICardConfigurator() { };
	
	//Set hardware ID for opening card interface
	virtual void set_hw_id(std::string& hw_id) = 0;
	//Start card configuration process
	virtual Errors_e configure(ICardConfiguration_t& config) = 0;
};

#endif

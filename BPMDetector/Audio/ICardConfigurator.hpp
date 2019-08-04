#ifndef _ICARDCONFIGURATOR_H
#define _ICARDCONFIGURATOR_H

#include <string>


//Forward declaration of error enum class
enum class Errors_e;


//Interface for card configurator. The template parameter
//defines the card config type
template <typename T>
class ICardConfigurator
{
public:
	virtual ~ICardConfigurator() { };
	
	//Set hardware ID for opening card interface
	virtual void set_hw_id(std::string& hw_id) = 0;
	//Start card configuration process
	virtual Errors_e configure(T& config) = 0;
};

#endif

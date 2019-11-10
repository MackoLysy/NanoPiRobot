#include "IDisplay.hpp"

IDisplay::IDisplay(int _address) :  address(_address)
{
    wlanIP = "No wlan";
    espIP = "No esp";
}
IDisplay::~IDisplay()
{
    
}

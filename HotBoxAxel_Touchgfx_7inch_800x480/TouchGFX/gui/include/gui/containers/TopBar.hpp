#ifndef TOPBAR_HPP
#define TOPBAR_HPP

#include <gui_generated/containers/TopBarBase.hpp>

class TopBar : public TopBarBase
{
public:
    TopBar();
    virtual ~TopBar() {}

    virtual void initialize();
    void setDate(uint8_t day, uint8_t month, uint16_t year);
    void setClock(uint8_t hours, uint8_t minutes, uint8_t seconds);
    void setEnvTemperature(int16_t temp);
protected:
};

#endif // TOPBAR_HPP

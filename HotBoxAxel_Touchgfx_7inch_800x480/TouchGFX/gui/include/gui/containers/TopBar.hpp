#ifndef TOPBAR_HPP
#define TOPBAR_HPP

#include <gui_generated/containers/TopBarBase.hpp>

class TopBar : public TopBarBase
{
public:
    TopBar();
    virtual ~TopBar() {}

    virtual void initialize();
    void setDate(uint16_t year,uint16_t month,uint16_t day);
    void setTime(uint8_t hour,uint8_t minute);
    void setEnvTemp(int16_t temp);
protected:
};

#endif // TOPBAR_HPP

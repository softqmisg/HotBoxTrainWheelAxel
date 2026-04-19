#include <gui/containers/TopBar.hpp>

TopBar::TopBar()
{

}

void TopBar::initialize()
{
    TopBarBase::initialize();
}

void TopBar::setDate(uint16_t year,uint16_t month,uint16_t day){
    Unicode::snprintf(dateTextBuffer, DATETEXT_SIZE, "%04d/%02d/%02d", year,month,day);
	dateText.invalidate();

}
void TopBar::setTime(uint8_t hour,uint8_t minute){
    digitalClock.setTime24Hour(hour, minute, 0);
    digitalClock.invalidate();
};

void TopBar::setEnvTemp(int16_t temp){
    Unicode::snprintf(envTempTextBuffer, ENVTEMPTEXT_SIZE, "%+ 3i", temp);
	envTempText.invalidate();
}

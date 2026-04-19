#include <gui/containers/TopBar.hpp>

TopBar::TopBar()
{

}

void TopBar::initialize()
{
    TopBarBase::initialize();
}


void TopBar::setEnvTemperature(int16_t temp){
    Unicode::snprintf(envTempTextBuffer, ENVTEMPTEXT_SIZE, "%+3i", temp);
	envTempText.invalidate();
}
void TopBar::setDate(uint8_t day, uint8_t month, uint16_t year){
    Unicode::snprintf(dateTextBuffer, DATETEXT_SIZE, "%04d/%02d/%02d", year,month,day);
	dateText.invalidate();

}
void TopBar::setClock(uint8_t hours, uint8_t minutes, uint8_t seconds){
    digitalClock.setTime24Hour(hours, minutes, 0);
    digitalClock.invalidate();
};

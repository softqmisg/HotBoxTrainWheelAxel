#include <gui/containers/TopBar.hpp>
#include "Utility.h"

TopBar::TopBar()
{

}

void TopBar::initialize()
{
    TopBarBase::initialize();
}

void TopBar::exitButtonClicked()
{
	if (exitButtonClickCallback) exitButtonClickCallback->execute(*this);
}
void TopBar::setExitButtonClickedCallback(GenericCallback<const TopBar&>& callback) {
	exitButtonClickCallback = &callback;
}

void TopBar::setEnvTemperature(int16_t temp){
	if(temp==ERROR_TEMP)
		Unicode::snprintf(envTempTextBuffer, ENVTEMPTEXT_SIZE, "---");
	else
		Unicode::snprintf(envTempTextBuffer, ENVTEMPTEXT_SIZE, "%+3i", temp);
	envTempText.invalidate();
}
void TopBar::setDate(uint8_t day, uint8_t month, uint16_t year, char *name){
    Unicode::snprintf(dateTextBuffer1, DATETEXTBUFFER1_SIZE, "%04d/%02d/%02d", year,month,day);
    Unicode::fromUTF8((const uint8_t *)name, dateTextBuffer2, DATETEXTBUFFER2_SIZE);
    dateText.invalidate();

}
void TopBar::setClock(uint8_t hours, uint8_t minutes, uint8_t seconds){
    digitalClock.setTime24Hour(hours, minutes, 0);
    digitalClock.invalidate();
};


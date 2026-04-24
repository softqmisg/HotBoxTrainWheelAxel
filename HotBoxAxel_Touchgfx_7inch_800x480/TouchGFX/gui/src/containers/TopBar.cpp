#include <gui/containers/TopBar.hpp>
#include<texts/TextKeysAndLanguages.hpp>
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
void TopBar::setDate(uint8_t day, uint8_t month, uint16_t year,uint8_t dayofweek){
    Unicode::snprintf(dateTextBuffer, DATETEXT_SIZE, "%04d/%02d/%02d", year,month,day);
    dateText.invalidate();
    touchgfx::TypedTextId textID;
    switch(dayofweek)
    {
    case 0: //Sunday
    	textID=T_DAY_SUNDAY;
    	break;
    case 1: //Monday
    	textID=T_DAY_MONDAY;
    	break;
    case 2: //Tuesday
    	textID=T_DAY_TUESDAY;
    	break;
    case 3: //Wednesday
    	textID=T_DAY_WEDNESDAY;
    	break;
    case 4: //Thursday
    	textID=T_DAY_THURSDAY;
    	break;
    case 5: //Friday
    	textID=T_DAY_SUNDAY;
    	break;
    case 6: //Saturday
    	textID=T_DAY_SUNDAY;
    	break;

    }
    dayText.setTypedText(touchgfx::TypedText(textID));
    dayText.invalidate();

}
void TopBar::setClock(uint8_t hours, uint8_t minutes, uint8_t seconds){
    digitalClock.setTime24Hour(hours, minutes, 0);
    digitalClock.invalidate();
};


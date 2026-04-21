#include <gui/mainscreen_screen/mainScreenView.hpp>
#include "Utility.h"
mainScreenView::mainScreenView()
{

}

void mainScreenView::setupScreen()
{
    mainScreenViewBase::setupScreen();
    ledMain.setTitle("Main");ledMain.setState(Led::State::GREEN);
    ledAlarm.setTitle("Alarm");ledAlarm.setState(Led::State::RED);
    ledComm.setTitle("Comm");ledComm.setState(Led::State::GREEN);

    /////////////digitalClock////////////////////////
//    updateClock(0, 0, 0);
    //////////envTemperature//////////////////
//    	updateEnvTemperature(0);
    //////////carSelector//////////////////
//    carSelector.initialize();    // Initialize carSelector
    carSelector.setParentView(this);    // Set parent view to communicate back
    if(presenter!=nullptr)    // Load saved value from presenter
    {
    	carSelector.setCarNumber(presenter->getSavedCarNumber());
    }
    //////////////axelTemperature/////////////////////////////
//    updateAxelTemperatures(carData)
}

void mainScreenView::tearDownScreen()
{
    if(presenter!=nullptr)
    {
    	presenter->saveCarNumber(carSelector.getCarNumber());
    }
	mainScreenViewBase::tearDownScreen();
}
///////////digitalClock//////////////
void mainScreenView::updateClock(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	topBar.setClock(hours, minutes, seconds);
}
void mainScreenView::updateDate(uint8_t day, uint8_t month, uint16_t year)
{
	uint8_t tmpDay=day,tmpMonth=month;
	uint16_t tmpYear=year;
	if (presenter != nullptr) {
		if(presenter->getCalenderType()==Model::CalenderType::JALALI)
		{
			Utility::gregorianToJalali(year, month, day, tmpYear, tmpMonth, tmpDay);
		}
		char name[5]="    ";

		Utility::getDayNameShort(year, month, day,name);
		topBar.setDate(tmpDay, tmpMonth, tmpYear,name);
	}
}
///////////envTempText//////////////
void mainScreenView::updateEnvTemperature(int16_t temp)
{
	topBar.setEnvTemperature(temp);
}
///////////carSelector//////////////
void mainScreenView::onCarNumberChanged(uint8_t newValue){
    // Forward value change to presenter (saves to model)
    if (presenter != nullptr) {
        presenter->saveCarNumber(newValue);
    }
}
void mainScreenView::updateCarNumber(uint8_t value)
{
	carSelector.setCarNumber(value);
}
//////////tempAxelList////////////////
void mainScreenView::updateAxelTemperatures(Car carData)
{
	tempAxelList.updateTempAllItems(carData);
}

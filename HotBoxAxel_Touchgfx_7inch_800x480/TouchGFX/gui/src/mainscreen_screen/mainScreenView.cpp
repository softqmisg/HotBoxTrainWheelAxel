#include <gui/mainscreen_screen/mainScreenView.hpp>
#include<texts/TextKeysAndLanguages.hpp>
#include "Utility.h"
mainScreenView::mainScreenView():
carNumberChangedCallback(this, &mainScreenView::onCarNumberChanged),
warningAcceptClickedCallback(this,&mainScreenView::onWarningAcceptButtonClicked)
{

}

void mainScreenView::setupScreen()
{
    mainScreenViewBase::setupScreen();
    ledMain.setTitle(T_TEXT_MAIN);//ledMain.setState(Led::State::GREEN);
    ledAlarm.setTitle(T_TEXT_ALARM);//ledAlarm.setState(Led::State::RED);
    ledComm.setTitle(T_TEXT_COMM);//ledComm.setState(Led::State::GREEN);
    topBar.setExitButtonVisible(false);
    topBar.setEnvTemperatureVisible(true);
    /////////////digitalClock////////////////////////
//    updateClock(0, 0, 0);
    //////////envTemperature//////////////////
//    	updateEnvTemperature(0);
    //////////carSelector//////////////////
//    carSelector.initialize();    // Initialize carSelector
    carSelector.setNextButtonClickedCallback(carNumberChangedCallback);    // Set parent view to communicate back
    if(presenter!=nullptr)    // Load saved value from presenter
    {
    	carSelector.setCarNumber(presenter->getSavedCarNumber());
    }
    //////////////axelTemperature/////////////////////////////
//    updateAxelTemperatures(carData)
    //////////////warning///////////////////////
    warningBar.setAcceptButtonClickedCallback(warningAcceptClickedCallback);
    updateWarning();
    /////////////password popup//////////////
}

void mainScreenView::tearDownScreen()
{
    if(presenter!=nullptr)
    {
    	presenter->saveCarNumber(carSelector.getCarNumber());
    }
	mainScreenViewBase::tearDownScreen();
}
///////////Date and Day/////////////////
void mainScreenView::updateDate(uint8_t day, uint8_t month, uint16_t year)
{
	uint8_t tmpDay=day,tmpMonth=month;
	uint16_t tmpYear=year;
	if (presenter != nullptr) {
		if(presenter->getCalenderType()==Model::CalenderType::JALALI)
		{
			Utility::gregorianToJalali(year, month, day, tmpYear, tmpMonth, tmpDay);
		}
//		char name[5]="    ";
//		Utility::getDayNameShort(year, month, day,name);
		topBar.setDate(tmpDay, tmpMonth, tmpYear,(uint8_t)Utility::getDayOfWeek(year, month, day));
	}
}

///////////digitalClock//////////////
void mainScreenView::updateClock(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	topBar.setClock(hours, minutes, seconds);
}
/////////////envTempText//////////////
//void mainScreenView::updateEnvTemperature(int16_t temp)
//{
//	topBar.setEnvTemperature(temp);
//}
///////////carSelector//////////////
void mainScreenView::updateCarNumber(uint8_t value)
{
	carSelector.setCarNumber(value);
}
void mainScreenView::onCarNumberChanged(const CarSelector& selector){
    // Forward value change to presenter (saves to model)
    if (presenter != nullptr) {
        presenter->saveCarNumber(selector.getCarNumber());
    }
}

//////////tempAxelList////////////////
void mainScreenView::updateCarTemperatures(Car carData)
{
	tempAxelList.updateTempAllItems(carData);
	topBar.setEnvTemperature(carData.getTemperature(MAX_SENSORNUM).temperature);
}
//////////led////////////////////
void mainScreenView::updateLedMainColor(LedParam::ColorState colorState)
{
	Led::Color color;
	switch (colorState) {
		case LedParam::ColorState::COLORFIXED:
				color=Led::Color::GREY;
			break;
		case LedParam::ColorState::COLORBLINKOFF:
			color=Led::Color::GREY;
			break;
		case LedParam::ColorState::COLORBLINKON:
				color=Led::Color::GREEN;
			break;

		default:
			break;
	}
	ledMain.setState(color);

}
void mainScreenView::updateLedAlarmColor(LedParam::ColorState colorState)
{
	Led::Color color;
	switch (colorState) {
		case LedParam::ColorState::COLORFIXED:
				color=Led::Color::GREY;
			break;
		case LedParam::ColorState::COLORBLINKOFF:
				color=Led::Color::GREEN;
			break;
		case LedParam::ColorState::COLORBLINKON:
				color=Led::Color::RED;
			break;

		default:
			break;
	}
	ledAlarm.setState(color);
}
void mainScreenView:: updateLedCommColor(LedParam::ColorState colorState)
{
	Led::Color color;
	switch (colorState) {
		case LedParam::ColorState::COLORFIXED:
				color=Led::Color::GREY;
			break;
		case LedParam::ColorState::COLORBLINKOFF:
				color=Led::Color::GREY;
			break;
		case LedParam::ColorState::COLORBLINKON:
				color=Led::Color::RED;
			break;

		default:
			break;
	}
	ledComm.setState(color);
}
/////////Setting Button////////////
void mainScreenView::settingButtonClicked()
{
	passwordPopup.cleanPassword();
	passwordPopup.setVisible(true);
	passwordPopup.invalidate();
}
///////////Warning bar///////////////
void mainScreenView::updateWarning()
{
	test_car=3;
	test_axel=6;
	warningBar.setWarning(test_car,test_axel, 13, 42, 25, 4, 2026);
}
void mainScreenView::onWarningAcceptButtonClicked(const WarningBar& warning)
{
	if(Texts::getLanguage()==0)
		Texts::setLanguage(1);
	else
		Texts::setLanguage(0);
	test_car++;if(test_car>MAX_CARNUM) test_car=1;
	test_axel++;if(test_axel>MAX_SENSORNUM) test_axel=1;
//	warningBar.setWarning(test_car,test_axel, 13, 42, 25, 4, 2026);
}


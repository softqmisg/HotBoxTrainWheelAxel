#include <gui/mainscreen_screen/mainScreenView.hpp>
#include <gui/mainscreen_screen/mainScreenPresenter.hpp>

mainScreenPresenter::mainScreenPresenter(mainScreenView& v)
    : view(v)
{

}

void mainScreenPresenter::activate()
{
    // When screen becomes active, load saved value
    // digitalClock init
    model->startRefreshingMain();
    requestTimeDateUpdate();// Get initial time immediately
    // EnvTemperature init
//    requestEnvTemperatureUpdate();
	// Carselector init
	uint8_t saved= getSavedCarNumber();
    view.updateCarNumber(saved);
    requestCarTempUpdate(saved);

    requestLedColorUpdate();
}

void mainScreenPresenter::deactivate()
{
    model->stopRefreshinMain();
}
///////////////digitalClock////////////////////
void mainScreenPresenter::requestTimeDateUpdate()
{
	model->updateRTC();
}
void mainScreenPresenter::timeUpdated(uint8_t hours,uint8_t minutes,uint8_t seconds){
	view.updateClock(hours,minutes,seconds);
}
void mainScreenPresenter::dateUpdated(uint8_t day, uint8_t month, uint16_t year){
	view.updateDate(day,month,year);
}

void mainScreenPresenter::setCalenderType(Model::CalenderType type) {
   if (model != nullptr) {
		model->setCalenderType(type);
	}
}

Model::CalenderType mainScreenPresenter:: getCalenderType() {
	if(model!=nullptr){
		return model->getCalenderType();
	}
	return Model::CalenderType::GEORGIAN;
}

///////////////CarSelector////////////////////
void mainScreenPresenter::saveCarNumber(uint8_t carNum) {
   if (model != nullptr) {
		model->saveCarNumber(carNum);
	}
}

int mainScreenPresenter::getSavedCarNumber() {
	if(model!=nullptr){
    return model->getCarNumber();
	}
	return 0;
}
void mainScreenPresenter::carNumberUpdated(uint8_t carNum)
{
	 view.updateCarNumber(carNum);
	requestCarTempUpdate(carNum);
}
///////////////AxelTemp //////////////////////////////////
void mainScreenPresenter::requestCarTempUpdate(uint8_t carNum)
{
	model->updateCarTemperatures(carNum);

}
void mainScreenPresenter::carTempUpdated(Car car)
{
	view.updateCarTemperatures(car);
}
///////////////EnvTemperature////////////////////////
//void mainScreenPresenter::requestEnvTemperatureUpdate()
//{
//	model->updateEnvTemperature();
//}
//void mainScreenPresenter::envTempUpdated(int16_t temp)
//{
//	view.updateEnvTemperature(temp);
//}
void mainScreenPresenter::requestLedColorUpdate()
{
	model->updateLedMain();
	model->updateLedAlarm();
	model->updateLedComm();
}
void mainScreenPresenter::ledColorUpdate(uint8_t ledId, LedParam::ColorState colorState)
{
	switch(ledId)
	{
	case 0: //Main
		view.updateLedMainColor(colorState);
		break;
	case 1: //Alarm
		view.updateLedAlarmColor(colorState);
		break;
	case 2: //Comm
		view.updateLedCommColor(colorState);
		break;
	}
}

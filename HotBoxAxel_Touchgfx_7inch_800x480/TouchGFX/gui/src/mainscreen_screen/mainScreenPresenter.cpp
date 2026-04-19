#include <gui/mainscreen_screen/mainScreenView.hpp>
#include <gui/mainscreen_screen/mainScreenPresenter.hpp>

mainScreenPresenter::mainScreenPresenter(mainScreenView& v)
    : view(v)
{

}

void mainScreenPresenter::activate()
{
    // When screen becomes active, load saved value
	/////// Carselector init//////////
	uint8_t saved= getSavedCarNumber();
    view.updateCarNumber(saved);
    requestTempUpdate(saved);
    /////// digitalClock init//////////
    model->startClockUpdates();
    requestTimeUpdate();// Get initial time immediately
}

void mainScreenPresenter::deactivate()
{
    model->stopClockUpdates();
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
void requestTempUpdate(uint8_t carNum)
{

}
///////////////digitalClock////////////////////
void mainScreenPresenter::requestTimeUpdate()
{
	model->updateRTC();
}
void mainScreenPresenter::timeUpdated(uint8_t hours,uint8_t minutes,uint8_t seconds){
	view.updateClock(hours,minutes,seconds);
}
void mainScreenPresenter::dateUpdated(uint8_t day, uint8_t month, uint16_t year){
	view.updateDate(day,month,year);
}

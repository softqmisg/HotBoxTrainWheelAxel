#include <gui/settingscreen_screen/settingScreenView.hpp>
#include <gui/settingscreen_screen/settingScreenPresenter.hpp>

settingScreenPresenter::settingScreenPresenter(settingScreenView& v)
    : view(v)
{

}

void settingScreenPresenter::activate()
{
    requestTimeDateUpdate();// Get initial time immediately

}

void settingScreenPresenter::deactivate()
{
	int a=10;
}
void settingScreenPresenter::exitButtonClicked()
{
	//saving parameters//
	int a=10;
	//then goto
}
///////////////digitalClock////////////////////
void settingScreenPresenter::requestTimeDateUpdate()
{
	model->updateRTC();
}
void settingScreenPresenter::timeUpdated(uint8_t hours,uint8_t minutes,uint8_t seconds){
	view.updateClock(hours,minutes,seconds);
}
void settingScreenPresenter::dateUpdated(uint8_t day, uint8_t month, uint16_t year){
	view.updateDate(day,month,year);
}

void settingScreenPresenter::setCalenderType(Model::CalenderType type) {
   if (model != nullptr) {
		model->setCalenderType(type);
	}
}

Model::CalenderType settingScreenPresenter:: getCalenderType() {
	if(model!=nullptr){
		return model->getCalenderType();
	}
	return Model::CalenderType::GEORGIAN;
}

///////////////CarSelector////////////////////

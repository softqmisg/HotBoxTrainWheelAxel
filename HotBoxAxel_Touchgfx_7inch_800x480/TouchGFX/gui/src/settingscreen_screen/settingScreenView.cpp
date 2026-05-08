#include <gui/settingscreen_screen/settingScreenView.hpp>
#include <tim.h>
extern TIM_HandleTypeDef htim3;

settingScreenView::settingScreenView():
exitButtonClickedCallback(this,&settingScreenView::onExitButtonClicked),
volumeSliderConfirmedCallback(this,&settingScreenView::onVolumeSliderConfirmed),
brightnessSliderChangedCallback(this,&settingScreenView::onBrightnessSliderChanged),
locoEditable(Editable(locoEditText,locoEditTextBuffer))
{

}

void settingScreenView::setupScreen()
{
    settingScreenViewBase::setupScreen();
    const uint16_t h = HAL::DISPLAY_HEIGHT*3/5;     // Screen height.
    const uint16_t w = HAL::DISPLAY_WIDTH*3/4;      // Screen width.
    const uint16_t offsetX=(HAL::DISPLAY_WIDTH-w)/2;
    const uint16_t offsetY=HAL::DISPLAY_HEIGHT-h;

    keyboard.initialize(w,h);
    keyboard.setXY(offsetX, offsetY);
    keyboard.setTimout(5000);


    topBar.setEnvTemperatureVisible(false);
    topBar.setExitButtonVisible(true);
    topBar.setExitButtonClickedCallback(exitButtonClickedCallback);


    volumeSliderWithLabel.setValueConfirmedCallback(volumeSliderConfirmedCallback);
    volumeSliderWithLabel.setValueRange(1,10);
    volumeSliderWithLabel.setValue(8);

    brightnessSliderWithLabel.setValueChangeCallback(brightnessSliderChangedCallback);

    brightnessSliderWithLabel.setValueRange(1, 10);
    brightnessSliderWithLabel.setValue((uint8_t)getBrightness());
}

void settingScreenView::tearDownScreen()
{
    settingScreenViewBase::tearDownScreen();
}
void settingScreenView::onExitButtonClicked(const TopBar& bar)
{
	if(presenter!=nullptr)
	{
		presenter->exitButtonClicked();
	}
	application().gotomainScreenScreenNoTransition();
}
///////////digitalClock//////////////
void settingScreenView::updateClock(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	topBar.setClock(hours, minutes, seconds);
}
void settingScreenView::updateDate(uint8_t day, uint8_t month, uint16_t year)
{
	uint8_t tmpDay=day,tmpMonth=month;
	uint16_t tmpYear=year;
	if (presenter != nullptr) {
		if(presenter->getCalenderType()==Model::CalenderType::JALALI)
		{
			Utility::gregorianToJalali(year, month, day, tmpYear, tmpMonth, tmpDay);
		}

//		Utility::getDayNameShort(year, month, day,name);
//		topBar.setDate(tmpDay, tmpMonth, tmpYear,name);
		topBar.setDate(tmpDay, tmpMonth, tmpYear,(uint8_t)Utility::getDayOfWeek(year, month, day));

	}
}
///////Keyboard Events//////////////////////////
void settingScreenView::keyboardAppliedClicked()
{
	if(keyboard.targets(locoEditable))
	{
		locoEditable.toUTF8(keyboardText);
	}
}
void settingScreenView::keyboardCancelClicked()
{
}
void settingScreenView::keyboardCharTyped(Unicode::UnicodeChar value)
{

}

////////////////////Page1//////////////////
void settingScreenView::locoEditClicked(){
	keyboard.edit(locoEditable);
}
void settingScreenView::onVolumeSliderConfirmed(const uint8_t value){

}
uint8_t settingScreenView::getBrightness(){
    uint32_t period=__HAL_TIM_GET_AUTORELOAD(&htim3)+1;
    uint32_t cmp=__HAL_TIM_GET_COMPARE(&htim3,TIM_CHANNEL_2)+1;
    uint32_t brightness=cmp*10/period;
    if(brightness<1) brightness=1;
}
void settingScreenView::setBrightness(uint8_t brightness){
    if(brightness<1) brightness=1;
	uint32_t period=__HAL_TIM_GET_AUTORELOAD(&htim3);
	uint32_t cmp=(period+1)*brightness/10;
	if(cmp==period)
		cmp--;
	  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,cmp);
}
void settingScreenView::onBrightnessSliderChanged(const uint8_t value){
		setBrightness(value);
}


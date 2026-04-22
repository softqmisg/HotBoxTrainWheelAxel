#include <gui/settingscreen_screen/settingScreenView.hpp>

settingScreenView::settingScreenView():
exitButtonClickedCallback(this,&settingScreenView::onExitButtonClicked)
{

}

void settingScreenView::setupScreen()
{
    settingScreenViewBase::setupScreen();
    topBar.setEnvTemperatureVisible(false);
    topBar.setExitButtonVisible(true);
    topBar.setExitButtonClickedCallback(exitButtonClickedCallback);
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
		char name[5]="    ";

		Utility::getDayNameShort(year, month, day,name);
		topBar.setDate(tmpDay, tmpMonth, tmpYear,name);
	}
}

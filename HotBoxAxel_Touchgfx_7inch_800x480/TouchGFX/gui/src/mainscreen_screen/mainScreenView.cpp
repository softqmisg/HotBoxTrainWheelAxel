#include <gui/mainscreen_screen/mainScreenView.hpp>
//#include <gui/containers/TempMehvar.hpp>
//#include <gui/containers/TempMehvarList.hpp>
//#include <gui/containers/topBar.hpp>

mainScreenView::mainScreenView()
{

}

void mainScreenView::setupScreen()
{
    mainScreenViewBase::setupScreen();
    topBar.setEnvTemp(-4);
    for(int id=1;id<=8;id++)
    {
    	tempMehvarList.updateItem(id, TempMehvar::State::NORMAL, 0.0);
    }
    ledMain.setTitle(0);ledMain.setState(Led::State::GREEN);
    ledAlarm.setTitle(1);ledAlarm.setState(Led::State::RED);
    ledComm.setTitle(2);ledComm.setState(Led::State::GREEN);

    //////////carSelector//////////////////
//    carSelector.initialize();    // Initialize carSelector
    carSelector.setParentView(this);    // Set parent view to communicate back
    if(presenter!=nullptr)    // Load saved value from presenter
    {
    	carSelector.setCarNumber(presenter->getSavedCarNumber());
    }
    /////////////digitalClock////////////////////////
//    updateClock(0, 0, 0);
}

void mainScreenView::tearDownScreen()
{
    if(presenter!=nullptr)
    {
    	presenter->saveCarNumber(carSelector.getCarNumber());
    }
	mainScreenViewBase::tearDownScreen();
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
///////////digitalClock//////////////
void mainScreenView::updateClock(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	topBar.setClock(hours, minutes, seconds);
}
void mainScreenView::updateDate(uint8_t day, uint8_t month, uint16_t year)
{
	topBar.setDate(day, month, year);
}

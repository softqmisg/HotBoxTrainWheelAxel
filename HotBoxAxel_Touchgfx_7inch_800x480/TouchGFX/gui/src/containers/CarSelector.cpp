#include <gui/containers/CarSelector.hpp>
#include <gui/mainscreen_screen/mainScreenView.hpp>
#include "Car.h"
CarSelector::CarSelector():
currentCarNumber(1)
{

}

void CarSelector::initialize()
{
    CarSelectorBase::initialize();
    updateCarNumberTextArea();
}
void CarSelector::setNextButtonClickedCallback(GenericCallback<const CarSelector&>& callback) {
	nextButtonClickedCallback = &callback;
}
void CarSelector::nextButtonClicked(){
	currentCarNumber++;
	if(currentCarNumber>=MAX_CARNUM)
		currentCarNumber=0;
	updateCarNumberTextArea();
    if (nextButtonClickedCallback)
    	nextButtonClickedCallback->execute(*this);
}

void CarSelector::updateCarNumberTextArea(){
	Unicode::snprintf(carNumberTextBuffer,CARNUMBERTEXT_SIZE,"%02d",currentCarNumber+1);
	carNumberText.invalidate();
}
void CarSelector::setCarNumber(uint8_t value) {
    currentCarNumber = value;
    updateCarNumberTextArea();
}
uint8_t CarSelector::getCarNumber() const {
    return currentCarNumber;
}

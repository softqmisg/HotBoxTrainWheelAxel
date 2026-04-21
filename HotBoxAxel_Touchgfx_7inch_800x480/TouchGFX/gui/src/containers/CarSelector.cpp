#include <gui/containers/CarSelector.hpp>
#include <gui/mainscreen_screen/mainScreenView.hpp>
#include "Car.h"
CarSelector::CarSelector():
parentView(nullptr),
currentCarNumber(1)
{

}

void CarSelector::initialize()
{
    CarSelectorBase::initialize();
    updateCarNumberTextArea();
}
void CarSelector::nextButtonClicked(){
	currentCarNumber++;
	if(currentCarNumber>=MAX_CARNUM)
		currentCarNumber=0;
	updateCarNumberTextArea();
    // Notify parent view (Screen1View) about value change
    if (parentView != nullptr) {
        parentView->onCarNumberChanged(currentCarNumber);
    }
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

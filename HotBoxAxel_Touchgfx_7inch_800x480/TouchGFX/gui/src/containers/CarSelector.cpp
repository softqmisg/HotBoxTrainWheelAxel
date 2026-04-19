#include <gui/containers/CarSelector.hpp>
#include <gui/mainscreen_screen/mainScreenView.hpp>
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
	if(currentCarNumber>MAX_CARNUMBER)
		currentCarNumber=1;
	updateCarNumberTextArea();
    // Notify parent view (Screen1View) about value change
    if (parentView != nullptr) {
        parentView->onCarNumberChanged(currentCarNumber);
    }
}
void CarSelector::updateCarNumberTextArea(){
	Unicode::snprintf(carNumberTextBuffer,CARNUMBERTEXT_SIZE,"%02d",currentCarNumber);
	carNumberText.invalidate();
}
void CarSelector::setCarNumber(uint8_t value) {
    currentCarNumber = value;
    updateCarNumberTextArea();
}

uint8_t CarSelector::getCarNumber() const {
    return currentCarNumber;
}

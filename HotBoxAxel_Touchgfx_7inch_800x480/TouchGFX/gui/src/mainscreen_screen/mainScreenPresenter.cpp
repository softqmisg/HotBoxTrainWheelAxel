#include <gui/mainscreen_screen/mainScreenView.hpp>
#include <gui/mainscreen_screen/mainScreenPresenter.hpp>

mainScreenPresenter::mainScreenPresenter(mainScreenView& v)
    : view(v)
{

}

void mainScreenPresenter::activate()
{
    // When screen becomes active, load saved value
    view.updateCarNumber(getSavedCarNumber());
}

void mainScreenPresenter::deactivate()
{

}


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

#include <gui/containers/passwordPopup.hpp>

PasswordPopup::PasswordPopup()
{

}

void PasswordPopup::initialize()
{
    PasswordPopupBase::initialize();
}
void PasswordPopup::okButtonClicked(){
}
void PasswordPopup::exitButtonClicked(){
	this->setVisible(false);
	this->invalidate();
}

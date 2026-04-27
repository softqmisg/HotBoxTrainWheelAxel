#include <gui/containers/passwordPopup.hpp>

PasswordPopup::PasswordPopup()
{

}

void PasswordPopup::initialize()
{
    PasswordPopupBase::initialize();
}
void PasswordPopup::setPasswordEditCallback(GenericCallback< const PasswordPopup&>&callback
		)
{
	passwordEditCallback=&callback;
}
void PasswordPopup::okButtonClicked(){
	 application().gotosettingScreenScreenNoTransition();

}
void PasswordPopup::exitButtonClicked(){
	this->setVisible(false);
	this->invalidate();
}
void PasswordPopup::userToggleClicked(){

}
void PasswordPopup::paswordEditClicked(){
	if(passwordEditCallback) passwordEditCallback->execute(*this);
}

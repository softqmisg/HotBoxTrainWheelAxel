#include <gui/containers/passwordPopup.hpp>
#include  <gui/containers/Keyboard.hpp>
PasswordPopup::PasswordPopup():
passwordEditable(Editable(passwordText,passwordTextBuffer)),
keyboardText()
{

}

void PasswordPopup::initialize()
{
    PasswordPopupBase::initialize();

}
void PasswordPopup::cleanPassword()
{
	Unicode::snprintf(passwordTextBuffer,PASSWORDTEXT_SIZE,"");
	passwordText.invalidate();
}
void PasswordPopup::setPasswordEditCallback(
		GenericCallback< const PasswordPopup&>&callback
		)
{
	passwordEditCallback=&callback;
}
void PasswordPopup::exitButtonClicked(){
	this->setVisible(false);
	this->invalidate();
}
void PasswordPopup::okButtonClicked(){
	 application().gotosettingScreenScreenNoTransition();

}
void PasswordPopup::userToggleClicked(){

}
void PasswordPopup::paswordEditClicked(){
	keyboard.edit(passwordEditable);
//	if(passwordEditCallback) passwordEditCallback->execute(*this);
}
void PasswordPopup::keyboardAppliedClicked()
{
	if(keyboard.targets(passwordEditable))
		passwordEditable.toUTF8(keyboardText);
}
void PasswordPopup::keyboardCancelClicked()
{

}
void PasswordPopup::keyboardCharTyped(Unicode::UnicodeChar value)
{

}

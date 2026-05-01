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
    const uint16_t h = HAL::DISPLAY_HEIGHT*3/5;     // Screen height.
    const uint16_t w = HAL::DISPLAY_WIDTH*3/4;      // Screen width.
    const uint16_t offsetX=(HAL::DISPLAY_WIDTH-w)/2;
    const uint16_t offsetY=HAL::DISPLAY_HEIGHT-h;
    keyboard.initialize(w,h);
    keyboard.setXY(offsetX, offsetY);
    keyboard.setTimout(5000);


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

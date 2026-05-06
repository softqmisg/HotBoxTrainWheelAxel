#include <gui/containers/passwordPopup.hpp>
#include  <gui/containers/Keyboard.hpp>
#include <touchgfx/Color.hpp>
PasswordPopup::PasswordPopup():
passwordEditable(Editable(passwordText,passwordTextBuffer)),
keyboardText(),
startTimer(false),
startTimerWrong(false),
counterTimout(0),
counterPasswrong(0),
isTogglePressed(false)
{
	Application::getInstance()->registerTimerWidget(this);
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

    resetTimerTimeout();
    startTimer=true;

}
void PasswordPopup::setOKCallback(
		GenericCallback<bool,char *>&callback
		)
{
	okCallback=&callback;
}
/////////////Timer Methods/////////////////////////////
void PasswordPopup::resetTimerPassWrong()
{
	counterPasswrong=(PASSWRONGSHOW_MS*60)/1000;
	if (counterPasswrong < 1) counterPasswrong = 1;
}
void PasswordPopup::resetTimerTimeout()
{
	counterTimout=(TIMEOUT_MS*60)/1000;
	if (counterTimout < 1) counterTimout = 1;

}
void PasswordPopup::handleTickEvent()
{
    if(startTimer)
    {
    	counterTimout--;
    	if(counterTimout<=0)
    		cancelButtonClicked();
    }
    if(startTimerWrong)
    {
    	counterPasswrong--;
    	if(counterPasswrong<=0)
    	{
    		showWrongPass(false);
    	}
    }
}
///////Toggle/OK/CANCEL Button & edit//////////////////////////
void PasswordPopup::userToggleClicked(){
	resetTimerTimeout();
	isTogglePressed=userToggleButton.getState();
}
void PasswordPopup::cancelButtonClicked(){
	resetTimerTimeout();
	startTimer=false;
	keyboardText[0]='\0';
	showPopup(false);
}
void PasswordPopup::okButtonClicked(){
	resetTimerTimeout();
	startTimer=false;
	if(okCallback) okCallback->execute(isTogglePressed,keyboardText);
}
void PasswordPopup::paswordEditClicked(){
	showWrongPass(false);
	cleanPassword();
	keyboard.edit(passwordEditable);
}

///////Keyboard Events//////////////////////////
void PasswordPopup::keyboardAppliedClicked()
{
	if(keyboard.targets(passwordEditable))
	{
		startTimer=true;
		passwordEditable.toUTF8(keyboardText);
		for (int i = 0; i < PASSWORDTEXT_SIZE - 1; i++)
		{
		    passwordTextBuffer[i] = (Unicode::UnicodeChar)'*';
		}
		passwordTextBuffer[PASSWORDTEXT_SIZE - 1] = 0; // Null terminate
		passwordText.invalidate();
	}
}
void PasswordPopup::keyboardCancelClicked()
{
	resetTimerTimeout();
	startTimer=true;
	keyboardText[0]='\0';
	cleanPassword();
}
void PasswordPopup::keyboardCharTyped(Unicode::UnicodeChar value)
{

}

////////Ui Methods////////////
void PasswordPopup::cleanPassword()
{
	Unicode::snprintf(passwordTextBuffer,PASSWORDTEXT_SIZE,"");
	passwordText.invalidate();
}
void PasswordPopup::showPopup(bool show)
{
	resetTimerTimeout();
	startTimer=show;
	this->setVisible(show);
	this->invalidate();
}
void PasswordPopup::showWrongPass(bool show)
{
	resetTimerPassWrong();
	startTimerWrong=show;
	keyboardText[0]='\0';
	passWrong.setVisible(show);
	passWrong.invalidate();
}
////////////General methods on Variables///////////////////////////
void PasswordPopup::setIsTogglePressed(bool isAdmin){
	isTogglePressed=isAdmin;
	userToggleButton.forceState(isAdmin);
}

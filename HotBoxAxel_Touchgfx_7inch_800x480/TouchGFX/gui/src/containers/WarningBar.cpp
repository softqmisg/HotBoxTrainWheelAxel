#include <gui/containers/WarningBar.hpp>
#include<texts/TextKeysAndLanguages.hpp>
WarningBar::WarningBar()
{

}

void WarningBar::initialize()
{
    WarningBarBase::initialize();
}
void WarningBar::setAcceptButtonClickedCallback(GenericCallback<const WarningBar&>&callback)
{
	acceptButtonClickedCallback = &callback;
}
void WarningBar::acceptButtonClicked()
{
	warningTextTime.setVisible(false);
	warningTextCar.setVisible(false);
	acceptButton.setVisible(false);

	warningTextTime.invalidate();
	warningTextCar.invalidate();
	acceptButton.invalidate();



	if(acceptButtonClickedCallback)
		acceptButtonClickedCallback->execute(*this);
}

void WarningBar::setWarning(uint8_t carnum,uint8_t axelnum,
		uint8_t hour,uint8_t minute,
		uint8_t day,uint8_t month,uint16_t year
		)
{

	warningTextTime.setVisible(true);
	warningTextCar.setVisible(true);
	acceptButton.setVisible(true);

	Unicode::snprintf(warningTextCarBuffer1, WARNINGTEXTCARBUFFER1_SIZE, "%2d",carnum);
	Unicode::snprintf(warningTextCarBuffer2, WARNINGTEXTCARBUFFER2_SIZE, "%d",axelnum);

	Unicode::snprintf(warningTextTimeBuffer1, WARNINGTEXTTIMEBUFFER1_SIZE,
			"%02d:%02d",hour,minute);
	Unicode::snprintf(warningTextTimeBuffer2, WARNINGTEXTTIMEBUFFER2_SIZE,
			"%04d/%02d/%02d",year,month,day);
//	warningTextCar.resizeToCurrentText();
//	warningTextTime.resizeToCurrentText();
	warningTextTime.invalidate();
	warningTextCar.invalidate();
	acceptButton.invalidate();

}

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
void WarningBar::setVisibleTextButton(bool state)
{
	warningTextTime.setVisible(state);
	warningText.setVisible(state);
	acceptButton.setVisible(state);

	warningTextTime.invalidate();
	warningText.invalidate();
	acceptButton.invalidate();
}
void WarningBar::acceptButtonClicked()
{
	if(acceptButtonClickedCallback)
		acceptButtonClickedCallback->execute(*this);
}
void WarningBar::setWarning(uint16_t errorcode,
		SystemSubtype subtype,
		uint8_t hours, uint8_t minutes,
		uint16_t year,uint8_t month,uint8_t day)
{

	Unicode::snprintf(warningTextBuffer, WARNINGTEXT_SIZE, "SYSTEM:%2d:%2d",(int)subtype,errorcode);

	Unicode::snprintf(warningTextTimeBuffer1, WARNINGTEXTTIMEBUFFER1_SIZE,
			"%02d:%02d",hours,minutes);
	Unicode::snprintf(warningTextTimeBuffer2, WARNINGTEXTTIMEBUFFER2_SIZE,
			"%04d/%02d/%02d",year,month,day);


	warningTextTime.invalidate();
	warningText.invalidate();

}
void WarningBar::setWarning(uint8_t carnum,uint8_t senID,
		SensorSubtype subtype,
		uint8_t hours,uint8_t minutes,
		uint16_t year,uint8_t month,uint8_t day
		)
{
	if(subtype==SensorSubtype::SENSOR_TEMPOUTRANGE)
	{
		Unicode::snprintf(warningTextBuffer, WARNINGTEXT_SIZE, "OUT@CAR#%02d:%d",(int)carnum+1,senID+1);
	}
	else if(subtype==SensorSubtype::SENSOR_TEMPNOTRECEIVED)
	{
		Unicode::snprintf(warningTextBuffer, WARNINGTEXT_SIZE, "CAR#%02d:%d",(int)carnum+1,senID+1);

	}

	Unicode::snprintf(warningTextTimeBuffer1, WARNINGTEXTTIMEBUFFER1_SIZE,
			"%02d:%02d",hours,minutes);
	Unicode::snprintf(warningTextTimeBuffer2, WARNINGTEXTTIMEBUFFER2_SIZE,
			"%04d/%02d/%02d",year,month,day);


	warningTextTime.invalidate();
	warningText.invalidate();

}

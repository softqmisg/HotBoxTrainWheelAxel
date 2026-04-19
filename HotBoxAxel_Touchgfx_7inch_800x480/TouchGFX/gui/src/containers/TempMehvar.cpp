#include <gui/containers/TempMehvar.hpp>

TempMehvar::TempMehvar()
{

}

void TempMehvar::initialize()
{
    TempMehvarBase::initialize();
}

void TempMehvar::setID(uint8_t id)
{
	Unicode::snprintf(numMehvarTextBuffer, NUMMEHVARTEXT_SIZE, "%d", id);
	numMehvarText.invalidate();
}

void TempMehvar::setState(TempMehvar::State state){
	if(state==State::NORMAL){
		tempAreaBox.setColor(touchgfx::Color::getColorFromRGB(0x5C, 0xF0,0x00));
	}
	else
	{
		tempAreaBox.setColor(touchgfx::Color::getColorFromRGB(0xE6, 0x0E,0x0E));
	}
	tempAreaBox.invalidate();
}

void TempMehvar::setTemperature(int16_t temperature){
	if(temperature==ERROR_TEMP)
	{
		Unicode::snprintf(tempTextBuffer, TEMPTEXT_SIZE, "----");
	}
	else
	{
		Unicode::snprintf(tempTextBuffer, TEMPTEXT_SIZE, "%+3i",temperature);
	}
	tempText.invalidate();
}

void TempMehvar::updateData(uint8_t id,TempMehvar::State state,int16_t temperature){
	setID(id);
	setState(state);
	setTemperature(temperature);
}

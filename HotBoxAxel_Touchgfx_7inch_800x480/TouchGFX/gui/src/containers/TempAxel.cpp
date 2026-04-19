#include <gui/containers/TempAxel.hpp>
#include <touchgfx/Color.hpp>
TempAxel::TempAxel()
{

}

void TempAxel::initialize()
{
    TempAxelBase::initialize();
}

void TempAxel::setID(uint8_t id)
{
	Unicode::snprintf(numAxelTextBuffer, NUMAXELTEXT_SIZE, "%d", id);
	numAxelText.invalidate();
}

void TempAxel::setState(TempAxel::State state){
	if(state==State::NORMAL){
		tempAreaBox.setColor(touchgfx::Color::getColorFromRGB(0x5C, 0xF0,0x00));
	}
	else
	{
		tempAreaBox.setColor(touchgfx::Color::getColorFromRGB(0xE6, 0x0E,0x0E));
	}
	tempAreaBox.invalidate();
}

void TempAxel::setTemperature(int16_t temperature){
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

void TempAxel::updateData(uint8_t id,TempAxel::State state,int16_t temperature){
	setID(id);
	setState(state);
	setTemperature(temperature);
}

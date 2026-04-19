#include <gui/containers/Led.hpp>
#include <touchgfx/Color.hpp>
Led::Led()
{

}

void Led::initialize()
{
    LedBase::initialize();
}
//void Led::setTitle(const char *text){
//
//	Unicode::snprintf(titleTextBuffer, TITLETEXT_SIZE, "%s", text);
//	titleText.invalidate();
//}
void Led::setTitle(uint8_t id){
	switch(id){
	case 0:
		Unicode::snprintf(titleTextBuffer, TITLETEXT_SIZE, "Main");
		break;
	case 1:
		Unicode::snprintf(titleTextBuffer, TITLETEXT_SIZE, "Alarm");
		break;
	case 2:
		Unicode::snprintf(titleTextBuffer, TITLETEXT_SIZE, "Comm");
		break;
	}

	titleText.invalidate();
}

void Led::setState(Led::State state){
	if(state==State::GREEN){
		stateCirclePainter.setColor(touchgfx::Color::getColorFromRGB(0x00, 0xFA,0x15));
	}
	else{
		stateCirclePainter.setColor(touchgfx::Color::getColorFromRGB(0xE6, 0x0E,0x0E));
	}
	stateCircle.invalidate();

}

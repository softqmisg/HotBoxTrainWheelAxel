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
void Led::setTitle(const char *name){
    Unicode::fromUTF8((const uint8_t *)name, titleTextBuffer, TITLETEXT_SIZE);
	titleText.invalidate();
}

void Led::setState(Led::Color state){
	if(state==Color::GREEN){
		stateCirclePainter.setColor(touchgfx::Color::getColorFromRGB(0x00, 0xFA,0x15));
	}
	else if(state==Color::RED){
		stateCirclePainter.setColor(touchgfx::Color::getColorFromRGB(0xE6, 0x0E,0x0E));
	}
	else  if(state==Color::GREY){
		stateCirclePainter.setColor(touchgfx::Color::getColorFromRGB(0x80, 0x80,0x80));
	}

	stateCircle.invalidate();

}

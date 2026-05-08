#include <gui/containers/SliderWithLabel.hpp>

SliderWithLabel::SliderWithLabel()
{

}

void SliderWithLabel::initialize()
{
    SliderWithLabelBase::initialize();
}
void SliderWithLabel::updateValueText(int value)
{
	if(!isInit)
	{
		Unicode::snprintf(valueTextBuffer, VALUETEXT_SIZE, "%02d",value);
		valueText.invalidate();
		emitValueChangeCallback(value);
	}
	isInit=false;
}
void SliderWithLabel::setValueRange(uint8_t min,uint8_t max)
{
	valueSlider.setValueRange(min, max);
}
void SliderWithLabel::setValue(uint8_t value){
	valueSlider.setValue(value);
	updateValueText(value);
}
uint8_t SliderWithLabel::getValue(){
	return valueSlider.getValue();
}

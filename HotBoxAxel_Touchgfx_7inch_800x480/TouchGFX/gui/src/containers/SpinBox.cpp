#include <gui/containers/SpinBox.hpp>

SpinBox::SpinBox():
currentValue(0)
{

}

void SpinBox::initialize()
{
    SpinBoxBase::initialize();
    for(int i = 0; i < VALUETEXTAREA_SIZE - 1; i++) {
         valueTextAreaBuffer[i] = ' ';
     }
     valueTextAreaBuffer[VALUETEXTAREA_SIZE - 1] = '\0';
     setValue(currentValue);
}


void SpinBox::upButtonClicked(){
	currentValue++;
	setValue(currentValue);
}
void SpinBox::downButtonClicked() {
	currentValue--;
	setValue(currentValue);
}
void SpinBox::clearBuffer(){

	 for (int i = 0; i < VALUETEXTAREA_SIZE - 1; i++) {
	        valueTextAreaBuffer[i] = ' ';
	    }
	    valueTextAreaBuffer[VALUETEXTAREA_SIZE - 1] = '\0';
}
void SpinBox::setValue(int16_t value){
	currentValue=value;
	clearBuffer();
	Unicode::snprintf(valueTextAreaBuffer, VALUETEXTAREA_SIZE, "%+04d",value);
	valueTextArea.invalidate();
}

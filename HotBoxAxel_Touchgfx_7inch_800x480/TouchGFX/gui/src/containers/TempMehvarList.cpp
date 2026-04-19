#include <gui/containers/TempMehvarList.hpp>
#include <gui/containers/TempMehvar.hpp>

TempMehvarList::TempMehvarList()
{

}

void TempMehvarList::initialize()
{
    TempMehvarListBase::initialize();
    tempMehvar1.setID(1);
    tempMehvar2.setID(2);
    tempMehvar3.setID(3);
    tempMehvar4.setID(4);
    tempMehvar5.setID(5);
    tempMehvar6.setID(6);
    tempMehvar7.setID(7);
    tempMehvar8.setID(8);
}
void TempMehvarList::updateItem(uint8_t id,TempMehvar::State state,int16_t temperature)
{
	updateStateItem(id,state);
	updateTempItem(id,temperature);
}
void TempMehvarList::updateStateItem(uint8_t id,TempMehvar::State state){
	switch(id)
	{
	case 1:
		tempMehvar1.setState(state);
		break;
	case 2:
		tempMehvar2.setState(state);
		break;
	case 3:
		tempMehvar3.setState(state);
		break;
	case 4:
		tempMehvar4.setState(state);
		break;
	case 5:
		tempMehvar5.setState(state);
		break;
	case 6:
		tempMehvar6.setState(state);
		break;
	case 7:
		tempMehvar7.setState(state);
		break;
	case 8:
		tempMehvar8.setState(state);
		break;

	}
}
void TempMehvarList::updateTempItem(uint8_t id,int16_t temperature){
	switch(id){
	case 1:
		tempMehvar1.setTemperature(temperature);
		break;
	case 2:
		tempMehvar2.setTemperature(temperature);
		break;
	case 3:
		tempMehvar3.setTemperature(temperature);
		break;
	case 4:
		tempMehvar4.setTemperature(temperature);
		break;
	case 5:
		tempMehvar5.setTemperature(temperature);
		break;
	case 6:
		tempMehvar6.setTemperature(temperature);
		break;
	case 7:
		tempMehvar7.setTemperature(temperature);
		break;
	case 8:
		tempMehvar8.setTemperature(temperature);
		break;
	}
}

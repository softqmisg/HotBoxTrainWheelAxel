#include <gui/containers/TempAxelList.hpp>

TempAxelList::TempAxelList()
{

}

void TempAxelList::initialize()
{
    TempAxelListBase::initialize();
    tempAxel1.setID(1);
    tempAxel2.setID(2);
    tempAxel3.setID(3);
    tempAxel4.setID(4);
    tempAxel5.setID(5);
    tempAxel6.setID(6);
    tempAxel7.setID(7);
    tempAxel8.setID(8);
}
void TempAxelList::updateItem(uint8_t id,TempAxel::State state,int16_t temperature)
{
	updateStateItem(id,state);
	updateTempItem(id,temperature);
}
void TempAxelList::updateStateItem(uint8_t id,TempAxel::State state){
	switch(id)
	{
	case 1:
		tempAxel1.setState(state);
		break;
	case 2:
		tempAxel2.setState(state);
		break;
	case 3:
		tempAxel3.setState(state);
		break;
	case 4:
		tempAxel4.setState(state);
		break;
	case 5:
		tempAxel5.setState(state);
		break;
	case 6:
		tempAxel6.setState(state);
		break;
	case 7:
		tempAxel7.setState(state);
		break;
	case 8:
		tempAxel8.setState(state);
		break;

	}
}
void TempAxelList::updateTempItem(uint8_t id,int16_t temperature){
	switch(id){
	case 1:
		tempAxel1.setTemperature(temperature);
		break;
	case 2:
		tempAxel2.setTemperature(temperature);
		break;
	case 3:
		tempAxel3.setTemperature(temperature);
		break;
	case 4:
		tempAxel4.setTemperature(temperature);
		break;
	case 5:
		tempAxel5.setTemperature(temperature);
		break;
	case 6:
		tempAxel6.setTemperature(temperature);
		break;
	case 7:
		tempAxel7.setTemperature(temperature);
		break;
	case 8:
		tempAxel8.setTemperature(temperature);
		break;
	}
}

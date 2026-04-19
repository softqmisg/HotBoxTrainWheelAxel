#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0),saveCarNumberValue(1)
{

}

void Model::tick()
{
    // Called periodically by the framework
}
void Model::saveCarNumber(int carNum){
	saveCarNumberValue=carNum;
}
int  Model::getCarNumber() const{
	return saveCarNumberValue;
}

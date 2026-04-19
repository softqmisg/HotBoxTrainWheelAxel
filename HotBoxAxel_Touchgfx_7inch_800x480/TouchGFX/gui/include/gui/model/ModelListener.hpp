#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

	void bind(Model* m)
    {
        model = m;
    }
    // Virtual methods that can be overridden by Presenter
    virtual void onCarNumberChanged(int newValue) {}

    virtual void timeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds) {}
	virtual void dateUpdated(uint8_t day, uint8_t month, uint16_t year) {}
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP

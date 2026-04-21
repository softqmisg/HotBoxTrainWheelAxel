#ifndef TEMPAXELLIST_HPP
#define TEMPAXELLIST_HPP

#include <gui_generated/containers/TempAxelListBase.hpp>
#include "Car.h"
class TempAxelList : public TempAxelListBase
{
public:
    TempAxelList();
    virtual ~TempAxelList() {}

    virtual void initialize();
    void updateItem(uint8_t id,Car::TempState state,int16_t temperature);
    void updateStateItem(uint8_t id,Car::TempState state);
    void updateTempItem(uint8_t id,int16_t temperature);
    void updateTempAllItems(Car carData);
protected:
};

#endif // TEMPAXELLIST_HPP

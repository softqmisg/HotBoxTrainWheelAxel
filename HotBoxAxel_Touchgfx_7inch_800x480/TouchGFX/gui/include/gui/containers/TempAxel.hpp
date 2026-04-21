#ifndef TEMPAXEL_HPP
#define TEMPAXEL_HPP

#include <gui_generated/containers/TempAxelBase.hpp>
#define ERROR_TEMP 32767

class TempAxel : public TempAxelBase
{
public:
    TempAxel();
    virtual ~TempAxel() {}

    virtual void initialize();
    void setState(Car::TempState state);
    void setID(uint8_t id);
    void setTemperature(int16_t temperature);
    void updateData(uint8_t id,Car::TempState state,int16_t temperature);
protected:
};

#endif // TEMPAXEL_HPP

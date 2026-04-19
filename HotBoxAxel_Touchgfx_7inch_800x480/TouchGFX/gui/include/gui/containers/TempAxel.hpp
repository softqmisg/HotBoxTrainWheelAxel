#ifndef TEMPAXEL_HPP
#define TEMPAXEL_HPP

#include <gui_generated/containers/TempAxelBase.hpp>

class TempAxel : public TempAxelBase
{
public:
    TempAxel();
    virtual ~TempAxel() {}

    virtual void initialize();
    enum class State{NORMAL,ERROR};
    void setState(TempAxel::State state);
    void setID(uint8_t id);
    void setTemperature(int16_t temperature);
    void updateData(uint8_t id,TempAxel::State state,int16_t temperature);
    const int16_t ERROR_TEMP=65535;
protected:
};

#endif // TEMPAXEL_HPP

#ifndef TEMPMEHVAR_HPP
#define TEMPMEHVAR_HPP

#include <gui_generated/containers/TempMehvarBase.hpp>
#include <touchgfx/Color.hpp>
class TempMehvar : public TempMehvarBase
{
public:
    TempMehvar();
    virtual ~TempMehvar() {}

    virtual void initialize();
    enum class State{NORMAL,ERROR};
    void setState(TempMehvar::State state);
    void setID(uint8_t id);
    void setTemperature(int16_t temperature);
    void updateData(uint8_t id,TempMehvar::State state,int16_t temperature);
    const int16_t ERROR_TEMP=65535;
protected:
};

#endif // TEMPMEHVAR_HPP

#ifndef TEMPMEHVARLIST_HPP
#define TEMPMEHVARLIST_HPP

#include <gui_generated/containers/TempMehvarListBase.hpp>

class TempMehvarList : public TempMehvarListBase
{
public:
    TempMehvarList();
    virtual ~TempMehvarList() {}

    virtual void initialize();
    void updateItem(uint8_t id,TempMehvar::State state,int16_t temperature);
    void updateStateItem(uint8_t id,TempMehvar::State state);
    void updateTempItem(uint8_t id,int16_t temperature);

protected:
};

#endif // TEMPMEHVARLIST_HPP

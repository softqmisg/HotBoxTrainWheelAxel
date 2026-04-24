#ifndef TOPBAR_HPP
#define TOPBAR_HPP

#include <gui_generated/containers/TopBarBase.hpp>

class TopBar : public TopBarBase
{
public:
    TopBar();
    virtual ~TopBar() {}

    virtual void initialize();


    void setDate(uint8_t day, uint8_t month, uint16_t year, uint8_t dayofweek);
    void setClock(uint8_t hours, uint8_t minutes, uint8_t seconds);
    void setEnvTemperature(int16_t temp);
    void setEnvTemperatureVisible(bool visible){envTempText.setVisible(visible);}
    void setExitButtonVisible(bool visible){buttonWithLabel.setVisible(visible);}
    virtual void exitButtonClicked();
    void setExitButtonClickedCallback(GenericCallback<const TopBar&>& callback);

protected:
private:
    GenericCallback<const TopBar&>* exitButtonClickCallback{nullptr};

};

#endif // TOPBAR_HPP

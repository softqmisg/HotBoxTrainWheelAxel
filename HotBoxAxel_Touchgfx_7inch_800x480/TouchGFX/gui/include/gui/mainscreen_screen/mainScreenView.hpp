#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/mainScreenViewBase.hpp>
#include <gui/mainscreen_screen/mainScreenPresenter.hpp>
#include <gui/containers/CarSelector.hpp>

class mainScreenView : public mainScreenViewBase
{
public:
    mainScreenView();
    virtual ~mainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void setPresenter(mainScreenPresenter& presenter) { this->presenter = &presenter; }

    ////////////////carSelector//////////////////
    // Called by CarSelector when value changes
    void onCarNumberChanged(uint8_t newValue);
    // Called by Presenter to update UI
    void updateCarNumber(uint8_t value);
    ////////////////digitalClock////////////////////////////
    // Update methods called by Presenter
       void updateClock(uint8_t hours, uint8_t minutes, uint8_t seconds);
       void updateDate(uint8_t day, uint8_t month, uint16_t year);


//    enum class LEDTYPE{ MAIN,ALARM,COMM};
//    void updateDate();
//    void updateTime();
//    void updateEnvTemp();
//    void updateCarNumber();
//    void updateMehvar(uint8_t id,TempMehvar::State state,int16_t temperatur);
//    void updateLedState(mainScreenView::LEDTYPE ledtype,Led::State state);
protected:
    mainScreenPresenter* presenter;
};

#endif // MAINSCREENVIEW_HPP

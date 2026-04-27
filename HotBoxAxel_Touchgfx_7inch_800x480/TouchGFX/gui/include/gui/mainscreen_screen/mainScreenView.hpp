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
//    void setPresenter(mainScreenPresenter& presenter) { this->presenter = &presenter; }

    ////////////////digitalClock////////////////////////////
    // Update methods called by Presenter
    void updateClock(uint8_t hours, uint8_t minutes, uint8_t seconds);
    void updateDate(uint8_t day, uint8_t month, uint16_t year);
    ////////////////carSelector//////////////////
    void updateCarNumber(uint8_t value);    // Called by Presenter to update UI
    void onCarNumberChanged(const CarSelector& selector);    // Called by CarSelector when value changes
    /////////////////AxelTemperature///////////////////////
    void updateCarTemperatures(Car carData);
//    //////////////////EnvTemperature//////////////////////
//    void updateEnvTemperature(int16_t temp);

//    enum class LEDTYPE{ MAIN,ALARM,COMM};
//    void updateLedState(mainScreenView::LEDTYPE ledtype,Led::State state);
    /////////////////////led /////////////////////////
    void updateLedMainColor(LedParam::ColorState colorState);
    void updateLedAlarmColor(LedParam::ColorState colorState);
    void updateLedCommColor(LedParam::ColorState colorState);
    //////////////////Warning///////////////////
    void updateWarning();
    void onWarningAcceptButtonClicked(const WarningBar& warning);
    /////////Setting Button////////////
    virtual void settingButtonClicked();
    ////////////password popup////////////////

private:
    Callback<mainScreenView, const CarSelector&> carNumberChangedCallback;
    Callback<mainScreenView, const WarningBar&> warningAcceptClickedCallback;

//    char keyboardPasswordText[PASSWORDTEXT_SIZE];

    uint8_t test_car=0,test_axel=0;

};

#endif // MAINSCREENVIEW_HPP

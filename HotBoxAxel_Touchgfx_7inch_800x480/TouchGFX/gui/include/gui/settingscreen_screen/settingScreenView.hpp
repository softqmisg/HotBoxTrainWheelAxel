#ifndef SETTINGSCREENVIEW_HPP
#define SETTINGSCREENVIEW_HPP

#include <gui_generated/settingscreen_screen/settingScreenViewBase.hpp>
#include <gui/settingscreen_screen/settingScreenPresenter.hpp>
#include <gui/common/Editable.hpp>

class settingScreenView : public settingScreenViewBase
{
public:
    settingScreenView();
    virtual ~settingScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent() override;
    ////////////////digitalClock////////////////////////////
    // Update methods called by Presenter
    void updateClock(uint8_t hours, uint8_t minutes, uint8_t seconds);
    void updateDate(uint8_t day, uint8_t month, uint16_t year);
    //////////////////////////////////////////////////////
    void onExitButtonClicked(const TopBar& bar);
    void  exitScreen();
    ////////////////////Page1////////////////////////////////////

    void onVolumeSliderConfirmed(const uint8_t value);
    void onBrightnessSliderChanged(const uint8_t value);
    uint8_t getBrightness();
    void setBrightness(uint8_t brightness);
protected:
    void locoEditClicked() override;
    void keyboardAppliedClicked() override;
    void keyboardCancelClicked() override;
    void keyboardCharTyped(Unicode::UnicodeChar value) override;
private:
    Callback<settingScreenView, const TopBar&> exitButtonClickedCallback;
    Callback<settingScreenView, const uint8_t> volumeSliderConfirmedCallback;
    Callback<settingScreenView, const uint8_t> brightnessSliderChangedCallback;

    Editable locoEditable;
    char keyboardText[LOCOEDITTEXT_SIZE];
    int previousPageIndex;
    void onPageChanged(int newPage);

};

#endif // SETTINGSCREENVIEW_HPP

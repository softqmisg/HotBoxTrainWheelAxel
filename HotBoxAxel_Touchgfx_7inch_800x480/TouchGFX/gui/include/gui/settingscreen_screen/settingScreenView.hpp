#ifndef SETTINGSCREENVIEW_HPP
#define SETTINGSCREENVIEW_HPP

#include <gui_generated/settingscreen_screen/settingScreenViewBase.hpp>
#include <gui/settingscreen_screen/settingScreenPresenter.hpp>

class settingScreenView : public settingScreenViewBase
{
public:
    settingScreenView();
    virtual ~settingScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    ////////////////digitalClock////////////////////////////
    // Update methods called by Presenter
    void updateClock(uint8_t hours, uint8_t minutes, uint8_t seconds);
    void updateDate(uint8_t day, uint8_t month, uint16_t year);
    //////////////////////////////////////////////////////
    void onExitButtonClicked(const TopBar& bar);
    void  exitScreen();
protected:
private:
    Callback<settingScreenView, const TopBar&> exitButtonClickedCallback;

};

#endif // SETTINGSCREENVIEW_HPP

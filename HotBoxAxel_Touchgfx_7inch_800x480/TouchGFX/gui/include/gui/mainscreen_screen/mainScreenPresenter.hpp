#ifndef MAINSCREENPRESENTER_HPP
#define MAINSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include "EventLogger.h"
using namespace touchgfx;

class mainScreenView;

class mainScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    mainScreenPresenter(mainScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~mainScreenPresenter() {}
    //handle digitalClock
    void requestTimeDateUpdate();
    virtual void timeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds) override;     // Called from Model (via ModelListener)
    virtual void dateUpdated(uint8_t day, uint8_t month, uint16_t year) override;    // Called from Model (via ModelListener)
    void setCalenderType(Model::CalenderType type);
    Model::CalenderType getCalenderType();

    //handle CarSelector
    virtual void carNumberUpdated(uint8_t carNum) override;
    void saveCarNumber(uint8_t carNum);// Method to update counter value from view
    int getSavedCarNumber();    // Method to get current saved counter value
    //handle AxelTemp & envTemp
    void requestCarTempUpdate(uint8_t carNum);
    virtual void carTempUpdated(Car car) override;
    //handle Leds
    void requestLedColorUpdate();
    virtual void ledColorUpdated(uint8_t ledId, LedParam::ColorState colorState) override;
    ////Warning Handle/////////////////////
    void requestWarningUpdate();
    virtual void warnigTextUpdated(EventEntry *event) override;
    virtual void navigateWarningUpdated() override;

private:
    mainScreenView& view;

};

#endif // MAINSCREENPRESENTER_HPP

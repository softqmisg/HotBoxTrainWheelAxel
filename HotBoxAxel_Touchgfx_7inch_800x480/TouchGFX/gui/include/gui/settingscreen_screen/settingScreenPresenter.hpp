#ifndef SETTINGSCREENPRESENTER_HPP
#define SETTINGSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class settingScreenView;

class settingScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    settingScreenPresenter(settingScreenView& v);

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

    virtual ~settingScreenPresenter() {}
    //handle digitalClock
    void requestTimeDateUpdate();
    virtual void timeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds) override;     // Called from Model (via ModelListener)
    virtual void dateUpdated(uint8_t day, uint8_t month, uint16_t year) override;    // Called from Model (via ModelListener)
    void setCalenderType(Model::CalenderType type);
    Model::CalenderType getCalenderType();
    // handle disappear screen on exit
    void exitButtonClicked();
private:
    settingScreenPresenter();

    settingScreenView& view;
};

#endif // SETTINGSCREENPRESENTER_HPP

#ifndef MAINSCREENPRESENTER_HPP
#define MAINSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

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
    //handle CarSelector
    void requestTempUpdate(uint8_t carNum);
    void saveCarNumber(uint8_t carNum);// Method to update counter value from view
    int getSavedCarNumber();    // Method to get current saved counter value

    //handle digitalClock
    void requestTimeUpdate();
    virtual void timeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds) override;     // Called from Model (via ModelListener)
    virtual void dateUpdated(uint8_t day, uint8_t month, uint16_t year) override;    // Called from Model (via ModelListener)


private:
    mainScreenView& view;

};

#endif // MAINSCREENPRESENTER_HPP

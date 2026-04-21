#ifndef CARSELECTOR_HPP
#define CARSELECTOR_HPP

#include <gui_generated/containers/CarSelectorBase.hpp>

class mainScreenView;
class CarSelector : public CarSelectorBase
{
public:
    CarSelector();
    virtual ~CarSelector() {}

    virtual void initialize();
    // Set the parent view to communicate with presenter
     void setParentView(mainScreenView* view) { parentView = view; }

    // Public method to update counter from presenter
    void setCarNumber(uint8_t value);
    uint8_t getCarNumber() const;
protected:
    mainScreenView* parentView;
    uint8_t currentCarNumber;
    // Callback for button click (if using Callback)
    void nextButtonClicked();
    // Update the textarea display
    void updateCarNumberTextArea();
private:

};

#endif // CARSELECTOR_HPP

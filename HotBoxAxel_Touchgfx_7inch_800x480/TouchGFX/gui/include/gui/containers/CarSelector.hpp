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
    // Callback for button click (if using Callback)
    virtual void nextButtonClicked();
    void setNextButtonClickedCallback(GenericCallback<const CarSelector&>& callback);
    // Set the parent view to communicate with presenter
    // Public method to update counter from presenter
    void setCarNumber(uint8_t value);
    uint8_t getCarNumber() const;
protected:
private:
    GenericCallback<const CarSelector&>* nextButtonClickCallback{nullptr};
    uint8_t currentCarNumber;

    void updateCarNumberTextArea();


};

#endif // CARSELECTOR_HPP

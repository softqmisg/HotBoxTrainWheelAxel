#ifndef SPINBOX_HPP
#define SPINBOX_HPP

#include <gui_generated/containers/SpinBoxBase.hpp>

class SpinBox : public SpinBoxBase
{
public:
    SpinBox();
    virtual ~SpinBox() {}

    virtual void initialize();
    void clearBuffer();
    virtual void upButtonClicked() override;
    virtual void downButtonClicked() override;
    void setValue(int16_t value);
    int16_t getValue(){return currentValue;};

protected:
private:
    int16_t currentValue;
};

#endif // SPINBOX_HPP

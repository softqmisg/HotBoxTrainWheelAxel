#ifndef SLIDERWITHLABEL_HPP
#define SLIDERWITHLABEL_HPP

#include <gui_generated/containers/SliderWithLabelBase.hpp>

class SliderWithLabel : public SliderWithLabelBase
{
public:
    SliderWithLabel();
    virtual ~SliderWithLabel() {}

    virtual void initialize();
    virtual void updateValueText(int value) override;
    void setValueRange(uint8_t min,uint8_t max);
    void setValue(uint8_t value);
    uint8_t getValue();
protected:
private:
    bool isInit=true;
};

#endif // SLIDERWITHLABEL_HPP

#ifndef LED_HPP
#define LED_HPP

#include <gui_generated/containers/LedBase.hpp>

class Led : public LedBase
{
public:
    Led();
    virtual ~Led() {}

    virtual void initialize();
//    void setTitle(const char *text);
    void setTitle(touchgfx::TypedTextId textId);

    enum class Color{GREY,GREEN,RED};
    void setState(Led::Color state);
protected:
};

#endif // LED_HPP

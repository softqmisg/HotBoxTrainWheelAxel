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
    void setTitle(const char* name);

    enum class State{GREEN,RED};
    void setState(Led::State state);
protected:
};

#endif // LED_HPP

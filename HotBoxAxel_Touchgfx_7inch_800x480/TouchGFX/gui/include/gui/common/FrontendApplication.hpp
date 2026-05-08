#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }
    void gotosettingScreenScreenNoTransition();
    void gotomainScreenScreenNoTransition();

protected:
    touchgfx::Callback<FrontendApplication> transitionCallback;
    void gotosettingScreenScreenNoTransitionImpl();
    void gotomainScreenScreenNoTransitionImpl();

private:
};

#endif // FRONTENDAPPLICATION_HPP

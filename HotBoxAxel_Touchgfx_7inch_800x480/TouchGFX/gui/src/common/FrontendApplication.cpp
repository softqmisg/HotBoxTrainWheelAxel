#include <gui/common/FrontendApplication.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/settingscreen_screen/settingScreenView.hpp>
#include <gui/settingscreen_screen/settingScreenPresenter.hpp>
FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap)
{

}
// settingScreen

void FrontendApplication::gotosettingScreenScreenNoTransition()
{
    transitionCallback = Callback<FrontendApplication>(this, &FrontendApplication::gotosettingScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotosettingScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<settingScreenView, settingScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

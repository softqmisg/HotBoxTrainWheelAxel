#ifndef PASSWORDPOPUP_HPP
#define PASSWORDPOPUP_HPP

#include <gui_generated/containers/passwordPopupBase.hpp>
#include <gui/common/Editable.hpp>
class mainScreenView;

class PasswordPopup : public PasswordPopupBase
{
public:
	PasswordPopup();
    virtual ~PasswordPopup() {}

    virtual void initialize();
    void handleTickEvent() override;
//    void setParentView(mainScreenView* view) { parentView = view; }
    void cleanPassword();
    void setOKCallback(GenericCallback<bool,char *>&callback);

    bool getIsTogglePressed(){return isTogglePressed;}
    void setIsTogglePressed(bool isAdmin);

    void showPopup(bool);
    void showWrongPass(bool);

protected:
    void userToggleClicked() override;
    void cancelButtonClicked() override ;
    void okButtonClicked() override ;
    void paswordEditClicked() override;

    void keyboardAppliedClicked() override;
    void keyboardCancelClicked() override;
    void keyboardCharTyped(Unicode::UnicodeChar value) override;

private:
//    mainScreenView* parentView;
    GenericCallback<bool,char*> *okCallback{nullptr};

    Editable passwordEditable;
    char keyboardText[PASSWORDTEXT_SIZE];

    bool startTimer;
    bool startTimerWrong;
    int32_t counterTimout;
    int32_t counterPasswrong;
    void resetTimerTimeout();
    void resetTimerPassWrong();
    const int32_t TIMEOUT_MS=10000;
    const int32_t PASSWRONGSHOW_MS=3000;

    bool isTogglePressed;

};

#endif // PASSWORDPOPUP_HPP

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
//    void setParentView(mainScreenView* view) { parentView = view; }
    void cleanPassword();
    void setPasswordEditCallback(	GenericCallback< const PasswordPopup&>&callback);

protected:

    void exitButtonClicked() override ;
    void okButtonClicked() override ;
    void userToggleClicked()override;
    void paswordEditClicked() override;
    void keyboardAppliedClicked() override;
    void keyboardCancelClicked() override;
    void keyboardCharTyped(Unicode::UnicodeChar value) override;

private:
//    mainScreenView* parentView;
    GenericCallback< const PasswordPopup&> *passwordEditCallback{nullptr};
    Editable passwordEditable;
    char keyboardText[PASSWORDTEXT_SIZE];

};

#endif // PASSWORDPOPUP_HPP

#ifndef PASSWORDPOPUP_HPP
#define PASSWORDPOPUP_HPP

#include <gui_generated/containers/passwordPopupBase.hpp>
class mainScreenView;

class PasswordPopup : public PasswordPopupBase
{
public:
	PasswordPopup();
    virtual ~PasswordPopup() {}

    virtual void initialize();
//    void setParentView(mainScreenView* view) { parentView = view; }
    void setPasswordEditCallback(	GenericCallback< const PasswordPopup&>&callback);

protected:

    virtual void exitButtonClicked() ;
    virtual void okButtonClicked() ;
    virtual void userToggleClicked();
    virtual void paswordEditClicked();
private:
//    mainScreenView* parentView;
    GenericCallback< const PasswordPopup&> *passwordEditCallback{nullptr};

};

#endif // PASSWORDPOPUP_HPP

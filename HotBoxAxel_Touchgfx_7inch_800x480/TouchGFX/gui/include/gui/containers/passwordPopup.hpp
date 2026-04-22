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
    void setParentView(mainScreenView* view) { parentView = view; }

protected:
    mainScreenView* parentView;
    void okButtonClicked();
    void exitButtonClicked();
};

#endif // PASSWORDPOPUP_HPP

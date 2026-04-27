#ifndef WARNINGBAR_HPP
#define WARNINGBAR_HPP

#include <gui_generated/containers/WarningBarBase.hpp>

class WarningBar : public WarningBarBase
{
public:
    WarningBar();
    virtual ~WarningBar() {}

    virtual void initialize();
    virtual void acceptButtonClicked();
    void setAcceptButtonClickedCallback(GenericCallback<const WarningBar&>&callback);
    void setWarning(uint8_t carnum,uint8_t axelnum,
    		uint8_t hour,uint8_t minute,
			uint8_t day,uint8_t month,uint16_t year
    		);
protected:
private:
    GenericCallback<const WarningBar&> *acceptButtonClickedCallback{nullptr};
};

#endif // WARNINGBAR_HPP

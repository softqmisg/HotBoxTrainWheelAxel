#ifndef WARNINGBAR_HPP
#define WARNINGBAR_HPP

#include <gui_generated/containers/WarningBarBase.hpp>
#include "EventLogger.h"
class WarningBar : public WarningBarBase
{
public:
    WarningBar();
    virtual ~WarningBar() {}

    virtual void initialize();
    virtual void acceptButtonClicked();
    void setAcceptButtonClickedCallback(GenericCallback<const WarningBar&>&callback);
    void setWarning(uint8_t carnum,uint8_t senID,SensorSubtype subtype,
    		uint8_t hours,uint8_t minutes,
			uint16_t year,uint8_t month,uint8_t day
    		);
    void setWarning(uint16_t errorcode,SystemSubtype subtype,
    						uint8_t hours, uint8_t minutes,
    						uint16_t year,uint8_t month,uint8_t day);
    void setVisibleTextButton(bool state);
protected:
private:
    GenericCallback<const WarningBar&> *acceptButtonClickedCallback{nullptr};
};

#endif // WARNINGBAR_HPP

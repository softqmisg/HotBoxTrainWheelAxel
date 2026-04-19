#ifndef WARNINGBAR_HPP
#define WARNINGBAR_HPP

#include <gui_generated/containers/WarningBarBase.hpp>

class WarningBar : public WarningBarBase
{
public:
    WarningBar();
    virtual ~WarningBar() {}

    virtual void initialize();
protected:
};

#endif // WARNINGBAR_HPP

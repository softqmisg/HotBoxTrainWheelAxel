#ifndef BOTTOMBAR_HPP
#define BOTTOMBAR_HPP

#include <gui_generated/containers/BottomBarBase.hpp>

class BottomBar : public BottomBarBase
{
public:
    BottomBar();
    virtual ~BottomBar() {}

    virtual void initialize();
    void setDefaultBottomVisible(bool state){
    	defaultButtonWithLabel.setVisible(state);
    	defaultButtonWithLabel.invalidate();
    }
    void setSaveButtomVisible(bool state){
    	saveBttonWithLabel.setVisible(state);
    	saveBttonWithLabel.invalidate();
    }
    void setDownloadButtomVisible(bool state){
    	downloadButtonWithLabel.setVisible(state);
    	downloadButtonWithLabel.invalidate();
    }
protected:
};

#endif // BOTTOMBAR_HPP

/*
 * LedParam.h
 *
 *  Created on: Apr 21, 2026
 *      Author: mehdi
 */

#ifndef INC_LEDPARAM_H_
#define INC_LEDPARAM_H_
#include <touchgfx/hal/Types.hpp>
#include <functional>

class LedParam {
public:
	enum class ColorState{COLORFIXED,COLORBLINKOFF,COLORBLINKON};
    using StateChangeCallback = std::function<void(uint8_t ledId, ColorState colorState)>;

	LedParam(uint8_t id);
	virtual ~LedParam();
    void setCallback(StateChangeCallback cb);

    void setPeriod(uint16_t pdon,uint16_t pdoff);
    void setPeriodMS(uint16_t pdmson,uint16_t pdmsoff);
	void setBlinking(ColorState stateon,ColorState stateoff);
	void setFixed();
	void startBlinking();
	void stopBlinking();
	bool getBlinking(){return isBlinking;}
	void tick(); // call in model ~60FPS

private:
	uint8_t id;
//	ColorState colorON;
//	ColorState colorOFF;
//	ColorState colorFixed;
	ColorState currentColor;
	bool isBlinking;
	uint16_t periodOn;
	uint16_t periodOff;
	bool currentMode;
	int timerCounter;
    StateChangeCallback callback;
	void updateOutput();
};

#endif /* INC_LEDPARAM_H_ */

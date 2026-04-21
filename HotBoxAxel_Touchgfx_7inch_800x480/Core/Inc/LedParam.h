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
	enum class ColorState{OFF,GREEN,RED};
    using StateChangeCallback = std::function<void(uint8_t ledId, ColorState state)>;

	LedParam(uint8_t id);
	virtual ~LedParam();
    void setCallback(StateChangeCallback cb);

    void setPeriod(uint16_t pd);
    void setPeriodMS(uint16_t pdms);
	void setBlinking(ColorState stateon,ColorState stateoff);
	void setFixed(ColorState colorfixed);
	void startBlinking();
	void stopBlinking();
	void tick(); // call in model ~60FPS

private:
	uint8_t id;
	ColorState colorON;
	ColorState colorOFF;
	ColorState colorFixed;
	ColorState currentColor;
	bool isBlinking;
	uint16_t period;
	int timerCounter;
    StateChangeCallback callback;
	void updateOutput();
};

#endif /* INC_LEDPARAM_H_ */

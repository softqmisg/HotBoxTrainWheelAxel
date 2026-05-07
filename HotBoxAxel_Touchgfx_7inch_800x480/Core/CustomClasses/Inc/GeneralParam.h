/*
 * GeneralParam.h
 *
 *  Created on: May 7, 2026
 *      Author: mehdi
 */

#ifndef CUSTOMCLASSES_SRC_GENERALPARAM_H_
#define CUSTOMCLASSES_SRC_GENERALPARAM_H_
#include <touchgfx/hal/Types.hpp>

class GeneralParam {
public:
	GeneralParam();
	virtual ~GeneralParam();
private:
	uint16_t locNum;
	bool language;
	uint32_t delayBetweenShows;
	uint8_t volume;
	uint8_t brighness;
};

#endif /* CUSTOMCLASSES_SRC_GENERALPARAM_H_ */

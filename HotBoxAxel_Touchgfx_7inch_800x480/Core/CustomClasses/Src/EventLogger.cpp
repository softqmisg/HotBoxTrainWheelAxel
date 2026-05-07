/*
 * EventLogger.cpp
 *
 *  Created on: Apr 27, 2026
 *      Author: mehdi
 */

#include <EventLogger.h>

EventLogger::EventLogger(size_t maxLogSize ) : maxSize(maxLogSize) {
    logs.reserve(maxSize);
	// TODO Auto-generated constructor stub

}



/*
 * Logger.cpp
 *
 *  Created on: Apr 27, 2026
 *      Author: mehdi
 */

#include <Logger.h>

Logger::Logger(size_t maxLogSize ) : maxSize(maxLogSize) {
    logs.reserve(maxSize);
}


/**
* @file RotationSource.h
 * @author Kyle Nguyen
 *
 * Interface for objects that can provide rotation
 */

#ifndef MACHINELIB_ROTATIONSOURCE_H
#define MACHINELIB_ROTATIONSOURCE_H

#include "RotationSink.h"

/**
 * Interface for objects that provide rotation to sinks
 */
class RotationSource {
public:
    virtual ~RotationSource() = default;

    /**
     * Set the sink that this source drives
     * @param sink The sink to drive
     */
    virtual void SetSink(std::shared_ptr<RotationSink> sink) = 0;
};

#endif //MACHINELIB_ROTATIONSOURCE_H
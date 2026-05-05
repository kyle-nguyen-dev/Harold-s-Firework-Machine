/**
* @file RotationSink.h
 * @author Kyle Nguyen
 *
 * Interface for objects that can receive rotation
 */

#ifndef MACHINELIB_ROTATIONSINK_H
#define MACHINELIB_ROTATIONSINK_H

/**
 * Interface for objects that can receive rotation from a source
 */
class RotationSink {
public:
    virtual ~RotationSink() = default;

    /**
     * Set the rotation of this sink
     * @param rotation Rotation in turns (0-1 is one full revolution)
     */
    virtual void SetRotation(double rotation) = 0;
};

#endif //MACHINELIB_ROTATIONSINK_H
/**
* @file Flag.h
 * @author Kyle Nguyen
 */

#ifndef MACHINELIB_FLAG_H
#define MACHINELIB_FLAG_H

#include "MachinePart.h"
#include "RotationSink.h"
#include "Polygon.h"

/**
 * Flag component that rotates around its base pivot point.
 * It is a rotation sink driven by a pulley.
 */
class Flag : public MachinePart, public RotationSink {
private:
    double mRotation = 0;       ///< Current rotation in turns
    cse335::Polygon mFlag;      ///< Flag image polygon

public:
    Flag(const std::wstring& resourcesDir);

    /**
     * Set the rotation of the flag
     * @param rotation Rotation in turns
     */
    void SetRotation(double rotation) override { mRotation = rotation; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    /**
     * Update the flag (no-op)
     * @param elapsed Time elapsed in seconds
     */
    void Update(double elapsed) override {}
};

#endif //MACHINELIB_FLAG_H
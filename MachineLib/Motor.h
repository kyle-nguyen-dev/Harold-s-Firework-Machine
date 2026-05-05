/**
* @file Motor.h
 * @author Kyle Nguyen
 */

#ifndef MACHINELIB_MOTOR_H
#define MACHINELIB_MOTOR_H

#include "MachinePart.h"
#include "RotationSource.h"
#include "Polygon.h"

/**
 * Motor component — rotation source only.
 * Draws using motor3.png for the body and shaft.png for the rotating shaft.
 */
class Motor : public MachinePart, public RotationSource {
private:
    double mRotation = 0;       ///< Current rotation in turns
    double mTime = 0;           ///< Current time in seconds
    std::vector<std::shared_ptr<RotationSink>> mSinks;  ///< All sinks this motor drives

    cse335::Polygon mBody;      ///< Motor body image (motor3.png)
    cse335::Polygon mShaft;     ///< Rotating shaft image (shaft.png)

public:
    Motor(const std::wstring& resourcesDir);

    /**
     * Add a rotation sink driven by this motor
     * @param sink The sink to drive
     */
    void SetSink(std::shared_ptr<RotationSink> sink) override;

    /**
     * Set the current time and update rotation
     * @param time Current time in seconds
     */
    void SetTime(double time);

    /**
     * Get the current rotation
     * @return Rotation in turns
     */
    double GetRotation() const { return mRotation; }

    /**
     * Draw the motor
     * @param graphics Graphics context to draw on
     * @param x Machine origin X
     * @param y Machine origin Y
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    /**
     * Update the motor for elapsed time
     * @param elapsed Time elapsed in seconds
     */
    void Update(double elapsed) override;

    /**
     * Set the machine frame
     * @param frame Frame number
     * @param frameRate Frame rate in frames per second
     */
    void SetMachineFrame(int frame, double frameRate) override;
};

#endif //MACHINELIB_MOTOR_H
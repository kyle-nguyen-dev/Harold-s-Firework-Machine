/**
* @file Machine.h
 * @author Kyle Nguyen
 *
 * A machine — owns and manages all its parts
 */

#ifndef MACHINELIB_MACHINE_H
#define MACHINELIB_MACHINE_H

#include "MachinePart.h"
#include "Motor.h"
#include "Pulley.h"

/**
 * A machine that owns all of its parts.
 * The machine manages drawing and updating all parts.
 */
class Machine {
private:
    /// All parts in this machine
    std::vector<std::shared_ptr<MachinePart>> mParts;

    /// All motors (need separate access for SetTime)
    std::vector<std::shared_ptr<Motor>> mMotors;

    /// All pulleys (need separate access for belt drawing)
    std::vector<std::shared_ptr<Pulley>> mPulleys;

    /// Machine location
    wxPoint mLocation = wxPoint(0, 0);

    /// Machine number
    int mMachineNumber = 1;

    /// Frame rate
    double mFrameRate = 30;
    double mLastTime = 0;  ///< Last time value for computing elapsed

public:
    Machine() = default;

    /// Copy constructor disabled
    Machine(const Machine&) = delete;
    /// Assignment operator disabled
    void operator=(const Machine&) = delete;

    void AddPart(std::shared_ptr<MachinePart> part);
    void AddMotor(std::shared_ptr<Motor> motor);
    void AddPulley(std::shared_ptr<Pulley> pulley);

    /**
     * Set the machine location
     * @param location New location
     */
    void SetLocation(wxPoint location) { mLocation = location; }

    /**
     * Get the machine location
     * @return Location
     */
    wxPoint GetLocation() const { return mLocation; }

    /**
     * Set the frame rate
     * @param rate Frame rate in frames per second
     */
    void SetFrameRate(double rate) { mFrameRate = rate; }

    void SetMachineFrame(int frame);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
};

#endif //MACHINELIB_MACHINE_H
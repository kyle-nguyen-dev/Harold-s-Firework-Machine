/**
 * @file MachinePart.h
 * @author Kyle Nguyen
 *
 * Abstract base class for all machine components
 */

#ifndef MACHINELIB_MACHINEPART_H
#define MACHINELIB_MACHINEPART_H

#include "Polygon.h"

/**
 * Abstract base class for all machine components.
 * Every component has a position and can be drawn.
 */
class MachinePart {
private:
    /// Position of this part relative to machine origin
    wxPoint mPosition = wxPoint(0, 0);

    /// The polygon used to draw this part
    cse335::Polygon mPolygon;

    /// Current rotation speed in turns per second
    double mRotationSpeed = 0;

public:
    MachinePart() = default;
    virtual ~MachinePart() = default;

    /// Copy constructor disabled
    MachinePart(const MachinePart&) = delete;
    /// Assignment operator disabled
    void operator=(const MachinePart&) = delete;

    /**
     * Get the position of this part
     * @return Position as wxPoint
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * Set the position of this part
     * @param pos New position
     */
    void SetPosition(wxPoint pos) { mPosition = pos; }

    /**
     * Get the rotation speed
     * @return Rotation speed in turns per second
     */
    double GetRotationSpeed() const { return mRotationSpeed; }

    /**
     * Set the rotation speed
     * @param speed Rotation speed in turns per second
     */
    void SetRotationSpeed(double speed) { mRotationSpeed = speed; }

    /**
     * Draw this part
     * @param graphics Graphics context to draw on
     * @param x X position to draw at
     * @param y Y position to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) = 0;

    /**
     * Update this part for a new frame
     * @param elapsed Time elapsed since last frame in seconds
     */
    virtual void Update(double elapsed) = 0;

    /**
     * Set the machine frame
     * @param frame Frame number
     * @param frameRate Frame rate in frames per second
     */
    virtual void SetMachineFrame(int frame, double frameRate) {}
};

#endif //MACHINELIB_MACHINEPART_H
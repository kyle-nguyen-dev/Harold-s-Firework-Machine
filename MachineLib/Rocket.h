/**
 * @file Rocket.h
 * @author Kyle Nguyen
 */

#ifndef MACHINELIB_ROCKET_H
#define MACHINELIB_ROCKET_H

#include "Polygon.h"

/// Rocket states
enum class RocketState { Launching, Exploding, OutOfBounds };

/**
 * A single rocket launched by RocketLauncher.
 * Uses rocket.png for display, explodes into colored particles.
 */
class Rocket {
private:
    wxPoint2DDouble mPosition;      ///< Current position relative to launcher origin
    wxPoint2DDouble mVelocity;      ///< Velocity in pixels/second
    RocketState mState = RocketState::Launching;  ///< Current rocket state
    double mRotation = 0;           ///< Rotation in turns
    double mExplodeTime = 0;        ///< Time spent exploding
    double mAge = 0;                ///< Total time alive
    double mExplodeAge = 1.0;       ///< Random time to explode

    cse335::Polygon mPolygon;       ///< Rocket image polygon
    bool mIsMSU = false;            ///< Is this an MSU rocket?

    /// Particle polygons (shared_ptr because Polygon is not copyable)
    std::vector<std::shared_ptr<cse335::Polygon>> mParticles;
    std::vector<wxPoint2DDouble> mParticlePositions;   ///< Particle positions
    std::vector<wxPoint2DDouble> mParticleVelocities;  ///< Particle velocities

public:
    /**
     * Constructor
     * @param position Starting position relative to launcher origin
     * @param velocity Initial velocity in pixels per second
     * @param rotation Initial rotation in turns
     * @param resourcesDir Directory containing resources
     */
    Rocket(wxPoint2DDouble position, wxPoint2DDouble velocity,
           double rotation, const std::wstring& resourcesDir);

    /**
     * Get the current rocket state
     * @return Current RocketState
     */
    RocketState GetState() const { return mState; }

    /**
     * Update the rocket position and state
     * @param elapsed Time elapsed in seconds
     * @return true if the rocket should be removed
     */
    bool Update(double elapsed);

    /**
     * Draw the rocket or its explosion particles
     * @param graphics Graphics context to draw on
     * @param x Machine origin X
     * @param y Machine origin Y
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);
};

#endif //MACHINELIB_ROCKET_H
/**
 * @file RocketLauncher.h
 * @author Kyle Nguyen
 */

#ifndef MACHINELIB_ROCKETLAUNCHER_H
#define MACHINELIB_ROCKETLAUNCHER_H

#include "MachinePart.h"
#include "RotationSink.h"
#include "Rocket.h"
#include "Polygon.h"
#include <list>
#include <random>

/**
 * Rocket launcher — rotation sink only.
 * Uses launcher.png for the barrel and launcherBase.png for the base.
 * Rotation drives rocket launch rate.
 */
class RocketLauncher : public MachinePart, public RotationSink {
private:
    double mRotation = 0;            ///< Current rotation in turns
    double mPreviousRotation = 0;    ///< Previous rotation for delta computation
    double mAccumulatedRotation = 0; ///< Accumulated rotation for launch threshold

    std::list<std::shared_ptr<Rocket>> mRockets;  ///< Active rockets
    std::mt19937 mRandom;                          ///< Random number generator

    cse335::Polygon mLauncher;      ///< Launcher barrel (launcher.png)
    cse335::Polygon mBase;          ///< Launcher base (launcherBase.png)

    std::wstring mResourcesDir;     ///< For creating rockets with rocket.png

    /**
     * Generate a uniform random number in a range
     * @param fmValue Minimum value
     * @param toValue Maximum value
     * @return Random double between fmValue and toValue
     */
    double Random(double fmValue, double toValue);

public:
    /**
     * Constructor
     * @param resourcesDir Directory containing resources
     */
    RocketLauncher(const std::wstring& resourcesDir);

    /**
     * Receive rotation and launch rockets proportionally
     * @param rotation New rotation in turns
     */
    void SetRotation(double rotation) override;

    /**
     * Draw the launcher barrel, base, and all active rockets
     * @param graphics Graphics context to draw on
     * @param x Machine origin X
     * @param y Machine origin Y
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    /**
     * Update all active rockets, removing expired ones
     * @param elapsed Time elapsed in seconds
     */
    void Update(double elapsed) override;
};

#endif //MACHINELIB_ROCKETLAUNCHER_H
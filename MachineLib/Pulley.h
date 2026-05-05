/**
 * @file Pulley.h
 * @author Kyle Nguyen
 */

#ifndef MACHINELIB_PULLEY_H
#define MACHINELIB_PULLEY_H

#include "MachinePart.h"
#include "RotationSource.h"
#include "RotationSink.h"
#include "Polygon.h"

/**
 * Pulley component — both rotation source and sink.
 * Uses pulley images for display.
 */
class Pulley : public MachinePart, public RotationSource, public RotationSink {
private:
    double mRadius;                         ///< Radius in pixels
    double mRotation = 0;                   ///< Current rotation in turns
    std::vector<std::shared_ptr<RotationSink>> mSinks;  ///< All sinks this pulley drives
    std::shared_ptr<Pulley> mBeltTo;        ///< Belt-connected pulley

    cse335::Polygon mPolygon;               ///< Pulley image polygon
    double mTime = 0;                       ///< Current time for belt animation
    double mBeltRock = 0;                   ///< Current belt rock amount

public:
    Pulley(double radius, const std::wstring& resourcesDir, const std::wstring& imageFile = L"pulley.png");

    void SetSink(std::shared_ptr<RotationSink> sink) override;
    void SetRotation(double rotation) override;

    /**
     * Get the radius of this pulley
     * @return Radius in pixels
     */
    double GetRadius() const { return mRadius; }

    /**
     * Get the current rotation
     * @return Rotation in turns
     */
    double GetRotation() const { return mRotation; }

    /**
     * Connect this pulley to another via a belt
     * @param other The pulley to connect to
     */
    void DrivePulleyWithBelt(std::shared_ptr<Pulley> other) { mBeltTo = other; }

    /**
     * Set whether the Y axis is inverted for the pulley image
     * @param inv True to invert Y axis
     */
    void SetInvertedY(bool inv) { mPolygon.SetInvertedY(inv); }

    void DrawBelt(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    /**
     * Update the pulley for elapsed time
     * @param elapsed Time elapsed in seconds
     */
    void Update(double elapsed) override { mTime += elapsed; }
};

#endif //MACHINELIB_PULLEY_H
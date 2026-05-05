/**
* @file Shape.h
 * @author Kyle Nguyen
 */

#ifndef MACHINELIB_SHAPE_H
#define MACHINELIB_SHAPE_H

#include "MachinePart.h"
#include "RotationSink.h"
#include "Polygon.h"

/**
 * A basic drawable shape — rotation sink only.
 * Can display an image or a colored polygon.
 */
class Shape : public MachinePart, public RotationSink {
private:
    double mRotation = 0;       ///< Current rotation in turns
    cse335::Polygon mPolygon;   ///< The polygon for this shape

public:
    Shape() = default;

    /**
     * Set the rotation of this shape
     * @param rotation Rotation in turns
     */
    void SetRotation(double rotation) override;

    /**
     * Get the current rotation
     * @return Rotation in turns
     */
    double GetRotation() const { return mRotation; }

    /**
     * Get the polygon for configuration (add points, set image/color)
     * @return Pointer to the polygon
     */
    cse335::Polygon* GetPolygon() { return &mPolygon; }

    /**
     * Draw this shape
     * @param graphics Graphics context to draw on
     * @param x Machine origin X
     * @param y Machine origin Y
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    /**
     * Update this shape (no-op)
     * @param elapsed Time elapsed in seconds
     */
    void Update(double elapsed) override {}
};

#endif //MACHINELIB_SHAPE_H
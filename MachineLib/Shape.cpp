/**
* @file Shape.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "Shape.h"
#include "MachinePart.h"
#include "RotationSink.h"

void Shape::SetRotation(double rotation)
{
    mRotation = rotation;
}

void Shape::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mPolygon.DrawPolygon(graphics,
        x + GetPosition().x,
        y + GetPosition().y,
        mRotation);
}
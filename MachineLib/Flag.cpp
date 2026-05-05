/**
* @file Flag.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "Flag.h"
#include <cmath>

/// Width of the flag image in pixels
const int FlagWidth = 75;

/// Height of the flag image in pixels
const int FlagHeight = 75;

/// Height of the pole in pixels
const int PoleHeight = 50;

/**
 * Constructor
 * @param resourcesDir Directory containing resources
 */
Flag::Flag(const std::wstring& resourcesDir)
{
    mFlag.Rectangle(0, -PoleHeight, FlagWidth, FlagHeight);
    mFlag.SetImage(resourcesDir + L"/images/flag.png");
    mFlag.SetInvertedY(false);
}

/**
 * Draw the flag rotated around its base pivot point
 * @param graphics Graphics context
 * @param x Machine origin X
 * @param y Machine origin Y
 */
void Flag::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    int px = x + GetPosition().x;
    int py = y + GetPosition().y;

    graphics->PushState();
    graphics->Translate(px, py);
    graphics->Rotate(mRotation * 2.0 * M_PI);
    mFlag.DrawPolygon(graphics, -74, -20, 0);
    graphics->PopState();
}
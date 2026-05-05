/**
 * @file Pulley.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "Pulley.h"
#include <cmath>

/**
 * Constructor
 * @param radius Radius in pixels
 * @param resourcesDir Resources directory
 * @param imageFile Which pulley image to use (default pulley.png)
 */
Pulley::Pulley(double radius, const std::wstring& resourcesDir, const std::wstring& imageFile)
    : mRadius(radius)
{
    mPolygon.Circle(mRadius);
    mPolygon.SetImage(resourcesDir + L"/images/" + imageFile);
    mPolygon.SetInvertedY(false);
}

/**
 * Set the sink this pulley drives
 * @param sink Sink to drive
 */
void Pulley::SetSink(std::shared_ptr<RotationSink> sink)
{
    mSinks.push_back(sink);
}

/**
 * Receive rotation and propagate to sink and belt target
 * @param rotation Rotation in turns
 */
void Pulley::SetRotation(double rotation)
{
    mRotation = rotation;

    for (auto& sink : mSinks)
    {
        sink->SetRotation(mRotation);
    }

    if (mBeltTo != nullptr)
    {
        mBeltTo->SetRotation(mRotation * mRadius / mBeltTo->GetRadius());
    }
}

/**
 * Draw belt lines to mBeltTo pulley
 * @param graphics Graphics context
 * @param x Machine origin X
 * @param y Machine origin Y
 */
void Pulley::DrawBelt(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    if (mBeltTo == nullptr)
        return;

    double x1 = x + GetPosition().x;
    double y1 = y + GetPosition().y;
    double x2 = x + mBeltTo->GetPosition().x;
    double y2 = y + mBeltTo->GetPosition().y;

    double r1 = mRadius - 3;
    double r2 = mBeltTo->GetRadius() - 3;

    double dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    double theta = atan2(y2 - y1, x2 - x1);
    double phi = asin((r2 - r1) / dist);

    // Side 1
    double beta1 = theta + phi + M_PI / 2.0;
    double ax1 = x1 + r1 * cos(beta1);
    double ay1 = y1 + r1 * sin(beta1);
    double ax2 = x2 + r2 * cos(beta1);
    double ay2 = y2 + r2 * sin(beta1);

    // Side 2
    double beta2 = theta - phi - M_PI / 2.0;
    double bx1 = x1 + r1 * cos(beta2);
    double by1 = y1 + r1 * sin(beta2);
    double bx2 = x2 + r2 * cos(beta2);
    double by2 = y2 + r2 * sin(beta2);

    /// Maximum amount to rock the belt
    const double BeltRockAmount = 0.01;

    /// How quickly to rock the belt — divided by length to get actual rate
    const double BeltRockBaseRate = M_PI * 1000;

    // Compute belt rock — oscillates based on time and belt length
    double rate = BeltRockBaseRate / dist;
    double rock = BeltRockAmount * dist * sin(mTime * rate);

    // Perpendicular direction to belt — used for control point offset
    double perpX = -(y2 - y1) / dist;
    double perpY =  (x2 - x1) / dist;

    // Control points for Bezier curve — midpoint offset perpendicular by rock amount
    double midX1 = (ax1 + ax2) / 2.0 + perpX * rock;
    double midY1 = (ay1 + ay2) / 2.0 + perpY * rock;

    double midX2 = (bx1 + bx2) / 2.0 - perpX * rock;
    double midY2 = (by1 + by2) / 2.0 - perpY * rock;

    wxPen beltPen(*wxBLACK, 2);
    graphics->SetPen(beltPen);
    graphics->SetBrush(*wxTRANSPARENT_BRUSH);

    // Draw side 1 as Bezier curve
    auto path1 = graphics->CreatePath();
    path1.MoveToPoint(ax1, ay1);
    path1.AddCurveToPoint(midX1, midY1, midX1, midY1, ax2, ay2);
    graphics->StrokePath(path1);

    // Draw side 2 as Bezier curve (rocks opposite direction)
    auto path2 = graphics->CreatePath();
    path2.MoveToPoint(bx1, by1);
    path2.AddCurveToPoint(midX2, midY2, midX2, midY2, bx2, by2);
    graphics->StrokePath(path2);
}

/**
 * Draw this pulley
 * @param graphics Graphics context
 * @param x Machine origin X
 * @param y Machine origin Y
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    int px = x + GetPosition().x;
    int py = y + GetPosition().y;
    mPolygon.DrawPolygon(graphics, px, py, mRotation);
}
/**
* @file Motor.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "Motor.h"

/**
 * Constructor
 * @param resourcesDir Directory containing resources
 */
Motor::Motor(const std::wstring& resourcesDir)
{
    // Motor body — motor3.png, reasonable size
    mBody.CenteredSquare(100);
    mBody.SetImage(resourcesDir + L"/images/motor3.png");
    mBody.SetInvertedY(false);

    // Shaft — shaft.png, smaller, rotates on top
    mShaft.CenteredSquare(80);
    mShaft.SetImage(resourcesDir + L"/images/shaft.png");
    mShaft.SetInvertedY(false);
}

void Motor::SetSink(std::shared_ptr<RotationSink> sink)
{
    mSinks.push_back(sink);
}

void Motor::SetTime(double time)
{
    mTime = time;
    mRotation = time;

    for (auto& sink : mSinks)
    {
        sink->SetRotation(mRotation);
    }
}

void Motor::Update(double elapsed)
{
    mTime += elapsed;
    SetTime(mTime);
}

void Motor::SetMachineFrame(int frame, double frameRate)
{
    SetTime(frame / frameRate);
}

void Motor::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    int px = x + GetPosition().x;
    int py = y + GetPosition().y;

    mBody.DrawPolygon(graphics, px, py, 0);
    mShaft.DrawPolygon(graphics, px, py, mRotation);
}
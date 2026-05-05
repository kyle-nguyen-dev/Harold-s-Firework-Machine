/**
* @file Machine.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "Machine.h"

/**
 * Add a part to the machine
 * @param part Part to add
 */
void Machine::AddPart(std::shared_ptr<MachinePart> part)
{
    mParts.push_back(part);
}

/**
 * Add a motor to the machine
 * @param motor Motor to add
 */
void Machine::AddMotor(std::shared_ptr<Motor> motor)
{
    mParts.push_back(motor);
    mMotors.push_back(motor);
}

/**
 * Add a pulley to the machine
 * @param pulley Pulley to add
 */
void Machine::AddPulley(std::shared_ptr<Pulley> pulley)
{
    mParts.push_back(pulley);
    mPulleys.push_back(pulley);
}

/**
 * Set the current machine frame
 * @param frame Frame number
 */
void Machine::SetMachineFrame(int frame)
{
    double time = frame / mFrameRate;
    double elapsed = time - mLastTime;

    // On backwards jump (frame reset), just update time
    if (elapsed < 0)
    {
        mLastTime = time;
        for (auto& motor : mMotors)
            motor->SetTime(time);
        return;
    }

    mLastTime = time;

    // Update motors (propagates rotation to all sinks)
    for (auto& motor : mMotors)
        motor->SetTime(time);

    // Update all parts (moves rockets, etc.)
    for (auto& part : mParts)
        part->Update(elapsed);
}

/**
 * Draw the machine
 * @param graphics Graphics context
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    int x = mLocation.x;
    int y = mLocation.y;

    // Draw belts first so they appear behind pulleys
    for (auto& pulley : mPulleys)
    {
        pulley->DrawBelt(graphics, x, y);
    }

    // Draw all parts
    for (auto& part : mParts)
    {
        part->Draw(graphics, x, y);
    }
}
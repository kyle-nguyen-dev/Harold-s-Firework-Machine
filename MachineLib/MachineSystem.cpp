/**
 * @file MachineSystem.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "MachineSystem.h"
#include "MachineFactory1.h"
#include "MachineFactory2.h"

/**
 * Constructor
 * @param resourcesDir Directory containing resources
 */
MachineSystem::MachineSystem(std::wstring resourcesDir)
    : mResourcesDir(resourcesDir)
{
    BuildMachine(1);
}

/**
 * Build a machine based on the machine number
 * @param machineNumber Which machine to build
 */
void MachineSystem::BuildMachine(int machineNumber)
{
    mMachineNumber = machineNumber;

    if (machineNumber == 1)
    {
        MachineFactory1 factory(mResourcesDir);
        mMachine = factory.Create();
    }
    else
    {
        MachineFactory2 factory(mResourcesDir);
        mMachine = factory.Create();
    }

    mMachine->SetLocation(mLocation);
    mMachine->SetFrameRate(mFrameRate);
    mMachine->SetMachineFrame(mCurrentFrame);
}

/**
 * Set the machine location
 * @param location New location
 */
void MachineSystem::SetLocation(wxPoint location)
{
    mLocation = location;
    if (mMachine != nullptr)
    {
        mMachine->SetLocation(location);
    }
}

/**
 * Get the machine location
 * @return Location
 */
wxPoint MachineSystem::GetLocation()
{
    return mLocation;
}

/**
 * Draw the machine
 * @param graphics Graphics context
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mMachine != nullptr)
    {
        mMachine->Draw(graphics);
    }
}

/**
 * Set the machine frame
 * @param frame Frame number
 */
void MachineSystem::SetMachineFrame(int frame)
{
    mCurrentFrame = frame;
    if (mMachine != nullptr)
    {
        mMachine->SetMachineFrame(frame);
    }
}

/**
 * Set the frame rate
 * @param rate Frame rate in frames per second
 */
void MachineSystem::SetFrameRate(double rate)
{
    mFrameRate = rate;
    if (mMachine != nullptr)
    {
        mMachine->SetFrameRate(rate);
    }
}

/**
 * Choose a machine number — rebuilds the machine
 * @param machine Machine number to build
 */
void MachineSystem::ChooseMachine(int machine)
{
    BuildMachine(machine);
}

/**
 * Get the current machine number
 * @return Machine number
 */
int MachineSystem::GetMachineNumber()
{
    return mMachineNumber;
}

/**
 * Get the current machine time
 * @return Time in seconds
 */
double MachineSystem::GetMachineTime()
{
    return mCurrentFrame / mFrameRate;
}

/**
 * Set the flag
 * @param flag Flag value
 */
void MachineSystem::SetFlag(int flag)
{
    mFlag = flag;
}
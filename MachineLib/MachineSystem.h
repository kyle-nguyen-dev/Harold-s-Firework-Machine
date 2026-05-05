/**
* @file MachineSystem.h
 * @author Kyle Nguyen
 *
 * Implements IMachineSystem — manages the machine and delegates all calls
 */

#ifndef MACHINELIB_MACHINESYSTEM_H
#define MACHINELIB_MACHINESYSTEM_H

#include "IMachineSystem.h"
#include "Machine.h"

/**
 * Concrete implementation of IMachineSystem.
 * Owns one Machine at a time and swaps it when ChooseMachine is called.
 */
class MachineSystem : public IMachineSystem {
private:
    /// The current machine
    std::shared_ptr<Machine> mMachine;

    /// Current machine number
    int mMachineNumber = 1;

    /// Current location
    wxPoint mLocation = wxPoint(0, 0);

    /// Frame rate
    double mFrameRate = 30;

    /// Resources directory
    std::wstring mResourcesDir;

    /// Current frame
    int mCurrentFrame = 0;

    /// Flag value
    int mFlag = 0;

    void BuildMachine(int machineNumber);

public:
    MachineSystem(std::wstring resourcesDir);

    void SetLocation(wxPoint location) override;
    wxPoint GetLocation() override;
    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetMachineFrame(int frame) override;
    void SetFrameRate(double rate) override;
    void ChooseMachine(int machine) override;
    int GetMachineNumber() override;
    double GetMachineTime() override;
    void SetFlag(int flag) override;
};

#endif //MACHINELIB_MACHINESYSTEM_H
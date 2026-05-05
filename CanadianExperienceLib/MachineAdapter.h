/**
 * @file MachineAdapter.h
 * @author Kyle Nguyen
 *
 * Adapter class that makes IMachineSystem work as a Drawable
 * in the CanadianExperience project.
 */

#ifndef CANADIANEXPERIENCE_MACHINEADAPTER_H
#define CANADIANEXPERIENCE_MACHINEADAPTER_H

#include "Drawable.h"
#include <machine-api.h>

/**
 * Adapter class that wraps IMachineSystem as a Drawable.
 *
 * This is an encapsulation adapter — it owns an IMachineSystem
 * and delegates draw/update calls to it, while fitting into
 * the Drawable hierarchy of CanadianExperience.
 *
 * The machine starts running at a specific frame (mStartFrame).
 * Before that frame the machine shows frame 0.
 */
class MachineAdapter : public Drawable {
private:
    /// The machine system we are adapting
    std::shared_ptr<IMachineSystem> mMachine;

    /// The frame at which this machine starts running
    int mStartFrame = 0;

    /// The machine number (1 or 2)
    int mMachineNumber = 1;

    /// Resources directory needed to recreate machine on load
    std::wstring mResourcesDir;

public:
    MachineAdapter(const std::wstring& name, const std::wstring& resourcesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Hit test — machines are not clickable
     * @param pos Position to test
     * @return false always
     */
    bool HitTest(wxPoint pos) override { return false; }

    void SetTimeline(Timeline* timeline) override;

    /**
     * Set a keyframe — machines do not use keyframes
     */
    void SetKeyframe() override {}

    /**
     * Get a keyframe — machines do not use keyframes
     */
    void GetKeyframe() override {}

    /**
     * Get the start frame for this machine
     * @return Start frame number
     */
    int GetStartFrame() const { return mStartFrame; }

    /**
     * Set the start frame for this machine
     * @param frame Frame number to start running
     */
    void SetStartFrame(int frame) { mStartFrame = frame; }

    void ShowMachineDialog(wxWindow* parent);

    wxXmlNode* XmlSave(wxXmlNode* node);
    void XmlLoad(wxXmlNode* node);

    /**
     * Set the machine number to display
     * @param num Machine number (1 or 2)
     */
    void SetMachineNumber(int num) { mMachine->ChooseMachine(num); }
};

#endif //CANADIANEXPERIENCE_MACHINEADAPTER_H
/**
 * @file MachineAdapter.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "MachineAdapter.h"
#include "Timeline.h"

/**
 * Constructor
 * @param name Drawable name
 * @param resourcesDir Path to resources directory
 */
MachineAdapter::MachineAdapter(const std::wstring& name, const std::wstring& resourcesDir)
    : Drawable(name), mResourcesDir(resourcesDir)
{
    MachineSystemFactory factory(resourcesDir);
    mMachine = factory.CreateMachineSystem();
}

/**
 * Draw the machine.
 * Computes the current machine frame based on the timeline
 * and the start frame, then delegates drawing to the machine.
 * @param graphics Graphics context to draw on
 */
void MachineAdapter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Get timeline current frame from the actor's timeline
    auto timeline = GetAngleChannel()->GetTimeline();
    if (timeline == nullptr)
        return;

    int currentFrame = timeline->GetCurrentFrame();

    // Machine frame is offset by start frame; clamp to 0
    int machineFrame = currentFrame - mStartFrame;
    if (machineFrame < 0)
        machineFrame = 0;

    mMachine->SetFrameRate(timeline->GetFrameRate());
    mMachine->SetMachineFrame(machineFrame);
    mMachine->SetLocation(mPlacedPosition);

    double scale = 0.5;
    graphics->PushState();
    graphics->Translate(mPlacedPosition.x, mPlacedPosition.y);
    graphics->Scale(scale, scale);
    mMachine->SetLocation(wxPoint(0, 0));
    mMachine->DrawMachine(graphics);
    graphics->PopState();
}

/**
 * Set the timeline — machines don't use animation channels
 * but we still need to register with the timeline so we
 * receive frame updates.
 * @param timeline The timeline to use
 */
void MachineAdapter::SetTimeline(Timeline* timeline)
{
    Drawable::SetTimeline(timeline);
}

/**
 * Show the machine selection dialog
 * @param parent Parent window
 */
void MachineAdapter::ShowMachineDialog(wxWindow* parent)
{
    MachineDialog dialog(parent, mMachine);
    if (dialog.ShowModal() == wxID_OK)
    {
        mMachineNumber = mMachine->GetMachineNumber();
    }
}

/**
 * Save this adapter to XML
 * @param node Parent XML node
 * @return The created XML node
 */
wxXmlNode* MachineAdapter::XmlSave(wxXmlNode* node)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"machine");
    node->AddChild(itemNode);

    itemNode->AddAttribute(L"name", GetName());
    itemNode->AddAttribute(L"machine-number",
        wxString::Format(wxT("%i"), mMachine->GetMachineNumber()));
    itemNode->AddAttribute(L"start-frame",
        wxString::Format(wxT("%i"), mStartFrame));

    return itemNode;
}

/**
 * Load this adapter from XML
 * @param node The XML node to load from
 */
void MachineAdapter::XmlLoad(wxXmlNode* node)
{
    int machineNumber = wxAtoi(node->GetAttribute(L"machine-number", L"1"));
    mStartFrame = wxAtoi(node->GetAttribute(L"start-frame", L"0"));

    mMachine->ChooseMachine(machineNumber);
    mMachineNumber = machineNumber;
}
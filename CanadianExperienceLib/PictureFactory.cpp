/**
 * @file PictureFactory.cpp
 * @author Charles Owen
 * @author Team Cypress
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "MachineAdapter.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";

/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background.jpg");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);
    harold->SetPosition(wxPoint(300, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);
    sparty->SetPosition(wxPoint(550, 620));
    picture->AddActor(sparty);

    // ── Machine 1 ──────────────────────────────────────────
    auto machine1Actor = std::make_shared<Actor>(L"Machine 1");
    machine1Actor->SetClickable(false);
    machine1Actor->SetPosition(wxPoint(150, 650));

    auto machine1Drawable = std::make_shared<MachineAdapter>(L"Machine 1", resourcesDir);
    machine1Drawable->SetPosition(wxPoint(0, 0));
    machine1Drawable->SetStartFrame(0);
    machine1Actor->AddDrawable(machine1Drawable);
    machine1Actor->SetRoot(machine1Drawable);
    picture->AddActor(machine1Actor);

    // ── Machine 2 ──────────────────────────────────────────
    auto machine2Actor = std::make_shared<Actor>(L"Machine 2");
    machine2Actor->SetClickable(false);
    machine2Actor->SetPosition(wxPoint(900, 650));

    auto machine2Drawable = std::make_shared<MachineAdapter>(L"Machine 2", resourcesDir);
    machine2Drawable->SetPosition(wxPoint(0, 0));
    machine2Drawable->SetStartFrame(100); // Starts at a different time
    machine2Drawable->SetMachineNumber(2);
    machine2Actor->AddDrawable(machine2Drawable);
    machine2Actor->SetRoot(machine2Drawable);

    picture->AddActor(machine2Actor);

    return picture;
}
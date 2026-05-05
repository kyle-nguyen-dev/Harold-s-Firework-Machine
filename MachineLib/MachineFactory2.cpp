/**
 * @file MachineFactory2.cpp
 * @author Kyle Nguyen
 *
 * Machine 2 — contest machine.
 * Two motors, different sized pulleys on each side,
 * two rocket launchers firing at different rates.
 */

#include "pch.h"
#include "MachineFactory2.h"
#include "Motor.h"
#include "Pulley.h"
#include "Shape.h"
#include "Flag.h"
#include "RocketLauncher.h"

MachineFactory2::MachineFactory2(const std::wstring& resourcesDir)
    : mResourcesDir(resourcesDir)
{
}

std::shared_ptr<Machine> MachineFactory2::Create()
{
    auto machine = std::make_shared<Machine>();

    // ── Base ────────────────────────────────────────────────
    auto base = std::make_shared<Shape>();
    base->SetPosition(wxPoint(0, 0));
    base->GetPolygon()->Rectangle(-300, -80, 600, 80);
    base->GetPolygon()->SetImage(mResourcesDir + L"/images/base.png");
    base->GetPolygon()->SetInvertedY(false);
    machine->AddPart(base);

    auto baseL = std::make_shared<Shape>();
    baseL->SetPosition(wxPoint(-400, -125));
    baseL->GetPolygon()->Rectangle(-100, -26, 200, 26);
    baseL->GetPolygon()->SetImage(mResourcesDir + L"/images/base.png");
    baseL->GetPolygon()->SetInvertedY(false);
    machine->AddPart(baseL);

    auto baseR = std::make_shared<Shape>();
    baseR->SetPosition(wxPoint(400, -125));
    baseR->GetPolygon()->Rectangle(-100, -26, 200, 26);
    baseR->GetPolygon()->SetImage(mResourcesDir + L"/images/base.png");
    baseR->GetPolygon()->SetInvertedY(false);
    machine->AddPart(baseR);

    // ── LEFT SIDE ───────────────────────────────────────────

    // Left pillar
    auto pillarL = std::make_shared<Shape>();
    pillarL->SetPosition(wxPoint(-80, -125));
    pillarL->GetPolygon()->Rectangle(-8, -300, 16, 350);
    pillarL->GetPolygon()->SetColor(wxColour(20, 20, 20));
    machine->AddPart(pillarL);

    auto motorL = std::make_shared<Motor>(mResourcesDir);
    motorL->SetPosition(wxPoint(-400, -200));

    // Static deco on left motor
    auto motorDecoL = std::make_shared<Shape>();
    motorDecoL->SetPosition(wxPoint(-400, -200));
    motorDecoL->GetPolygon()->Circle(35);
    motorDecoL->GetPolygon()->SetImage(mResourcesDir + L"/images/pulley2.png");
    motorDecoL->GetPolygon()->SetInvertedY(false);

    // Motor belt pulley left
    auto motorPulleyL = std::make_shared<Pulley>(35, mResourcesDir, L"pulley2.png");
    motorPulleyL->SetPosition(wxPoint(-400, -200));
    motorL->SetSink(motorPulleyL);
    motorPulleyL->SetInvertedY(false);

    auto pulleyL1 = std::make_shared<Pulley>(50, mResourcesDir, L"pulley.png");
    pulleyL1->SetPosition(wxPoint(-200, -160));
    motorPulleyL->DrivePulleyWithBelt(pulleyL1);

    // Deco pulley at left launcher base
    auto pulleyDecoL = std::make_shared<Pulley>(20, mResourcesDir, L"pulley2.png");
    pulleyDecoL->SetPosition(wxPoint(-200, -160));
    pulleyL1->SetSink(pulleyDecoL);

    auto pulleyL2 = std::make_shared<Pulley>(30, mResourcesDir, L"pulley1.png");
    pulleyL2->SetPosition(wxPoint(-80, -425));
    pulleyDecoL->DrivePulleyWithBelt(pulleyL2);

    auto launcherL = std::make_shared<RocketLauncher>(mResourcesDir);
    launcherL->SetPosition(wxPoint(-200, -175));
    pulleyL1->SetSink(launcherL);

    // Flag on left using Flag class
    auto flagL = std::make_shared<Flag>(mResourcesDir);
    flagL->SetPosition(wxPoint(-80, -425));
    pulleyL2->SetSink(flagL);

    // ── RIGHT SIDE ──────────────────────────────────────────

    // Right pillar
    auto pillarR = std::make_shared<Shape>();
    pillarR->SetPosition(wxPoint(80, -125));
    pillarR->GetPolygon()->Rectangle(-8, -300, 16, 350);
    pillarR->GetPolygon()->SetColor(wxColour(20, 20, 20));
    machine->AddPart(pillarR);

    auto motorR = std::make_shared<Motor>(mResourcesDir);
    motorR->SetPosition(wxPoint(400, -200));

    // Static deco on right motor
    auto motorDecoR = std::make_shared<Shape>();
    motorDecoR->SetPosition(wxPoint(400, -200));
    motorDecoR->GetPolygon()->Circle(35);
    motorDecoR->GetPolygon()->SetImage(mResourcesDir + L"/images/pulley2.png");
    motorDecoR->GetPolygon()->SetInvertedY(false);

    // Motor belt pulley right
    auto motorPulleyR = std::make_shared<Pulley>(35, mResourcesDir, L"pulley2.png");
    motorPulleyR->SetPosition(wxPoint(400, -200));
    motorR->SetSink(motorPulleyR);
    motorPulleyR->SetInvertedY(false);

    auto pulleyR1 = std::make_shared<Pulley>(50, mResourcesDir, L"pulley3.png");
    pulleyR1->SetPosition(wxPoint(200, -160));
    motorPulleyR->DrivePulleyWithBelt(pulleyR1);

    // Deco pulley at right launcher base
    auto pulleyDecoR = std::make_shared<Pulley>(20, mResourcesDir, L"pulley2.png");
    pulleyDecoR->SetPosition(wxPoint(200, -160));
    pulleyR1->SetSink(pulleyDecoR);

    auto pulleyR2 = std::make_shared<Pulley>(25, mResourcesDir, L"pulley4.png");
    pulleyR2->SetPosition(wxPoint(80, -425));
    pulleyDecoR->DrivePulleyWithBelt(pulleyR2);

    auto launcherR = std::make_shared<RocketLauncher>(mResourcesDir);
    launcherR->SetPosition(wxPoint(200, -170));
    pulleyR1->SetSink(launcherR);

    // Flag on right using Flag class
    auto flagR = std::make_shared<Flag>(mResourcesDir);
    flagR->SetPosition(wxPoint(80, -425));
    pulleyR2->SetSink(flagR);

    // ── Add to machine ───────────────────────────────────────
    machine->AddMotor(motorL);
    machine->AddMotor(motorR);
    machine->AddPulley(motorPulleyL);
    machine->AddPart(launcherR);
    machine->AddPart(launcherL);
    machine->AddPulley(pulleyL1);
    machine->AddPulley(pulleyDecoL);
    machine->AddPulley(pulleyL2);
    machine->AddPulley(motorPulleyR);
    machine->AddPulley(pulleyR1);
    machine->AddPulley(pulleyDecoR);
    machine->AddPulley(pulleyR2);
    machine->AddPart(motorDecoL);
    machine->AddPart(motorDecoR);
    machine->AddPart(flagL);
    machine->AddPart(flagR);



    return machine;
}
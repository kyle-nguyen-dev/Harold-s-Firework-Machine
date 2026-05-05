/**
 * @file MachineFactory1.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "MachineFactory1.h"
#include "Motor.h"
#include "Pulley.h"
#include "Shape.h"
#include "Flag.h"
#include "RocketLauncher.h"

MachineFactory1::MachineFactory1(const std::wstring& resourcesDir)
    : mResourcesDir(resourcesDir)
{
}

std::shared_ptr<Machine> MachineFactory1::Create()
{
    auto machine = std::make_shared<Machine>();

    // ── Base platform ─────────────────────────────────────────
    auto base = std::make_shared<Shape>();
    base->SetPosition(wxPoint(0, 0));
    base->GetPolygon()->Rectangle(-250, -80, 500, 80);
    base->GetPolygon()->SetImage(mResourcesDir + L"/images/base.png");
    base->GetPolygon()->SetInvertedY(false);
    machine->AddPart(base);

    // ── Pillar under the right pulley ─────────────────────────
    auto pillar = std::make_shared<Shape>();
    pillar->SetPosition(wxPoint(130, 0));
    pillar->GetPolygon()->Rectangle(-8, -300, 16, 225);
    pillar->GetPolygon()->SetColor(wxColour(20, 20, 20));
    machine->AddPart(pillar);

    // ── Motor ─────────────────────────────────────────────────
    auto motor = std::make_shared<Motor>(mResourcesDir);
    motor->SetPosition(wxPoint(60, -120));

    // ── Static decorative pulley2 on the motor — does not spin
    auto motorDeco = std::make_shared<Shape>();
    motorDeco->SetPosition(wxPoint(60, -120));
    motorDeco->GetPolygon()->Circle(35);
    motorDeco->GetPolygon()->SetImage(mResourcesDir + L"/images/pulley2.png");
    motorDeco->GetPolygon()->SetInvertedY(false);
    machine->AddPart(motorDeco);

    // ── Motor belt pulley — sits on motor, draws belt to pulleyLarge
    // Same image as motorDeco so it looks like one pulley, but this one
    // is a real Pulley so it can DrivePulleyWithBelt
    auto motorPulley = std::make_shared<Pulley>(35, mResourcesDir, L"pulley2.png");
    motorPulley->SetPosition(wxPoint(60, -120));
    motor->SetSink(motorPulley);
    motorPulley->SetInvertedY(false);

    // ── Large pulley — driven via belt from motorPulley ───────
    auto pulleyLarge = std::make_shared<Pulley>(50, mResourcesDir, L"pulley.png");
    pulleyLarge->SetPosition(wxPoint(-160, -175));
    motorPulley->DrivePulleyWithBelt(pulleyLarge);

    // ── Decorative pulley2 at launcher base — spins with pulleyLarge
    auto pulleyDeco = std::make_shared<Pulley>(20, mResourcesDir, L"pulley2.png");
    pulleyDeco->SetPosition(wxPoint(-160, -175));
    pulleyLarge->SetSink(pulleyDeco);

    // ── Decorative pulley3 at top of pillar
    auto pulleyDeco2 = std::make_shared<Pulley>(10, mResourcesDir, L"pulley2.png");
    pulleyDeco2->SetPosition(wxPoint(130, -300));
    pulleyLarge->SetSink(pulleyDeco2);

    // ── Small pulley — top of pillar, belt FROM pulleyDeco ────
    auto pulleySmall = std::make_shared<Pulley>(30, mResourcesDir, L"pulley1.png");
    pulleySmall->SetPosition(wxPoint(130, -300));
    pulleyDeco->DrivePulleyWithBelt(pulleySmall);

    // ── Flag ──────────────────────────────────────────────────
    auto flag = std::make_shared<Flag>(mResourcesDir);
    flag->SetPosition(wxPoint(130, -300));
    pulleySmall->SetSink(flag);

    // ── Rocket launcher driven by pulleyLarge ─────────────────
    auto launcher = std::make_shared<RocketLauncher>(mResourcesDir);
    launcher->SetPosition(wxPoint(-160, -175));
    pulleyLarge->SetSink(launcher);

    // ── Add to machine ────────────────────────────────────────
    machine->AddMotor(motor);
    machine->AddPulley(pulleySmall);
    machine->AddPulley(pulleyDeco2);
    machine->AddPart(motorDeco);
    machine->AddPart(flag);
    machine->AddPart(launcher);
    machine->AddPulley(pulleyLarge);
    machine->AddPulley(motorPulley);  // draws belt to pulleyLarge
    machine->AddPulley(pulleyDeco);   // draws belt to pulleySmall

    return machine;
}
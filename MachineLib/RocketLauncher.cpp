/**
 * @file RocketLauncher.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "RocketLauncher.h"
#include <cmath>
#include <random>

/// Average rockets launched per rotation
const double RocketsPerRotation = 5;

/// Variance in rockets launched
const double RocketVariancePerSecond = 10;

/// Range of random angle variance in radians
const double RocketAngleVariance = 0.15;

/// Angle range for end of launcher in radians
const double RocketLauncherAngleRange = 0.15;

/// Offset to end of launcher from pivot in pixels
const double RocketLauncherOffset = 190;

/// Random variance in offset
const double RocketLauncherOffsetVariance = 5;

/// Minimum rocket velocity
const double RocketMinimumVelocity = 90;

/// Maximum rocket velocity
const double RocketMaximumVelocity = 110;

/// Width of launcher in pixels
const int LauncherWidth = 60;

/// Height of launcher in pixels
const int LauncherHeight = 190;

/// Maximum oscillation angle in turns
const double MaxOscillationAngle = 0.06;

RocketLauncher::RocketLauncher(const std::wstring& resourcesDir)
    : mResourcesDir(resourcesDir)
{
    std::random_device rd;
    mRandom.seed(rd());

    // Barrel pivots from y=0 at bottom, extends upward
    mLauncher.Rectangle(-LauncherWidth / 2, -LauncherHeight + 40, LauncherWidth, LauncherHeight);
    mLauncher.SetImage(resourcesDir + L"/images/launcher.png");
    mLauncher.SetInvertedY(false);

    // Base sits below pivot
    mBase.Rectangle(-LauncherWidth, 0, LauncherWidth * 2, 100);
    mBase.SetImage(resourcesDir + L"/images/launcherBase.png");
    mBase.SetInvertedY(false);
}

double RocketLauncher::Random(double fmValue, double toValue)
{
    std::uniform_real_distribution<> dist(fmValue, toValue);
    return dist(mRandom);
}

void RocketLauncher::SetRotation(double rotation)
{
    double delta = rotation - mPreviousRotation;

    if (delta < 0)
    {
        mPreviousRotation = rotation;
        mRotation = sin(rotation * 1.0 * M_PI) * MaxOscillationAngle;
        return;
    }

    mPreviousRotation = rotation;
    mRotation = sin(rotation * 1.0 * M_PI) * MaxOscillationAngle;

    // Accumulate rotation — launch rockets every 0.2 turns
    mAccumulatedRotation += delta;
    const double LaunchThreshold = 0.5;
    if (mAccumulatedRotation < LaunchThreshold)
        return;

    mAccumulatedRotation -= LaunchThreshold;

    int num = 1;  // launch 1 rocket each threshold

    for (int i = 0; i < num; i++)
    {
        // Small random spread around straight up
        double spread = Random(-RocketAngleVariance, RocketAngleVariance);

        // Start at top of launcher barrel — just above the tip
        double startX = Random(-5, 5);
        double startY = -(LauncherHeight - 40);  // top of barrel

        // Velocity — shoot straight up with small random spread
        double speed = Random(600, 800);
        double vx = sin(spread) * speed;
        double vy = -speed;  // negative Y = upward

        auto rocket = std::make_shared<Rocket>(
            wxPoint2DDouble(startX, startY),
            wxPoint2DDouble(vx, vy),
            mRotation,
            mResourcesDir);

        mRockets.push_back(rocket);
    }
}

void RocketLauncher::Update(double elapsed)
{
    for (auto it = mRockets.begin(); it != mRockets.end(); )
    {
        if ((*it)->Update(elapsed))
            it = mRockets.erase(it);
        else
            ++it;
    }
}

void RocketLauncher::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    int px = x + GetPosition().x;
    int py = y + GetPosition().y;

    // Draw rockets
    for (auto& rocket : mRockets)
    {
        rocket->Draw(graphics, px, py);
    }

    // Fixed base
    mBase.DrawPolygon(graphics, px, py, 0);

    // Rotating barrel around pivot
    graphics->PushState();
    graphics->Translate(px, py);
    graphics->Rotate(mRotation * 2.0 * M_PI);
    mLauncher.DrawPolygon(graphics, 0, 0, 0);
    graphics->PopState();
}
/**
 * @file Rocket.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "Rocket.h"
#include <cmath>
#include <random>

/// Probability of a rocket being an MSU rocket
const double MSURocketProbability = 0.2;

/// Width of the rocket image in pixels
const int RocketWidth = 32;

/// Height of the rocket image in pixels
const int RocketHeight = 64;

/// Number of particles created on explosion
const int NumParticles = 12;

/// Size of each explosion particle in pixels
const int ParticleSize = 8;

/// Duration of the explosion animation in seconds
const double ExplosionDuration = 0.6;

/// Gravity applied to rockets and particles in pixels per second squared
const double Gravity = 15.0;

Rocket::Rocket(wxPoint2DDouble position, wxPoint2DDouble velocity,
               double rotation, const std::wstring& resourcesDir)
    : mPosition(position), mVelocity(velocity), mRotation(rotation)
{
    // Rocket image — bottom center at origin, extends upward
    mPolygon.Rectangle(-RocketWidth / 2, -RocketHeight, RocketWidth, RocketHeight);
    mPolygon.SetImage(resourcesDir + L"/images/rocket.png");
    mPolygon.SetInvertedY(false);

    // Randomize explode time and decide if MSU rocket
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<> dist(0.5, 1.5);
    mExplodeAge = dist(rng);

    std::uniform_real_distribution<> chanceDist(0.0, 1.0);
    if (chanceDist(rng) < MSURocketProbability)
    {
        mIsMSU = true;
        mPolygon.SetImage(resourcesDir + L"/images/rocket-msu.png");
    }
}

bool Rocket::Update(double elapsed)
{
    if (mState == RocketState::Launching)
    {
        mAge += elapsed;
        mPosition.m_x += mVelocity.m_x * elapsed;
        mPosition.m_y += mVelocity.m_y * elapsed;
        mVelocity.m_y += Gravity * elapsed;

        // Explode after random time between 0.5 and 1.5 seconds
        if (mAge >= mExplodeAge)
        {
            mState = RocketState::Exploding;

            // Seed random for particles
            std::mt19937 rng(std::random_device{}());
            std::uniform_real_distribution<> speedDist(150, 280);
            std::uniform_real_distribution<> angleDist(0, 2 * M_PI);

            // MSU rockets emit green and white particles
            wxColour msColors[] = {
                wxColour(24, 69, 59),   // MSU green
                wxColour(24, 69, 59),
                wxColour(255, 255, 255), // white
                wxColour(255, 255, 255),
                wxColour(24, 69, 59)
            };
            wxColour normalColors[] = {
                wxColour(255, 0, 0),
                wxColour(255, 255, 255),
                wxColour(0, 0, 255),
                wxColour(255, 200, 0),
                wxColour(0, 255, 100)
            };
            wxColour* colors = mIsMSU ? msColors : normalColors;

            for (int i = 0; i < NumParticles; i++)
            {
                auto p = std::make_shared<cse335::Polygon>();
                p->Circle(ParticleSize);
                p->SetColor(colors[i % 5]);
                mParticles.push_back(p);

                double angle = angleDist(rng);
                double speed = speedDist(rng);
                mParticlePositions.push_back(mPosition);
                mParticleVelocities.push_back(
                    wxPoint2DDouble(cos(angle) * speed, sin(angle) * speed));
            }
        }
    }
    else if (mState == RocketState::Exploding)
    {
        mExplodeTime += elapsed;

        for (int i = 0; i < (int)mParticlePositions.size(); i++)
        {
            mParticlePositions[i].m_x += mParticleVelocities[i].m_x * elapsed;
            mParticlePositions[i].m_y += mParticleVelocities[i].m_y * elapsed;
            mParticleVelocities[i].m_y += Gravity * elapsed;
        }

        if (mExplodeTime >= ExplosionDuration)
        {
            mState = RocketState::OutOfBounds;
            return true;
        }
    }

    return false;
}

void Rocket::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    if (mState == RocketState::Launching)
    {
        mPolygon.DrawPolygon(graphics,
            x + mPosition.m_x,
            y + mPosition.m_y,
            mRotation);
    }
    else if (mState == RocketState::Exploding)
    {
        double opacity = 1.0 - (mExplodeTime / ExplosionDuration);
        for (int i = 0; i < (int)mParticles.size(); i++)
        {
            mParticles[i]->SetOpacity(opacity);
            mParticles[i]->DrawPolygon(graphics,
                x + mParticlePositions[i].m_x,
                y + mParticlePositions[i].m_y,
                0);
        }
    }
}
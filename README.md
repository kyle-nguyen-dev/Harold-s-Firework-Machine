# CSE 335 Project 2 — Harold's Firework Machine 🎆

**Michigan State University | Object-Oriented Software Design**

A C++ animation system built with wxWidgets featuring Harold's Firework Machine — a fully functional mechanical system with motors, pulleys, belts, and rocket launchers integrated into the Canadian Experience animation project.

---

## 🎬 Overview

This project extends the Canadian Experience animation system with two fully operational firework machines. Characters can interact with the machines, which are animated using a timeline-based keyframe system.

---

## ✨ Features

### Machine Components
- **Motor** — Powers the machine at 1 rotation per second using `motor3.png` and a rotating shaft
- **Pulley** — Rotation source and sink with belt-drive support and speed ratios based on radius
- **Rocket Launcher** — Oscillating barrel that launches rockets upward with randomized spread
- **Shape** — Flexible polygon/image component used for the base platform, pillar, and decorative elements
- **Flag** — Spins 360° around its base pivot point

### Rockets 🚀
- Rockets fly upward and explode into colored particles after 0.5–1.5 seconds
- **20% chance** of launching an MSU rocket (green and white explosion particles)
- Particles fade out with opacity animation

### Challenge Tasks Implemented
- 🟢 **MSU Rockets** — Each rocket has a 20% probability of being an MSU-themed rocket with green and white particles
- 🟢 **Flapping Belts** — Belts oscillate using Bézier curves via `wxGraphicsPath::AddCurveToPoint`, with flap rate and amount dependent on belt length

### Canadian Experience Integration
- Two machines displayed simultaneously in the animation scene
- Machines start at **different times** (Machine 1 at frame 0, Machine 2 at frame 100)
- Machine selection via `MachineDialog`
- XML save/load support for machine number and start frame
- **Katana prop** added to Sparty as a drawable that stays attached to the right arm

---

## 🏗️ Architecture

The project follows the **Adapter Pattern** to integrate `MachineLib` into `CanadianExperience`:

```
CanadianExperience          MachineLib
──────────────────          ──────────
MachineAdapter              IMachineSystem (interface)
  └─ Drawable                 └─ MachineSystem
       │                           └─ Machine
       └──────uses──────►               ├─ Motor (RotationSource)
                                        ├─ Pulley (Source + Sink)
                                        ├─ RocketLauncher (RotationSink)
                                        ├─ Shape (RotationSink)
                                        └─ Flag (RotationSink)
```

**Key design decisions:**
- `RotationSource` and `RotationSink` interfaces eliminate redundant code across Motor and Pulley
- Both Motor and Pulley support **multiple sinks** via `std::vector<shared_ptr<RotationSink>>`
- `MachineSystem` implements `IMachineSystem` and swaps `Machine` objects on `ChooseMachine()` — the pointer never changes (Parable of the Tree)
- `MachineFactory1` and `MachineFactory2` build the specific machine configurations
- No `CanadianExperience` classes used inside `MachineLib`

---

## 🛠️ Tech Stack

- **C++17**
- **wxWidgets** — UI, graphics, XML
- **CMake** — Build system
- **Google Test** — Unit testing
- **Visual Paradigm** — UML design
- **Doxygen** — Documentation

---

## 📁 Project Structure

```
Project2Starter/
├── CanadianExperience/       # Root executable
├── CanadianExperienceLib/    # Animation system + MachineAdapter
│   ├── MachineAdapter.h/.cpp
│   └── KatanaDrawable.h/.cpp
├── MachineLib/               # Machine library
│   ├── Machine.h/.cpp
│   ├── MachineSystem.h/.cpp
│   ├── Motor.h/.cpp
│   ├── Pulley.h/.cpp
│   ├── Shape.h/.cpp
│   ├── Flag.h/.cpp
│   ├── RocketLauncher.h/.cpp
│   ├── Rocket.h/.cpp
│   ├── MachineFactory1.h/.cpp
│   ├── MachineFactory2.h/.cpp
│   ├── RotationSource.h
│   └── RotationSink.h
├── MachineDemo/              # Standalone machine demonstrator
├── Tests/                    # Unit tests for CanadianExperienceLib
└── MachineTests/             # Unit tests for MachineLib
```

---

## 👥 Team Cypress

| Name | MSU ID |
|------|--------|
| Rashed Almazrouei | almazr11 |
| Manish Chevuru | chevurum |
| Ha Anh Mai Do | domai |
| Carson Patrick Meredith | meredi78 |
| Aaditya Moudgil | moudgil1 |
| Kyle Nguyen | nguy1219 |
| Iliana Slimane | slimanei |
| Michelle Wesenberg | wesenbe8 |

---

## 📝 Notes

- All machine implementation code lives in `MachineLib` — no cross-contamination with `CanadianExperience`
- `MachineDemo` was not modified (as required)
- `IMachineSystem`, `MachineDialog`, `MachineStandin`, and `MachineSystemStandin` were not modified (as required)

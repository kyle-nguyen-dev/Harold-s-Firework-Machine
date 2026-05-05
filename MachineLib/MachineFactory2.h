/**
* @file MachineFactory2.h
 * @author Kyle Nguyen
 *
 * Factory that builds machine 2 — the contest machine
 */

#ifndef MACHINELIB_MACHINEFACTORY2_H
#define MACHINELIB_MACHINEFACTORY2_H

#include "Machine.h"

/**
 * Factory that builds machine 2.
 * This is the contest machine — features two motors,
 * multiple pulleys at different sizes creating a complex
 * belt system, and two rocket launchers firing simultaneously.
 */
class MachineFactory2 {
private:
    /// Resources directory
    std::wstring mResourcesDir;

public:
    /**
     * Constructor
     * @param resourcesDir Directory containing resources
     */
    MachineFactory2(const std::wstring& resourcesDir);

    /**
     * Create and return machine 2
     * @return The constructed machine
     */
    std::shared_ptr<Machine> Create();
};

#endif //MACHINELIB_MACHINEFACTORY2_H
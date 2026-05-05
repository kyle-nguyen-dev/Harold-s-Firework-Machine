/**
* @file MachineFactory1.h
 * @author Kyle Nguyen
 */

#ifndef MACHINELIB_MACHINEFACTORY1_H
#define MACHINELIB_MACHINEFACTORY1_H

#include "Machine.h"

/**
 * Builds machine 1 — the standard machine with motor, pulleys,
 * flag shape, and rocket launcher using the provided images.
 */
class MachineFactory1 {
private:
    std::wstring mResourcesDir;  ///< Directory containing resources

public:
    /**
     * Constructor
     * @param resourcesDir Directory containing resources
     */
    MachineFactory1(const std::wstring& resourcesDir);

    /**
     * Create and return machine 1
     * @return The constructed machine
     */
    std::shared_ptr<Machine> Create();
};

#endif //MACHINELIB_MACHINEFACTORY1_H
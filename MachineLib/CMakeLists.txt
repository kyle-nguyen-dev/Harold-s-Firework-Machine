project(MachineLib)

set(SOURCE_FILES
        pch.h
        IMachineSystem.h
        MachineSystemFactory.cpp MachineSystemFactory.h
        MachineStandin.cpp MachineStandin.h
        Polygon.cpp Polygon.h
        Consts.h
        MachineDialog.cpp MachineDialog.h include/machine-api.h
        MachineSystemStandin.cpp
        MachineSystemStandin.h
        MachineSystem.cpp
        MachineSystem.h
        Machine.cpp
        Machine.h
        Motor.cpp
        Motor.h
        Pulley.cpp
        Pulley.h
        Shape.cpp
        Shape.h
        RocketLauncher.cpp
        RocketLauncher.h
        Rocket.cpp
        Rocket.h
        MachinePart.cpp
        MachinePart.h
        RotationSink.h
        RotationSource.h
        MachineFactory1.cpp
        MachineFactory1.h
        MachineFactory2.cpp
        MachineFactory2.h
        Flag.cpp
        Flag.h
)

# Removed:
# Motor.cpp Motor.h Pulley.cpp Pulley.h

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

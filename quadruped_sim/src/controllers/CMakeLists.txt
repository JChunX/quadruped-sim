
target_sources(QuadrupedSim PRIVATE 
    BaseController.cpp
    QuadrupedController.cpp
    Controller.cpp
    MPCController.cpp
    ContactScheduler.cpp
    TrajectoryGenerator.cpp
)

target_include_directories (QuadrupedSim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#ifndef APPLICATION_H
#define APPLICATION_H

#include "QuadrupedSim.h"
#include <string>

class Application
{
public:
    Application();
    ~Application();
    void run();

    std::string model_path = "models/xml/mini_cheetah.xml";

};

#endif // APPLICATION_H
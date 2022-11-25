#include "Application.h"
#include <string>

Application::Application()
{
    model_path = "models/xml/mini_cheetah.xml";
}

Application::~Application() 
{

}

void Application::run()
{
    QuadrupedSim sim = QuadrupedSim(model_path);
    while (sim.gl_ok())
    {
        sim.step();
        sim.render();
    }
}
#include <iostream>
#include <filesystem>
#include "Application.h"

int main(int argc, char** argv) {

    // print pwd
    std::cout << "pwd:" << std::filesystem::current_path() << std::endl;

    Application app;
    
    app.run();

    return 0;
}
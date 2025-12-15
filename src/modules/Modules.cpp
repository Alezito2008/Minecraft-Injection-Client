#include "modules.h"

#include <iostream>

std::vector<Module*> modules;

Module::Module(const std::string &n) : name(n), category(Categories::MISC)
{
    modules.push_back(this);
}

Module::~Module()
{
    modules.erase(
        std::remove(modules.begin(), modules.end(), this),
        modules.end()
    );
}

void Module::Enable()
{
    std::cout << "Enabled module: " << getName() << std::endl;
    enabled = true;
    onEnable();
}

void Module::Disable()
{
    std::cout << "Disabled module: " << getName() << std::endl;
    enabled = false;
    onDisable();
}

void Module::Tick()
{
    if (!enabled) return;
    onTick();
}

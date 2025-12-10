#include "modules.h"

std::vector<Module*> modules{};

Module::Module(const std::string &n) : name(n)
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

void Module::Tick()
{
    if (!enabled) return;
    onTick();
}

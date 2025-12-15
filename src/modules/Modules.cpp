#include "modules.h"

#include <iostream>
#include <imgui.h>

std::vector<Module*> modules;
std::unordered_map<Module::Categories, std::vector<Module*>> groupedModules;

Module::Module(const std::string &n,
    Module::Categories c)
    : name(n), category(c)
{
    modules.push_back(this);
    groupedModules[category].push_back(this);
}

Module::~Module()
{
    modules.erase(
        std::remove(modules.begin(), modules.end(), this),
        modules.end()
    );

    auto& group = groupedModules[category];
    group.erase(
        std::remove(group.begin(), group.end(), this),
        group.end()
    );
}

const std::string Module::categoryToString(Categories category)
{
    switch (category)
    {
        case Categories::COMBAT: return "Combat";
        case Categories::MISC: return "Misc";
        case Categories::WORLD: return "World";
        case Categories::MOVEMENT: return "Movement";
        default: return "Unknown";
    }
}

void Module::RenderDefaultGUI()
{
    if (ImGui::Checkbox(name.c_str(), &enabled)) {
        enabled ? Enable() : Disable();
    };
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

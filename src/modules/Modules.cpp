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
    bool enabled = m_isEnabled;
    if (ImGui::Selectable(name.c_str(), enabled)) {
        Toggle();
    }
}

void Module::Enable()
{
    std::cout << "Enabled module: " << getName() << std::endl;
    m_isEnabled = true;
    onEnable();
}

void Module::Disable()
{
    std::cout << "Disabled module: " << getName() << std::endl;
    m_isEnabled = false;
    onDisable();
}

void Module::Toggle()
{
    m_isEnabled = !m_isEnabled;
    m_isEnabled ? Enable() : Disable();
}

void Module::Tick()
{
    if (!m_isEnabled) return;
    onTick();
}

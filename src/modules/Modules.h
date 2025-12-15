#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Module {
public:
    enum class Categories {
        MOVEMENT,
        WORLD,
        COMBAT,
        MISC
    };

    Module(const std::string &n,
        Module::Categories c = Module::Categories::MISC);
    Module::~Module();

    static const std::string categoryToString(Categories category);

    virtual const std::string& getName() const { return name; }
    virtual const Categories getCategory() const { return category; }
    inline bool isEnabled() const { return m_isEnabled; }

    void RenderDefaultGUI();
    void Toggle();
    void Enable();
    void Disable();
    void Tick();

private:
    std::string name;
    Categories category;
protected:
    bool m_isEnabled = false;

    virtual void onEnable() = 0;
    virtual void onDisable() = 0;
    virtual void onTick() = 0;
};

extern std::vector<Module*> modules;
extern std::unordered_map<Module::Categories, std::vector<Module*>> groupedModules;

#pragma once

#include <string>
#include <vector>

class Module {
public:
    enum class Categories {
        MOVEMENT,
        WORLD,
        COMBAT,
        MISC
    };

    Module(const std::string& n);
    Module::~Module();

    virtual const std::string& getName() const { return name; }
    virtual const Categories getCategory() const { return category; }
    inline bool isEnabled() const { return enabled; }

    void Enable();
    void Disable();
    void Tick();

    inline void Toggle() {
        enabled = !enabled;
        enabled ? Enable() : Disable();
    };

private:
    std::string name;
    Categories category;
protected:
    bool enabled = false;

    virtual void onEnable() = 0;
    virtual void onDisable() = 0;
    virtual void onTick() = 0;
};

extern std::vector<Module*> modules;

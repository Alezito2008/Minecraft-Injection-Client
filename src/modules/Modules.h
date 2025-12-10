#pragma once

#include <string>
#include <vector>

class Module {
public:
    Module(const std::string& n);
    Module::~Module();

    virtual const std::string& getName() const { return name; };
    inline bool isEnabled() const { return enabled; }

    void Tick();

    virtual void onEnable() = 0;
    virtual void onDisable() = 0;
    virtual void onTick() {};

    inline void Toggle() {
        enabled = !enabled;
        enabled ? onEnable() : onDisable();
    };

    inline void Enable() { enabled = true; }
    inline void Disable() { enabled = false; }

private:
    std::string name;
protected:
    bool enabled = false;
};

extern std::vector<Module*> modules;

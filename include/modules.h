#pragma once

#include <string>
#include <vector>

class Module {
public:
    Module(const std::string& n) : name(n) {}

    virtual const std::string& getName() const { return name; };
    inline bool isEnabled() const { return enabled; }

    virtual void onEnable() {};
    virtual void onDisable() {};

    void Toggle() {
        enabled = !enabled;
        if (enabled) onEnable();
        else onDisable();
    };

private:
    std::string name;
    bool enabled = false;
};

extern std::vector<Module*> modules;

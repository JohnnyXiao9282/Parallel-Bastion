#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace Engine {

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    void clear();

private:
};

} // namespace Engine

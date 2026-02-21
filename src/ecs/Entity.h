#pragma once

#include <cstdint>

namespace ECS {

using EntityID = uint64_t;

class Entity {
public:
    explicit Entity(EntityID id = 0) : m_id(id) {}
    
    EntityID getID() const { return m_id; }
    bool isValid() const { return m_id != 0; }
    
    bool operator==(const Entity& other) const { return m_id == other.m_id; }
    bool operator!=(const Entity& other) const { return m_id != other.m_id; }

private:
    EntityID m_id;
};

} // namespace ECS

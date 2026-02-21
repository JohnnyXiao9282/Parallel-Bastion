#pragma once

namespace ECS {

struct Component {
    virtual ~Component() = default;
};

struct TransformComponent : Component {
    float x = 0.0f;
    float y = 0.0f;
    float rotation = 0.0f;
};

struct VelocityComponent : Component {
    float dx = 0.0f;
    float dy = 0.0f;
};

} // namespace ECS

#pragma once

namespace ECS {

class System {
public:
    virtual ~System() = default;
    virtual void update(double dt) = 0;
};

} // namespace ECS

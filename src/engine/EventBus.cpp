#include "EventBus.h"

namespace Engine {

void EventBus::clear() {
    m_listeners.clear();
}

} // namespace Engine

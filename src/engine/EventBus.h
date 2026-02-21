#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

namespace Engine {

struct Event {
    virtual ~Event() = default;
};

using EventListener = std::function<void(const Event&)>;

class EventBus {
public:
    EventBus() = default;
    ~EventBus() = default;

    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    template<typename T>
    void subscribe(const std::string& eventType, std::function<void(const T&)> listener);

    template<typename T>
    void publish(const std::string& eventType, const T& event);

    void clear();

private:
    std::unordered_map<std::string, std::vector<EventListener>> m_listeners;
};

template<typename T>
void EventBus::subscribe(const std::string& eventType, std::function<void(const T&)> listener) {
    m_listeners[eventType].push_back([listener](const Event& e) {
        listener(static_cast<const T&>(e));
    });
}

template<typename T>
void EventBus::publish(const std::string& eventType, const T& event) {
    auto it = m_listeners.find(eventType);
    if (it != m_listeners.end()) {
        for (auto& listener : it->second) {
            listener(event);
        }
    }
}

} // namespace Engine

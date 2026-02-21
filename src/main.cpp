#include "core/Application.h"
#include "utils/Logger.h"
#include <exception>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    
    try {
        Utils::Logger::info("=== Parallel Bastion ===");
        Utils::Logger::info("Starting game...");
        
        Core::Application app("Parallel Bastion", 1280, 720);
        app.run();
        
        Utils::Logger::info("Game ended gracefully");
        return 0;
        
    } catch (const std::exception& e) {
        Utils::Logger::error("Fatal error: " + std::string(e.what()));
        return 1;
    }
}

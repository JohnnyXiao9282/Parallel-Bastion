# Parallel Bastion

A modern tower defense game built with C++17 and SDL2, featuring parallel processing and clean architecture.

## Features

- **Fixed timestep game loop** (60 FPS target)
- **Thread pool** for parallel processing
- **A\* pathfinding** with priority queue
- **Spatial grid** for efficient collision detection
- **Entity Component System** (ECS) architecture
- **Cross-platform** (Windows, Linux, macOS)

## Architecture

```
parallel-bastion/
├── src/
│   ├── core/          # Game loop, time, application
│   ├── engine/        # Renderer, resources, events
│   ├── ecs/           # Entity-Component-System
│   ├── gameplay/      # Tower defense logic
│   ├── concurrency/   # Thread pool, task queue
│   └── utils/         # Logger, utilities
├── assets/            # Game assets
└── external/          # Third-party dependencies
```

## Requirements

- CMake 3.15+
- C++17 compatible compiler
  - GCC 7+ (Linux)
  - Clang 5+ (macOS)
  - MSVC 2017+ (Windows)
- SDL2 development libraries

## Building

### macOS

```bash
# Install SDL2
brew install sdl2

# Build
mkdir build && cd build
cmake ..
cmake --build .

# Run
./parallel_bastion
```

### Linux

```bash
# Install SDL2
sudo apt-get install libsdl2-dev

# Build
mkdir build && cd build
cmake ..
cmake --build .

# Run
./parallel_bastion
```

### Windows

```bash
# Install SDL2 via vcpkg or download from libsdl.org
# Then:
mkdir build && cd build
cmake ..
cmake --build . --config Release

# Run
.\Release\parallel_bastion.exe
```

## Controls

- **ESC** - Exit game

## Development Roadmap

### Phase 1: Foundation ✅

- [x] Project structure
- [x] CMake build system
- [x] Fixed timestep game loop
- [x] SDL2 window and rendering
- [x] Basic architecture

### Phase 2: Core Systems (Next)

- [ ] Thread pool implementation
- [ ] A\* pathfinding
- [ ] Spatial grid system
- [ ] Double-buffered game state

### Phase 3: Gameplay

- [ ] Tower placement
- [ ] Enemy spawning and movement
- [ ] Combat system
- [ ] Wave management

### Phase 4: Polish

- [ ] UI/HUD
- [ ] Visual effects
- [ ] Sound effects
- [ ] Level editor

## Design Goals

This project demonstrates:

1. **Clean Architecture** - Separation of concerns between core, engine, and gameplay
2. **Concurrency** - Thread pool for parallel AI and pathfinding
3. **Performance** - Spatial partitioning and efficient algorithms
4. **Maintainability** - Modern C++17, no global state, clear interfaces
5. **Scalability** - ECS allows easy feature additions

## License

MIT License - See LICENSE file for details

## Contributing

This is an educational project. Feel free to fork and experiment!

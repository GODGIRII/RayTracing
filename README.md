# RayTracing (2D Light Simulation in C using SDL2)

A simple real-time 2D ray tracing demo written in C using SDL2.  
Rays are emitted from a light source and stop when they hit an obstacle, simulating how light works in real environments.

---

## 🎮 Features

- Mouse-controlled light source
- Rays cast in all directions (adjustable)
- Light rays stop on collision with an object
- Smooth 60 FPS rendering using SDL2
- Minimal, single-file C implementation

---

## 🧰 Requirements

- [SDL2](https://libsdl.org/download-2.0.php)
- GCC or any C compiler with SDL2 support

---

## 🛠 Build & Run

```bash
gcc RayTracing.c -o RayTracing -lSDL2 -lm
./RayTracing

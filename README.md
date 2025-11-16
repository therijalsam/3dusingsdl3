# SDL3 Render3D

**SDL3 Render3D** is a lightweight 3D rendering engine written in **C++** using **SDL3 only** — no OpenGL, Vulkan, or GPU APIs.  
It features a full CPU-based software renderer capable of loading and projecting OBJ models in real time.  
This project is designed for learning and experimentation with low-level rendering techniques and engine architecture.

---

## ✨ Features

- **Software 3D Rasterizer** – Everything is rendered on the CPU using SDL3 framebuffers.
- **OBJ Mesh Loading** – Supports rendering OBJ files (e.g., `cube.obj`, `gorilla.obj`).
- **Perspective Projection** – Custom projection math using `Mat4` and `Vec3`.
- **Camera System** – Move and rotate within the 3D scene.
- **Model Transformations** – Translate, rotate, and scale objects.
- **Modular Architecture** – Independent mesh, math, projection, and rendering components.
- **No GPU Graphics APIs** – 100% CPU-side rendering.

---

## 📁 Project Structure

    sdl3render/
    │── assets/
    │   ├── cube.obj
    │   └── gorilla.obj
    │
    │── include/
    │   └── sdl3_renderer/
    │       ├── Camera.hpp
    │       ├── CameraController.hpp
    │       ├── GridRenderer.hpp
    │       ├── IMeshLoader.hpp
    │       ├── IProjector.hpp
    │       ├── Mat4.hpp
    │       ├── Mesh.hpp
    │       ├── ModelTransformer.hpp
    │       ├── OBJMeshLoader.hpp
    │       ├── Projector.hpp
    │       ├── Renderer3D.hpp
    │       └── Vec3.hpp
    │
    │── src/
    │   └── main.cpp
    │
    │── CMakeLists.txt
    │── LICENSE
    └── README.md

---

## 🔧 Technologies Used

- **C++17**
- **SDL3**
- **CMake**
- **Custom Math Library** (`Mat4`, `Vec3`)
- **Custom OBJ Loader**
- **Software Rasterization (no GPU)**

---

## 🛠 Requirements

### Dependencies

- C++17 or newer
- SDL3
- CMake 3.18+
- (Optional) CLion / VS Code / Make / Ninja

### Install SDL3 (via vcpkg)

    vcpkg install sdl3

Or build SDL3 from source:  
https://github.com/libsdl-org/SDL

---

## 🚀 Getting Started

### 1. Clone the repository

    git clone https://github.com/therijalsam/3dusingsdl3.git
    cd 3dusingsdl3

### 2. Configure and build

    mkdir build
    cd build
    cmake ..
    cmake --build .

### 3. Run the renderer

    ./sdl3render

---

## 🖥 Current Output

The renderer currently supports:

- Rendering a rotating cube or OBJ mesh.
- CPU-based rasterization using SDL3.
- Basic camera movement and projection.



---

## 🧱 Architecture Overview

| Component         | Purpose                                   |
|-------------------|-------------------------------------------|
| `Renderer3D`      | Main render loop and rasterizer           |
| `Mesh`            | Stores vertices and indices               |
| `OBJMeshLoader`   | Loads `.obj` model files                  |
| `Mat4` / `Vec3`   | Linear algebra utilities (matrices/vectors) |
| `Camera`          | View transformation and controls          |
| `Projector`       | Perspective projection logic              |
| `ModelTransformer`| Scaling, rotation, and translation        |

---

## 📌 Roadmap / TODO

- [ ] Triangle fill rasterization
- [ ] Backface culling
- [ ] Depth buffer (Z-buffer)
- [ ] Basic lighting model
- [ ] Texture mapping
- [ ] Keyboard controls for switching models
- [ ] `.mtl` material support

---

## 🤝 Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a new branch: `feature/your-feature-name`.
3. Commit your changes with clear messages.
4. Open a pull request describing your changes.

---

## 📄 License

This project is licensed under the **MIT License**.  
See the `LICENSE` file for details.

---


---

## ⭐ Support

If you find this project helpful, please consider giving it a ⭐ on GitHub.  


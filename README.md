# 3D Solar System Simulation

A 3D solar system built with **C++** and **OpenGL (GLUT)**. Watch planets orbit the Sun, Earth's moon spin, and take control with slick camera moves.

## Features

- Full planet: Sun, Mercury, Venus, Earth (+Moon), Mars, Jupiter, Saturn, Uranus, Neptune
- Custom sizes, colors, and orbit distances for that real-space vibe
- Mouse drag to rotate, scroll to zoom
- Clean gray orbit paths for each planet

## How It's Built

- Planets: Rendered with `glutSolidSphere`
- Orbits: Drawn using `GL_LINE_LOOP`
- Smooth animation using `GLUT` timer
- Description: We started by drawing spheres for each planet and updated their position using basic trigonometry.  
  We added orbits using line loops and used timer functions for smooth animation.  
  For the 3D view, we added camera controls and zoom functionality.

## 🎥 Demo

Video link: [Link](https://drive.google.com/file/d/1wVAG7uFWU1ZrmZ7jmt463uhAOpxGASfa/view?usp=sharing)

## Get It Running

### Linux

```bash
sudo apt-get install g++ freeglut3-dev
g++ -o solar_system solar_system.cpp -lGL -lGLU -lglut
./solar_system
```

### macOS

```bash
xcode-select --install
g++ -o solar_system solar_system.cpp -framework OpenGL -framework GLUT
./solar_system
```

### Windows

- Install MinGW with OpenGL and freeglut
  Compile using:

```bash
g++ -o solar_system.exe solar_system.cpp -lglut32 -lopengl32 -lglu32
```

- Run solar_system.exe

# Air Battle
[![OctoCounts](https://api.octocounts.com/api/reports/5a9172ea749b7a1b6d3164f6c4c79c5f02e467a87846b0d07dd796bbc5bf77d9/badge.svg)](https://octocounts.com/github/Cookie-LINcq/Air_Battle_3D_Engine/commit/b1dfd7c247df4f4b02a1926853e632c5aeb821eb?analysis=%7B%22ignoredDirs%22%3A%5B%5D%2C%22ignoredLanguages%22%3A%5B%5D%2C%22profile%22%3A%22default%22%2C%22includeDocs%22%3Afalse%2C%22includeTests%22%3Afalse%2C%22includeGenerated%22%3Afalse%7D&reportId=5a9172ea749b7a1b6d3164f6c4c79c5f02e467a87846b0d07dd796bbc5bf77d9)

A two-player split-screen air combat game built on my self-developed 3D engine.

## Game Controls
- Spacebar: pause, lock the aircraft, mainly for capturing high-speed scenes.

### Red Aircraft
- W: speed up
- S: slow down
- A: turn left
- D: turn right
- T: dive
- G: climb
- F: roll left
- H: roll right
- Z: toggle target marker
- E: hold to fire machine gun
- R: toggle machine gun
- Q: mark target / lock target / fire missile

### Blue Aircraft
- I: speed up
- K: slow down
- J: turn left
- L: turn right
- ↑: dive
- ↓: climb
- ←: roll left
- →: roll right
- M: toggle target marker
- O: hold to fire machine gun
- P: toggle machine gun
- U: mark target / lock target / fire missile

## Core Features
- 3D coordinate transformation and quaternion rotation
- 3D-to-3D and 3D-to-2D projection
- Simple lighting system
- Self-developed triangle occlusion sorting algorithm

## Dependencies
- Windows
- Visual Studio: https://visualstudio.microsoft.com/
- C++ standard library
- EasyX graphics library: https://easyx.cn/ (a free, simple C++ drawing library
 for Windows, supporting Visual Studio and MinGW series compilers)

## How to run
1. Make sure your operating system is Windows
2. Install Visual Studio
3. Install and configure the EasyX graphics library for Visual Studio
4. Keep `3D_Engine.sln` and the `3D_Engine` source folder in the same directory
5. Open `3D_Engine.sln` with Visual Studio
6. Build the project and run the compiled program

> Tested on Windows with Visual Studio 2022 and EasyX. The exact minor version of EasyX is not tracked; any stable EasyX release compatible with Visual Studio 2022 is acceptable.

## Code Statistics
https://octocounts.com/github/Cookie-LINcq/Air_Battle_3D_Engine

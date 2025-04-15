# Savely

Savely is a open source, community driven project designed to allow people to freely modify there game saves.

## Features

- Built using Qt framework.
- Uses CMake for cross-platform builds.
- Organized modular structure (`src/`, `build/`, `.vscode/`).
- Clean and lightweight design.

## Getting Started

### Prerequisites

- CMake 3.16+
- C++17-compatible compiler
- Qt (Qt6 recommended)

### Build Instructions

```bash
git clone https://github.com/itswyattfr/Savely.git
cd Savely
mkdir build
cd build
cmake ..
make
```

## Project Structure

- `src/` – Main application source code
- `build/` – Compiled binaries (not included in repo)
- `.vscode/` – Editor settings for Visual Studio Code
- `CMakeLists.txt` – Main CMake configuration
- `CMakeLists.txt.qtds` – Qt Designer-specific CMake config

## Contributing

Feel free to fork the project and submit pull requests. Issues and suggestions are also welcome.

## License

MIT License

Copyright (c) 2025 Wyatt

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

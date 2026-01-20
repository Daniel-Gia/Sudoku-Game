<div align="center">
<div align="center" style="width: 100%;">
    <img src="assets/github/logo.png" alt="Sudoku Game Logo" style="max-width: 100%;"/>
    <br>
</div>
</div>

<p align="center">
   <a href="LICENSE">
      <img src="https://img.shields.io/badge/License-Apache%202.0-blue.svg" alt="License: Apache-2.0" />
   </a>
</p>

# Sudoku Game

## About this project
This is a desktop Sudoku game application built using C++ and the Qt framework. It provides a clean, native interface for playing Sudoku puzzles.
<div align="center">
    <img src="assets/github/demo.jpg" alt="Game Demo" width="300"/>
</div>

## How to install the compiled game
If you just want to play the game, you don't need to build it from source.

1. Go to the **[Releases](https://github.com/Daniel-Gia/Sudoku-Game/releases)** section of this repository.
2. Download the version for your operating system:
   - **Windows:** Download the `SudokuGame-Windows.zip` file.
3. Extract the zip and run the generic executable (`SudokuGame.exe` on Windows).

## Libraries used
*   **[Qt 6](https://www.qt.io/)**: Used for the graphical user interface (Qt Widgets), core logic, and window management.

## Project Setup & Building
To develop or build this project from source, follow these steps.

### Prerequisites
1.  **Install Qt 6**: Download and install Qt from the official website.
2.  **Environment Variables**: Ensure your `CMake` and compiler (`Mingw64` or `g++`) paths are correctly set in your system environment variables so the scripts can find them. (and also the qt env path)

### Building on Windows
1.  Open a terminal in the project root.
2.  Initialize the project:
    ```powershell
    .\scripts\windows\init-cmake.ps1
    ```
3.  Build the project (Debug):
    ```powershell
    .\scripts\windows\build.ps1
    ```
    *   **VS Code User?** You can simply press `Ctrl + Shift + B` to trigger the default build task configured in this workspace.

4.  **Create a Final Release**:
    To create a deployable release version, run:
    ```powershell
    .\scripts\windows\release.ps1
    ```
    The build artifacts will be located in the `build/` folder.

## License
This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.
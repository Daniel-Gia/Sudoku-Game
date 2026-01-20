$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectRoot = Resolve-Path "$ScriptDir\..\.."

# Step 1: Initialize CMake for Release
& "$ScriptDir\init-cmake.ps1" -BuildType "release"

# Step 2: Build the project
& "$ScriptDir\build.ps1" -BuildType "release"

# Step 3: Run the final build process
& "$ScriptDir\final-build.ps1"
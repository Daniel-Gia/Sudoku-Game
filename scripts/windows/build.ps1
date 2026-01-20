param(
    [string]$BuildType = "Debug"
)

if ($BuildType -eq "release") {
    $BuildType = "Release"
}

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectRoot = Resolve-Path "$ScriptDir\..\.."

cmake --build "$ProjectRoot\build\$BuildType"
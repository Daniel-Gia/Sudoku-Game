param(
    [string]$BuildType = "Debug"
)

if ($BuildType -eq "release") {
    $BuildType = "Release"
}

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectRoot = Resolve-Path "$ScriptDir\..\.."

if (Test-Path "$ProjectRoot\build\$BuildType") {
    Remove-Item -Recurse -Force "$ProjectRoot\build\$BuildType"
}

cmake -S "$ProjectRoot" -B "$ProjectRoot\build\$BuildType" -DCMAKE_BUILD_TYPE=$BuildType
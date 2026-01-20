$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectRoot = Resolve-Path "$ScriptDir\..\.."

cmake --install "$ProjectRoot\build\Release" --prefix "$ProjectRoot\build\Release-Final"
windeployqt "$ProjectRoot\build\Release-Final\SudokuGame.exe"
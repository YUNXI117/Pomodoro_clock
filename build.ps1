$ErrorActionPreference = "Stop"

$sourceFiles = Get-ChildItem -Path "src" -Recurse -Filter "*.cpp" |
    ForEach-Object { $_.FullName }

clang++ -std=c++17 -Wall -Wextra -Iinclude $sourceFiles -o test.exe -l SplashKit

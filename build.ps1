$ErrorActionPreference = "Stop"
$mingwBin = "C:\msys64\mingw64\bin"
if (Test-Path $mingwBin) { $env:PATH = "$mingwBin;$env:PATH" }

New-Item -ItemType Directory -Force -Path "build" | Out-Null
New-Item -ItemType Directory -Force -Path "data" | Out-Null

$sources = Get-ChildItem -Recurse -Path "src" -Filter "*.cpp" | ForEach-Object { $_.FullName }

& g++ -std=c++17 -Wall -Wextra -Iinclude $sources -static -o "build/data_monitor.exe"

Write-Output "Build succeeded: build/data_monitor.exe"

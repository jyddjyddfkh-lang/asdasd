param([switch]$clean)
$ErrorActionPreference = 'Stop'
if ($clean -and (Test-Path build)) { Remove-Item -Recurse -Force build }
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

$ErrorActionPreference = 'Stop'
$so = Get-ChildItem -Path . -Recurse -Filter 'libquestmap-browser.so' | Select-Object -First 1
if (-not $so) { throw 'libquestmap-browser.so not found. Build the project first.' }
$stage = Join-Path $PWD 'qmod_out'
if (Test-Path $stage) { Remove-Item -Recurse -Force $stage }
New-Item -ItemType Directory -Path $stage | Out-Null
Copy-Item $so.FullName (Join-Path $stage 'libquestmap-browser.so')
Copy-Item 'qmod/mod.json' (Join-Path $stage 'mod.json')
Copy-Item 'qmod/cover.png' (Join-Path $stage 'cover.png')
& 7z a -tzip 'QuestMapBrowser.qmod' "$stage\*" | Out-Null
if ($LASTEXITCODE -ne 0) { throw '7z failed to create QMOD.' }
Write-Host "Created QuestMapBrowser.qmod"

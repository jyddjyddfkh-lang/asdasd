$ErrorActionPreference = 'Stop'
$manifest = Get-Content ./qmod/mod.json -Raw | ConvertFrom-Json
if ($manifest.packageId -ne 'com.beatgames.beatsaber') { throw 'Wrong packageId' }
if ($manifest.packageVersion -ne '1.40.8_7379') { throw 'Wrong packageVersion' }
if ($manifest.modloader -ne 'Scotland2') { throw 'Wrong modloader' }
if (-not ($manifest.lateModFiles -contains 'libquestmap-browser.so')) { throw 'Missing lateModFiles entry' }
Write-Host 'Manifest OK' -ForegroundColor Green

param(
    [Parameter(Mandatory = $true)]
    [string]$Port,

    [Parameter(Mandatory = $true)]
    [ValidateRange(9600, 921600)]
    [int]$BaudRate,

    [Parameter(Mandatory = $true)]
    [ValidateSet("status", "sd-mount", "audio", "offline", "online", "p1", "p2-storage", "p2-migration", "p2-migration-exact", "p2-projects", "p2-chats", "p2-context", "p2-summary", "p2-limits", "p2-archive", "p2-file", "p2-binary", "p6-providers", "hotfix-message", "hotfix-latency", "hotfix-device-ui", "web-console-start", "web-console-cycle", "full")]
    [string]$Suite,

    [Parameter(Mandatory = $true)]
    [string]$LogPath
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"
$script:readinessLost = $false
$script:webConsoleActive = $false
$script:cleanupReadinessConfirmed = $false
$script:serialPending = ""

function New-RegressionCase {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Name,

        [Parameter(Mandatory = $true)]
        [string]$Command,

        [Parameter(Mandatory = $true)]
        [string]$CompletionPattern,

        [Parameter(Mandatory = $true)]
        [string]$PassPattern,

        [Parameter(Mandatory = $true)]
        [ValidateRange(1, 600)]
        [int]$TimeoutSeconds
    )

    return [pscustomobject]@{
        Name = $Name
        Command = $Command
        CompletionPattern = $CompletionPattern
        PassPattern = $PassPattern
        TimeoutSeconds = $TimeoutSeconds
    }
}

function Read-SerialLines {
    param(
        [Parameter(Mandatory = $true)]
        [System.IO.Ports.SerialPort]$Serial,

        [Parameter(Mandatory = $true)]
        [AllowEmptyString()]
        [string]$Pending
    )

    $combined = $Pending + $Serial.ReadExisting()
    $parts = $combined -split "`n"
    $lines = [System.Collections.Generic.List[string]]::new()
    for ($index = 0; $index -lt $parts.Count - 1; $index++) {
        $lines.Add($parts[$index].TrimEnd("`r"))
    }
    return [pscustomobject]@{
        Lines = $lines
        Pending = $parts[-1]
    }
}

function Add-SerialCrashTail {
    param(
        [Parameter(Mandatory = $true)]
        [System.IO.Ports.SerialPort]$Serial,

        [Parameter(Mandatory = $true)]
        [string]$LogPath
    )

    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    while ($stopwatch.Elapsed.TotalSeconds -lt 4) {
        Start-Sleep -Milliseconds 40
        $read = Read-SerialLines -Serial $Serial -Pending $script:serialPending
        $script:serialPending = $read.Pending
        foreach ($line in $read.Lines) {
            if ($line.Length -gt 0) {
                Add-Content -LiteralPath $LogPath -Value $line
            }
        }
    }
    if ($script:serialPending.Length -gt 0) {
        Add-Content -LiteralPath $LogPath -Value $script:serialPending
    }
}

function Read-ClassifiedSerialLines {
    param(
        [Parameter(Mandatory = $true)]
        [System.IO.Ports.SerialPort]$Serial,

        [Parameter(Mandatory = $true)]
        [string]$LogPath,

        [Parameter(Mandatory = $true)]
        [string]$Context
    )

    try {
        $read = Read-SerialLines -Serial $Serial -Pending $script:serialPending
    } catch {
        $script:readinessLost = $true
        throw
    }
    $script:serialPending = $read.Pending

    $readinessLossLine = ""
    foreach ($line in $read.Lines) {
        if ($readinessLossLine.Length -eq 0 -and $line -match "Guru Meditation|Brownout|abort\(\)|\bFATAL\b|ESP-ROM:esp32s3|rst:0x") {
            $readinessLossLine = $line
        }
    }
    if ($readinessLossLine.Length -eq 0 -and $script:serialPending -match "Guru Meditation|Brownout|abort\(\)|\bFATAL\b|ESP-ROM:esp32s3|rst:0x") {
        $readinessLossLine = $script:serialPending
    }
    if ($readinessLossLine.Length -gt 0) {
        $script:readinessLost = $true
    }

    foreach ($line in $read.Lines) {
        if ($line.Length -gt 0) {
            Add-Content -LiteralPath $LogPath -Value $line
        }
    }
    if ($readinessLossLine.Length -gt 0) {
        Add-SerialCrashTail -Serial $Serial -LogPath $LogPath
        throw "Device reset or panic during ${Context}: $readinessLossLine"
    }
    return $read.Lines
}

function Assert-InitialDeviceReadiness {
    param(
        [Parameter(Mandatory = $true)]
        [System.IO.Ports.SerialPort]$Serial,

        [Parameter(Mandatory = $true)]
        [string]$LogPath
    )

    try {
        Read-ClassifiedSerialLines -Serial $Serial -LogPath $LogPath -Context "initial readiness drain" | Out-Null
        $Serial.WriteLine("PING")
        $Serial.BaseStream.Flush()
    } catch {
        $script:readinessLost = $true
        throw
    }
    $pongObserved = $false
    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    while ($stopwatch.Elapsed.TotalSeconds -lt 8) {
        Start-Sleep -Milliseconds 40
        $lines = Read-ClassifiedSerialLines -Serial $Serial -LogPath $LogPath -Context "initial readiness"
        foreach ($line in $lines) {
            if ($line.Length -eq 0) {
                continue
            }
            if ($line -eq "PONG") {
                $pongObserved = $true
            }
        }
        if ($pongObserved) {
            return
        }
    }
    $script:readinessLost = $true
    throw "Serial channel did not answer the initial PING"
}

function Invoke-RegressionCase {
    param(
        [Parameter(Mandatory = $true)]
        [System.IO.Ports.SerialPort]$Serial,

        [Parameter(Mandatory = $true)]
        [pscustomobject]$Case,

        [Parameter(Mandatory = $true)]
        [string]$LogPath
    )

    if ($script:readinessLost) {
        throw "Device readiness was already lost before '$($Case.Name)'"
    }
    $script:cleanupReadinessConfirmed = $false
    Start-Sleep -Milliseconds 100
    try {
        Read-ClassifiedSerialLines -Serial $Serial -LogPath $LogPath -Context "drain before '$($Case.Name)'" | Out-Null
        $Serial.WriteLine($Case.Command)
        $Serial.BaseStream.Flush()
    } catch {
        $script:readinessLost = $true
        throw
    }
    Write-Host ("RUN  {0}" -f $Case.Name)
    Add-Content -LiteralPath $LogPath -Value ("COMMAND name={0}" -f $Case.Name)

    $completedLine = ""
    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    while ($stopwatch.Elapsed.TotalSeconds -lt $Case.TimeoutSeconds) {
        Start-Sleep -Milliseconds 40
        $lines = Read-ClassifiedSerialLines -Serial $Serial -LogPath $LogPath -Context "'$($Case.Name)'"
        foreach ($line in $lines) {
            if ($line.Length -eq 0) {
                continue
            }
            if ($completedLine.Length -eq 0 -and $line -match $Case.CompletionPattern) {
                $completedLine = $line
            }
        }
        if ($completedLine.Length -gt 0) {
            $script:cleanupReadinessConfirmed = $true
            break
        }
    }

    if ($completedLine.Length -eq 0) {
        $script:readinessLost = $true
        $script:cleanupReadinessConfirmed = $false
        throw "Timed out after $($Case.TimeoutSeconds)s waiting for '$($Case.Name)'"
    }
    if ($completedLine -notmatch $Case.PassPattern) {
        throw "Regression '$($Case.Name)' failed: $completedLine"
    }
    Write-Host ("PASS {0}" -f $Case.Name)
}

function ConvertTo-P6UnsignedField {
    param(
        [Parameter(Mandatory = $true)]
        [System.Text.RegularExpressions.Match]$Match,

        [Parameter(Mandatory = $true)]
        [string]$Name
    )

    return [uint64]::Parse(
        $Match.Groups[$Name].Value,
        [System.Globalization.NumberStyles]::None,
        [System.Globalization.CultureInfo]::InvariantCulture)
}

function Assert-P6ProviderMeasuredLine {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Line,

        [Parameter(Mandatory = $true)]
        [string]$Nonce
    )

    $pattern = '^P6PROVIDERTEST stage=measured nonce=(?<nonce>[0-9]{1,20}) ' +
        'profiles_before=(?<profilesBefore>[0-9]+) profiles_max=(?<profilesMax>[0-9]+) ' +
        'owned_profiles=(?<ownedProfiles>[0-9]+) presets_max=(?<presetsMax>[0-9]+) ' +
        'total=(?<total>[0-9]+) used_before=(?<usedBefore>[0-9]+) ' +
        'available_before=(?<availableBefore>[0-9]+) namespace_before=(?<namespaceBefore>[0-9]+) ' +
        'used_max=(?<usedMax>[0-9]+) available_max=(?<availableMax>[0-9]+) ' +
        'namespace_max=(?<namespaceMax>[0-9]+) profile_reject_available=(?<profileRejected>[0-9]+) ' +
        'profile_recovered_available=(?<profileRecovered>[0-9]+) preset_reject_available=(?<presetRejected>[0-9]+) ' +
        'preset_recovered_available=(?<presetRecovered>[0-9]+) available_clean=(?<availableClean>[0-9]+) ' +
        'namespace_clean=(?<namespaceClean>[0-9]+) heap_before=(?<heapBefore>[0-9]+) ' +
        'heap_after=(?<heapAfter>[0-9]+) largest_before=(?<largestBefore>[0-9]+) ' +
        'largest_after=(?<largestAfter>[0-9]+) stack_free=(?<stackFree>[0-9]+) ' +
        'operation_ms=(?<operationMs>[0-9]+) render_ms=(?<renderMs>[0-9]+) resources=pass$'
    $match = [regex]::Match($Line, $pattern)
    if (-not $match.Success -or $match.Groups["nonce"].Value -ne $Nonce) {
        throw "P6 provider measured envelope is malformed or belongs to another nonce"
    }

    $profilesBefore = ConvertTo-P6UnsignedField -Match $match -Name "profilesBefore"
    $profilesMax = ConvertTo-P6UnsignedField -Match $match -Name "profilesMax"
    $ownedProfiles = ConvertTo-P6UnsignedField -Match $match -Name "ownedProfiles"
    $presetsMax = ConvertTo-P6UnsignedField -Match $match -Name "presetsMax"
    $total = ConvertTo-P6UnsignedField -Match $match -Name "total"
    $usedBefore = ConvertTo-P6UnsignedField -Match $match -Name "usedBefore"
    $availableBefore = ConvertTo-P6UnsignedField -Match $match -Name "availableBefore"
    $namespaceBefore = ConvertTo-P6UnsignedField -Match $match -Name "namespaceBefore"
    $usedMax = ConvertTo-P6UnsignedField -Match $match -Name "usedMax"
    $availableMax = ConvertTo-P6UnsignedField -Match $match -Name "availableMax"
    $namespaceMax = ConvertTo-P6UnsignedField -Match $match -Name "namespaceMax"
    $profileRejected = ConvertTo-P6UnsignedField -Match $match -Name "profileRejected"
    $profileRecovered = ConvertTo-P6UnsignedField -Match $match -Name "profileRecovered"
    $presetRejected = ConvertTo-P6UnsignedField -Match $match -Name "presetRejected"
    $presetRecovered = ConvertTo-P6UnsignedField -Match $match -Name "presetRecovered"
    $availableClean = ConvertTo-P6UnsignedField -Match $match -Name "availableClean"
    $namespaceClean = ConvertTo-P6UnsignedField -Match $match -Name "namespaceClean"
    $heapBefore = ConvertTo-P6UnsignedField -Match $match -Name "heapBefore"
    $heapAfter = ConvertTo-P6UnsignedField -Match $match -Name "heapAfter"
    $largestBefore = ConvertTo-P6UnsignedField -Match $match -Name "largestBefore"
    $largestAfter = ConvertTo-P6UnsignedField -Match $match -Name "largestAfter"
    $stackFree = ConvertTo-P6UnsignedField -Match $match -Name "stackFree"
    $operationMs = ConvertTo-P6UnsignedField -Match $match -Name "operationMs"
    $renderMs = ConvertTo-P6UnsignedField -Match $match -Name "renderMs"
    if ($profilesBefore -notin @([uint64]1, [uint64]2) -or
        $profilesMax -ne 3 -or $ownedProfiles -ne (3 - $profilesBefore) -or
        $presetsMax -ne 6) {
        throw "P6 provider profile or preset boundary measurement is invalid"
    }
    if ($total -eq 0 -or $usedBefore -eq 0 -or $availableBefore -eq 0 -or
        $namespaceBefore -eq 0 -or $usedMax -le $usedBefore -or
        $availableMax -ge $availableBefore -or
        $namespaceMax -lt $namespaceBefore -or
        $usedBefore -gt $total -or $availableBefore -gt $total -or
        $usedMax -gt $total -or $availableMax -gt $total -or
        $availableClean -gt $total) {
        throw "P6 provider NVS accounting measurement is invalid"
    }
    if ($profileRejected -ge 30 -or $presetRejected -ge 8 -or
        $profileRecovered -le $profileRejected -or
        $presetRecovered -le $presetRejected -or
        $availableClean -le $availableMax -or
        $namespaceClean -ne $namespaceBefore) {
        throw "P6 provider capacity rejection or recovery measurement is invalid"
    }
    $heapFloor = [uint64](70 * 1024)
    if ($heapBefore -eq 0 -or $heapAfter -lt $heapFloor -or
        $largestBefore -eq 0 -or $largestAfter -eq 0 -or
        $largestBefore -gt $heapBefore -or $largestAfter -gt $heapAfter -or
        $stackFree -eq 0 -or $operationMs -gt 3000 -or $renderMs -gt 250) {
        throw "P6 provider resource or latency measurement is invalid"
    }
    return [pscustomobject]@{
        Total = $total
        NamespaceBefore = $namespaceBefore
    }
}

function Assert-P6ProviderFinalLine {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Line,

        [Parameter(Mandatory = $true)]
        [string]$Nonce,

        [Parameter(Mandatory = $true)]
        [pscustomobject]$Measured
    )

    $pattern = '^P6PROVIDERTEST result=pass nonce=(?<nonce>[0-9]{1,20}) ' +
        'reboot=pass persistence=pass resolver=pass default=pass cleanup=pass ' +
        'total=(?<total>[0-9]+) used=(?<used>[0-9]+) available=(?<available>[0-9]+) ' +
        'namespace=(?<namespace>[0-9]+) heap=(?<heap>[0-9]+) largest=(?<largest>[0-9]+) ' +
        'stack_free=(?<stackFree>[0-9]+) error=none$'
    $match = [regex]::Match($Line, $pattern)
    if (-not $match.Success -or $match.Groups["nonce"].Value -ne $Nonce) {
        throw "P6 provider final envelope is malformed or belongs to another nonce"
    }
    $total = ConvertTo-P6UnsignedField -Match $match -Name "total"
    $used = ConvertTo-P6UnsignedField -Match $match -Name "used"
    $available = ConvertTo-P6UnsignedField -Match $match -Name "available"
    $namespace = ConvertTo-P6UnsignedField -Match $match -Name "namespace"
    $heap = ConvertTo-P6UnsignedField -Match $match -Name "heap"
    $largest = ConvertTo-P6UnsignedField -Match $match -Name "largest"
    $stackFree = ConvertTo-P6UnsignedField -Match $match -Name "stackFree"
    if ($total -ne $Measured.Total -or $total -eq 0 -or
        $used -eq 0 -or $used -gt $total -or
        $available -eq 0 -or $available -gt $total -or
        $namespace -ne $Measured.NamespaceBefore -or
        $heap -lt [uint64](70 * 1024) -or $largest -eq 0 -or
        $largest -gt $heap -or $stackFree -eq 0) {
        throw "P6 provider final cleanup or resource measurement is invalid"
    }
}

function Invoke-P6ProviderRegression {
    param(
        [Parameter(Mandatory = $true)]
        [System.IO.Ports.SerialPort]$Serial,

        [Parameter(Mandatory = $true)]
        [string]$LogPath,

        [Parameter(Mandatory = $true)]
        [string]$Nonce
    )

    if ($script:readinessLost) {
        throw "Device readiness was already lost before the P6 provider regression"
    }
    $command = "P6PROVIDERTEST$Nonce"
    $finishCommand = "P6PROVIDERFINISH$Nonce"
    Start-Sleep -Milliseconds 100
    try {
        $initialRead = Read-SerialLines -Serial $Serial -Pending $script:serialPending
    } catch {
        $script:readinessLost = $true
        throw
    }
    $script:serialPending = $initialRead.Pending
    $initialFailure = ""
    foreach ($line in $initialRead.Lines) {
        if ($line -match 'Guru Meditation|Brownout|abort\(\)|\bFATAL\b|ESP-ROM:esp32s3|rst:0x|^BOOT ') {
            $initialFailure = $line
        }
    }
    if ($initialFailure.Length -eq 0 -and
        $script:serialPending -match 'Guru Meditation|Brownout|abort\(\)|\bFATAL\b|ESP-ROM:esp32s3|rst:0x|^BOOT ') {
        $initialFailure = $script:serialPending
    }
    if ($initialFailure.Length -gt 0) {
        $script:readinessLost = $true
    }
    foreach ($line in $initialRead.Lines) {
        if ($line.Length -gt 0) {
            Add-Content -LiteralPath $LogPath -Value $line
        }
    }
    if ($initialFailure.Length -gt 0) {
        if ($script:serialPending.Length -gt 0) {
            Add-Content -LiteralPath $LogPath -Value $script:serialPending
        }
        throw "Device reset, panic, or fatal output before P6 provider regression"
    }
    try {
        $Serial.WriteLine($command)
        $Serial.BaseStream.Flush()
    } catch {
        $script:readinessLost = $true
        throw
    }
    Write-Host "RUN  P6 provider persistence and limits"
    Add-Content -LiteralPath $LogPath -Value "COMMAND name=P6 provider persistence and limits"

    $phase = "await_reboot_marker"
    $stageDeadline = [DateTime]::UtcNow.AddSeconds(300)
    $readyDeadline = [DateTime]::MaxValue
    $finalDeadline = [DateTime]::MaxValue
    $measured = $null
    $romObserved = $false
    $resetLineObserved = $false
    $bootObserved = $false
    $continuationSent = $false
    $finalObserved = $false
    while ($true) {
        $now = [DateTime]::UtcNow
        $deadline = switch ($phase) {
            "await_reboot_marker" { $stageDeadline }
            "await_boot" { $readyDeadline }
            "await_ready" { $readyDeadline }
            "ready_observed" { $readyDeadline }
            "await_final" { $finalDeadline }
            default { [DateTime]::MinValue }
        }
        if ($now -ge $deadline) {
            $script:readinessLost = $true
            if ($script:serialPending.Length -gt 0) {
                Add-Content -LiteralPath $LogPath -Value $script:serialPending
            }
            throw "P6 provider regression timed out during $phase"
        }

        Start-Sleep -Milliseconds 40
        try {
            $read = Read-SerialLines -Serial $Serial -Pending $script:serialPending
        } catch {
            $script:readinessLost = $true
            throw
        }
        $script:serialPending = $read.Pending
        $batchFailure = ""
        $batchReadinessLost = $false
        foreach ($line in $read.Lines) {
            if ($line.Length -eq 0) {
                continue
            }
            if ($line -match 'Guru Meditation|Brownout|abort\(\)|\bFATAL\b') {
                if ($batchFailure.Length -eq 0) {
                    $batchFailure = "panic or fatal output: $line"
                }
                $batchReadinessLost = $true
                continue
            }

            $isRomLine = $line -match 'ESP-ROM:esp32s3'
            $isResetLine = $line -match 'rst:0x'
            $isBootLine = $line -match '^BOOT '
            if ($isRomLine -or $isResetLine -or $isBootLine) {
                if ($phase -ne "await_boot") {
                    if ($batchFailure.Length -eq 0) {
                        $batchFailure = "unexpected or second reset output: $line"
                    }
                    $batchReadinessLost = $true
                    continue
                }
                if ($isRomLine) {
                    if ($romObserved) {
                        if ($batchFailure.Length -eq 0) {
                            $batchFailure = "second ROM boot marker before READY"
                        }
                        $batchReadinessLost = $true
                    }
                    $romObserved = $true
                }
                if ($isResetLine) {
                    if ($resetLineObserved) {
                        if ($batchFailure.Length -eq 0) {
                            $batchFailure = "second reset-reason line before READY"
                        }
                        $batchReadinessLost = $true
                    }
                    $resetLineObserved = $true
                }
                if ($isBootLine) {
                    if ($bootObserved -or
                        $line -notmatch '^BOOT firmware=[^ ]+ reset_reason=3$') {
                        if ($batchFailure.Length -eq 0) {
                            $batchFailure = "planned BOOT marker is missing or invalid: $line"
                        }
                        $batchReadinessLost = $true
                    } else {
                        $bootObserved = $true
                        $phase = "await_ready"
                    }
                }
                continue
            }
            if ($line -match '^P6PROVIDERTEST result=failed\b') {
                if ($batchFailure.Length -eq 0) {
                    $batchFailure = "firmware reported a failed P6 provider proof"
                }
                continue
            }
            if ($batchFailure.Length -gt 0) {
                continue
            }

            if ($phase -eq "await_reboot_marker") {
                if ($line -match '^P6PROVIDERTEST stage=measured\b') {
                    if ($null -ne $measured) {
                        $batchFailure = "duplicate P6 provider measured envelope"
                    } else {
                        try {
                            $measured = Assert-P6ProviderMeasuredLine -Line $line -Nonce $Nonce
                        } catch {
                            $batchFailure = $_.Exception.Message
                        }
                    }
                    continue
                }
                if ($line -eq "P6PROVIDERTEST stage=reboot nonce=$Nonce") {
                    if ($null -eq $measured) {
                        $batchFailure = "P6 provider reboot marker preceded its measured envelope"
                    } else {
                        $phase = "await_boot"
                        $readyDeadline = [DateTime]::UtcNow.AddSeconds(45)
                    }
                    continue
                }
                if ($line -match '^P6PROVIDERTEST ') {
                    $batchFailure = "unexpected P6 provider output before reboot: $line"
                }
                continue
            }
            if ($phase -eq "await_boot") {
                if ($line -eq "READY") {
                    $batchFailure = "READY arrived before the exact planned BOOT marker"
                    $batchReadinessLost = $true
                } elseif ($line -match '^P6PROVIDERTEST ') {
                    $batchFailure = "unexpected P6 provider output while awaiting BOOT: $line"
                }
                continue
            }
            if ($phase -eq "await_ready") {
                if ($line -eq "READY") {
                    $phase = "ready_observed"
                } elseif ($line -match '^P6PROVIDERTEST ') {
                    $batchFailure = "unexpected P6 provider output while awaiting READY: $line"
                }
                continue
            }
            if ($phase -eq "ready_observed") {
                if ($line -eq "READY") {
                    $batchFailure = "duplicate READY after the planned reboot"
                    $batchReadinessLost = $true
                } elseif ($line -match '^P6PROVIDERTEST ') {
                    $batchFailure = "unexpected P6 provider output before continuation"
                }
                continue
            }
            if ($phase -eq "await_final") {
                if ($line -eq "READY") {
                    $batchFailure = "unexpected READY after P6 provider continuation"
                    $batchReadinessLost = $true
                } elseif ($line -match '^P6PROVIDERTEST result=pass\b') {
                    if ($finalObserved) {
                        $batchFailure = "duplicate P6 provider final envelope"
                    } else {
                        try {
                            Assert-P6ProviderFinalLine -Line $line -Nonce $Nonce -Measured $measured
                            $finalObserved = $true
                        } catch {
                            $batchFailure = $_.Exception.Message
                        }
                    }
                } elseif ($line -match '^P6PROVIDERTEST ') {
                    $batchFailure = "unexpected P6 provider continuation output: $line"
                }
            }
        }

        $pendingFatal = $script:serialPending -match
            'Guru Meditation|Brownout|abort\(\)|\bFATAL\b'
        $pendingReset = $script:serialPending -match
            'ESP-ROM:esp32s3|rst:0x|^BOOT(?: |$)'
        if ($pendingFatal -or ($pendingReset -and $phase -ne "await_boot")) {
            if ($batchFailure.Length -eq 0) {
                $batchFailure = "panic, fatal, or forbidden reset output in carried serial data"
            }
            $batchReadinessLost = $true
        }
        if ($batchReadinessLost) {
            $script:readinessLost = $true
        }
        foreach ($line in $read.Lines) {
            if ($line.Length -gt 0) {
                Add-Content -LiteralPath $LogPath -Value $line
            }
        }
        if ($batchFailure.Length -gt 0) {
            if ($script:serialPending.Length -gt 0) {
                Add-Content -LiteralPath $LogPath -Value $script:serialPending
            }
            throw "P6 provider regression failed: $batchFailure"
        }

        if ($phase -eq "ready_observed" -and
            $script:serialPending.Length -eq 0) {
            if ($continuationSent) {
                $script:readinessLost = $true
                throw "P6 provider continuation would be sent more than once"
            }
            try {
                $Serial.WriteLine($finishCommand)
                $Serial.BaseStream.Flush()
            } catch {
                $script:readinessLost = $true
                throw
            }
            $continuationSent = $true
            $phase = "await_final"
            $finalDeadline = [DateTime]::UtcNow.AddSeconds(60)
            Add-Content -LiteralPath $LogPath -Value "COMMAND name=P6 provider reboot continuation"
        }
        if ($finalObserved -and $script:serialPending.Length -eq 0) {
            $script:cleanupReadinessConfirmed = $true
            Write-Host "PASS P6 provider persistence and limits"
            return
        }
    }
}

$offlineCases = @(
    (New-RegressionCase -Name "status" -Command "STATUS" -CompletionPattern "^STATUS version=" -PassPattern "board_adv=yes.*microsd=ready.*chats=ready.*files=ready" -TimeoutSeconds 15),
    (New-RegressionCase -Name "pure functions" -Command "SELFTEST" -CompletionPattern "^SELFTEST result=" -PassPattern "^SELFTEST result=pass$" -TimeoutSeconds 15),
    (New-RegressionCase -Name "display frame budget" -Command "UIBENCH" -CompletionPattern "^UIBENCH result=" -PassPattern "^UIBENCH result=pass" -TimeoutSeconds 20),
    (New-RegressionCase -Name "cancellation" -Command "CANCELTEST" -CompletionPattern "^CANCELTEST result=" -PassPattern "^CANCELTEST result=pass$" -TimeoutSeconds 20),
    (New-RegressionCase -Name "chat and SD storage" -Command "STORAGETEST" -CompletionPattern "^STORAGETEST result=" -PassPattern "^STORAGETEST result=pass$" -TimeoutSeconds 45),
    (New-RegressionCase -Name "large workspace file" -Command "FILETEST" -CompletionPattern "^FILETEST result=" -PassPattern "^FILETEST result=pass" -TimeoutSeconds 180),
    (New-RegressionCase -Name "device settings" -Command "DEVICESETTINGSTEST" -CompletionPattern "^DEVICESETTINGSTEST result=" -PassPattern "^DEVICESETTINGSTEST result=pass" -TimeoutSeconds 45),
    (New-RegressionCase -Name "offline tools" -Command "OFFLINETEST" -CompletionPattern "^OFFLINETEST result=" -PassPattern "^OFFLINETEST result=pass$" -TimeoutSeconds 20),
    (New-RegressionCase -Name "SSH runtime" -Command "SSHCHECK" -CompletionPattern "^SSHCHECK result=" -PassPattern "^SSHCHECK result=pass" -TimeoutSeconds 60),
    (New-RegressionCase -Name "Python partition layout" -Command "PYTHONCHECK" -CompletionPattern "^PYTHONCHECK result=" -PassPattern "^PYTHONCHECK result=pass.*layout=yes.*image=yes" -TimeoutSeconds 20),
    (New-RegressionCase -Name "microphone before speaker" -Command "MICTEST" -CompletionPattern "^MICTEST result=" -PassPattern "^MICTEST result=pass.*peak=[1-9][0-9]*" -TimeoutSeconds 20),
    (New-RegressionCase -Name "speaker hardware" -Command "TTSHW" -CompletionPattern "^TTSHW result=" -PassPattern "^TTSHW result=pass$" -TimeoutSeconds 20),
    (New-RegressionCase -Name "speaker cancellation" -Command "TTSSTOPTEST" -CompletionPattern "^TTSSTOPTEST result=" -PassPattern "^TTSSTOPTEST result=pass$" -TimeoutSeconds 20),
    (New-RegressionCase -Name "microphone after speaker" -Command "MICTEST" -CompletionPattern "^MICTEST result=" -PassPattern "^MICTEST result=pass.*peak=[1-9][0-9]*" -TimeoutSeconds 20),
    (New-RegressionCase -Name "web console start" -Command "CONSOLE" -CompletionPattern "^WEB_CONSOLE result=ready" -PassPattern "^WEB_CONSOLE result=ready" -TimeoutSeconds 20),
    (New-RegressionCase -Name "web console status" -Command "STATUS" -CompletionPattern "^WEB_CONSOLE status=" -PassPattern "^WEB_CONSOLE status=ready authenticated=no" -TimeoutSeconds 15),
    (New-RegressionCase -Name "web console exit" -Command "EXIT" -CompletionPattern "^WEB_CONSOLE result=stopped" -PassPattern "^WEB_CONSOLE result=stopped$" -TimeoutSeconds 20),
    (New-RegressionCase -Name "post-console responsiveness" -Command "STATUS" -CompletionPattern "^STATUS version=" -PassPattern "board_adv=yes.*microsd=ready.*chats=ready.*files=ready" -TimeoutSeconds 15)
)

$audioCases = @(
    (New-RegressionCase -Name "microphone before speaker" -Command "MICTEST" -CompletionPattern "^MICTEST result=" -PassPattern "^MICTEST result=pass.*peak=[1-9][0-9]*" -TimeoutSeconds 20),
    (New-RegressionCase -Name "codec idle after microphone" -Command "AUDIOSTATUS" -CompletionPattern "^AUDIOSTATUS result=" -PassPattern "^AUDIOSTATUS result=pass$" -TimeoutSeconds 15),
    (New-RegressionCase -Name "speaker hardware" -Command "TTSHW" -CompletionPattern "^TTSHW result=" -PassPattern "^TTSHW result=pass$" -TimeoutSeconds 20),
    (New-RegressionCase -Name "codec idle after speaker" -Command "AUDIOSTATUS" -CompletionPattern "^AUDIOSTATUS result=" -PassPattern "^AUDIOSTATUS result=pass$" -TimeoutSeconds 15),
    (New-RegressionCase -Name "speaker cancellation" -Command "TTSSTOPTEST" -CompletionPattern "^TTSSTOPTEST result=" -PassPattern "^TTSSTOPTEST result=pass$" -TimeoutSeconds 20),
    (New-RegressionCase -Name "codec idle after cancellation" -Command "AUDIOSTATUS" -CompletionPattern "^AUDIOSTATUS result=" -PassPattern "^AUDIOSTATUS result=pass$" -TimeoutSeconds 15),
    (New-RegressionCase -Name "microphone after speaker" -Command "MICTEST" -CompletionPattern "^MICTEST result=" -PassPattern "^MICTEST result=pass.*peak=[1-9][0-9]*" -TimeoutSeconds 20),
    (New-RegressionCase -Name "codec final idle" -Command "AUDIOSTATUS" -CompletionPattern "^AUDIOSTATUS result=" -PassPattern "^AUDIOSTATUS result=pass$" -TimeoutSeconds 15)
)

$onlineCases = @(
    (New-RegressionCase -Name "chat API" -Command "APITEST" -CompletionPattern "^APITEST result=" -PassPattern "^APITEST result=pass" -TimeoutSeconds 120),
    (New-RegressionCase -Name "model file tool" -Command "TOOLTEST" -CompletionPattern "^TOOLTEST result=" -PassPattern "^TOOLTEST result=pass" -TimeoutSeconds 180),
    (New-RegressionCase -Name "web search API" -Command "WEBTEST" -CompletionPattern "^WEBTEST result=" -PassPattern "^WEBTEST result=pass(?: error=none)?$" -TimeoutSeconds 120),
    (New-RegressionCase -Name "web contents API" -Command "FETCHTEST" -CompletionPattern "^FETCHTEST result=" -PassPattern "^FETCHTEST result=pass(?: error=none)?$" -TimeoutSeconds 120),
    (New-RegressionCase -Name "search sources cache" -Command "SEARCHCACHETEST" -CompletionPattern "^SEARCHCACHETEST result=" -PassPattern "^SEARCHCACHETEST result=pass" -TimeoutSeconds 30),
    (New-RegressionCase -Name "model search tool decision" -Command "SEARCHTEST" -CompletionPattern "^SEARCHTEST result=" -PassPattern "^SEARCHTEST result=(?:pass search_called=yes tool=web_search response_bytes=[1-9][0-9]* error=none|failed search_called=no tool=(?:WebSearch|none) response_bytes=[1-9][0-9]* error=Model did not call every required tool capability \(group mask 0x1\))$" -TimeoutSeconds 240),
    (New-RegressionCase -Name "UI search path" -Command "E2ETEST" -CompletionPattern "^E2ETEST result=" -PassPattern "^E2ETEST result=pass.*response=yes.*cleanup=yes" -TimeoutSeconds 300),
    (New-RegressionCase -Name "SSH host probe" -Command "SSHPROBE" -CompletionPattern "^SSHPROBE result=" -PassPattern "^SSHPROBE result=pass" -TimeoutSeconds 120),
    (New-RegressionCase -Name "public SSH SFTP and PTY" -Command "SSHDEMOTEST" -CompletionPattern "^SSHDEMOTEST result=" -PassPattern "^SSHDEMOTEST result=pass" -TimeoutSeconds 300),
    (New-RegressionCase -Name "STT TLS" -Command "STTTLS" -CompletionPattern "^STTTLS result=" -PassPattern "^STTTLS result=pass$" -TimeoutSeconds 90),
    (New-RegressionCase -Name "STT authentication" -Command "STTAUTH" -CompletionPattern "^STTAUTH result=" -PassPattern "^STTAUTH result=pass$" -TimeoutSeconds 120),
    (New-RegressionCase -Name "TTS TLS" -Command "TTSTLS" -CompletionPattern "^TTSTLS result=" -PassPattern "^TTSTLS result=pass$" -TimeoutSeconds 90),
    (New-RegressionCase -Name "TTS authentication" -Command "TTSAUTH" -CompletionPattern "^TTSAUTH result=" -PassPattern "^TTSAUTH result=pass" -TimeoutSeconds 120),
    (New-RegressionCase -Name "TTS synthesis and playback" -Command "TTSTEST" -CompletionPattern "^TTSTEST result=" -PassPattern "^TTSTEST result=pass" -TimeoutSeconds 180),
    (New-RegressionCase -Name "post-online responsiveness" -Command "STATUS" -CompletionPattern "^STATUS version=" -PassPattern "wifi=connected.*heap=[1-9][0-9]+" -TimeoutSeconds 15),
    (New-RegressionCase -Name "configured SSH terminal" -Command "SSHSESSIONTEST" -CompletionPattern "^SSHSESSIONTEST result=" -PassPattern "^SSHSESSIONTEST result=pass" -TimeoutSeconds 180),
    (New-RegressionCase -Name "configured SFTP" -Command "SFTPTEST" -CompletionPattern "^SFTPTEST result=" -PassPattern "^SFTPTEST result=pass" -TimeoutSeconds 180),
    (New-RegressionCase -Name "OTA metadata" -Command "OTACHECK" -CompletionPattern "^OTACHECK result=" -PassPattern "^OTACHECK result=pass" -TimeoutSeconds 120),
    (New-RegressionCase -Name "OTA download and digest" -Command "OTADOWNLOADTEST" -CompletionPattern "^OTADOWNLOADTEST result=" -PassPattern "^OTADOWNLOADTEST result=pass" -TimeoutSeconds 300)
)

$p1Cases = @(
    (New-RegressionCase -Name "chat API" -Command "APITEST" -CompletionPattern "^APITEST result=" -PassPattern "^APITEST result=pass" -TimeoutSeconds 120),
    (New-RegressionCase -Name "model file tool" -Command "TOOLTEST" -CompletionPattern "^TOOLTEST result=" -PassPattern "^TOOLTEST result=pass" -TimeoutSeconds 180),
    (New-RegressionCase -Name "web search API" -Command "WEBTEST" -CompletionPattern "^WEBTEST result=" -PassPattern "^WEBTEST result=pass(?: error=none)?$" -TimeoutSeconds 120),
    (New-RegressionCase -Name "web contents API" -Command "FETCHTEST" -CompletionPattern "^FETCHTEST result=" -PassPattern "^FETCHTEST result=pass(?: error=none)?$" -TimeoutSeconds 120),
    (New-RegressionCase -Name "search sources cache" -Command "SEARCHCACHETEST" -CompletionPattern "^SEARCHCACHETEST result=" -PassPattern "^SEARCHCACHETEST result=pass" -TimeoutSeconds 30),
    (New-RegressionCase -Name "model search tool decision" -Command "SEARCHTEST" -CompletionPattern "^SEARCHTEST result=" -PassPattern "^SEARCHTEST result=(?:pass search_called=yes tool=web_search response_bytes=[1-9][0-9]* error=none|failed search_called=no tool=(?:WebSearch|none) response_bytes=[1-9][0-9]* error=Model did not call every required tool capability \(group mask 0x1\))$" -TimeoutSeconds 240),
    (New-RegressionCase -Name "UI search path" -Command "E2ETEST" -CompletionPattern "^E2ETEST result=" -PassPattern "^E2ETEST result=pass.*response=yes.*cleanup=yes" -TimeoutSeconds 300),
    (New-RegressionCase -Name "STT TLS" -Command "STTTLS" -CompletionPattern "^STTTLS result=" -PassPattern "^STTTLS result=pass$" -TimeoutSeconds 90),
    (New-RegressionCase -Name "STT authentication" -Command "STTAUTH" -CompletionPattern "^STTAUTH result=" -PassPattern "^STTAUTH result=pass$" -TimeoutSeconds 120),
    (New-RegressionCase -Name "TTS TLS" -Command "TTSTLS" -CompletionPattern "^TTSTLS result=" -PassPattern "^TTSTLS result=pass$" -TimeoutSeconds 90),
    (New-RegressionCase -Name "TTS authentication" -Command "TTSAUTH" -CompletionPattern "^TTSAUTH result=" -PassPattern "^TTSAUTH result=pass" -TimeoutSeconds 120),
    (New-RegressionCase -Name "TTS synthesis and playback" -Command "TTSTEST" -CompletionPattern "^TTSTEST result=" -PassPattern "^TTSTEST result=pass" -TimeoutSeconds 180),
    (New-RegressionCase -Name "post-P1 responsiveness" -Command "STATUS" -CompletionPattern "^STATUS version=" -PassPattern "wifi=connected.*heap=[1-9][0-9]+" -TimeoutSeconds 15)
)

$p2StorageCases = @(
    (New-RegressionCase -Name "project schema and pagination" -Command "PROJECTSCHEMATEST" -CompletionPattern "^PROJECTSCHEMATEST result=" -PassPattern "^PROJECTSCHEMATEST result=pass chats=33 error=none$" -TimeoutSeconds 180),
    (New-RegressionCase -Name "legacy project migration" -Command "MIGRATIONTEST" -CompletionPattern "^MIGRATIONTEST result=" -PassPattern "^MIGRATIONTEST result=pass legacy=([0-9]+) matched=\1 messages=[0-9]+ archived=[0-9]+ history_fnv32=[0-9a-f]{8} metadata=pass history=pass revision=[1-9][0-9]* error=none$" -TimeoutSeconds 240),
    (New-RegressionCase -Name "migration interruption and corruption" -Command "MIGRATIONRECOVERYTEST" -CompletionPattern "^MIGRATIONRECOVERYTEST result=" -PassPattern "^MIGRATIONRECOVERYTEST result=pass staging=yes corruption=yes restored=yes error=none$" -TimeoutSeconds 180)
)

$p2SharedNonce = [DateTimeOffset]::UtcNow.ToUnixTimeMilliseconds().ToString(
    [System.Globalization.CultureInfo]::InvariantCulture)
$p2SharedCommand = "P2SHAREDTEST$p2SharedNonce"
$p2SharedCompletion = '^P2SHAREDTEST result=(?:pass|failed) nonce={0} ' -f (
    [regex]::Escape($p2SharedNonce))
$p2SharedPass = '^P2SHAREDTEST result=pass nonce={0} identity=pass tools=pass isolation=pass cleanup=pass remaining=0 errors=0 error=none$' -f (
    [regex]::Escape($p2SharedNonce))

$p2ProjectCases = @(
    (New-RegressionCase -Name "project device parity" -Command "PROJECTPARITYTEST" -CompletionPattern "^PROJECTPARITYTEST result=" -PassPattern "^PROJECTPARITYTEST result=pass ui=pass empty=pass rename_cancel=pass rename=pass later_save=pass delete_cancel=pass delete=pass replacement=pass page_zero=pass cleanup=pass resources=pass heap_before=[0-9]+ heap_after=[0-9]+ largest_before=[0-9]+ largest_after=[0-9]+ minimum_heap=[0-9]+ stack_free=[0-9]+ error=none$" -TimeoutSeconds 240),
    (New-RegressionCase -Name "shared project isolation" -Command $p2SharedCommand -CompletionPattern $p2SharedCompletion -PassPattern $p2SharedPass -TimeoutSeconds 180)
)

$p2ChatCases = @(
    (New-RegressionCase -Name "project chat isolation" -Command "PROJECTCHATTEST" -CompletionPattern "^PROJECTCHATTEST result=" -PassPattern "^PROJECTCHATTEST result=pass chats=3 draft_only=pass general_ms=[0-9]+ draft_ms=[0-9]+ error=none$" -TimeoutSeconds 120),
    (New-RegressionCase -Name "instruction precedence" -Command "INSTRUCTIONTEST" -CompletionPattern "^INSTRUCTIONTEST result=" -PassPattern "^INSTRUCTIONTEST result=pass order=pass error=none$" -TimeoutSeconds 20),
    (New-RegressionCase -Name "retry persistence" -Command "RETRYPERSISTENCETEST" -CompletionPattern "^RETRYPERSISTENCETEST result=" -PassPattern "^RETRYPERSISTENCETEST result=pass messages=2 user_copies=1 error=none$" -TimeoutSeconds 60),
    (New-RegressionCase -Name "context compaction persistence" -Command "COMPACTIONTEST" -CompletionPattern "^COMPACTIONTEST result=" -PassPattern "^COMPACTIONTEST result=pass raw=12 manual_tail=8 auto_tail=4 error=none$" -TimeoutSeconds 60),
    (New-RegressionCase -Name "production summary regeneration" -Command "P2SUMMARYTEST26001" -CompletionPattern "^P2SUMMARYTEST result=" -PassPattern "^P2SUMMARYTEST result=pass nonce=26001 provider=pass replace=pass covered=pass raw=pass context=pass cleanup=pass error=none$" -TimeoutSeconds 180)
)

$p2LimitCases = @(
    (New-RegressionCase -Name "P2 storage and request boundaries" -Command "P2LIMITTEST" -CompletionPattern "^P2LIMITTEST result=" -PassPattern "^P2LIMITTEST result=pass prompt=pass project=pass chat=pass error=none$" -TimeoutSeconds 120)
)

$p2FileCases = @(
    (New-RegressionCase -Name "large workspace window, search and edit" -Command "FILETEST" -CompletionPattern "^FILETEST result=" -PassPattern "^FILETEST result=pass$" -TimeoutSeconds 180)
)

$p2DiagnosticNonce = [DateTimeOffset]::UtcNow.ToUnixTimeMilliseconds().ToString(
    [System.Globalization.CultureInfo]::InvariantCulture)
$p2ArchiveCases = @(
    (New-RegressionCase -Name "unbounded project chat archive" -Command "P2ARCHIVETEST$p2DiagnosticNonce" -CompletionPattern "^P2ARCHIVETEST result=(?:pass|failed) nonce=$p2DiagnosticNonce " -PassPattern "^P2ARCHIVETEST result=pass nonce=$p2DiagnosticNonce beyond_2mib=pass quota=pass full=pass planner=pass nonmutation=pass first=pass middle=pass last=pass count=pass hash=pass artifacts=pass cleanup=pass heap_before=[1-9][0-9]* heap_after=[1-9][0-9]* largest_before=[1-9][0-9]* largest_after=[1-9][0-9]* error=none$" -TimeoutSeconds 600)
)
$p2BinaryCases = @(
    (New-RegressionCase -Name "binary transfer and text-tool boundary" -Command "P2BINARYTEST$p2DiagnosticNonce" -CompletionPattern "^P2BINARYTEST result=(?:pass|failed) nonce=$p2DiagnosticNonce " -PassPattern "^P2BINARYTEST result=pass nonce=$p2DiagnosticNonce matrix=pass ui=pass read=pass write=pass append=pass nonmutation=pass cleanup=pass error=none$" -TimeoutSeconds 90)
)

$hotfixLatencyCases = @(
    (New-RegressionCase -Name "project and chat navigation latency" -Command "HOTFIXNAVTEST" -CompletionPattern "^HOTFIXNAVTEST result=" -PassPattern "^HOTFIXNAVTEST result=pass iterations=8 projects_ms=[0-9]+ chats_ms=[0-9]+ average_ms=[0-9]+ actions_lazy=pass actions_ms=[0-9]+ open_ms=[0-9]+ tail_messages=[0-9]+ tail_bytes=[0-9]+ state=pass error=none$" -TimeoutSeconds 30)
)
$hotfixDeviceUiCases = @(
    (New-RegressionCase -Name "device chat input latency" -Command "HOTFIXINPUTTEST" -CompletionPattern "^HOTFIXINPUTTEST result=" -PassPattern "^HOTFIXINPUTTEST result=pass full_average_us=[0-9]+ input_average_us=[0-9]+ scroll_average_us=[0-9]+ scroll=pass scroll_max=[1-9][0-9]* tail_messages=32 tail_bytes=7680 error=none$" -TimeoutSeconds 30),
    (New-RegressionCase -Name "project and chat navigation latency" -Command "HOTFIXNAVTEST" -CompletionPattern "^HOTFIXNAVTEST result=" -PassPattern "^HOTFIXNAVTEST result=pass iterations=8 projects_ms=[0-9]+ chats_ms=[0-9]+ average_ms=[0-9]+ actions_lazy=pass actions_ms=[0-9]+ open_ms=[0-9]+ tail_messages=[0-9]+ tail_bytes=[0-9]+ state=pass error=none$" -TimeoutSeconds 30),
    (New-RegressionCase -Name "microSD read and recovery guards" -Command "HOTFIXSDTEST" -CompletionPattern "^HOTFIXSDTEST result=" -PassPattern "^HOTFIXSDTEST result=pass removed=pass replaced=pass nonmutation=pass error=none$" -TimeoutSeconds 20)
)

$sdMountCases = @(
    (New-RegressionCase -Name "SD remount" -Command "SDMOUNTTEST" -CompletionPattern "^SDMOUNTTEST result=" -PassPattern "^SDMOUNTTEST result=pass card_type=[1-9][0-9]* total_bytes=[1-9][0-9]* used_bytes=[0-9]+ error=none$" -TimeoutSeconds 20)
)

$webConsoleStartCases = @(
    (New-RegressionCase -Name "web console start" -Command "CONSOLE" -CompletionPattern "^WEB_CONSOLE result=ready" -PassPattern "^WEB_CONSOLE result=ready" -TimeoutSeconds 20),
    (New-RegressionCase -Name "web console exit" -Command "EXIT" -CompletionPattern "^WEB_CONSOLE result=stopped" -PassPattern "^WEB_CONSOLE result=stopped$" -TimeoutSeconds 20)
)

$webConsoleCycleCases = @(
    (New-RegressionCase -Name "web console first start" -Command "CONSOLE" -CompletionPattern "^WEB_CONSOLE result=ready" -PassPattern "^WEB_CONSOLE result=ready" -TimeoutSeconds 20),
    (New-RegressionCase -Name "web console first exit" -Command "EXIT" -CompletionPattern "^WEB_CONSOLE result=stopped" -PassPattern "^WEB_CONSOLE result=stopped$" -TimeoutSeconds 20),
    (New-RegressionCase -Name "web console second start" -Command "CONSOLE" -CompletionPattern "^WEB_CONSOLE result=ready" -PassPattern "^WEB_CONSOLE result=ready" -TimeoutSeconds 20),
    (New-RegressionCase -Name "web console second exit" -Command "EXIT" -CompletionPattern "^WEB_CONSOLE result=stopped" -PassPattern "^WEB_CONSOLE result=stopped$" -TimeoutSeconds 20)
)

$resolvedLogPath = [System.IO.Path]::GetFullPath($LogPath)
$logDirectory = [System.IO.Path]::GetDirectoryName($resolvedLogPath)
if (-not [string]::IsNullOrEmpty($logDirectory)) {
    [System.IO.Directory]::CreateDirectory($logDirectory) | Out-Null
}
Set-Content -LiteralPath $resolvedLogPath -Value ("CARDMIND_REGRESSION suite={0} port={1} started={2:o}" -f $Suite, $Port, [DateTime]::UtcNow)

$serial = [System.IO.Ports.SerialPort]::new($Port, $BaudRate, [System.IO.Ports.Parity]::None, 8, [System.IO.Ports.StopBits]::One)
$serial.NewLine = "`r`n"
$serial.DtrEnable = $false
$serial.RtsEnable = $false
$serial.ReadTimeout = 250
$serial.WriteTimeout = 2000

try {
    $serial.Open()
    Start-Sleep -Seconds 12
    Assert-InitialDeviceReadiness -Serial $serial -LogPath $resolvedLogPath
    if ($Suite -eq "p6-providers") {
        $p6ProviderNonce = [DateTimeOffset]::UtcNow.ToUnixTimeMilliseconds().ToString(
            [System.Globalization.CultureInfo]::InvariantCulture)
        Invoke-P6ProviderRegression -Serial $serial -LogPath $resolvedLogPath -Nonce $p6ProviderNonce
        Add-Content -LiteralPath $resolvedLogPath -Value ("CARDMIND_REGRESSION result=pass completed={0:o}" -f [DateTime]::UtcNow)
        Write-Host ("CARDMIND_REGRESSION result=pass cases=1 log={0}" -f $resolvedLogPath)
        return
    }
    $cases = [System.Collections.Generic.List[object]]::new()
    if ($Suite -eq "status") {
        $cases.Add($offlineCases[0])
    }
    if ($Suite -eq "sd-mount") {
        $cases.AddRange([object[]]$sdMountCases)
    }
    if ($Suite -eq "audio") {
        $cases.AddRange([object[]]$audioCases)
    }
    if ($Suite -eq "offline" -or $Suite -eq "full") {
        $cases.AddRange([object[]]$offlineCases)
    }
    if ($Suite -eq "online" -or $Suite -eq "full") {
        $cases.AddRange([object[]]$onlineCases)
    }
    if ($Suite -eq "hotfix-message") {
        $cases.Add($onlineCases[6])
    }
    if ($Suite -eq "hotfix-latency") {
        $cases.AddRange([object[]]$hotfixLatencyCases)
    }
    if ($Suite -eq "hotfix-device-ui") {
        $cases.AddRange([object[]]$hotfixDeviceUiCases)
    }
    if ($Suite -eq "p1") {
        $cases.AddRange([object[]]$p1Cases)
    }
    if ($Suite -eq "p2-storage" -or $Suite -eq "full") {
        $cases.AddRange([object[]]$p2StorageCases)
    }
    if ($Suite -eq "p2-migration") {
        $cases.Add($p2StorageCases[1])
        $cases.Add($p2StorageCases[2])
    }
    if ($Suite -eq "p2-migration-exact") {
        $cases.Add($p2StorageCases[1])
    }
    if ($Suite -eq "p2-projects" -or $Suite -eq "full") {
        $cases.AddRange([object[]]$p2ProjectCases)
    }
    if ($Suite -eq "p2-chats" -or $Suite -eq "full") {
        $cases.AddRange([object[]]$p2ChatCases)
    }
    if ($Suite -eq "p2-summary") {
        $cases.Add($p2ChatCases[4])
    }
    if ($Suite -eq "p2-context") {
        $cases.Add($p2ChatCases[3])
    }
    if ($Suite -eq "p2-limits" -or $Suite -eq "full") {
        $cases.AddRange([object[]]$p2LimitCases)
    }
    if ($Suite -eq "p2-archive") {
        $cases.AddRange([object[]]$p2ArchiveCases)
    }
    if ($Suite -eq "p2-file") {
        $cases.AddRange([object[]]$p2FileCases)
    }
    if ($Suite -eq "p2-binary") {
        $cases.AddRange([object[]]$p2BinaryCases)
    }
    if ($Suite -eq "web-console-start") {
        $cases.AddRange([object[]]$webConsoleStartCases)
    }
    if ($Suite -eq "web-console-cycle") {
        $cases.AddRange([object[]]$webConsoleCycleCases)
    }
    foreach ($case in $cases) {
        Invoke-RegressionCase -Serial $serial -Case $case -LogPath $resolvedLogPath
        if ($case.Command -eq "CONSOLE") {
            $script:webConsoleActive = $true
        }
        if ($case.Command -eq "EXIT") {
            $script:webConsoleActive = $false
        }
    }
    Add-Content -LiteralPath $resolvedLogPath -Value ("CARDMIND_REGRESSION result=pass completed={0:o}" -f [DateTime]::UtcNow)
    Write-Host ("CARDMIND_REGRESSION result=pass cases={0} log={1}" -f $cases.Count, $resolvedLogPath)
} catch {
    $primaryError = $_.Exception
    if ($script:webConsoleActive -and -not $script:readinessLost -and $script:cleanupReadinessConfirmed -and $serial.IsOpen) {
        $cleanupCase = New-RegressionCase -Name "web console failure cleanup" -Command "EXIT" -CompletionPattern "^WEB_CONSOLE result=stopped" -PassPattern "^WEB_CONSOLE result=stopped$" -TimeoutSeconds 20
        try {
            Invoke-RegressionCase -Serial $serial -Case $cleanupCase -LogPath $resolvedLogPath
            $script:webConsoleActive = $false
        } catch {
            throw "Regression failed: $($primaryError.Message); Web Console cleanup failed: $($_.Exception.Message)"
        }
    }
    throw $primaryError
} finally {
    if ($serial.IsOpen) {
        $serial.Close()
    }
    $serial.Dispose()
}

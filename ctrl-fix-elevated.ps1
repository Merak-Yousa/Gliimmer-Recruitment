# Ctrl Fix (elevated) - internal PS/2 keyboard
# All changes are reversible. Does two things:
#   1) Disable Fast Startup (better state reset for internal keyboard on resume)
#   2) Restart the internal keyboard device stack once (does NOT uninstall driver)
$ErrorActionPreference = 'Continue'
$log = 'C:\Users\19991\Desktop\Gliimmer-Recruitment\.dsh-tmp\ctrl-fix-elevated-log.txt'

function Log($msg) {
    Add-Content -Path $log -Value $msg -Encoding utf8
    Write-Host $msg
}

"=== Ctrl Fix (elevated) $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss') ===" | Set-Content $log -Encoding utf8
$isAdmin = (New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
Log "RunAsAdmin: $isAdmin"

# 1) Disable Fast Startup
try {
    Set-ItemProperty -Path 'HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Power' `
        -Name 'HiberbootEnabled' -Value 0 -Type DWord -ErrorAction Stop
    Log "[OK] Fast startup disabled (takes effect after reboot)"
} catch {
    Log "[FAIL] Fast startup: $($_.Exception.Message)"
}

# 2) Restart internal keyboard device stack
try {
    $kbd = Get-PnpDevice -Class Keyboard -ErrorAction Stop |
        Where-Object { $_.FriendlyName -match 'PS/2' } | Select-Object -First 1
    if ($kbd) {
        Log "[INFO] Internal keyboard: $($kbd.FriendlyName) | $($kbd.InstanceId)"
        $out = & pnputil /restart-device "$($kbd.InstanceId)" 2>&1
        $out | ForEach-Object { Log "    $_" }
        Log "[OK] Keyboard device stack restart submitted"
    } else {
        Log "[WARN] PS/2 keyboard device not found"
    }
} catch {
    Log "[FAIL] Keyboard restart: $($_.Exception.Message)"
}

# 3) Record current keyboard devices
try {
    Log "--- Keyboard devices ---"
    $list = Get-PnpDevice -Class Keyboard -ErrorAction Stop |
        Select-Object Status, FriendlyName, InstanceId | Format-Table -AutoSize | Out-String
    $list -split "`r?`n" | Where-Object { $_ } | ForEach-Object { Log "    $_" }
} catch {
    Log "[WARN] Device list failed: $($_.Exception.Message)"
}

Log "=== DONE ==="

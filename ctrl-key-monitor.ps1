# ============================================================
#  Ctrl 键健康监控小工具
#  用途：实时统计「系统实际收到」的 Ctrl 按下/松开次数，
#        帮你区分是「键盘没发出来」还是「系统/软件吞掉了」。
#  用法：右键此文件 →「使用 PowerShell 运行」
#        或在 PowerShell 里执行：pwsh -NoProfile -File .\ctrl-key-monitor.ps1
# ============================================================

Add-Type @'
using System;
using System.Runtime.InteropServices;
public static class KeyWatch {
    [DllImport("user32.dll")] public static extern short GetAsyncKeyState(int vKey);
}
'@

$VK_LCONTROL = 0xA2
$VK_RCONTROL = 0xA3

function Get-CtrlDown {
    $left  = ([KeyWatch]::GetAsyncKeyState($VK_LCONTROL) -band 0x8000) -ne 0
    $right = ([KeyWatch]::GetAsyncKeyState($VK_RCONTROL) -band 0x8000) -ne 0
    return ($left -or $right)
}

$durationSec = 10

Write-Host ""
Write-Host "  Ctrl 键监控已启动" -ForegroundColor Cyan
Write-Host ("  接下来 {0} 秒，请反复按 Ctrl 键（大约每秒 2~3 次，按下去再松开）" -f $durationSec) -ForegroundColor Yellow
Write-Host "  脚本会统计【系统实际收到】的按下 / 松开次数。" -ForegroundColor DarkGray
Write-Host ""

$prev    = $false
$presses = 0
$releases = 0
$downAt  = 0L
$sw      = [System.Diagnostics.Stopwatch]::StartNew()

while ($sw.Elapsed.TotalSeconds -lt $durationSec) {
    $down = Get-CtrlDown
    $now  = $sw.ElapsedMilliseconds
    if ($down -and -not $prev) { $presses++; $downAt = $now }
    if (-not $down -and $prev) { $releases++ }
    $prev = $down
    Start-Sleep -Milliseconds 5
}

$sw.Stop()
Write-Host ""
Write-Host ("  结果：系统收到 按下 {0} 次 / 松开 {1} 次" -f $presses, $releases) -ForegroundColor Cyan
Write-Host ""

if ($presses -eq 0) {
    Write-Host "  一次都没收到！说明按键根本没到系统层——" -ForegroundColor Red
    Write-Host "  优先检查：键盘连接、USB 口、电池、是否换过输入法/驱动。" -ForegroundColor Red
}
elseif ($presses -ne $releases) {
    Write-Host "  按下与松开次数不一致，说明有按键在中途丢失。" -ForegroundColor Yellow
    Write-Host "  典型于：USB 电源管理休眠、无线干扰、键盘接触不良。" -ForegroundColor Yellow
}
else {
    Write-Host "  按下与松开次数一致，按键链路基本正常。" -ForegroundColor Green
    Write-Host "  若这时应用里 Ctrl 快捷键仍偶发失灵，多半是软件层抢了快捷键。" -ForegroundColor Green
}

Write-Host ""
Write-Host "  对照实验小建议：" -ForegroundColor DarkGray
Write-Host "  1) 分别用笔记本自带键盘 / 外接键盘各测一遍，定位是哪个键盘。" -ForegroundColor DarkGray
Write-Host "  2) 失效多发生在「闲置一会儿后第一次按」→ 多半是 USB 电源管理休眠。" -ForegroundColor DarkGray
Write-Host "  3) 失效多发生在「打字很急、连续组合键」时→ 检查筛选键/输入法/宏软件。" -ForegroundColor DarkGray
Write-Host ""

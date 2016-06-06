# viewTune

control your monitor's brightness

**Arg syntax:**
```
setBrightness [monitorIndex] [physicalMonitorIndex] [newBrightness(0-100)]
```
**Example usage:**
```
viewTune.exe setBrightness 0 0 75 // sets first monitor to 75% brightness
viewTune.exe setBrightness 1 0 20 // sets second monitor to 20% brightness
viewTune.exe print // output monitor brightness status and capabilities

viewTune.exe setPower 0 0 0 // sets first monitor power off
viewTune.exe setPower 0 0 1 // sets first monitor power on
```

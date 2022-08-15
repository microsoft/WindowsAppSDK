# Telemetry

## Thoughts

## References

### Terminal Commands
#### Removing Packages
```
powershell -c $(get-appxpackage micro*win*apprun*).packagefullname
```
```
powershell -c "get-appxpackage micro*win*apprun* | remove-appxpackage"
```
#### Collecting Traces
```
"C:\Program Files (x86)\Windows Kits\10\bin\10.0.22000.0\x64\TraceLog" -start WNSTrace -guid providers.guids -f WNSTrace.etl
```
```
"C:\Program Files (x86)\Windows Kits\10\bin\10.0.22000.0\x64\TraceLog" -stop WNSTrace
```

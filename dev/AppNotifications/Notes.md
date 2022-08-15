# One Pager
## Introduction
### Situation
### Complication
### Question
### Answer (claim)
## Reason - 1
### Evidence - 1
### Evidence - 2
### Evidence - 3
## Reason - 2
### Evidence - 1
### Evidence - 2
### Evidence - 3
## Reason - 3
### Evidence - 1
### Evidence - 2
### Evidence - 3

## Conclusion (reasononing)

# Notification Delivery Telemetry
A complete post and delivery loop telemetry by logging telemtry in LRP::OnRaw and in WAS:InvokeAll. This would By piping the correlation vector from the LongRunningProcess to the WIndowsAppSDK and 

* Telemetry is already being logged from the WindowsAppSDK APIs and through CoreOS for any App Notification posted.
*  Push Notifications aren't sent by the app but by an appserver, so there is no telemtry to be logged in this case.
* CoreOS already log telemetry for activated toasts all the way to WindowsAppSDK.
* CoreOS already log telemetry for received push notifications all the way up to the WindowsAppSDK (for packaged apps) or the LongRunningProcess (for unpackaged apps).
* For received push notifications, the correlation vector is pipped from the CoreOS into the WindowsAppSDK and the LongRunningProcess but not between the LongRunningProcess and the WindopwsAppSDK.

To complete the post and delivery telemetry loop for Push Notifications and App Notifications, we need to add telemetry logs up to the point where the notification is handled to the app once it has been received.

# LongRunningProcess Telemetry
# Thoughts

Improve Push telemetry 
* For Push foreground activations, log telemetry (including CV) at the point the app callback is called.  
* For Push Background activations, log telemetry (including CV) at the point were the app is launched.

Improve Toast Telemetry
* Add logging to AppNotificationManager::Activate.
AppNotificationManager::Activate seems to be last opportunity to log activation before either the app callback is called or the app is launched.

Add general telemetry to the LRP.
* j

## Add support for CV for foreground activstion

## Add support for CV for brackground activation

Change InvokeAll() API to accept an correlation vector.
* InvokeAll() is called from OnRaw... in the case of a packaged app but from ....::OnRaw in the case to an upackaged app. 
* Unpackaged

fdfskj;
## References
**Foreground Activation:**
* **Packaged Apps:** WAS::OnRaw... calls WAS::InvodeAll
* **Unpackaged Apps:** LRP::OnRaw... calls WAS::InvokeAll.
WAS::InvokeAll does not receive a correlationVector and thus cannot log it.

**Background Activation:**
* **Packaged Apps:** WNPCore::ActivateRawWorkItem.
* **Unpackaged Apps:** LRP::OnRaw calls Protocol Launch

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

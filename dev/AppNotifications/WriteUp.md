# Current
* **Note:** in all the table bellow, time information comes from various test runs and is only used to order the events. The event are ordered by time received, which do not necessarilly represent the call order. Most logging happens at scope exit, (usually when a function exits).
## Receiving Push Notification in the Foreground
### Unpackaged App
Event | Provider | Time
--- | --- | ---
CheckForNetMessageReceived | Wpnprv | 157.227430600
LogReceivedNFY | Wpnprv | 157.227467300
WnsPlatNotificationReceived | WnsCP | 157.229970500
WnsPlatNotificationPdcActivated | WnsCP | 157.229973200
WnsPlatNotificationDelivered | WnsCP | 157.276754000
NotificationReceived | WpnCore | 157.276773600
SendNetMsg | Wpnprv | 157.277694800
LogProcessedNFY | Wpnprv | 157.277766700
NotificationCallBack | WpncoreTelemetry | 157.403984300
PushNotificationDelivered | WpnCore | 157.404006100

### Packaged App
Event | Provider | Time
--- | --- | ---
CheckForNetMessageReceived | Wpnprv | 132.202804500
LogReceivedNFY | Wpnprv | 132.202861000
WnsPlatNotificationReceived | WnsCP | 132.207177100
WnsPlatNotificationPdcActivated | WnsCP | 132.207180300
WnsPlatNotificationDelivered | WnsCP | 132.255116300
NotificationReceived | WpnCore | 132.255136200
SendNetMsg | Wpnprv | 132.257037800
LogProcessedNFY | Wpnprv | 132.257064400
NotificationCallBack | WpncoreTelemetry | 132.394308200
PushNotificationDelivered | WpnCore | 132.394327800

## Receiving Push Notification in the Background
### Unpackaged App
Event | Provider | Time
--- | --- | ---
CheckForNetMessageReceived | Wpnprv | 90.175799100
LogReceivedNFY | Wpnprv | 90.175884700
WnsPlatNotificationReceived | WnsCP | 90.183019100
WnsPlatNotificationPdcActivated | WnsCP | 90.183024300
WnsPlatNotificationDelivered | WnsCP | 90.243906000
NotificationReceived | WpnCore | 90.243932700
SendNetMsg | Wpnprv | 90.245027100
LogProcessedNFY | Wpnprv | 90.245056900
NotificationCallBack | WpncoreTelemetry | 90.400729900
PushNotificationDelivered | WpnCore | 90.400757000

### Packaged App
Event | Provider | Time
--- | --- | ---
CheckForNetMessageReceived | Wpnprv | 89.744820000
LogReceivedNFY | Wpnprv | 89.744842400
WnsPlatNotificationReceived | WnsCP | 89.746812400
WnsPlatNotificationPdcActivated | WnsCP | 89.746813900
WnsPlatNotificationDelivered | WnsCP | 89.787161800
NotificationReceived | WpnCore | 89.787181700
SendNetMsg | Wpnprv | 89.788013200
LogProcessedNFY | Wpnprv | 89.788040700
NotificationCallBack | WpncoreTelemetry | 89.920292200
ActivateRawWorkItem | WpnCore | 89.920816900
PushNotificationDelivered | WpnCore | 89.920836200

# What's Missing
Except for the case of receiving a background Notification in the background by an Unpackaged app, all other scenarios are missing some steps in the logging process.

When receiving a Push Notification in the forground, the notification is routed directly to the WIndowsAppSDK (for a packaged app) or through the LRP then the WindowsAppSDK (for an upackaged app).
In both cases, the notification is routed through a function named *OnRawNotificationReceived*.
This function exists in both the LRP and the WindowsAppSDK.
From there it goes to *InvokeAll* in the WiondowsAppSDK.
Which one is called depends on whether the app is destined to a packaged app or an unpackaged app.
In both cases, *OnRawNotificationReceived* get the CorrelationVector but *InvokeAll* does not.
Adding a correlation Vector to *InvokeAll* is easy, though it required modifying the public definition of the function used by the LRP only.

# Proposed
## Receiving Push Notification in the Foreground
### Unpackaged App
Event | Provider | Time
--- | --- | ---
CheckForNetMessageReceived | Wpnprv | 157.227430600
LogReceivedNFY | Wpnprv | 157.227467300
WnsPlatNotificationReceived | WnsCP | 157.229970500
WnsPlatNotificationPdcActivated | WnsCP | 157.229973200
WnsPlatNotificationDelivered | WnsCP | 157.276754000
NotificationReceived | WpnCore | 157.276773600
SendNetMsg | Wpnprv | 157.277694800
LogProcessedNFY | Wpnprv | 157.277766700
**InvokeAll** | **PushNotificationTelemetry** | **157.403734700**
**OnRawNotificationReceived** | **PushNotificationLongRunningTaskTelemetry** | **157.403776100**
NotificationCallBack | WpncoreTelemetry | 157.403984300
PushNotificationDelivered | WpnCore | 157.404006100

### Packaged App
Event | Provider | Time
--- | --- | ---
CheckForNetMessageReceived | Wpnprv | 132.202804500
LogReceivedNFY | Wpnprv | 132.202861000
WnsPlatNotificationReceived | WnsCP | 132.207177100
WnsPlatNotificationPdcActivated | WnsCP | 132.207180300
WnsPlatNotificationDelivered | WnsCP | 132.255116300
NotificationReceived | WpnCore | 132.255136200
SendNetMsg | Wpnprv | 132.257037800
LogProcessedNFY | Wpnprv | 132.257064400
**InvokeAll** | **PushNotificationTelemetry** | **132.394107400**
**OnRawNotificationReceived** | **PushNotificationTelemetry** | **132.394111800**
NotificationCallBack | WpncoreTelemetry | 132.394308200
PushNotificationDelivered | WpnCore | 132.394327800

## Receiving Push Notification in the Background
### Unpackaged App
The only change required when receiving Push Notifications in the background for an upackaged app is adding telemetry to the LongRunningProcess at the point it pass controll to the app.

Event | Provider | Time
--- | --- | ---
CheckForNetMessageReceived | Wpnprv | 90.175799100
LogReceivedNFY | Wpnprv | 90.175884700
WnsPlatNotificationReceived | WnsCP | 90.183019100
WnsPlatNotificationPdcActivated | WnsCP | 90.183024300
WnsPlatNotificationDelivered | WnsCP | 90.243906000
NotificationReceived | WpnCore | 90.243932700
SendNetMsg | Wpnprv | 90.245027100
LogProcessedNFY | Wpnprv | 90.245056900
**OnRawNotificationReceived** | **PushNotificationLongRunningTaskTelemetry** | **90.400255200**
NotificationCallBack | WpncoreTelemetry | 90.400729900
PushNotificationDelivered | WpnCore | 90.400757000

### Packaged App
There are no changes required when receiving Push Notifications in the background for a packaged app as it is delivered directly to the app by WNPCore.
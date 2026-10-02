# Generate PushNotifications overrides for use at build time

Param(
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string]$Path
)

function Convert-Guid
{
    Param([string]$uuid)

    $fields = $uuid -Split '-', 5
    $field0 = $fields[0]
    $field1 = $fields[1]
    $field2 = $fields[2]
    $field3 = $fields[3]
    $b0 = $field3.SubString(0, 2)
    $b1 = $field3.SubString(2, 2)
    $field4 = $fields[4]
    $b2 = $field4.SubString(0, 2)
    $b3 = $field4.SubString(2, 2)
    $b4 = $field4.SubString(4, 2)
    $b5 = $field4.SubString(6, 2)
    $b6 = $field4.SubString(8, 2)
    $b7 = $field4.SubString(10, 2)
    $guid = "0x$field0, 0x$field1, 0x$field2, { 0x$b0, 0x$b1, 0x$b2, 0x$b3, 0x$b4, 0x$b5, 0x$b6, 0x$b7 }"
    return $guid
}

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

if (-not(Test-Path -Path $Path -PathType Container))
{
    Write-Host "Creating $Path..."
    $override = New-Item -Path $Path -ItemType Directory -Force
}
else
{
    Write-Output "$Path exists"
}

# Generate the json file
$content_json=@"
{
	"LIBID": "CE96C745-3017-460E-895B-4FD98E1194F2",
	"ComServer": {
		"CLSID": {
			"UUID": "E739C755-0D09-48DF-A468-A5DF0B5422DC"
		}
	},
	"ComInterfaces": {
		"LRP": {
			"CLSID": {
				"UUID": "60FC21B2-B396-4D49-94F0-7555869FB93C"
			}
		},
		"ForegroundSink": {
			"CLSID": {
				"UUID": "25604D55-9B17-426F-9D67-2B11B3A65598"
			}
		},
            "ForegroundSink2": {
			"CLSID": {
				"UUID": "559B4205-F810-4947-B02B-3EA9A311C6AD"
			}
		}
	}
}
"@

$file_json = Join-Path $Path 'PushNotifications-Override.json'
Write-Output "Writing $file_json..."
"$content_json" | Out-File $file_json -Encoding utf8

# Generate the Push Notifications header file
$content_h=@"
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

#ifndef _WSTRINGIZE
#define _WSTRINGIZEXX(x) L ## #x
#define _WSTRINGIZEX(x) _WSTRINGIZEXX(x)
#define _WSTRINGIZE(x) _WSTRINGIZEX({ ## x ## })
#endif

#ifdef PUSHNOTIFICATIONS_LIBID_UUID
#undef PUSHNOTIFICATIONS_LIBID_UUID
#define PUSHNOTIFICATIONS_LIBID_UUID             CE96C745-3017-460E-895B-4FD98E1194F2
#endif

#ifdef PUSHNOTIFICATIONS_IMPL_CLSID_UUID
#undef PUSHNOTIFICATIONS_IMPL_CLSID_UUID
#define PUSHNOTIFICATIONS_IMPL_CLSID_UUID        E739C755-0D09-48DF-A468-A5DF0B5422DC
#endif

#ifdef PUSHNOTIFICATIONS_IMPL_CLSID_STRING
#undef PUSHNOTIFICATIONS_IMPL_CLSID_STRING
#define PUSHNOTIFICATIONS_IMPL_CLSID_STRING      _STRINGIZE(PUSHNOTIFICATIONS_IMPL_CLSID_UUID)
#endif

#ifdef PUSHNOTIFICATIONS_IMPL_CLSID_WSTRING
#undef PUSHNOTIFICATIONS_IMPL_CLSID_WSTRING
#define PUSHNOTIFICATIONS_IMPL_CLSID_WSTRING   _WSTRINGIZE(PUSHNOTIFICATIONS_IMPL_CLSID_UUID)
#endif

#ifdef PUSHNOTIFICATIONS_LRP_CLSID_UUID
#undef PUSHNOTIFICATIONS_LRP_CLSID_UUID
#define PUSHNOTIFICATIONS_LRP_CLSID_UUID        60FC21B2-B396-4D49-94F0-7555869FB93C
#endif

#ifdef PUSHNOTIFICATIONS_LRP_CLSID_STRING
#undef PUSHNOTIFICATIONS_LRP_CLSID_STRING
#define PUSHNOTIFICATIONS_LRP_CLSID_STRING      _STRINGIZE(PUSHNOTIFICATIONS_LRP_CLSID_UUID)
#endif

#ifdef PUSHNOTIFICATIONS_LRP_CLSID_WSTRING
#undef PUSHNOTIFICATIONS_LRP_CLSID_WSTRING
#define PUSHNOTIFICATIONS_LRP_CLSID_WSTRING   _WSTRINGIZE(PUSHNOTIFICATIONS_LRP_CLSID_UUID)
#endif

#ifdef PUSHNOTIFICATIONS_FOREGROUNDSINK_CLSID_UUID
#undef PUSHNOTIFICATIONS_FOREGROUNDSINK_CLSID_UUID
#define PUSHNOTIFICATIONS_FOREGROUNDSINK_CLSID_UUID        25604D55-9B17-426F-9D67-2B11B3A65598
#endif

#ifdef PUSHNOTIFICATIONS_FOREGROUNDSINK2_CLSID_UUID
#undef PUSHNOTIFICATIONS_FOREGROUNDSINK2_CLSID_UUID
#define PUSHNOTIFICATIONS_FOREGROUNDSINK2_CLSID_UUID        559B4205-F810-4947-B02B-3EA9A311C6AD
#endif
"@
$file_h = Join-Path $Path 'PushNotifications-Override.h'
Write-Output "Writing $file_h..."
"$content_h" | Out-File $file_h -Encoding utf8

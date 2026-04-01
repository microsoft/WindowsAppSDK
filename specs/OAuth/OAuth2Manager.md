OAuth2Manager API
===

This is the spec for proposal: [Issue #441](https://github.com/microsoft/WindowsAppSDK/issues/441)

This spec details the API of a new `OAuth2Manager` in WinAppSDK,
enabling desktop applications such as WinUI3 to seamlessly perform OAuth functionality across diverse Windows platforms. 
OAuth2Manager API intentionally does not provide API for the implicit request & resource owner password credential because of the security concerns that follow it. It is recommended to use the 
authorization code grant type using Proof Key for Code Exchange (PKCE).



# Background

The current OS 
[WebAuthenticationBroker](https://docs.microsoft.com/uwp/api/windows.security.authentication.web.webauthenticationbroker),
primarily designed for UWP applications,
presents several challenges when used in desktop environments. 
Key issues include the dependency on `ApplicationView`, 
which are not compatible with desktop app frameworks.
As a result, developers are forced to resort to workarounds involving interop interfaces and 
additional code to implement OAuth 2.0 functionality into their WinUI 3 desktop applications.

In response to this feedback, this `OAuth2Manager` API for WinAppSDK aims to provide 
a streamlined solution that meets the expectations of our developer community. 
The goal is to offer seamless OAuth 2.0 capabilities with full feature parity across all Windows platforms supported by WinAppSDK. 
This new API eliminates the need for cumbersome workarounds and 
simplifies the process of incorporating OAuth 2.0 functionality into desktop applications.


This new WinAppSDK version of the `OAuth2Manager` is different than the existing public
[WebAuthenticationBroker](https://learn.microsoft.com/en-us/uwp/api/windows.security.authentication.web.webauthenticationbroker?view=winrt-22621) 
API. We've opted to follow OAuth best practices more closely - e.g. using user's default browser. The best practices for the API are taken from the
IETF(Internet Engineering Task Force) OAuth 2.0 Authorization Framework [RFC 6749](https://tools.ietf.org/html/rfc6749), 
Proof Key for Code Exchange (PKCE) [RFC 7636](https://tools.ietf.org/html/rfc7636),
and OAuth 2.0 for Native Apps [RFC 8252](https://tools.ietf.org/html/rfc8252).



# Conceptual pages

 ## Perform OAuth 2.0 (c++)

 Performing an Authorization Code Request (grant type/'response_type' = "code")

 ```c++
 // Get the WindowId for the application window
Microsoft::UI::WindowId parentWindowId = this->AppWindow().Id();

AuthRequestParams authRequestParams = AuthRequestParams::CreateForAuthorizationCodeRequest(L"my_client_id",
    Uri(L"my-app:/oauth-callback/"));
authRequestParams.Scope(L"user:email user:birthday");

AuthRequestResult authRequestResult = co_await OAuth2Manager::RequestAuthWithParamsAsync(parentWindowId, 
    Uri(L"https://my.server.com/oauth/authorize"), authRequestParams);
if (AuthResponse authResponse = authRequestResult.Response())
{
    //To obtain the authorization code
    //authResponse.Code();

    //To obtain the access token
    DoTokenExchange(authResponse);
}
else
{
    AuthFailure authFailure = authRequestResult.Failure();
    NotifyFailure(authFailure.Error(), authFailure.ErrorDescription());
}
```

Exchanging an Authorization Code for an Access Token (grant type/'response_type' = "code")

```c++

AuthResponse authResponse = authRequestResult.Response();
TokenRequestParams tokenRequestParams = TokenRequestParams::CreateForAuthorizationCodeRequest(authResponse);
ClientAuthentication clientAuth = ClientAuthentication::CreateForBasicAuthorization(L"my_client_id",
    L"my_client_secret");

TokenRequestResult tokenRequestResult = co_await OAuth2Manager::RequestTokenAsync(
    Uri(L"https://my.server.com/oauth/token"), tokenRequestParams, clientAuth);
if (TokenResponse tokenResponse = tokenRequestResult.Response())
{
    String accessToken = tokenResponse.AccessToken();
    String tokenType = tokenResponse.TokenType();

    // RefreshToken string null/empty when not present
    if (String refreshToken = tokenResponse.RefreshToken(); !refreshToken.empty())
    {
        // ExpiresIn is zero when not present
        DateTime expires = winrt::clock::now();
        if (String expiresIn = tokenResponse.ExpiresIn(); expiresIn != 0)
        {
            expires += std::chrono::seconds(static_cast<int64_t>(expiresIn));
        }
        else
        {
            // Assume a duration of one hour
            expires += std::chrono::hours(1);
        }

        //Schedule a refresh of the access token
        myAppState.ScheduleRefreshAt(expires, refreshToken);
    }

    // Use the access token for resources
    DoRequestWithToken(accessToken, tokenType);
}
else
{
    TokenFailure tokenFailure = tokenRequestResult.Failure();
    NotifyFailure(tokenFailure.Error(), tokenFailure.ErrorDescription());
}
```

Refreshing an Access Token (grant type/'response_type' = "code")

```c++
TokenRequestParams tokenRequestParams = TokenRequestParams::CreateForRefreshToken(refreshToken);
ClientAuthentication clientAuth = ClientAuthentication::CreateForBasicAuthorization(L"my_client_id",
    L"my_client_secret");
TokenRequestResult tokenRequestResult = co_await OAuth2Manager::RequestTokenAsync(
    Uri(L"https://my.server.com/oauth/token"), tokenRequestParams, clientAuth));
if (TokenResponse tokenResponse = tokenRequestResult.Response())
{
    UpdateToken(tokenResponse.AccessToken(), tokenResponse.TokenType(), tokenResponse.ExpiresIn());

    //Store new refresh token if present
    if (String refreshToken = tokenResponse.RefreshToken(); !refreshToken.empty())
    {
        // ExpiresIn is zero when not present
        DateTime expires = winrt::clock::now();
        if (String expiresIn = tokenResponse.ExpiresIn(); expiresIn != 0)
        {
            expires += std::chrono::seconds(static_cast<int64_t>(expiresIn));
        }
        else
        {
            // Assume a duration of one hour
            expires += std::chrono::hours(1);
        }

        //Schedule a refresh of the access token
        myAppState.ScheduleRefreshAt(expires, refreshToken);
    }
}
else
{
    TokenFailure tokenFailure = tokenRequestResult.Failure();
    NotifyFailure(tokenFailure.Error(), tokenFailure.ErrorDescription());
}
```

Completing an Authorization Request from a Protocol Activation

```c++
void App::OnActivated(const IActivatedEventArgs& args)
{
    if (args.Kind() == ActivationKind::Protocol)
    {
        auto protocolArgs = args.as<ProtocolActivatedEventArgs>();
        if (OAuth2Manager::CompleteAuthRequest(protocolArgs.Uri()))
        {
            TerminateCurrentProcess();
        }

        DisplayUnhandledMessageToUser();
    }
}
```

# API Pages


## OAuth2Manager class

It's a static class that provides methods to initiate an authorization request,
complete an authorization request, and request an access token for a user through a client.

> Note: Client refers to the OAuth 2.0 registered application.
  User refers to the end-user who is the resource owner and is authorizing the client application to access their resources.


## OAuth2Manager Methods

| Name | Description | Parameters | Returns |
|-|-|-|-| 
| RequestAuthWithParamsAsync(Microsoft.UI.WindowId, Windows.Foundation.Uri, AuthRequestParams) | Intiates auth request for a user in the user's default browser through a client.| Microsoft.UI.WindowId `parentWindowId`, Windows.Foundation.Uri `authEndPoint`  , AuthRequestParams `params` | Windows.Foundation.IAsyncOperation< AuthRequestResult > |
| CompleteAuthRequest(Windows.Foundation.Uri) | Completes an auth request through a redirect URI. | Windows.Foundation.Uri `responseUri` | Boolean |
| RequestTokenAsync(Windows.Foundation.Uri, TokenRequestParams) | Initiates an access token request. | Windows.Foundation.Uri `tokenEndPoint` , TokenRequestParams `params` | Windows.Foundation.IAsyncOperation< TokenRequestResult > |
| RequestTokenAsync(Windows.Foundation.Uri, TokenRequestParams, ClientAuthentication) | Initiates an access token request with client authentication. | Windows.Foundation.Uri `tokenEndPoint` , TokenRequestParams `params` , ClientAuthentication `clientAuth` | Windows.Foundation.IAsyncOperation< TokenRequestResult > |


## ClientAuthentication class

It's a class that provides methods to create a client authentication object for basic authorization of the client to the authorization server. 

> Note: This is used to authenticate the client application to the authorization server. 
  It is not used to authenticate the user to the client application. 
  User authentication is handled by the RequestAuthWithParamsAsync method of OAuth2Manager class.

## ClientAuthentication constructor

| Name | Description |
|-|-|
| ClientAuthentication() | Create a new ClientAuthentication object.|
| ClientAuthentication(Windows.Web.Http.Headers.HttpCredentialsHeaderValue) | Create a new ClientAuthentication object with the specified `authorization` header as parameter.|

## ClientAuthentication Methods

| Name | Description | Parameters | Returns |
|-|-|-|-|
| CreateForBasicAuthorization(String, String) | A static method to return a new ClientAuthentication object with basic authorization. | String `clientId` , String `clientSecret` | ClientAuthentication |

## ClientAuthentication Properties
| Name | Description | Type |
|-|-|-|
| Authorization | Specifies the 'Authorization' header of the HTTP POST request when requesting a token. | Windows.Web.Http.Headers.HttpCredentialsHeaderValue |
| ProxyAuthorization | Specifies the 'Proxy-Authorization' header of the HTTP POST request when requesting a token. | Windows.Web.Http.Headers.HttpCredentialsHeaderValue |
| AdditionalHeaders | Specifies additional header values of the HTTP POST request when requesting a token. | Windows.Foundation.Collections.IMap<String, String> |

## CodeChallengeMethodKind enum

It's an enum that specifies the 'code_challenge_method' as described by section 4.3 of [RFC 7636](https://datatracker.ietf.org/doc/html/rfc7636#section-4.3) : Proof Key for Code Exchange by OAuth Public Clients.

| Name | Description |
|-|-|
| None | Suppresses the use of a code verifier. An error will be thrown if a code challenge string is set when this option is used. |
| S256 | Challenge method of "S256" (i.e. SHA256). This is the default unless explicitly set. |
| Plain | Challenge method of "plain" (i.e. send as plain text). |

## AuthRequestParams class

It's a class that provides methods to create an authorization request parameter object.

> Note: This object is used to request authorization 'code' from the server when response_type is 'code' and 'access_token' when response_type is 'token'.
response_type is described in section 3.1.1 of [RFC 6749](https://www.rfc-editor.org/rfc/rfc6749#section-3.1.1).

## AuthRequestParams constructor

| Name | Description |
|-|-|
| AuthRequestParams(String, String) | Construct AuthRequestParams object with `responseType` and `clientId` parameters passed in the order mentioned. |
| AuthRequestParams(String, String, Windows.Foundation.Uri) | Construct AuthRequestParams object with `responseType`, `clientId` and a `redirectUri` passed in the order mentioned. |


## AuthRequestParams Methods

| Name | Description | Parameters | Returns |
|-|-|-|-|
| CreateForAuthorizationCodeRequest(String) | Helper method to create for an authorization code grant request ("code" response type) with required parameters. | String `clientId` | AuthRequestParams |
| CreateForAuthorizationCodeRequest(String, Windows.Foundation.Uri) | Helper method to create for an authorization code grant request ("code" response type) with required parameters. | String `clientId` , Windows.Foundation.Uri `redirectUri` | AuthRequestParams |

## AuthRequestParams Properties

| Name | Description | Type |
|-|-|-|
| ResponseType | Specifies the required "response_type" parameter of the authorization request described by the section 3.1.1 of [RFC 6749](https://www.rfc-editor.org/rfc/rfc6749.html#section-3.1.1). | String |
| ClientId | Specifies the required "client_id" parameter of the authorization request described by the section 2.2 of [RFC 6749](https://www.rfc-editor.org/rfc/rfc6749.html#section-2.2). | String |
| RedirectUri | Specifies the optional "redirect_uri" parameter of the authorization request described by the section 3.1.2 of [RFC 6749](https://www.rfc-editor.org/rfc/rfc6749.html#section-3.1.2). | Windows.Foundation.Uri |
| State | Specifies the recommended "state" parameter of the authorization request described in section 4.1.1 of [RFC 6749] (https://www.rfc-editor.org/rfc/rfc6749#section-4.1.1) | String |
| Scope | Specifies the optional "scope" parameter of the authorization request described by the section 3.3 of [RFC 6749](https://www.rfc-editor.org/rfc/rfc6749#section-3.3). | String |
| CodeChallenge | Used as the PKCE code_challenge described by the section 4.2 of [RFC 7636](https://www.rfc-editor.org/rfc/rfc7636#section-4.2). | String |
| CodeChallengeMethod | Specifies the optional "code_challenge_method" parameter of the authorization request described by the section 4.3 of [RFC 7636](https://www.rfc-editor.org/rfc/rfc7636#section-4.3). | CodeChallengeMethodKind |
| AdditionalParams | Additional parameters passed along in the query string of the request URL. | Windows.Foundation.Collections.IMap<String, String> |

## AuthRequestResult class

It's a class that provides the result of an authorization request.

## AuthRequestResult Properties

| Name | Description | Type |
|-|-|-|
| ResponseUri | The raw URI that was used to complete the request. | Windows.Foundation.Uri |
| Response | Non-null if the server's response indicates success, otherwise null. | AuthResponse |
| Failure | Non-null if the server's response indicates failure, otherwise null. | AuthFailure |

## AuthResponse class

It's a class that provides the response of an authorization request described by the section section 4.1.2 and 4.2.2 of [RFC 6749](https://www.rfc-editor.org/rfc/rfc6749.html#section-4.1.2).

## AuthResponse Properties

| Name | Description | Type |
|-|-|-|
| State | Derived from the "state" parameter of the authorization response. | String |
| Code | Derived from the "code" parameter of the authorization response. | String |
| AccessToken | Derived from the "access_token" parameter of the authorization response. This is available when ResponseType in AuthRequestParams is set as 'token'. | String |
| TokenType | Derived from the "token_type" parameter of the authorization response. This is available when ResponseType in AuthRequestParams is set as 'token'. | String |
| ExpiresIn | Derived from the "expires_in" parameter of the authorization response. It's the lieftime of access token in seconds. This is available when ResponseType in AuthRequestParams is set as 'token'. | String |
| Scope | Derived from the "scope" parameter of the authorization response. This is available when ResponseType in AuthRequestParams is set as 'token'. | String |
| AdditionalParams | Additional parameters set by the authorization server in the response URI. | Windows.Foundation.Collections.IMapView<String, String> |

## AuthFailure class

It's a class that provides the failure object of an authorization request.

> Note: It's null in case of a valid AuthResponse, and available in case of a failure.

## AuthFailure Properties

| Name | Description | Type |
|-|-|-|
| Error | Derived from the "error" parameter of the error response. | String |
| ErrorDescription | Derived from the "error_description" parameter of the error response. | String |
| ErrorUri | Derived from the "error_uri" parameter of the error response. | Windows.Foundation.Uri |
| State | Derived from the "state" parameter of the error response. | String |
| AdditionalParams | Additional parameters set by the authorization server in the response URI. | Windows.Foundation.Collections.IMapView<String, String> |


## TokenRequestParams class

It's a class that provides methods to create a token request parameter object. This is described by the section 4.1.3 of [RFC 6749](https://www.rfc-editor.org/rfc/rfc6749.html#section-4.1.3).

> Note: This object is used to request access_token from the server.

## TokenRequestParams constructor

| Name | Description |
|-|-|
| TokenRequestParams(String) | Construct TokenRequestParams object with `grantType` parameter passed. |

## TokenRequestParams Methods

| Name | Description | Parameters | Returns |
|-|-|-|-|
| CreateForAuthorizationCodeRequest(AuthResponse) | Helper method to create for an authorization code grant request ("authorization_code" grant type) with required parameters extracted from the authorization response. | AuthResponse `authResponse` | TokenRequestParams |
| CreateForClientCredentials() | Helper method to create for a client credentials grant request ("client_credentials" grant type) with required parameters. | None | TokenRequestParams |
| CreateForExtension(Windows.Foundation.Uri) | Helper method to create for an extension grant request, using the provided URI for the grant type. | Windows.Foundation.Uri `extensionUri` | TokenRequestParams |
| CreateForRefreshToken(String) | Helper method to create for an access token refresh request ("refresh_token" grant type) with required parameters. | String `refreshToken` | TokenRequestParams |

## TokenRequestParams Properties

| Name | Description | Type |
|-|-|-|
| GrantType | Specifies the required "grant_type" parameter of the token request. | String |
| Code | Specifies the "code" parameter of the token request. | String |
| RedirectUri | Specifies the "redirect_uri" parameter of the token request. | Windows.Foundation.Uri |
| CodeVerifier | Specifies the "code_verifier" parameter of the token request. This property is required when the grant type is "authorization_code" and a code challenge was included in the authorization request. This is described by the section 4.1 of [RFC 7636](https://www.rfc-editor.org/rfc/rfc7636#section-4.1) | String |
| ClientId | Specifies the "client_id" parameter of the token request. | String |
| Username | Specifies the "username" parameter of the token request. | String |
| Password | Specifies the "password" parameter of the token request. | String |
| RefreshToken | Specifies the "refresh_token" parameter of the token request. | String |
| ExtensionUri | Specifies the "extension_uri" parameter of the token request. | Windows.Foundation.Uri |
| AdditionalParams | Additional parameters passed along in the query string of the request URL. | Windows.Foundation.Collections.IMap<String, String> |

## TokenRequestResult class

It's a class that provides the result of a token request.

## TokenRequestResult Properties

| Name | Description | Type |
|-|-|-|
| ResponseMessage | The raw HTTP response message that was used to complete the request. | Windows.Web.Http.HttpResponseMessage |
| Response | Non-null if the server's response indicates success, otherwise null. | TokenResponse |
| Failure | Non-null if the server's response indicates failure, otherwise null. | TokenFailure |

## TokenResponse class

It's a class that provides the response of a token request. This is described by the section 4.1.4 and 4.2.2 of [RFC 6749](https://www.rfc-editor.org/rfc/rfc6749.html#section-4.1.4).

## TokenResponse Properties

| Name | Description | Type |
|-|-|-|
| AccessToken | Derived from the "access_token" parameter of the token response. | String |
| TokenType | Derived from the "token_type" parameter of the token response. | String |
| ExpiresIn | Derived from the "expires_in" parameter of the token response.  It's the lieftime of access token in seconds. | String |
| RefreshToken | Derived from the "refresh_token" parameter of the token response. | String |
| Scope | Derived from the "scope" parameter of the token response. | String |
| AdditionalParams | Additional parameters set by the authorization server in the response URI. | Windows.Foundation.Collections.IMapView<String, String> |

## TokenFailureKind enum

It's an enum that specifies the kind of token failure.

| Name | Description |
|-|-|
| ErrorResponse | The server responded with an error response as described by RFC 6749 section 5.2. This means that the failure object has an 'Error' string and possibly other specified properties |
| HttpFailure | The HTTP POST request failed. See the 'ErrorCode' property for more details as to why. |
| InvalidResponse | The server responded, but its response was improperly formatted. This could be that the server did not send the response as JSON, the response JSON string was improperly formatted, or the response JSON contained unexpected object types (e.g. a number when a string is expected, etc.). |

## TokenFailure class

It's a class that provides the failure object of a token request.

## TokenFailure Properties

| Name | Description | Type |
|-|-|-|
| Kind | Specifies the kind of token failure. | TokenFailureKind |
| Error | Derived from the "error" parameter of the error response. | String |
| ErrorDescription | Derived from the "error_description" parameter of the error response. | String |
| ErrorUri | Derived from the "error_uri" parameter of the error response. | Windows.Foundation.Uri |
| ErrorCode | The HTTP error code that was returned. | Windows.Web.Http.HttpStatusCode |
| AdditionalParams | Additional parameters set by the authorization server in the response URI. | Windows.Foundation.Collections.IMapView<String, String> |


# API Details

> Note: all of this new WinAppSDK API is to support 
  OAuth 2.0 launch using browser launch.
 
```c++ (but really MIDL3)
namespace Microsoft.Security.Authentication.OAuth
{
    [contractversion(1)]
    apicontract OAuthContract {};

    [contract(OAuthContract, 1)]
    runtimeclass ClientAuthentication
    {
        ClientAuthentication();
        ClientAuthentication(Windows.Web.Http.Headers.HttpCredentialsHeaderValue authorization);

        static ClientAuthentication CreateForBasicAuthorization(String clientId, String clientSecret);

        // Specifies the 'Authorization' header of the HTTP POST request when requesting a token
        Windows.Web.Http.Headers.HttpCredentialsHeaderValue Authorization { get; set; };

        // Specifies the 'Proxy-Authorization' header of the HTTP POST request when requesting a token
        Windows.Web.Http.Headers.HttpCredentialsHeaderValue ProxyAuthorization { get; set; };

        // Specifies additional header values of the HTTP POST request when requesting a token
        Windows.Foundation.Collections.IMap<String, String> AdditionalHeaders { get; };
    }

    [contract(OAuthContract, 1)]
    static runtimeclass OAuth2Manager
    {

        // Initiates an authorization request in the user's default browser as described by RFC 6749 section 3.1. The
        // returned 'IAsyncOperation' will remain in the 'Started' state until it is either cancelled or completed by a
        // call to 'CompleteAuthRequest'.
        static Windows.Foundation.IAsyncOperation<AuthRequestResult> RequestAuthWithParamsAsync(Microsoft.UI.WindowId parentWindowId,
            Windows.Foundation.Uri authEndpoint,
            AuthRequestParams params);

        // Called by the application when the user agent completes an auth request via a redirect Uri. Return value is
        // true if an appropriate request could be found and completed. Otherwise returns false indicating that the
        // response went unhandled and the application may respond as appropriate.
        static Boolean CompleteAuthRequest(Windows.Foundation.Uri responseUri);

        // Initiates an access token request as described by RFC 6749 section 3.2.
        static Windows.Foundation.IAsyncOperation<TokenRequestResult> RequestTokenAsync(
            Windows.Foundation.Uri tokenEndpoint,
            TokenRequestParams params);

        // Initiates an access token request as described by RFC 6749 section 3.2.
        static Windows.Foundation.IAsyncOperation<TokenRequestResult> RequestTokenAsync(
            Windows.Foundation.Uri tokenEndpoint,
            TokenRequestParams params,
            ClientAuthentication clientAuth);
    }

    // Correlates to the 'code_challenge_method' as described by section 4.3 of RFC 7636: Proof Key for Code Exchange by
    // OAuth Public Clients (https://www.rfc-editor.org/rfc/rfc7636.html#section-4.3)
    [contract(OAuthContract, 1)]
    enum CodeChallengeMethodKind
    {
        // Suppresses the use of a code verifier. An error will be thrown if a code challenge string is set when this
        // option is used
        None = 0,
        // Challenge method of "S256" (i.e. SHA256). This is the default unless explicitly set
        S256 = 1,
        // Challenge method of "plain" (i.e. send as plain text)
        Plain = 2,
    };

    [contract(OAuthContract, 1)]
    runtimeclass AuthRequestParams
    {
        // Construct with required parameters
        AuthRequestParams(String responseType, String clientId);
        // Construct with required parameters as well as a redirect URI, which is frequently specified
        AuthRequestParams(String responseType, String clientId, Windows.Foundation.Uri redirectUri);

        // Helper method to create for an authorization code grant request ("code" response type) with required
        // parameters, per RFC 6749 section 4.1.1.
        static AuthRequestParams CreateForAuthorizationCodeRequest(String clientId);

        // Helper method to create for an authorization code grant request ("code" response type) with required
        // parameters as well as a redirect URI, which is frequently specified.
        static AuthRequestParams CreateForAuthorizationCodeRequest(String clientId, Windows.Foundation.Uri redirectUri);

        // Specifies the required "response_type" parameter of the authorization request. This property is initialized
        // by the creation function used ("code" for 'CreateForAuthorizationCodeRequest').
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.1.1 and 4.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.1
        String ResponseType { get; set; };

        // Specifies the required "client_id" parameter of the authorization request. This property is initialized by
        // the value provided in the creation function call.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.1.1 and 4.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.1
        String ClientId { get; set; };

        // Specifies the optional "redirect_uri" parameter of the authorization request.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.1.1 and 4.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.1
        Windows.Foundation.Uri RedirectUri { get; set; };

        // Specifies the recommended "state" parameter of the authorization request. Note that although this is not
        // required by the OAuth standard, a state value will always be set to correlate requests and responses. This
        // parameter can be manually specified, in which case it must be globally unique across the entire system,
        // otherwise an error will be thrown. It is therefore recommended to let the API select a value for you as it
        // will guarantee that a unique value will be used.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.1.1 and 4.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.1
        String State { get; set; };

        // Specifies the optional "scope" parameter of the authorization request.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.1.1 and 4.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.1
        String Scope { get; set; };

        // Used as the PKCE code verifier. Either this value or a hash of this value will be used to specify the
        // "code_challenge" parameter of the authorization request, depending on the value of 'CodeChallengeMethod'. If
        // this value is not specified and 'CodeChallengeMethod' is not 'None', a random value will be generated for
        // this property. The code verifier will persist all the way through to the token request.
        //
        // Defined by RFC 7636: Proof Key for Code Exchange by OAuth Public Clients, section 4.1
        //      https://www.rfc-editor.org/rfc/rfc7636#section-4.1
        String CodeChallenge { get; set; };

        // Specifies the optional "code_challenge_method" parameter of the authorization request. For authorization code
        // requests, this value defaults to 'S256'.
        // Defined by RFC 7636: Proof Key for Code Exchange by OAuth Public Clients, section 4.3
        //      https://www.rfc-editor.org/rfc/rfc7636#section-4.3
        CodeChallengeMethodKind CodeChallengeMethod { get; set; };

        // Additional parameters passed along in the query string of the request URL.
        Windows.Foundation.Collections.IMap<String, String> AdditionalParams { get; };
    }

    [contract(OAuthContract, 1)]
    runtimeclass AuthResponse
    {
        // From the "state" parameter of the authorization response. This property will always be set because a state
        // value is always sent with the request.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.1.2 and 4.2.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.2
        String State { get; };

        // From the "code" parameter of the authorization response. Set only if the request was an authorization code
        // request.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 4.1.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.2
        String Code { get; };

        // From the "access_token" parameter of the authorization response. 
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 4.2.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.2
        String AccessToken { get; };

        // From the "token_type" parameter of the authorization response.
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 4.2.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.2
        String TokenType { get; };

        // From the "expires_in" parameter of the authorization response.
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 4.2.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.2
        String ExpiresIn { get; }; // TODO: DateTime?

        // From the "scope" parameter of the authorization response.
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 4.2.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.2
        String Scope { get; };

        // Additional parameters set by the authorization server in the response URI.
        Windows.Foundation.Collections.IMapView<String, String> AdditionalParams { get; };
    }

    [contract(OAuthContract, 1)]
    runtimeclass AuthFailure
    {
        // From the "error" parameter of the error response. The value of this property will map to a well known string
        // specified in RFC 6749 sections 4.1.2.1 and 4.2.2.1, or approved extensions.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.1.2.1 and 4.2.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.2.1
        String Error { get; };

        // From the "error_description" parameter of the error response. An optional parameter that, when set, provides
        // additional human-readable information intended to assist the developer in understanding the error.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.1.2.1 and 4.2.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.2.1
        String ErrorDescription { get; };

        // From the "error_uri" parameter of the error response. An optional parameter that, when set, specifies a URI
        // identifying a human-readable webpage intended to assist the developer in understanding the error.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.1.2.1 and 4.2.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.2.1
        Windows.Foundation.Uri ErrorUri { get; };

        // From the "state" parameter of the error response. This property will always be set because a state value is
        // always sent with the request.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.1.2.1 and 4.2.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.2.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.2.2.1
        String State { get; };

        // Additional parameters set by the authorization server in the response URI.
        Windows.Foundation.Collections.IMapView<String, String> AdditionalParams { get; };
    }

    [contract(OAuthContract, 1)]
    runtimeclass AuthRequestResult
    {
        // The raw URI that was used to complete the request.
        Windows.Foundation.Uri ResponseUri { get; };

        // Non-null if the server's response indicates success, otherwise null
        AuthResponse Response { get; };

        // Non-null if the server's response indicates failure, otherwise null
        AuthFailure Failure { get; };
    }

    [contract(OAuthContract, 1)]
    runtimeclass TokenRequestParams
    {
        // Construct with required parameters
        TokenRequestParams(String grantType);

        // Helper method to create for an authorization code grant request ("authorization_code" grant type),
        // initialized with the required parameters extracted from the authorization response, per RFC 6749 section
        // 4.1.3.
        static TokenRequestParams CreateForAuthorizationCodeRequest(AuthResponse authResponse);

        // Helper method to create for a client credentials grant request ("client_credentials" grant type), initialized
        // with the required parameters, per RFC 6749 section 4.4.2.
        static TokenRequestParams CreateForClientCredentials();

        // Helper method to create for an extension grant request, using the provided URI for the grant type, per RFC
        // 6749 section 4.5.
        static TokenRequestParams CreateForExtension(Windows.Foundation.Uri extensionUri);

        // Helper method to create for an access token refresh request ("refresh_token" grant type), initialized with
        // the required parameters, per RFC 6749 section 6.
        static TokenRequestParams CreateForRefreshToken(String refreshToken);

        // Specifies the required "grant_type" parameter of the token request. This property is initialized by the
        // creation function used ("authorization_code" for 'CreateForAuthorizationCodeRequest', "password" for
        // 'CreateForResourceOwnerPasswordCredentials', "client_credentials" for 'CreateForClientCredentials',
        // "refresh_token" for 'CreateForRefreshToken', or the specified URI for 'CreateForExtension').
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.1.3, 4.3.2, 4.4.2, 4.5, and 6
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.3
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.3.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.4.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.5
        //      https://www.rfc-editor.org/rfc/rfc6749#section-6
        String GrantType { get; set; };

        // Specifies the "code" parameter of the token request. This property is required when the grant type is
        // "authorization_code" and is initialized by 'CreateForAuthorizationCodeRequest'.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 4.1.3
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.3
        String Code { get; set; };

        // Specifies the "redirect_uri" parameter of the token request. This property is required when the grant type is
        // "authorization_code" and a redirect URI was included in the authorization request. This property is
        // initialized by 'CreateForAuthorizationCodeRequest'.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 4.1.3
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.3
        Windows.Foundation.Uri RedirectUri { get; set; };

        // Specifies the "code_verifier" parameter of the token request. This property is required when the grant type
        // is "authorization_code" and a code challenge was included in the authorization request. This property is
        // initialized by 'CreateForAuthorizationCodeRequest'.
        //
        // Defined by RFC 7636: Proof Key for Code Exchange by OAuth Public Clients, section 4.5
        //      https://www.rfc-editor.org/rfc/rfc7636#section-4.5
        String CodeVerifier { get; set; };

        // Specifies the "client_id" parameter of the token request. This property is required when the grant type is
        // "authorization_code" and no alternative client authentication is specified. This property is initiated by
        // 'CreateForAuthorizationCodeRequest'.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 4.1.3
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.1.3
        String ClientId { get; set; };

        // Specifies the "username" parameter of the token request. This property is required when the grant type is
        // "password" and is initialized by 'CreateForResourceOwnerPasswordCredentials'.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 4.3.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.3.2
        String Username { get; set; };

        // Specifies the "password" parameter of the token request. This property is required when the grant type is
        // "password" and is initialized by 'CreateForResourceOwnerPasswordCredentials'.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 4.3.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.3.2
        String Password { get; set; };

        // Specifies the "scope" parameter of the token request. This property is valid only when the grant type is
        // "password", "client_credentials", or "refresh_token".
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, sections 4.3.2, 4.4.2, and 6
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.3.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-4.4.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-6
        String Scope { get; set; };

        // Specifies the "refresh_token" parameter of the token request. This property is required when the grant type
        // is "refresh_token" and is initialized by 'CreateForRefreshToken'.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 6
        //      https://www.rfc-editor.org/rfc/rfc6749#section-6
        String RefreshToken { get; set; };

        // Additional parameters passed along in the HTTP request entity-body.
        Windows.Foundation.Collections.IMap<String, String> AdditionalParams { get; };
    }

    [contract(OAuthContract, 1)]
    runtimeclass TokenResponse
    {
        // From the "access_token" parameter of the token response. A required property that should always be set.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 5.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-5.1
        String AccessToken { get; };

        // From the "token_type" parameter of the token response. A required property that should always be set.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 5.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-5.1
        String TokenType { get; };

        // From the "expires_in" parameter of the token response. An optional property that, when set, specifies the
        // lifetime of the access token in seconds.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 5.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-5.1
        Double ExpiresIn { get; }; // TODO: DateTime?

        // From the "refresh_token" parameter of the token response. An optional property that, when set, can be used to
        // obtain new access tokens using the same authorization grant provided during the request.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 5.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-5.1
        String RefreshToken { get; };

        // From the "scope" parameter of the token response. An optional property that, when set, describes the scope of
        // the access token issued by the authorization server.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 5.1
        //      https://www.rfc-editor.org/rfc/rfc6749#section-5.1
        String Scope { get; };

        // Additional parameters set by the authorization server in the token response.
        Windows.Foundation.Collections.IMapView<String, Windows.Data.Json.IJsonValue> AdditionalParams { get; };
    }

    [contract(OAuthContract, 1)]
    enum TokenFailureKind
    {
        // The server responded with an error response as described by RFC 6749 section 5.2. This means that the failure
        // object has an 'Error' string and possibly other specified properties.
        ErrorResponse = 0,

        // The HTTP POST request failed. See the 'ErrorCode' property for more details as to why.
        HttpFailure = 1,

        // The server responded, but its response was improperly formatted. This could be that the server did not send
        // the response as JSON, the response JSON string was improperly formatted, or the response JSON contained
        // unexpected object types (e.g. a number when a string is expected, etc.).
        InvalidResponse = 2,
    };

    [contract(OAuthContract, 1)]
    runtimeclass TokenFailure
    {
        // Indicates the type of failure that this object describes, which will indicate which properties might be set.
        TokenFailureKind Kind { get; };

        // If 'Kind' was anything other than 'ErrorResponse',
        HRESULT ErrorCode { get; };

        // From the "error" parameter of the error response. The value of this property will map to a well known string
        // specified in RFC 6749 section 5.2, or approved extensions.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 5.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-5.2
        String Error { get; };

        // From the "error_description" parameter of the error response. An optional parameter that, when set, provides
        // additional human-readable information intended to assist the developer in understanding the error.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 5.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-5.2
        String ErrorDescription { get; };

        // From the "error_uri" parameter of the error response. An optional parameter that, when set, specifies a URI
        // identifying a human-readable webpage intended to assist the developer in understanding the error.
        //
        // Defined by RFC 6749: The OAuth 2.0 Authorization Framework, section 5.2
        //      https://www.rfc-editor.org/rfc/rfc6749#section-5.2
        Windows.Foundation.Uri ErrorUri { get; };

        // Additional parameters set by the authorization server in the token response.
        Windows.Foundation.Collections.IMapView<String, Windows.Data.Json.IJsonValue> AdditionalParams { get; };
    }

    [contract(OAuthContract, 1)]
    runtimeclass TokenRequestResult
    {
        // The raw HTTP response that was used to complete the request
        Windows.Web.Http.HttpResponseMessage ResponseMessage { get; };

        // Non-null if the server's response indicates success, otherwise null
        TokenResponse Response { get; };

        // Non-null if the server's response indicates failure, otherwise null
        TokenFailure Failure { get; };
    }
}
```

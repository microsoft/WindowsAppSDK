# Error Handling and Logging

# Error Handling

<span style="color:green">**DO**</span> Throw exceptions to report exceptional failures.

<span style="color:green">**DO**</span> Use [WIL error handling helpers](https://github.com/Microsoft/wil/wiki/Error-handling-helpers) when handling error code failures (`THROW_*()`, `RETURN_*()`, `FAIL_FAST_*()`, `LOG_*()`).

# Logging

<span style="color:green">**DO**</span> Rely on [WIL error handling helpers](https://github.com/Microsoft/wil/wiki/Error-handling-helpers) to log failures.

 <span style="color:green">**DO**</span> Use `TraceLoggingWrite()` to log non-failure information.

 <span style="color:red">**DON'T**</span> Use WIL's `LOG_HR()` to report non-failure information. `LOG_HR()` will FAIL_FAST if handled a `SUCCEEDED(hr)`.

 <span style="color:red">**DON'T**</span> Define error `HRESULTS` to pass to `LOG_HR()` to report non-failure information. Non-error information should be reported via `TraceLoggingWrite()`.
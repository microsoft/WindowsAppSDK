class TestFunctions
{
public:
    static void VerifyRegisterAndUnregister();
    static void ChannelRequestUsingNullRemoteId();
    static void ChannelRequestUsingRemoteId();
    static void MultipleChannelClose();
    static void VerifyRegisterAndUnregisterAll();
    static void MultipleRegister();
    static void VerifyMultipleRegisterAndUnregister();
    static void VerifyMultipleRegisterAndUnregisterAll();
    static void VerifyUnregisterTwice();
    static void VerifyUnregisterAll();
    static void VerifyUnregisterAllTwice();
    static void VerifyUnregisterAndUnregisterAll();
    static void VerifyForegroundHandlerSucceeds();
    static void VerifyForegroundHandlerFails();
};

namespace AppAttachMessenger.Enums
{
    /// <summary>
    /// Represents the notification category for messages.
    /// </summary>
    public enum NotificationCategory
    {
        // Category for general log messages
        ProcessFlow,

        // Category for messages related to the status of a specific stage or step
        CurrentStageInfo,

        // Category for messages related to the overall status of process flow
        OverallProcessResult
    }
}

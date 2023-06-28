// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachMessenger.Enums;

namespace AppAttachMessenger
{
    /// <summary>
    /// Represents a message with associated information.
    /// </summary>
    public class Message
    {
        /// <summary>
        /// Parameterized constructor
        /// </summary>
        /// <param name="content"></param>
        /// <param name="category"></param>
        public Message(string content, NotificationCategory category)
        {
            this.Content = content;
            this.Category = category;
        }

        /// <summary>
        /// The content of the message.
        /// </summary>
        public string Content { get; }

        /// <summary>
        /// The category for the message.
        /// </summary>
        public NotificationCategory Category { get; }

    }
}

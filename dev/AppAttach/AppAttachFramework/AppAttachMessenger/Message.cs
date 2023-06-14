using AppAttachMessenger.Enums;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
        /// <param name="message"></param>
        /// <param name="category"></param>
        public Message(string message, NotificationCategory category)
        {
            this.message = message;
            this.category = category;
        }

        /// <summary>
        /// The content of the message.
        /// </summary>
        public string message { get; }

        /// <summary>
        /// The category for the message.
        /// </summary>
        public NotificationCategory category { get; }

    }
}

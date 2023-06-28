// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachMessenger.Enums;
using AppAttachMessenger.Interface;
using System;
using System.Collections.Concurrent;
using System.Threading.Tasks;

namespace AppAttachMessenger
{
    /// <summary>
    /// Singleton class that provides functionality for sending and processing messages asynchronously.
    /// </summary>
    public class Messenger
    {
        /// <summary>
        /// The singleton instance.
        /// </summary>
        private static Messenger instance = new Messenger();

        /// <summary>
        /// The blocking collection used to store incoming messages.
        /// </summary>
        private BlockingCollection<Message> messageQueue;

        /// <summary>
        /// The delegate function used to handle incoming messages.
        /// </summary>
        private Func<Message, string> handleMessage;

        /// <summary>
        /// Private constructor to prevent instantiation.
        /// </summary>
        private Messenger()
        {
            messageQueue = new BlockingCollection<Message>();
        }

        /// <summary>
        /// Public static method to access the singleton instance.
        /// </summary>
        public readonly static Messenger Instance = instance;

        /// <summary>
        /// Getter for Handle Message.
        /// </summary>
        /// <returns></returns>
        public Func<Message, string> getHandleMessage()
        {
            return handleMessage;
        }

        /// <summary>
        /// Initializes the Messenger with a message handler to process incoming messages.
        /// </summary>
        /// <param name="messageHandler"></param>
        public void Initialize(IMessageHandler messageHandler)
        {
            handleMessage = messageHandler.HandleMessage;
            Task.Run(MessageProcessingTask);
        }

        /// <summary>
        /// Deinitializes the Messenger class
        /// </summary>
        public void Deinitialize()
        {
            // Clearing the singleton instance
            instance = null;

            // Mark MessageQueue as not accepting any more additions
            messageQueue.CompleteAdding();
        }


        /// <summary>
        /// Sends a message to the Messenger for processing.
        /// </summary>
        /// <param name="message"></param>
        /// <param name="location"></param>
        public void SendMessage(string message, NotificationCategory category)
        {
            try
            {
                messageQueue.Add(new Message(message, category));
            }
            catch (InvalidOperationException e)
            {
                // MessageQueue marked as not accepting any more additions
                throw new InvalidOperationException("Messenger already closed and cannot process further messages.\n" + e.Message, e);
            }
        }

        /// <summary>
        /// The task responsible for processing incoming messages from the message queue.
        /// </summary>
        private void MessageProcessingTask()
        {
            foreach (var message in messageQueue.GetConsumingEnumerable())
            {
                handleMessage(message);
            }
        }
    }
}

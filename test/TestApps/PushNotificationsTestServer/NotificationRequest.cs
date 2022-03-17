using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace PushNotificationsTestServer
{
    [Serializable]
    class NotificationRequest
    {
        public string ChannelUri { get; set; }

        public string Content_Type { get; set; }

        public string X_WNS_Type { get; set; }

        public string X_WNS_SuppressPopup { get; set; }

        public string Payload { get; set; }

        public bool Delay { get; set; }

        // A deserializer for the notification payload (byte[] -> NotificationPayload).
        public static NotificationRequest Deserialize(byte[] data)
        {
            NotificationRequest result = new NotificationRequest();
            using (MemoryStream m = new MemoryStream(data))
            {
                using (BinaryReader reader = new BinaryReader(m))
                {
                    result.ChannelUri = reader.ReadString();
                    result.Content_Type = reader.ReadString();
                    result.X_WNS_Type = reader.ReadString();
                    result.X_WNS_SuppressPopup = reader.ReadString();
                    result.Payload = reader.ReadString();
                    result.Delay = reader.ReadBoolean();
                }
            }
            return result;
        }
    }
}

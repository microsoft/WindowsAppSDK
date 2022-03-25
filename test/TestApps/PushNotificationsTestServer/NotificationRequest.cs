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

        public string Payload { get; set; }
    }
}

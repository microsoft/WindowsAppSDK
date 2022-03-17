using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using System.Diagnostics;
using System.Net.Http;
using System.Collections.Generic;
using System.Net.Http.Headers;

namespace PushNotificationsTestServer
{
    public static class PostPushNotificationforChannel
    {
        [FunctionName("PostPushNotificationforChannel")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Anonymous, "get", "post", Route = null)] HttpRequest req,
            ILogger log)
        {
            log.LogInformation("C# HTTP trigger function processed a request.");

            // Parse the parameters as GET arguments.
            string ChannelUri = req.Query["ChannelUri"];
            string X_WNS_Type = req.Query["X_WNS_Type"];
            string Content_Type = req.Query["Content_Type"];
            string NotificationPayloadString = req.Query["Payload"];

            if (req.Headers["Content-Type"] == "application/octet-stream")
            {
                Debug.WriteLine("BYTE");
                byte[] notificationBuffer = new byte[req.Body.Length];
                // Reads the request body as a byte stream.
                await new StreamReader(req.Body).BaseStream.ReadAsync(notificationBuffer, 0, notificationBuffer.Length);

                NotificationRequest payload = NotificationRequest.Deserialize(notificationBuffer);

                NotificationPayloadString = payload.Payload;
                X_WNS_Type = payload.X_WNS_Type;
                Content_Type = payload.Content_Type;
                ChannelUri = payload.ChannelUri;
            }
            else
            {
                Debug.WriteLine("JSON");

                string requestBody = await new StreamReader(req.Body).ReadToEndAsync();
                dynamic data = JsonConvert.DeserializeObject(requestBody);

                // If the parameters were empty get the arguments as a JSON.
                ChannelUri = ChannelUri ?? data?.ChannelUri;
                X_WNS_Type = X_WNS_Type ?? data?.X_WNS_Type;
                Content_Type = Content_Type ?? data?.Content_Type;
                NotificationPayloadString = NotificationPayloadString ?? data?.Payload;
            }

            // Currently always true. Once long lasting storage is in place this will not always be required.
            bool requiresAuthentication = true;

            string responseMessage = "";
            string token = "";

            using (var httpClient = new HttpClient())
            {
                if (requiresAuthentication)
                {
                    // Authenticate with the Windows Notification Service.
                    var parms = new List<KeyValuePair<String, String>>();
                    parms.Add(new KeyValuePair<String, String>("grant_type", "client_credentials"));
                    parms.Add(new KeyValuePair<String, String>("scope", "wns.connect"));
                    parms.Add(new KeyValuePair<string, string>("resource", "https://wns.windows.com/"));
                    parms.Add(new KeyValuePair<String, String>("client_id", System.Environment.GetEnvironmentVariable("client_id")));
                    parms.Add(new KeyValuePair<String, String>("client_secret", System.Environment.GetEnvironmentVariable("client_secret")));

                    // Do the actual request and await the response
                    HttpResponseMessage authenticationResponse = await httpClient.PostAsync("https://login.microsoftonline.com/common/oauth2/token", new FormUrlEncodedContent(parms));
                    authenticationResponse.EnsureSuccessStatusCode();

                    // If the response contains content we want to read it!
                    if (authenticationResponse.Content != null)
                    {
                        String jsonContent = await authenticationResponse.Content.ReadAsStringAsync();
                        dynamic tokenResponse = JsonConvert.DeserializeObject(jsonContent);
                        token = tokenResponse?.access_token;
                    }
                }

                // Post the Notification
                StringContent notificationContent = new StringContent(NotificationPayloadString);
                notificationContent.Headers.ContentType = new MediaTypeHeaderValue(Content_Type);
                notificationContent.Headers.ContentLength = NotificationPayloadString.Length;
                httpClient.DefaultRequestHeaders.Add("Authorization", String.Format("Bearer {0}", token));
                httpClient.DefaultRequestHeaders.Add("X-WNS-Type", X_WNS_Type);
                httpClient.DefaultRequestHeaders.Add("X-WNS-RequestForStatus", "true");

                HttpResponseMessage postNotificationResponse = await httpClient.PostAsync(ChannelUri, notificationContent);
                postNotificationResponse.EnsureSuccessStatusCode();
                responseMessage = await postNotificationResponse.Content.ReadAsStringAsync();

            }
            return new OkObjectResult(responseMessage);
        }
    }
}

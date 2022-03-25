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
        private static HttpClient s_httpClient = new HttpClient();
        private static string s_accessToken;

        [FunctionName("PostPushNotificationforChannel")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Anonymous, "post", Route = null)] HttpRequest req,
            ILogger log)
        {
            log.LogInformation("C# HTTP trigger function processed a request.");

            string requestBody = await new StreamReader(req.Body).ReadToEndAsync();
            dynamic data = JsonConvert.DeserializeObject(requestBody);
            string ChannelUri = data?.ChannelUri;
            string X_WNS_Type = data?.X_WNS_Type;
            string Content_Type = data?.Content_Type;
            string NotificationPayloadString = data?.Payload;

            log.LogInformation("Payload {0}", NotificationPayloadString);

            if (s_accessToken == null)
            {
                await Authenticate();
            }

            StringContent notificationContent = new StringContent(NotificationPayloadString);
            notificationContent.Headers.ContentType = new MediaTypeHeaderValue(Content_Type);
            notificationContent.Headers.ContentLength = NotificationPayloadString.Length;

            HttpRequestMessage httpRequest = new HttpRequestMessage();
            httpRequest.RequestUri = new Uri(ChannelUri);
            httpRequest.Method = HttpMethod.Post;
            httpRequest.Headers.Authorization = new AuthenticationHeaderValue("Bearer", s_accessToken);
            httpRequest.Headers.Add("X-WNS-Type", X_WNS_Type);
            httpRequest.Headers.Add("X-WNS-RequestForStatus", "true");
            httpRequest.Content = notificationContent;

            HttpResponseMessage postNotificationResponse = await s_httpClient.SendAsync(httpRequest);

            if (postNotificationResponse.StatusCode == System.Net.HttpStatusCode.Unauthorized)
            {
                await Authenticate();
                httpRequest.Headers.Authorization = new AuthenticationHeaderValue("Bearer", s_accessToken);
                postNotificationResponse = await s_httpClient.SendAsync(httpRequest);
            }

            postNotificationResponse.EnsureSuccessStatusCode();
            string responseMessage = await postNotificationResponse.Content.ReadAsStringAsync();

            return new OkObjectResult(responseMessage);
        }

        static async Task Authenticate()
        {
            // Authenticate with the Windows Notification Service.
            var parms = new List<KeyValuePair<String, String>>();
            parms.Add(new KeyValuePair<String, String>("grant_type", "client_credentials"));
            parms.Add(new KeyValuePair<String, String>("scope", "wns.connect"));
            parms.Add(new KeyValuePair<string, string>("resource", "https://wns.windows.com/"));
            parms.Add(new KeyValuePair<String, String>("client_id", System.Environment.GetEnvironmentVariable("client_id")));
            parms.Add(new KeyValuePair<String, String>("client_secret", System.Environment.GetEnvironmentVariable("client_secret")));

            // Do the actual request and await the response
            HttpResponseMessage authenticationResponse = await s_httpClient.PostAsync("https://login.microsoftonline.com/common/oauth2/token", new FormUrlEncodedContent(parms));
            authenticationResponse.EnsureSuccessStatusCode();

            // If the response contains content we want to read it!
            if (authenticationResponse.Content != null)
            {
                String jsonContent = await authenticationResponse.Content.ReadAsStringAsync();
                dynamic tokenResponse = JsonConvert.DeserializeObject(jsonContent);
                s_accessToken = tokenResponse?.access_token;
            }
        }
    }
}

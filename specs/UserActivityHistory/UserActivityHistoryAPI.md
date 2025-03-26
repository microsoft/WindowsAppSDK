UserActivityHistory
===

# Background

The [UserActivity](https://learn.microsoft.com/uwp/api/windows.applicationmodel.useractivities.useractivity)
class can be used to note down and preserve a record of activities that the user
is currently doing on their computer - e.g., browsing a website, reading a Word document, etc.
This allows Windows to have insight into the application state, enabling smart experiences that are
built around the semantics of the app. For example, a document editor can give Windows information
about the document that the user is editing, so that Recall can later take the user to the document
at the same location.

To record user activity, an app uses [UserActivityChannel](https://learn.microsoft.com/en-us/uwp/api/windows.applicationmodel.useractivities.useractivitychannel?view=winrt-26100)
to retrieve a UserActivity object via the API [GetOrCreateUserActivityAsync](https://learn.microsoft.com/en-us/uwp/api/windows.applicationmodel.useractivities.useractivitychannel.getorcreateuseractivityasync?view=winrt-26100#windows-applicationmodel-useractivities-useractivitychannel-getorcreateuseractivityasync(system-string)).
If a UserActivity with the given ID already exists, it will be returned; otherwise, a new UserActivity
object will be created and returned. You can then call the API [GetSession](https://learn.microsoft.com/en-us/uwp/api/windows.applicationmodel.useractivities.useractivity.createsession?view=winrt-26100#windows-applicationmodel-useractivities-useractivity-createsession)
to return a [UserActivitySession](https://learn.microsoft.com/en-us/uwp/api/windows.applicationmodel.useractivities.useractivitysession?view=winrt-26100)
object that tracks how long the user is engaged in that activity. This structure allows multiple
sessions to be associated with the same activity, representing the case where the user completes
that activity a bit at a time - e.g., beginning to watch a movie, then pausing, then watching more later.
These will be treated as the same singular user activity that spans multiple sessions.

UserActivityHistory is a new set of APIs that allow you to query up to the past 28 days of the
user's activity history, which will enable you to bring back content that the user has previously
been interacting with.

# Conceptual pages (How To)

The intended use case of this API is to allow you to make search queries against the user's activity history
on their local computer.  The string matching in the query parameters in this API is lexical in nature,
meaning that it is expected that any natural language semantic parsing of the user's input will be done by
your app prior to calling this API.

For example, if a user types in something along the lines of, "Please find the Korean recipe I was looking at
earlier today", your app might have an agentic AI parse that input and determine that the user is looking
for a webpage that contains the keywords "Korean" and "recipe", and construct a query with those keywords,
a content type of "text/html", and an access time within the last 24 hours.

In order for an app to make use of this API, it must be Windows logo certified, and the user must provide
their consent to allow access to their activity history.  If either of these is not the case, the API will
throw an exception.

# API Pages

## UserActivityHistory class

This class provides static methods that enable you to query the user's activity history.
This activity history is stored in a database managed by a local service, and these APIs
call out to that service to retrieve data from the database.

Here is an example usage of the class that will enable you to bring back the webpage for a
Korean recipe that the user had previously interacted with within the last day:

```c#
UserActivityHistoryQuery query = new();
query.Keywords = new string[] { "Korean", "recipe" };
query.LatestStartTime = DateTime.Now.AddDays(-1);

IList<UserActivityHistoryItem> results = UserActivityHistory.Search(
    new UserActivityHistoryQuery[] { query },
    UserActivityHistoryOrderBy.DwellTime,
    maxResults: 1);

UserActivityHistoryItem item = results.FirstOrDefault();

if (item != null)
{
    // Now we can use item.ActivationUri to bring back the webpage in the state in which the user
    // was last viewing it.
}
```

## UserActivityHistory.Search method

This method synchronously queries the user's activity history and returns a list of items matching
the criteria specified in the `queries` parameter. The results are ordered in descending order
according by the `orderBy` parameter: either by the most recent start times, the most recent
end times, or the longest time spent on the activity.

The results will include the user activity history items that match any one of the queries passed in.
To match a given query, the item must match all of the criteria specified in that query.  Any query
property that is left empty or null will be ignored.  A case-insensitive lexical search will be
performed on the keywords in the query, which will match if all of the keywords are found somewhere
in the DisplayText property of the item.

This method will not perform any parsing of the keywords for semantic meaning or natural language -
it is expected that the app will have already performed that step and will pass the result of that
into this API.

A case-insensitive lexical search will also be performed on the ContentType property of the item,
which is the [MIME type](https://docs.w3cub.com/http/basics_of_http/mime_types/complete_list_of_mime_types.html)
of the resource the user was interacting with.  The search will match if the ContentType of the item matches
the ContentType property of the query.  The ContentType supports using an asterisk as a wildcard
to match a range of content types - e.g., "image/*" will match "image/png", "image/jpeg", etc.

## UserActivityHistory.GetAppsWithUserActivity method

This method synchronously retrieves a list of all the app names with data in the user's activity
history database. You can use this, for example, to show the user the list of apps that are being
queried against, so the user can understand why an app that is not recording user activity is not
showing up in the results.

## UserActivityHistoryItem class

This class represents a single item in the user's activity history. It contains properties that
describe in what app the activity occurred, how the app described the activity, what sort of
resource was being interacted with (e.g., a document, a webpage, a video, etc.), the URI of
the resource involved in the activity, the URI that can be used to bring back the state the user
left the activity in, and the times when the user started and ended the activity.

If the user performed the same activity multiple times, there will be multiple
`UserActivityHistoryItem` objects returned, each with different start and end times.

## UserActivityHistoryItem.AppName property

This property contains the name of the app in which the activity occurred.

## UserActivityHistoryItem.ActivityId property

This property contains the ID of the activity, which can be used to collate multiple sessions
of the same activity. For example, if the user watched a movie in multiple sessions, the
`ActivityId` property can be used to identify how long in total the user spent watching that movie.

## UserActivityHistoryItem.DisplayText property

This property contains a string that is how the app chose to describe the activity. For example,
if the activity was reading the contents of a webpage, this property might contain the webpage's title.

## UserActivityHistoryItem.ContentType property

This property contains the MIME type of the content being interacted with. For example, if the user
was looking at a PNG image, this property would contain the string "image/png".

Note that this is a string property, not an enum, so apps that populate this property
do not necessarily have to use existing recognized common MIME types.

## UserActivityHistoryItem.ContentUri property

This property contains the URI of the content being interacted with. For example, if the user was
looking at a webpage, this property would contain the URI of that webpage.

## UserActivityHistoryItem.ActivationUri property

This property contains the URI that can be used to bring back the state the user left the activity in.
For example, if the user was looking at a webpage, this property would contain the URI of that webpage
with additional information, such as what the scroll position was, etc.

If this property is not populated on the UserActivity object, then we won't add it to the user activity
history database, as we won't be able to bring back that activity.

## UserActivityHistoryItem.StartTime property

This property contains the time when the user started the activity session.

## UserActivityHistoryItem.EndTime property

This property contains the time when the user ended the activity session.

## UserActivityHistoryQuery class

This class is used to specify criteria for what portion of the user's activity history you want to
retrieve. It allows you to specify keywords to search for, content types to filter by, and time ranges
to filter by.

## UserActivityHistoryQuery.Keywords property

This property is an array of keywords, each of which is used to lexically search against the
DisplayText column in the database. Keywords are case-insensitive, and results returned will
be those that contain all of the keywords in the array.

## UserActivityHistoryQuery.ContentType property

This property is a string that specifies the content type associated with the activity you want
to retrieve. It allows the inclusion of an asterisk as a wildcard - e.g., "image/*" will match
all content types beginning with "image/", such as "image/png", "image/jpeg", etc.
This property is case-insensitive.

## UserActivityHistoryQuery.EarliestStartTime property

This is an optional DateTime property that specifies the earliest start time of the activity
you want to retrieve. Any activities with a StartTime property earlier than this will be excluded.
If this property is unspecified, it will be ignored.

## UserActivityHistoryQuery.EarliestEndTime property

This is an optional DateTime property that specifies the earliest end time of the activity
you want to retrieve. Any activities with an EndTime property earlier than this will be excluded.
If this property is unspecified, it will be ignored.

## UserActivityHistoryQuery.LatestStartTime property

This is an optional DateTime property that specifies the latest start time of the activity
you want to retrieve. Any activities with a StartTime property later than this will be excluded.
If this property is unspecified, it will be ignored.

## UserActivityHistoryQuery.LatestEndTime property

This is an optional DateTime property that specifies the latest end time of the activity
you want to retrieve. Any activities with an EndTime property later than this will be excluded.
If this property is unspecified, it will be ignored.

## UserActivityHistoryOrderBy enum

This enum specifies what property the results should be ordered by.  The options are as follows:

| Name | Description |
|-|-|
| StartTime | Results will be in descending order of their StartTime property |
| EndTime | Results will be in descending order of their EndTime property |
| DwellTime | Results will be in descending order of the difference between their EndTime and StartTime properties |

# API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.ApplicationModel.UserActivities
{
    runtimeclass UserActivityHistory
    {
        static IVector<UserActivityHistoryItem> Search(
            UserActivityHistoryQuery[] queries,
            UserActivityHistoryOrderBy orderBy,
            UInt32 maxResults); 

        static IAsyncOperation<IVector<UserActivityHistoryItem> > SearchAsync( 
            UserActivityHistoryQuery[] queries, 
            UserActivityHistoryOrderBy orderBy, 
            UInt32 maxResults);

        static IVector<String> GetAppsWithUserActivity();

        static IAsyncOperation<IVector<String>> GetAppsWithUserActivityAsync();
    }

    runtimeclass UserActivityHistoryItem
    {
        String AppName { get; };
        String ActivityId { get; };
        String DisplayText { get; };
        String ContentType { get; };
        String ContentUri { get; };
        String ActivationUri { get; };
        DateTime StartTime { get; };
        DateTime EndTime { get; };
    }

    runtimeclass UserActivityHistoryQuery
    {
        UserActivityHistoryQuery();

        String[] Keywords;
        String ContentType;
        IReference<DateTime> EarliestStartTime;
        IReference<DateTime> EarliestEndTime;
        IReference<DateTime> LatestStartTime;
        IReference<DateTime> LatestEndTime;
    }

    enum UserActivityHistoryOrderBy
    {
        StartTime,
        EndTime,
        DwellTime 
    };
}
```
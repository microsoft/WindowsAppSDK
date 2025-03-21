UserActivityHistory
===

# Background

The UserActivity class can be used to note down and preserve a record of activities that the user
is currently doing on their computer - e.g., browsing a website, reading a Word document, etc.

To record user activity, you use UserActivityChannel to retrieve a UserActivity object via the
API GetOrCreateUserActivityAsync. If a UserActivity with the given ID already exists, it will be
returned; otherwise, a new UserActivity object will be created and returned. You can then call
the API GetSession to return a UserActivitySession object that tracks how long the user is engaged
in that activity. This structure allows multiple sessions to be associated with the same activity,
representing the case where the user completes that activity a bit at a time - e.g., beginning to
watch a movie, then pausing, then watching more later. These will be treated as the same singular
user activity that spans multiple sessions.

UserActivityHistory is a new set of APIs that allow you to query the past 28 days of the user's
activity history, which will enable you to bring back content that the user has previously been
interacting with.

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

IList<UserActivityHistoryItem> results = await UserActivityHistory.SearchAsync(
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

Each parameter in `queries` is ORed together in the resulting database query, whereas the contents
of a single object in the `queries` array are ANDed together.  For example, if you provided two
queries, each of which contained the keywords "tax", one of which had a content type of
"application/pdf" and the other had a content type of "image/*", the resulting database query
would be something along these lines:

```sql
SELECT * FROM UserActivityHistory WHERE
    (CONTAINS (DisplayText, '"tax"')) AND
    ((CONTAINS (ContentType, '"application/pdf"')) OR
     (CONTAINS (ContentType, '"image/*"')));
```

## UserActivityHistory.SearchAsync method

This method is an asynchronous version of the `Search` method.

## UserActivityHistory.GetAppsWithUserActivity method

This method synchronously retrieves a list of all the app names with data in the user's activity
history database. You can use this, for example, to show the user the list of apps that are being
queried against, so the user can understand why an app that is not recording user activity is not
showing up in the results.

## UserActivityHistory.GetAppsWithUserActivityAsync method

This method is an asynchronous version of the `GetAppsWithUserActivity` method.

## UserActivityHistoryItem class

This class represents a single item in the user's activity history. It contains properties that
describe in what app the activity occurred, what the nature of the activity was, the URI of the
resource involved in the activity (e.g., a document, a webpage, a video, etc.), the URI that
can be used to bring back the state the user left the activity in, and the times when the user
started the activity and ended the activity.

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

## UserActivityHistoryItem.ContentUri property

This property contains the URI of the content being interacted with. For example, if the user was
looking at a webpage, this property would contain the URI of that webpage.

## UserActivityHistoryItem.ActivationUri property

This property contains the URI that can be used to bring back the state the user left the activity in.
For example, if the user was looking at a webpage, this property would contain the URI of that webpage
with additional information such as what page the user was on, what their scroll position was, etc.

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

This is a nullable DateTime property that specifies the earliest start time of the activity
you want to retrieve. Any activities with a StartTime property earlier than this will be excluded.
If this property is left as null, it will be ignored.

## UserActivityHistoryQuery.EarliestEndTime property

This is a nullable DateTime property that specifies the earliest end time of the activity
you want to retrieve. Any activities with an EndTime property earlier than this will be excluded.
If this property is left as null, it will be ignored.

## UserActivityHistoryQuery.LatestStartTime property

This is a nullable DateTime property that specifies the latest start time of the activity
you want to retrieve. Any activities with a StartTime property later than this will be excluded.
If this property is left as null, it will be ignored.

## UserActivityHistoryQuery.LatestEndTime property

This is a nullable DateTime property that specifies the latest end time of the activity
you want to retrieve. Any activities with an EndTime property later than this will be excluded.
If this property is left as null, it will be ignored.

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
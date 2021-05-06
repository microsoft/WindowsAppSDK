$Uri = '$(MaestroUri)'


$Body = @{
    commit  = 'John'
    assets   = 'Doe'
    email      = 'john.doe@contoso.com'
    avatar     = Get-Item -Path 'c:\Pictures\jdoe.png'
    birthday   = '1980-10-15'
    hobbies    = 'Hiking','Fishing','Jogging'
}
$Result = Invoke-RestMethod -Uri $Uri -Method 'Post' -Form $Body

# {
#   "commit": "string",
#   "assets": [
#     {
#       "name": "string",
#       "version": "string",
#       "nonShipping": true,
#       "locations": [
#         {
#           "location": "string",
#           "type": "none"
#         }
#       ]
#     }
#   ],
#   "dependencies": [
#     {
#       "buildId": 0,
#       "isProduct": true,
#       "timeToInclusionInMinutes": 0
#     }
#   ],
#   "azureDevOpsBuildId": 0,
#   "azureDevOpsBuildDefinitionId": 0,
#   "azureDevOpsAccount": "string",
#   "azureDevOpsProject": "string",
#   "azureDevOpsBuildNumber": "string",
#   "azureDevOpsRepository": "string",
#   "azureDevOpsBranch": "string",
#   "gitHubRepository": "string",
#   "gitHubBranch": "string",
#   "released": true,
#   "stable": true,
#   "incoherencies": [
#     {
#       "name": "string",
#       "version": "string",
#       "repository": "string",
#       "commit": "string"
#     }
#   ]
# }
# Git Checkin-to-main Policy

**NOTE: All policies apply to the [main and develop](develop-branch.md) branch unless otherwise stated.**

The main branch needs to be kept 'healthy' and ready to ship near daily (daily, or within a day or
two). An unhealthy main branch negatively impacts day-to-day development and jeopardizes release
schedules. We have policies to ensure a high quality bar in main. The details differ depending if a
code change is Experimental vs Preview or Stable.

See [Final Decision: Release channels and cadences #637](https://github.com/microsoft/WindowsAppSDK/discussions/637)
for the expectations of the various release channels.

Note: If a contribution only modifies repo documentation and does not touch product code or assets an
administrator is welcome to bypass build & test policies on the pull request to bypass build requirements.
Other contribution policies such as code review requirements still apply.

## Policy: Preview and Stable (aka non-Experimental)

The following requirements must be met to checkin non-Experimental changes to main:

1. API Review approval
2. Tests
3. Prepared to accept bug reports from the world
4. Functionality is Feature Complete by a release's fork for Preview1
4a. Approved Design Change Requests (DCR) can be made after Preview1. See the DCR process to approve these exceptions.

Changes of a non-Experimental nature must meet these policies to be committed to the main branch.

## Policy: Experimental

The policies for Experimental content differ from non-Experimental content because of the reasons for Experimental content:

1. **Selfhost** – a change is good but you're interested in community usage and feedback to verify
   it's ready for Preview/Stable.
2. **Skeleton** – API Review has approved and you've made an initial 'skeletal' implementation to
   get the interface and infrastructure building but isn't functionally complete e.g. skeletal code
   compiles but everything returns E_NOTIMPL/false/null/etc). Having the API surface building in
   main can unblock documentation, test and sample writers.
3. **Feedback** – your API shape isn't locked (or even clear) but you want and/or need feedback from
   the community, partners and/or others before deciding the API is ready to consider for
   non-Experimental releases. The API is not yet ready to go through API Review.

Reasons NOT to make Experimental content:

1. **Prototype** – prototypes, ideas and wild experimentation should be done on a 'feature branch'
   and not checked into main. To make a 'feature branch' checkout a new branch off main (or a child
   of main) with no intention to checkin to main any time soon (or maybe ever). Make a feature
   branch and don't check into main

Changes of an Experimental nature follow a modified form of the policies for non-Experimental content:

1. CONSIDER: Review API with your local-representative
2. Tests
3. Prepared to accept feedback from the world
4. Experimental APIs are marked experimental

Experimental APIs don't go through full API Review but should be discussed with your local API
Review representative. This ensures your API is aligned with API practices and policies and avoids
the risk of significant changes required to pass API Review.

Experimental content requires appropriate test coverage. This is no different than non-Experimental
content, except meaning of 'appropriate' may vary. For instance, 'skeletal' Experimental APIs don't
need the same breadth of test coverage as non-Experimental APIs.

Experimenal content is broadly shipped via Experimental releases. You should be prepared to receive
feedback on Experimental content.

Experimental content must be tagged to indicate it's Experimental. The mechanisms to do so may vary
(WinRT APIs, Flat-C APIs, non-API content (e.g. data files), etc) but the policy is the same -
Experimental content must be marked to indicate it's Experimental.

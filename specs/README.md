# Windows App SDK Specs

This directory contains archived and in-progress spec documents for APIs in Windows App SDK.

Documents in this directory are used as part of a feature or API review for features in development
and form the basis for public documentation and sample code. Write specs so they can be directly
consumed by an app developer or document author.

**DO** provide feedback by **commenting on active pull requests** tagged with
[the "api-design" label.](https://github.com/microsoft/WindowsAppSDK/pulls?q=is%3Apr+is%3Aopen+label%3Aapi-design)

**DO** provide feedback by **opening
[issues](https://github.com/microsoft/WindowsAppSDK/issues/new/choose) regarding spec documents in
this folder**. Specs in this folder are ready for implementation or have already been added to
Windows App SDK.

**DO** create pull requests for new or updated specs when requested to do so as part of an issue
thread.

**DO NOT** create unsolicited PRs that add or modify specs. To propose a new feature please follow
the Windows App SDK contribution process [described here](../docs/contributor-guide.md) and start by
[opening a new issue](https://github.com/microsoft/WindowsAppSDK/issues/new/choose).

## API Design

Designing a new Windows App SDK API involves creating a spec for the API, authoring some sample code
an app might use with the API, getting it reviewed by a group of other API designers, and finally
merging the spec into `main`.

| Who                   | Role                                                                                                                                                     |
| --------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Author                | Member of the Windows App SDK community proposing a new API or change to an existing API                                                                 |
| Design Representative | Member of the Windows API Design Representatives group responsible for the shape and direction of their component area within Windows or Windows App SDK |
| Reviewer              | Person providing commentary on an API under review                                                                                                       |

For additional help, create a new `api-design` tagged issue and assign it to @jonwis for assistance.

### Authoring an API Spec

For Windows App SDK team members, the spec and API design workflow is:

1. Ensure your proposal is approved and in plan.

2. Create a new working branch `user/<username>/<feature>` or work in your fork of the
   Windows App SDK repo.

3. Create a new folder for your spec under the `specs` folder: `/specs/<feature>`

4. Author your spec using the [spec template](spec_template.md). Please use relative links for
   images or other assets in the folder. Be sure to read and follow the commented instructions in
   the template.

5. Work with your API design representative and iterate on the specification in your branch as much
   as you see fit.

When your spec is ready for review, your API representative will help guide you through the
remainder.

**DO** follow the authoring guidelines from [the contributor's guide](../docs/contributor-guide.md).

**DO** follow the [spec template guidance](spec_template.md) for authoring samples and IDL.

**DO NOT** create a pull request from `user/<username>/<feature>` to `main` (see "Reviewing"
section).

### Reviewing APIs

Your API representative will help you finish the design document and get it reviewed with members of
the Windows API Design community. The process to finish the review is:

1. The representative creates a new pull request from `user/<username>/<feature>` to the `main`
   branch. Make sure the pull request mentions the original issue thread.

2. The representative schedules time with the Windows API Design community to review the pull
   request.

    - As the design group is spread out we prefer giving no less than 48h notice when reviewing APIs
    - Reviews are typically scheduled for Tuesdays 1-2pm or Thursdays 1-3pm (Seattle local time).
    - API reviewers should post in the initial issue thread with the date and time of the review and
      any group-call information.

3. The design group (and you, the community!) leaves comments in the pull request

    - Make sure to leave comments _before_ the scheduled time; comments afterwards may not be seen
      or applied
    - API authors should _avoid_ responding to posted comments until _after_ the review

4. During the review timeslot, the API design group will join a Teams call and review any comments
   on the pull request. See below for the "feedback keywords" the review meeting uses.

    > Note: community members are welcome to join our Teams call just as soon as we can figure out
    > how to publish the Teams link for public joining.

5. After review, the API design representative works with the API designer to apply any feedback
   generated during the review period.

6. When the API representative is satisfied that the spec is ready to go they can press the Merge
   button on the pull request.

**DO** send deep-links to both the formatted and raw views of the markdown spec. To get the link
information:

-   In the pull request UI, select the "Files Changed" tab
-   Click the "Changes from nn commits" drop down
-   Select the full range of commits to review
-   Send the resulting pull-request URI
-   Send a link to "source diff" of the markdown file in question
-   Click the "show rich diff" button and send a resulting link for the formatted version

**AVOID** pushing updates to the under-review branch until the review has completed.

**DO NOT** click the "Approve" button when finishing your review commentary. Instead, use the
"Comment" or "Request Changes" buttons.

**DO NOT** resolve conversations until _after_ the review period.

**DO** update the issue thread when the review has completed.

**DO** push updates to the under-review branch to apply feedback to the spec.

### Review Keywords

During API review the representative and members of the call may provide new guidance for the API
author to apply. There may also be discussion about why the API is shaped in a certain way, or how
it should work. Review feedback is added to the pull request as comments on existing comments.

The keywords are:

| Keyword    | Meaning                                                                                                                                                                                                                                                        |
| ---------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| DISCUSSION | Notes from any conversation about the comment, or notes on a discussion around this part of the API. Discussions often record why a certain design choice was made, interesting topics for the future, or explaining how this API intersects with another API. |
| RECOMMEND  | The API group _strongly recommends_ making a specific change to the API shape. Typical feedback includes naming, changes to type signatures, or modifications to behaviors or documentation.                                                                   |
| CONSIDER   | The reviewers ask that the author _consider_ making a specific change to the API shape, adding functionality, modifying samples or documentation, etc.                                                                                                         |
| SAMPLE     | A sample defect, missing sample, or other problem with the presented sample code. "Sample" tags typically do not modify the API shape itself                                                                                                                   |

The API design representative owns the quality and shape of the APIs for their area. Representatives
are free to ignore or modify RECOMMEND markers, but should reply back to the comment thread
indicating their reasoning. We use review commentary to adjust our design guidelines over time.

### Additional Links

-   [.NET API Design](https://github.com/dotnet/runtime/blob/main/docs/project/api-review-process.md)
-   [MIDL 3 Specification](https://docs.microsoft.com/uwp/midl-3/)

## Specification Notes

**DO** write specification templates as if they will be read by a developer trying to understand how
to use the API and feature.

**DO** include links to existing types, pointers into https://docs.microsoft.com when providing
converged features.

**DO** describe how packaged, unpackaged, AppContainer and Full Trust applications will use the
feature.

**DO NOT** reference Windows-internal features, plans, or scheduling. This includes links to
internal specifications.

**DO** use "https://task.ms/12345" links if necessary to reference internal tasks or deliverable
information.

**DO** update existing specifications when adding new functionality, rather than creating a
new-spec-per-change. Reviewers should read the changes to the specification in a pull request.

**DO NOT** gratuitously reformat specification documents, as that can obscure real changes vs
editorial, whitespace, or other changes.

**DO** specify any additional requirements on application authors, such as "you must define an
app.config" or "you must include this package manifest markup or this application manifest markup"
to use a feature.

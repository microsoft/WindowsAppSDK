# Project Reunion Specs

This directory contains archived and in-progress spec documents for APIs in
Project Reunion.

Documents in this directory are used as part of a feature and API review
for features in development and form the basis for public documentation
and sample code. Write specs so they can be directly consumed by an
app developer or document author.

## Please DO:

* Provide feedback by **commenting on active pull requests** tagged with
    [the "ApiReview" label.](https://github.com/microsoft/ProjectReunion/pulls?q=is%3Apr+is%3Aopen+label%3AApiReview)
* Provide feedback by **opening [issues](https://github.com/microsoft/ProjectReunion/issues/new/choose)
   regarding spec documents in the [reviewed](https://github.com/microsoft/ProjectReunion/tree/master/specs/reviewed) folder**.
   Specs in the `reviewed` folder have been previously reviewed for
   inclusion in Project Reunion.

## Please DO NOT:

* Provide feedback on spec documents in the `archive` folder since those
    features have been deprecated or altered substantially.
* Create unsolicited PRs that add new specs. To propose a new feature,
    please follow the Project Reunion contribution process [described here](https://github.com/Microsoft/ProjectReunion/docs/contributor-guide.md)
    and start by [opening a new issue](https://github.com/microsoft/ProjectReunion/issues/new/choose).

## Spec workflow

For Project Reunion team members, the spec and API design workflow is:

1. Ensure your proposal is approved and in plan.

2. Create a new working branch ```user/<username>/<feature>``` or work in
   your fork of the Project Reunion repo.

3. Create a new folder for your spec under the ```specs``` folder: ```/specs/<feature>```

4. Author your spec using the [spec template](spec_template.md).
   Please use relative links for images or other assets in the folder.

5. When your spec is ready for review:

   * Open a new pull request to merge your spec to the ```master``` branch
   * Reference the issue thread in the pull request to link them together

6. Provide adequate time for the community and Project Reunion members to
   review the API spec file.

7. Review requested changes with Project Reunion members and the Windows
   API Design representative responsible for the area.

8. Complete the pull request

This workflow applies to modifying API designs as well.


## Specification Notes

**DO** write specification templates as if they will be read by a
developer trying to understand how to use the API and feature.

**DO** include links to existing types, pointers into https://docs.microsoft.com
when providing converged features.

**DO** describe how packaged, unpackaged, AppContainer and Full Trust
applications will use the feature.

**DO NOT** reference Windows-internal features, plans, or scheduling. This
includes links to internal specifications.

**DO** use "http://task.ms/12345" links if necessary to reference internal
tasks or deliverable information.

**DO** update existing specifications when adding new functionality,
rather than creating a new-spec-per-change. Reviewers should read the
changes to the specification in a pull request.

**DO NOT** gratuitously reformat specification documents, as that can
obscure real changes vs editorial, whitespace, or other changes.

**DO** specify any additional requirements on application authors, such
as "you must define an app.config" or "you must include this package
manifest markup or this application manifest markup" to use a feature.

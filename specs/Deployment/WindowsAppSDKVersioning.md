Since we will now match the release version with the MSIX, it is worth explaining how that is going to increment.
* Major will increase when a stable or preview release contains Breaking Changes from the previous Stable release. This will happen 
no more than once per year.
* Minor will increase when a stable release contains new Functionality from the previous Stable release. This will happen no more than once 
per month.
* Every potential released build (stable, preview, experimental) will increase the Patch, unless the Major or Minor is increased.
No 2 builds will share the same Major.Minor.Patch version. The exception to that is X.Y.0, which could have muiltiple "preview" and
"experimental" releases prior to the X.Y.0 stable release.
If we notice an issue after building a candidate (stable, preview, or experimental), we will choose not to release it, at which 
point the patch will bump again.
This means that there will be times when there is a patch number that will not be released at all.
* Note: We see experimental releases as "containing" the closest stable + some experimental stuff, rather than "previewing" what is coming. We 
do not bump the Major/Minor for experimental things because the new/breaking things will at least sometimes not be in the next stable release, 
and may even be removed before the next experimental release. 
* Preview releases are optional if we feel the need to have a preview of nearly stable things without anything currently marked experimental.
This will only happen on the next Major release before making an official stable release. When we do have a Preview build, all Previews and 
Experimental releases will be X.0.0-\<pre or Exp\>\<Num\> until we release the first Stable release.

A simplified example is this:
* 2.0.0 is the first stable release.
* 2.0.1-experimental0 is the first experimental. (contains 2.0.0 + some exp APIs, and some bug fixes)
* 2.0.2 is the 2nd stable release. (bug fixes moved into 2)
* 2.0.3-experimental1 is the 2nd experimental. (contains 2.0.1 + some exp APIs, and some more bug fixes)
* 2.0.4-experimental2 is the 3rd experimental. (contains 2.0.1 + some Breaking Changes, some exp APIs, and some more bug fixes)
* 2.1.0 is the 3rd stable release (some of the exp APIs went stable, and some bug fixes)
* 2.1.1-experimental3 is the 4th experimental. (contains 2.1.0 + some Breaking Changes, and some more bug fixes)
* 3.0.0-preview0 is the preview 3 public release
* 3.0.0-experimental0 (contains 3.0.0-preview1 + some new APIs not in the preview build)
* 3.0.0-experimental1 (contains 3.0.0-preview1 + even more new APIs not in the preview build)
* 3.0.0-preview1 (one of the experimental APIs went public, but still not ready to release)
* 3.0.0-experimental2 (contains 3.0.0-preview2 + the experimental API and some bug fixes)
* 3.0.0 is the first 3 stable release
* 3.0.1-experimental3 (contains 3.0.0 + the new APIs from 3.0.0-experimental2)
* 3.0.3 is the 2nd stable release(we made 3.0.2, noticed issues, fixed and rebuilt)
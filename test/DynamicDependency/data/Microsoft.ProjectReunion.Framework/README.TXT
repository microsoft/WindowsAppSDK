This is a fake stand-in for ProjectReunion's Framework package.

The bootstrap API needs to find the ProjectReunion Framework package
but it's hard to find it if you're testing code before it's created.

The bootstrap API tests use this to (sufficiently) act as the expected
framework pacakge. It's not actually usable for anything except the
bootstrap tests, and even then requires additional games inside the
bootstrap tests to 'work'.

Maybe someday if the ProjectReunion Framework package is built and
available before the boostrap tests run we can delete this imitation
and use the real framework package. Until then, this will suffice.

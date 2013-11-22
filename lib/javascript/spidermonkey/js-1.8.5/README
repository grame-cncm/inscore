1.  The latest release notes for SpiderMonkey can be found at:

      https://developer.mozilla.org/En/SpiderMonkey/1.8.5


2.  js/jsd contains code for debugging support for the JavaScript engine in js/src.


Packaging Notes
---------------
This release is based on revision 5f8f494a4c29 of https://hg.mozilla.org/releases/mozilla-2.0, with
a few trivial changes applied to improve the manageability of the standalone-release. In addition 
to running autoconf 2.13 before bundling the release, the changes in the patches directory were
applied.

This standalone release introduces a new, experimental, naming convention for the SpiderMonkey
shared library.  This naming convention will not be rolled back into the mainline Mozilla source
tree, however the relevant patches are included with this distribution.

Note: Please copy wes@page.ca on bugs related to packaging this standalone release.

Linux and non-Mac OS X Unices
-----------------------------
Previous releases and the master source repositories build a shared library named libmozjs.so. In
an effort to make version identification easier for embedders and OS distribution maintainers, this
standalone release builds libmozjs185.so.1.0.0  (.dylib.1.0.0 on Mac OS X).

libmozjs185 indicates that this is the SpiderMonkey library which implements JavaScript 1.8.5. The
1.0.0 suffix is of the form major.minor.micro revision.  While it is unlikely that more than one 
official source release for a given version of JavaScript will be published, it has happened in the
past (e.g JS 1.4-1), and we want to provide clear direction in case there is a compelling need:

* a change in major revision number indicates a change which is ABI and API incompatible with the
  previous release,

* a change in minor revision number indicates a change which is ABI incompatible, but API 
  compatible with the previous release,

* a change in micro revision number indicates a change which is both ABI and API compatible with
  the previous release.
 
A symbolic link will be provided linking libmoz185.js.so to this library, along with
libmoz185.js.so.1.0 when building the install target.

Most embeddings building on Unix or Linux should link against libmozjs185.so.1.0.

The static library has been renamed, from libjs_static.a to libmozjs185-1.0.a.

Mac OS X
--------
The versioning rules and symbolic links are the same as for the other flavours of Unix, but the
library name is now libmozjs185.1.0.0.dylib.

Most embeddings building on Mac OS X should link against libmozjs185.1.0.dylib.

Microsoft Windows
-----------------
The versioning rules are the same as for Unix, but the the library name is now 
libmozjs185-1.0.dll. Symbolic links will not be created.

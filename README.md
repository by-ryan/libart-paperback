\page readme README

[![Build Status][build-badge]](https://code.helloryan.se/art/libart-paperback/actions)
[![License][license-badge]](https://code.helloryan.se/art/libart-paperback/src/branch/master/LICENSE)
[![Sponsor][sponsor-badge]](https://patreon.com/helloryan)
[![Language][language-badge]](https://en.wikipedia.org/wiki/C++)
[![Build System][build2-badge]](https://build2.org/)

# libart-paperback

libart-paperback is a PDF library for C++.

## Feature Requests

Feature requests can be sent to ryan@helloryan.se.

## Build System

libart-paperback uses the build2 build system for C++. More
information about installing build2 is available at https://build2.org.

This README is primarily intended for developers of libart-paperback.
For instructions on getting started with integrating libart-paperback
into your project, see \ref getting-started.

## Project Structure

The source code for libart-paperback is located at `$src_root$/art/paperback`.
Examples are available in `$src_root$/examples`.

## Documentation

Doxygen is used to generate the API reference documentation for
libart-paperback. If you have Doxygen installed and want to build the
documentation, you can do so by executing `b alias{docs}` in the
package root.

The documentation will be written to `$out_root$/docs`.

The Doxygen configuration is located at `$src_root$/Doxyfile.in`. This
file is preprocessed by build2 before Doxygen is invoked.

## Developer Documentation

The developer documentation can be built by executing
`b alias{docs-private}` in `$src_root$`. This version of the
documentation includes classes defined in .cxx files as well as
private class members.

Developer documentation will be written to the same directory as the
public documentation, i.e. `$out_root$/docs`.

Developer documentation is built nightly from `master` and can be found
at: https://docs.helloryan.se/libart-paperback/.

## GitHub Pull Requests

Pull requests on GitHub will definitely be ignored.

[build-badge]: https://code.helloryan.se/art/libart-paperback/actions/workflows/on-push.yaml/badge.svg
[license-badge]: https://img.shields.io/badge/License-BSD_4--Clause-orange
[sponsor-badge]: https://img.shields.io/badge/Sponsor-Patreon-green
[language-badge]: https://img.shields.io/badge/Language-C++-blue
[build2-badge]: https://img.shields.io/badge/Powered_by-build2-red

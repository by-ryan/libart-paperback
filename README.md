\page readme README

[![Build Status][build-badge]](https://code.helloryan.se/art/libart-paperback/actions)
[![Documentation][docs-badge]](https://docs.helloryan.se/libart-paperback/)
[![License][license-badge]](https://code.helloryan.se/art/libart-paperback/src/branch/master/LICENSE)
[![Sponsor][sponsor-badge]](https://patreon.com/helloryan)
[![Language][language-badge]](https://en.wikipedia.org/wiki/C++)
[![Build System][build2-badge]](https://build2.org/)
[![Made with Love][made-with-love-badge]](https://helloryan.se/)
[![Discord][discord-badge]](https://discord.gg/dCFMwrbNSP)

# libart-paperback

libart-paperback is a PDF library for C++.

## Feature Requests

Feature requests can be sent to art@helloryan.se or you can join the
Art Discord and have a chat: https://discord.gg/dCFMwrbNSP.

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
[docs-badge]: https://code.helloryan.se/art/libart-paperback/actions/workflows/publish-docs-nightly.yaml/badge.svg
[license-badge]: https://img.shields.io/badge/License-BSD_4--Clause-orange
[sponsor-badge]: https://img.shields.io/badge/Sponsor-Patreon-green
[language-badge]: https://img.shields.io/badge/Language-C++-blue
[build2-badge]: https://img.shields.io/badge/Powered_by-build2-red
[made-with-love-badge]: https://img.shields.io/badge/Made_with_%E2%9D%A4%EF%B8%8F_by-RYAN-red
[discord-badge]: https://img.shields.io/discord/1444936129718522024?label=Discord&color=blue

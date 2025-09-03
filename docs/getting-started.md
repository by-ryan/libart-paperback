\page getting-started Getting Started

# Getting Started

Paperback uses the build2 build system, see https://build2.org/.

The first step is to include Paperback in your build2 project.

Add the following lines to your repositories.manifest file:

```
:
role: prerequisite
location: https://code.helloryan.se/art/libart-paperback.git##HEAD
```

And the following to your manifest file:

```
depends: libart-paperback ^0.1.0-
```

Finally, link your executable or library with Paperback:

```
import libs =+ libart-paperback%lib{art-paperback}
```

## Usage Example

The example below shows how to use Paperback to create a new PDF
document and render some text on a page. More examples are available
in `$src_root$/examples`.

```c++
#include <fstream>
#include <iostream>

#include <art/paperback/document.hxx>
#include <art/paperback/page.hxx>

#include <art/paperback/graphics/canvas.hxx>
#include <art/paperback/graphics/standard-font.hxx>

using namespace std;
using namespace Art::Paperback;
using namespace Art::Paperback::Graphics;

int
main(int argc, char* argv[])
{
  if (argc != 2) {
    cerr << "usage: " << argv[0] << " <path>\n";
    return 1;
  }

  try {
    // Open the output file.
    //
    fstream fs{argv[1], std::ios_base::out | std::ios_base::binary};

    // Create a new document.
    //
    Document document{Document::create_new, fs, 1, 4};
    Standard_font helvetica{document, "Helvetica"};

    // Create a new A4 page.
    //
    double width = 595;
    double height = 842;

    auto& page = document.create_page(Page::Properties{
      Rectangle{0, 0, width, height}
    });

    // Create a page canvas and render some text.
    //
    {
      Canvas canvas{Canvas::clear, page};
      Canvas::Set_font use_font{canvas, helvetica, 14};

      // Measure the width of the text, so we can center it.
      //
      auto tw = helvetica.get_text_width("Hello, world!");

      auto text_width = (tw.width * 14) / 1000;
      auto capheight = (helvetica.get_capheight() * 14) / 1000;

      double cx = (width / 2) - (text_width / 2);
      double cy = (height / 2) - (capheight / 2);

      Canvas::Begin_text bt{canvas};

      bt.move_text_pos(cx, cy);
      bt.show_text("Hello, world!");
    }

    // Write the document explicitly to the underlying I/O stream.
    //
    // Otherwise, the Document destructor flushes it automatically,
    // ignoring any exceptions thrown.
    //
    document.flush();
  }
  catch (exception const& ex) {
    cerr << argv[0] << ": an error occurred: " << ex.what() << "\n";
    return 1;
  }
  catch (...) {
    cerr << argv[0] << ": an unknown error occurred\n";
    return 1;
  }

  return 0;
}
```

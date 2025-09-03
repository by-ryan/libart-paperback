#include <fstream>
#include <iostream>

#include <art/paperback/document.hxx>
#include <art/paperback/document-information.hxx>
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
    fstream fs{argv[1], ios_base::out | ios_base::binary};

    // Create a new document.
    //
    Document document{Document::create_new, fs, 1, 4};
    document.information().set_title("Example Document");
    document.information().set_author("Example Author");
    document.information().set_subject("Example Subject");
    document.information().set_keywords("PDF for C++");
    document.information().set_creator("libart-paperback");
    document.information().set_producer("libart-paperback");

    // Load one of the 14 standard fonts.
    //
    Standard_font font{document, "Helvetica-BoldOblique"};

    double width = 595;
    double height = 842;

    // Create a new page.
    //
    auto& page = document.create_page(Page::Properties{
      Rectangle{0, 0, width, height}
    });

    // Create a new canvas and render some text on the page.
    //
    Canvas canvas{Canvas::clear, page};

    // Set the font with a size of 14.
    //
    Canvas::Set_font use_font{canvas, font, 14};

    // Render some text and graphics.
    //
    {
      // Measure the width of the text, so we can center it.
      //
      auto tw = font.get_text_width("Hello, world!");

      auto text_width = (tw.width * 14) / 1000;
      auto capheight = (font.get_capheight() * 14) / 1000;

      double cx = (width / 2) - (text_width / 2);
      double cy = (height / 2) - (capheight / 2);

      {
        Canvas::Begin_text bt{canvas};

        bt.move_text_pos(cx, cy);
        bt.show_text("Hello, world!");
      }

      {
        Canvas::Path path{canvas, Canvas::Path::Paint_mode::stroke};

        // Draw borders around the text.
        //
        path.move_to(cx - 10, cy - 10);
        path.line_to(cx - 10, cy + capheight + 10);
        path.line_to(cx + text_width + 10, cy + capheight + 10);
        path.line_to(cx + text_width + 10, cy - 10);
      }
    }

    document.flush();
  }
  catch (exception const& ex) {
    cerr << argv[0] << ": error: " << ex.what() << '\n';
  }
  catch (int u) {
    cerr << argv[0] << ": " << u << '\n';
  }
  catch (...) {
    cerr << argv[0] << ": an unknown error occurred\n";
  }

  return 0;
}

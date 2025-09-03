#include <art/paperback/internals/graphics-state.hxx>

namespace Art::Paperback::Internals
{

  Matrix
  apply(Matrix const& ctm, Matrix const& cm)
  {
    return Matrix{
      cm.a * ctm.a + cm.c * ctm.b,
      cm.b * ctm.a + cm.d * ctm.b,
      cm.a * ctm.c + cm.c * ctm.d,
      cm.b * ctm.c + cm.d * ctm.d,
      cm.a * ctm.e + cm.c * ctm.f + cm.e,
      cm.b * ctm.e + cm.d * ctm.f + cm.f
    };
  }

} // namespace Art::Paperback::Internals

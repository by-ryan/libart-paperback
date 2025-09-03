#include <art/paperback/carousel/object.hxx>
#include <art/paperback/carousel/text.hxx>

#include <art/validation/main.hxx>

using namespace Art::Paperback;
using namespace Art::Paperback::Carousel;

// Test the identity of two objects.
//
VALIDATION_TEST(identity)
{
  Object object0{Text{"initial"}};

  VALIDATION_ASSERT_EQUAL(
    *object_cast<Text>(object0),
    "initial"
  );

  Object object1{object0};

  VALIDATION_ASSERT_EQUAL(
    object_cast<Text>(object0),
    object_cast<Text>(object1)
  );

  object0 = Text{"changed"};

  VALIDATION_ASSERT_EQUAL(
    *object_cast<Text>(object0),
    "changed"
  );

  VALIDATION_ASSERT_EQUAL(
    object_cast<Text>(object0),
    object_cast<Text>(object1)
  );
}

// Ensure changing a cloned object does not change the source object.
//
VALIDATION_TEST(cloning)
{
  Object object0{Text{"initial"}};

  VALIDATION_ASSERT_EQUAL(
    *object_cast<Text>(object0),
    "initial"
  );

  Object object1 = clone(object0);

  VALIDATION_ASSERT_EQUAL(
    object_cast<Text>(object0),
    object_cast<Text>(object1)
  );

  object0 = Text{"changed"};

  VALIDATION_ASSERT_EQUAL(
    *object_cast<Text>(object0),
    "changed"
  );

  VALIDATION_ASSERT_NOT_EQUAL(
    object_cast<Text>(object0),
    object_cast<Text>(object1)
  );
}

int
main(int argc, char* argv[])
{
  return art::validation::main(argc, argv);
}

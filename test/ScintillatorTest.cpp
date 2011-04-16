#include <gtest/gtest.h>
#include "../src/Scintillator.h"

TEST(Scintillator, Constructor) {
  Scintillator* s = new Scintillator(1.1, 2.2, 3.3, 4, 5, 6.2, 7.4, 8.6);
  EXPECT_EQ(1.1, s->getXLength());
  EXPECT_EQ(2.2, s->getYLength());
  EXPECT_EQ(3.3, s->getZLength());
  EXPECT_EQ(4, s->getYMesh());
  EXPECT_EQ(5, s->getZMesh());
  EXPECT_EQ(6.2, s->getXVert());
  EXPECT_EQ(7.4, s->getYVert());
  EXPECT_EQ(8.6, s->getZVert());
}
#include <gtest/gtest.h>
#include "../src/RectangularParallelpiped.h"
#include "../src/MeshRegion.h"

TEST(ScintillatorRectangularParallelpiped, Constructor) {
  RectangularParallelpiped* m = new RectangularParallelpiped(1, 2, 1.1, 1.2, 2.1, 2.2, 3.0, 4.0);
  
  EXPECT_EQ(1, m->getXLocation());
  EXPECT_EQ(2, m->getYLocation());
  EXPECT_EQ(1.1, m->getXMinimum());
  EXPECT_EQ(1.2, m->getXMaximum());
  EXPECT_EQ(2.1, m->getYMinimum());
  EXPECT_EQ(2.2, m->getYMaximum());
  EXPECT_EQ(3.0, m->getHeight());
  EXPECT_EQ(4.0, m->getElevation());
}

TEST(ScintillatorRectangularParallelpiped, toGeo) {
  RectangularParallelpiped* m = new RectangularParallelpiped(1, 2, 1.1, 1.2, 2.1, 2.2, 3.0, 4.0);
  string expected = \
    "'Scint_12' 'ag_rpp10' /\n"
    "1.1, 1.2, 2.1, 2.2, 4.0, 3.0 /\n"
    "'NULL' /" ;

  EXPECT_EQ(expected, m->toGeo());
}
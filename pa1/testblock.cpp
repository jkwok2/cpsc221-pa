// File:        testblock.cpp
// Date:        2020-05-14 23:52
// Description: Catch test cases for Block class

#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

#include <iostream>
#include <algorithm>

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "block.h"

using namespace cs221util;
using namespace std;

TEST_CASE("Block::build-dimensions full PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  HSLAPixel* p = img.getPixel(0, 0);
  p->h = 0; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(1, 0);
  p->h = 90; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(0, 1);
  p->h = 180; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(1, 1);
  p->h = 270; p->s = 1.0; p->l = 0.5;
  
  Block b;
  b.build(img, 0, 2);

  REQUIRE(b.width() == 2);
  REQUIRE(b.height() == 2);
}

TEST_CASE("Block::build-dimensions partial PNG", "[weight=1][part=block]") {

  PNG img(4, 4);

  HSLAPixel* p;
  for (unsigned int y = 0; y < img.height(); y++)
  {
    for (unsigned int x = 0; x < img.width(); x++)
    {
      p = img.getPixel(x, y);
      p->h = (double) 90 * max(x, y); p->s = 1.0; p->l = 0.5;
    }
  }

  Block b;
  b.build(img, 1, 3);

  REQUIRE(b.width() == 3);
  REQUIRE(b.height() == 4);
}

TEST_CASE("Block::build-render full PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  HSLAPixel* p = img.getPixel(0, 0);
  p->h = 0; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(1, 0);
  p->h = 90; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(0, 1);
  p->h = 180; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(1, 1);
  p->h = 270; p->s = 1.0; p->l = 0.5;

  Block b;
  b.build(img, 0, 2);

  PNG outimg(2, 2);
  b.render(outimg, 0);

  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(0, 1);
  HSLAPixel* p3 = outimg.getPixel(1, 1);

  REQUIRE(b.width() == 2);
  REQUIRE(b.height() == 2);
  REQUIRE(p0->h == 0);
  REQUIRE(p1->h == 90);
  REQUIRE(p2->h == 180);
  REQUIRE(p3->h == 270);
}

TEST_CASE("Block::build-render partial PNG", "[weight=1][part=block]") {

  PNG img(4, 4);

  HSLAPixel* p;
  for (unsigned int y = 0; y < img.height(); y++)
  {
    for (unsigned int x = 0; x < img.width(); x++)
    {
      p = img.getPixel(x, y);
      p->h = (double)90 * max(x, y); p->s = 1.0; p->l = 0.5;
    }
  }

  Block b;
  b.build(img, 2, 2);

  PNG outimg(4, 4);
  b.render(outimg, 2);

  REQUIRE(b.width() == 2);
  REQUIRE(b.height() == 4);

  for (unsigned int y = 0; y < img.height(); y++)
  {
    for (unsigned int x = 0; x < 2; x++)
    {
        p = outimg.getPixel(x, y);
        REQUIRE(p->h == 0);
    }
  }

  HSLAPixel* p0 = outimg.getPixel(2, 0);
  HSLAPixel* p1 = outimg.getPixel(3, 0);
  HSLAPixel* p2 = outimg.getPixel(2, 1);
  HSLAPixel* p3 = outimg.getPixel(3, 1);

  HSLAPixel* p0e = img.getPixel(2, 0);
  HSLAPixel* p1e = img.getPixel(3, 0);
  HSLAPixel* p2e = img.getPixel(2, 1);
  HSLAPixel* p3e = img.getPixel(3, 1);

  /**
  * Here we're just comparing the out pixels
  * to the expected ("e") versions of the pixel
  * from the initial image.
  */
  REQUIRE(p0->h == p0e->h);
  REQUIRE(p1->h == p1e->h);
  REQUIRE(p2->h == p2e->h);
  REQUIRE(p3->h == p3e->h);

  p0 = outimg.getPixel(2, 2);
  p1 = outimg.getPixel(3, 2);
  p2 = outimg.getPixel(2, 3);
  p3 = outimg.getPixel(3, 3);

  p0e = img.getPixel(2, 2);
  p1e = img.getPixel(3, 2);
  p2e = img.getPixel(2, 3);
  p3e = img.getPixel(3, 3);

  REQUIRE(p0->h == p0e->h);
  REQUIRE(p1->h == p1e->h);
  REQUIRE(p2->h == p2e->h);
  REQUIRE(p3->h == p3e->h);
}

TEST_CASE("Block::build-pastel full PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  HSLAPixel* p = img.getPixel(0, 0);
  p->h = 0; p->s = 1.0; p->l = 0.5;
  p = img.getPixel(1, 0);
  p->h = 90; p->s = 1.0; p->l = 0.25;
  p = img.getPixel(0, 1);
  p->h = 180; p->s = 0.5; p->l = 0.5;
  p = img.getPixel(1, 1);
  p->h = 270; p->s = 1.0; p->l = 1.0;

  Block b;
  b.build(img, 0, 2);
  b.pastel();

  PNG outimg(2, 2);
  b.render(outimg, 0);

  HSLAPixel* p0 = outimg.getPixel(0, 0);
  HSLAPixel* p1 = outimg.getPixel(1, 0);
  HSLAPixel* p2 = outimg.getPixel(0, 1);
  HSLAPixel* p3 = outimg.getPixel(1, 1);

  REQUIRE(p0->s == 0.5);
  REQUIRE(p0->l == 1.0);
  REQUIRE(p1->s == 0.5);
  REQUIRE(p1->l == 0.5);
  REQUIRE(p2->s == 0.25);
  REQUIRE(p2->l == 1.0);
  REQUIRE(p3->s == 0.5);
  REQUIRE(p3->l == 1.0);
}
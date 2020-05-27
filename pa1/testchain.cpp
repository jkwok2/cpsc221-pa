#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

// headers from PA's main.cpp
#include "chain.h"
#include "block.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

// chain copy constructor
TEST_CASE("chain::basic copy constructor", "[weight=1][part=chain]")
{

    PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin, 18);
    Chain d(c);

    PNG result = d.render(18);

    REQUIRE(result == pngin);
}

// chain copy constructor reverse
TEST_CASE("chain::basic copy constructor reverse", "[weight=1][part=chain]")
{

    PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin, 18);
    Chain d(c);

    PNG result = d.renderBack(18);

    REQUIRE(result == pngin);
}

TEST_CASE("chain::basic even mirror", "[weight=1][part=chain]")
{
    PNG img(2, 1);
    img.getPixel(0, 0)->h = 1;
    img.getPixel(1, 0)->h = 2;

    int cols = 2;
    Chain c(img, cols);
    c.mirror();

    PNG res = c.render(cols);
    HSLAPixel *p0 = res.getPixel(0, 0);
    HSLAPixel *p1 = res.getPixel(1, 0);

    REQUIRE(p0->h == 2);
    REQUIRE(p1->h == 1);
}

TEST_CASE("chain::basic odd mirror", "[weight=1][part=chain]")
{
    int cols = 3;
    PNG img(cols, cols);
    for (int x = 0; x < cols; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            img.getPixel(x, y)->h = x;
        }
    }

    Chain c(img, cols);
    c.mirror();

    PNG res = c.render(cols);

    HSLAPixel *p0 = res.getPixel(0, 0);
    HSLAPixel *p1 = res.getPixel(0, 1);
    HSLAPixel *p2 = res.getPixel(0, 2);
    REQUIRE(p0->h == 2);
    REQUIRE(p1->h == 2);
    REQUIRE(p2->h == 2);

    p0 = res.getPixel(1, 0);
    p1 = res.getPixel(1, 1);
    p2 = res.getPixel(1, 2);
    REQUIRE(p0->h == 1);
    REQUIRE(p1->h == 1);
    REQUIRE(p2->h == 1);

    p0 = res.getPixel(2, 0);
    p1 = res.getPixel(2, 1);
    p2 = res.getPixel(2, 2);
    REQUIRE(p0->h == 0);
    REQUIRE(p1->h == 0);
    REQUIRE(p2->h == 0);
}

TEST_CASE("chain::large odd mirror", "[weight=1][part=chain]")
{
    int cols = 9;
    PNG img(cols, cols);
    for (int x = 0; x < cols; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            img.getPixel(x, y)->h = x;
        }
    }

    Chain c(img, cols);
    c.mirror();

    PNG res = c.render(cols);
    for (int x = 0; x < cols; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            int hVal = cols - 1 - x;
            HSLAPixel *pr = res.getPixel(x, y);
            REQUIRE(pr->h == hVal);
        }
    }
}

TEST_CASE("chain::basic rotate k = 0", "[weight=1][part=chain]")
{
    int cols = 2;
    PNG img(cols, 1);
    img.getPixel(0, 0)->h = 1;
    img.getPixel(1, 0)->h = 2;

    Chain c(img, cols);
    c.rotate(0);

    PNG res = c.render(cols);
    HSLAPixel *p0 = res.getPixel(0, 0);
    HSLAPixel *p1 = res.getPixel(1, 0);

    REQUIRE(p0->h == 1);
    REQUIRE(p1->h == 2);
}

TEST_CASE("chain::basic rotate k = 1", "[weight=1][part=chain]")
{
    int cols = 2;
    PNG img(cols, 1);
    img.getPixel(0, 0)->h = 1;
    img.getPixel(1, 0)->h = 2;

    Chain c(img, cols);
    c.rotate(1);

    PNG res = c.render(cols);
    HSLAPixel *p0 = res.getPixel(0, 0);
    HSLAPixel *p1 = res.getPixel(1, 0);

    REQUIRE(p0->h == 2);
    REQUIRE(p1->h == 1);
}

TEST_CASE("chain::long rotate k = 1", "[weight=1][part=chain]")
{
    int cols = 5;
    PNG img(cols, 1);
    img.getPixel(0, 0)->h = 0;
    img.getPixel(1, 0)->h = 1;
    img.getPixel(2, 0)->h = 2;
    img.getPixel(3, 0)->h = 3;
    img.getPixel(4, 0)->h = 4;

    Chain c(img, cols);
    c.rotate(1);

    PNG res = c.render(cols);
    HSLAPixel *p0 = res.getPixel(0, 0);
    HSLAPixel *p1 = res.getPixel(1, 0);
    HSLAPixel *p2 = res.getPixel(2, 0);
    HSLAPixel *p3 = res.getPixel(3, 0);
    HSLAPixel *p4 = res.getPixel(4, 0);

    REQUIRE(p0->h == 1);
    REQUIRE(p1->h == 2);
    REQUIRE(p2->h == 3);
    REQUIRE(p3->h == 4);
    REQUIRE(p4->h == 0);
}

TEST_CASE("chain::basic rotate k = 2", "[weight=1][part=chain]")
{
    int cols = 5;
    PNG img(cols, 1);
    img.getPixel(0, 0)->h = 0;
    img.getPixel(1, 0)->h = 1;
    img.getPixel(2, 0)->h = 2;
    img.getPixel(3, 0)->h = 3;
    img.getPixel(4, 0)->h = 4;

    Chain c(img, cols);
    c.rotate(2);

    PNG res = c.render(cols);
    HSLAPixel *p0 = res.getPixel(0, 0);
    HSLAPixel *p1 = res.getPixel(1, 0);
    HSLAPixel *p2 = res.getPixel(2, 0);
    HSLAPixel *p3 = res.getPixel(3, 0);
    HSLAPixel *p4 = res.getPixel(4, 0);

    REQUIRE(p0->h == 2);
    REQUIRE(p1->h == 1);
    REQUIRE(p2->h == 4);
    REQUIRE(p3->h == 3);
    REQUIRE(p4->h == 0);
}

TEST_CASE("chain::wrapping rotate k = 3", "[weight=1][part=chain]")
{
    int cols = 5;
    PNG img(cols, 1);
    img.getPixel(0, 0)->h = 0;
    img.getPixel(1, 0)->h = 1;
    img.getPixel(2, 0)->h = 2;
    img.getPixel(3, 0)->h = 3;
    img.getPixel(4, 0)->h = 4;

    Chain c(img, cols);
    c.rotate(3);

    PNG res = c.render(cols);
    HSLAPixel *p0 = res.getPixel(0, 0);
    HSLAPixel *p1 = res.getPixel(1, 0);
    HSLAPixel *p2 = res.getPixel(2, 0);
    HSLAPixel *p3 = res.getPixel(3, 0);
    HSLAPixel *p4 = res.getPixel(4, 0);

    REQUIRE(p0->h == 3);
    REQUIRE(p1->h == 4);
    REQUIRE(p2->h == 2);
    REQUIRE(p3->h == 1);
    REQUIRE(p4->h == 0);
}

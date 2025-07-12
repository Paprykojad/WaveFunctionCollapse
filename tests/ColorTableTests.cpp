#include <doctest.hpp>

#include <aliases.hpp>
#include <raylib.h>

#include <algorithm/ColorTable.hpp>

#include <iostream>
using std::cout;
using std::endl;

class ColorTableFixture {
public:
    Color** colors;

    ColorTableFixture() {

        Color c1[] = {
            (Color){1, 1, 1, 1},
            (Color){2, 2, 2, 2},
            (Color){3, 3, 3, 3},
        };

        Color c2[] = {
            (Color){1, 2, 3, 4},
            (Color){2, 3, 4, 5},
            (Color){3, 4, 5, 6},
        };

        colors = new Color*[2];
        colors[0] = c1;
        colors[1] = c2;
    }
};

TEST_SUITE("Color table tests") {
    TEST_CASE("Testing constructor 1") {
        ColorTable c(3, 4);
        CHECK(c.width == 3);
        CHECK(c.height == 4);

        CHECK(c.data != nullptr);
        for range(i, c.height) {
            CHECK(c.data[i] != nullptr);
        }


        ColorTable c1(5, 4);
        CHECK(c1.width == 5);
        CHECK(c1.height == 4);

        CHECK(c1.data != nullptr);
        for range(i, c1.height) {
            CHECK(c1.data[i] != nullptr);
        }
    }

    TEST_CASE_FIXTURE(ColorTableFixture, "Testing constructor 2") {
        ColorTable c(3, 2, colors);

        for range(y, c.height) {
            for range(x, c.width) {

                Color col1 = c.Get(y, x);
                Color col2 = colors[y][x];
                cout << col1.r << col2.r;

                CHECK(c.Get(y, x) == colors[y][x]);
            }
        }
        CHECK(true);
    }

    TEST_CASE_FIXTURE(ColorTableFixture, "Testing GetData") {
        ColorTable c(3, 2);

        for range(y, 2) {
            for range(x, 3) {
                c.Set(y, x, (Color){1,1,1,1});
            }
        }

        for range(y, 2) {
            for range(x, 3) {
                CHECK(c.Get(y, x) == (Color){1,1,1,1});
            }
        }

        c.GetData(colors);

        for range(y, 2) {
            for range(x, 3) {
                auto col1 = colors[y][x];
                auto col2 = c.Get(y, x);
                cout << col1.r + col2.r;
                CHECK(c.Get(y, x) == colors[y][x]);
            }
        }

    }

    TEST_CASE_FIXTURE(ColorTableFixture, "Testing constructor 3") {

    }

    TEST_CASE_FIXTURE(ColorTableFixture, "Testing CopyTable") {
        ColorTable c(3, 2);

        for range(y, 2) {
            for range(x, 3) {
                c.Set(y, x, (Color){1,1,1,1});
            }
        }

        for range(y, 2) {
            for range(x, 3) {
                CHECK(c.Get(y, x) == (Color){1,1,1,1});
            }
        }

        ColorTable c2(3, 2, colors);

        ColorTable c3(2, 2, colors);
        CHECK_THROWS(c3.CopyTable(&c));
        CHECK_THROWS(c.CopyTable(&c3));

        CHECK_NOTHROW(c2.CopyTable(&c));


        for range(y, 2) {
            for range(x, 3) {
                CHECK(c.Get(y, x) == c2.Get(y, x));
            }
        }
    }

}

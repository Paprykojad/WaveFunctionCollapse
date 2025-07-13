#include <doctest.hpp>

#include <aliases.hpp>

#include <algorithm/ColorTable.hpp>
#include <algorithm/Color.hpp>

#include <iostream>
using std::cout;
using std::endl;

class ColorTableFixture {
public:
    Color** colors;

    ColorTableFixture() {
        Color* c1 = new Color[]{
            (Color){1, 1, 1, 1},
            (Color){2, 2, 2, 2},
            (Color){3, 3, 3, 3},
        };

        Color* c2 = new Color[]{
            (Color){1, 2, 3, 4},
            (Color){2, 3, 4, 5},
            (Color){3, 4, 5, 6},
        };

        colors = new Color*[2];
        colors[0] = c1;
        colors[1] = c2;
    }

    ~ColorTableFixture() {
        free(colors[0]);
        free(colors[1]);
        free(colors);
    }
};

void print(u32 y, u32 x, Color** ptr) {
    for range(y, 2) {
        for range(x, 3) {
            cout << (u32)ptr[y][x].r << (u32)ptr[y][x].g << (u32)ptr[y][x].b << (u32)ptr[y][x].a << ", ";
        }
        cout << "\n";
    }
}

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
                c.Set(y, x, (Color){1, 1, 1, 1});
            }
        }

        for range(y, 2) {
            for range(x, 3) {
                CHECK(c.Get(y, x) == (Color){1, 1, 1, 1});
            }
        }

        // print(2, 3, c.data);
        // cout << "\n";
        // print(2, 3, colors);


        c.GetData(colors);

        // cout << "\n";
        // cout << "\n";
        // print(2, 3, c.data);
        // cout << "\n";
        // print(2, 3, colors);
        // cout << "\n";

        for range(y, 2) {
            for range(x, 3) {
                auto col1 = colors[y][x];
                auto col2 = c.Get(y, x);

                CHECK(col1 == col2);
            }
        }
    }

    TEST_CASE_FIXTURE(ColorTableFixture, "Testing constructor 3") {
        ColorTable c(3, 2, colors);

        bool caught = false;
        try {
            ColorTable c1(nullptr);
        } catch (const std::exception& e) {
            caught = true;
        }

        if (!caught) {
            CHECK(false);
        }

        ColorTable c2(&c);
        CHECK_EQ(c.width, c2.width);
        CHECK_EQ(c.height, c2.height);

        for range(y, c.height) {
            for range(x, c.width) {
                CHECK_EQ(c.Get(y, x), c2.Get(y, x));
            }
        }

    }

    TEST_CASE_FIXTURE(ColorTableFixture, "Testing CopyTable") {
        ColorTable c(3, 2);

        for range(y, 2) {
            for range(x, 3) {
                c.Set(y, x, (Color){1, 1, 1, 1});
            }
        }

        for range(y, 2) {
            for range(x, 3) {
                CHECK(c.Get(y, x) == (Color){1, 1, 1, 1});
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

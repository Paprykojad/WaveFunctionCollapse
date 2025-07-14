#include <doctest.hpp>
#include <iostream>
#include <stdexcept>
#include <algorithm/Color.hpp>

#include "algorithm/ColorTable.hpp"
#include "algorithm/Learner.hpp"

class LearnerFixture {
public:
    Color** colors0;
    Color** colors;
    Color** colors2;
    Color** colors3;
    Color** colors4;

    Color* cols;


    LearnerFixture() {
        cols = new Color[]{
            (Color){80, 80, 80, 255},
            (Color){200, 100, 100, 255},
            (Color){140, 140, 140, 255},

            (Color){10, 20, 30, 255},
            (Color){20, 30, 40, 255},
            (Color){30, 40, 50, 255},

            (Color){160, 160, 160, 255},
            (Color){100, 50, 50, 255},
            (Color){100, 50, 50, 255},
        };

        Color* c1 = new Color[]{
            (Color){80, 80, 80, 255},
            (Color){200, 100, 100, 255},
            (Color){140, 140, 140, 255},
        };

        Color* c2 = new Color[]{
            (Color){10, 20, 30, 255},
            (Color){20, 30, 40, 255},
            (Color){30, 40, 50, 255},
        };

        Color* c3 = new Color[]{
            (Color){160, 160, 160, 255},
            (Color){100, 50, 50, 255},
            (Color){100, 50, 50, 255},
        };

        colors0 = new Color*[1];
        colors0[0] = c1;

        colors = new Color*[2];
        colors[0] = c1;
        colors[1] = c2;

        colors2 = new Color*[2];
        colors2[0] = c1;
        colors2[1] = c1;

        colors3 = new Color*[3];
        colors3[0] = c1;
        colors3[1] = c1;
        colors3[2] = c2;

        colors4 = new Color*[2];
        colors4[0] = c1;
        colors4[1] = c3;
    }

    ~LearnerFixture() {
        free(colors[0]);
        free(colors[1]);
        free(colors);
    }
};

void t() {
    Learner l(nullptr);
}

TEST_SUITE("Learner tests") {
    TEST_CASE_FIXTURE(LearnerFixture, "Testing constructor") {
        ColorTable ct(3, 2, colors);

        Learner l(&ct);
        CHECK_EQ(ct, l.data);
    }

    TEST_CASE_FIXTURE(LearnerFixture, "Testing with null pointer") {
        CHECK_THROWS(t());
    }

    TEST_CASE_FIXTURE(LearnerFixture, "Testing amount of colors detected") {
        ColorTable ct(3, 2, colors);
        Learner l(&ct);

        ColorTable ct2(3, 2, colors2);
        Learner l2(&ct2);

        ColorTable ct3(3, 3, colors3);
        Learner l3(&ct3);

        CHECK(l.coloredPixelsCount.size() == 6);

        for (auto pair : l.coloredPixelsCount) {
            CHECK(pair.second == 1);
        }

        CHECK(l2.coloredPixelsCount.size() == 3);

        for (auto pair : l2.coloredPixelsCount) {
            CHECK(pair.second == 2);
        }

        CHECK(l3.coloredPixelsCount.size() == 6);

        for (auto pair : l3.coloredPixelsCount) {
            if (pair.first == colors[0][0])
                CHECK(pair.second == 2);
            if (pair.first == colors[0][1])
                CHECK(pair.second == 2);
            if (pair.first == colors[0][2])
                CHECK(pair.second == 2);
            if (pair.first == colors[1][0])
                CHECK(pair.second == 1);
            if (pair.first == colors[1][1])
                CHECK(pair.second == 1);
            if (pair.first == colors[1][2])
                CHECK(pair.second == 1);
        }
    }

    TEST_CASE_FIXTURE(LearnerFixture, "Testing colorCounts setting function (in constructor)") {
        ColorTable ct(3, 1, colors4);
        Learner l(&ct);

        {
            CHECK(l.colorCounts[cols[0]].direction[Top].size() == 0);
            CHECK(l.colorCounts[cols[0]].direction[Right].size() == 1);
            CHECK(l.colorCounts[cols[0]].direction[Bottom].size() == 0);
            CHECK(l.colorCounts[cols[0]].direction[Left].size() == 0);

            CHECK(l.colorCounts[cols[0]].direction[Right][cols[1]] == 1);
        }

        {
            CHECK(l.colorCounts[cols[1]].direction[Top].size() == 0);
            CHECK(l.colorCounts[cols[1]].direction[Right].size() == 1);
            CHECK(l.colorCounts[cols[1]].direction[Bottom].size() == 0);
            CHECK(l.colorCounts[cols[1]].direction[Left].size() == 1);

            CHECK(l.colorCounts[cols[1]].direction[Right][cols[2]] == 1);
            CHECK(l.colorCounts[cols[1]].direction[Left][cols[0]] == 1);
        }

        {
            CHECK(l.colorCounts[cols[2]].direction[Top].size() == 0);
            CHECK(l.colorCounts[cols[2]].direction[Right].size() == 0);
            CHECK(l.colorCounts[cols[2]].direction[Bottom].size() == 0);
            CHECK(l.colorCounts[cols[2]].direction[Left].size() == 1);

            CHECK(l.colorCounts[cols[2]].direction[Left][cols[1]] == 1);
        }



    }
}

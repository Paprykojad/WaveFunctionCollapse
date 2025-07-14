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
        Color** colors5; // Added for larger test cases
        Color** colors6; // Added for larger test cases

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

            // c1 corresponds to cols[0] to cols[2]
            // c2 corresponds to cols[3] to cols[5]
            // c3 corresponds to cols[6] to cols[8]

            colors0 = new Color*[1];
            colors0[0] = &cols[0]; // Used to be c1

            colors = new Color*[2];
            colors[0] = &cols[0]; // Used to be c1
            colors[1] = &cols[3]; // Used to be c2

            colors2 = new Color*[2];
            colors2[0] = &cols[0]; // Used to be c1
            colors2[1] = &cols[0]; // Used to be c1

            colors3 = new Color*[3];
            colors3[0] = &cols[0]; // Used to be c1
            colors3[1] = &cols[0]; // Used to be c1
            colors3[2] = &cols[3]; // Used to be c2

            colors4 = new Color*[2];
            colors4[0] = &cols[0]; // Used to be c1
            colors4[1] = &cols[6]; // Used to be c3

            // Define colors5 for a 4x4 grid (16 pixels)
            // Pattern:
            // cols[0] cols[1] cols[0] cols[1]
            // cols[3] cols[4] cols[3] cols[4]
            // cols[0] cols[1] cols[0] cols[1]
            // cols[3] cols[4] cols[3] cols[4]
            colors5 = new Color*[4];
            colors5[0] = new Color[4]{cols[0], cols[1], cols[0], cols[1]};
            colors5[1] = new Color[4]{cols[3], cols[4], cols[3], cols[4]};
            colors5[2] = new Color[4]{cols[0], cols[1], cols[0], cols[1]};
            colors5[3] = new Color[4]{cols[3], cols[4], cols[3], cols[4]};

            // Define colors6 for a 3x3 grid (9 pixels) with alternating pattern
            // Pattern:
            // cols[0] cols[1] cols[0]
            // cols[1] cols[0] cols[1]
            // cols[0] cols[1] cols[0]
            colors6 = new Color*[3];
            colors6[0] = new Color[3]{cols[0], cols[1], cols[0]};
            colors6[1] = new Color[3]{cols[1], cols[0], cols[1]};
            colors6[2] = new Color[3]{cols[0], cols[1], cols[0]};
        }

        ~LearnerFixture() {
            delete[] colors0;
            delete[] colors;
            delete[] colors2;
            delete[] colors3;
            delete[] colors4;

            // Clean up colors5
            delete[] colors5[0];
            delete[] colors5[1];
            delete[] colors5[2];
            delete[] colors5[3];
            delete[] colors5;

            // Clean up colors6
            delete[] colors6[0];
            delete[] colors6[1];
            delete[] colors6[2];
            delete[] colors6;

            delete[] cols;
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

    TEST_CASE_FIXTURE(LearnerFixture, "Testing selectColor boundary checks") {
        ColorTable ct(3, 2, colors); // 3 wide, 2 high (colors is c1 followed by c2)
        Learner l(&ct);

        // Valid access
        CHECK(l.selectColor(0, 0) == colors[0][0]);
        CHECK(l.selectColor(1, 2) == colors[1][2]); // Bottom-right pixel

        // Invalid Y coordinates
        CHECK_THROWS_AS(l.selectColor(ct.height, 0), std::invalid_argument);
        CHECK_THROWS_AS(l.selectColor(ct.height + 5, 0), std::invalid_argument);
        CHECK_THROWS_AS(l.selectColor(-1, 0), std::invalid_argument); // Negative Y

        // Invalid X coordinates
        CHECK_THROWS_AS(l.selectColor(0, ct.width), std::invalid_argument);
        CHECK_THROWS_AS(l.selectColor(0, ct.width + 5), std::invalid_argument);
        CHECK_THROWS_AS(l.selectColor(0, -1), std::invalid_argument); // Negative X

        // Both invalid
        CHECK_THROWS_AS(l.selectColor(ct.height, ct.width), std::invalid_argument);
        CHECK_THROWS_AS(l.selectColor(-1, -1), std::invalid_argument);
    }

    TEST_CASE_FIXTURE(LearnerFixture, "Testing colorCounts for top-left corner pixel") {
        ColorTable ct(3, 2, colors); // 3 wide, 2 high
        Learner l(&ct);

        Color topLeftColor = colors[0][0]; // Pixel at (0,0) in the grid
        Color actualRightNeighbor = colors[0][1]; // Pixel at (0,1)
        Color actualBottomNeighbor = colors[1][0]; // Pixel at (1,0)

        // Learner's `direction[Top]` stores actual BOTTOM neighbors
        CHECK(l.colorCounts[topLeftColor].direction[Top].size() == 1);
        CHECK(l.colorCounts[topLeftColor].direction[Top][actualBottomNeighbor] == 1);

        // Learner's `direction[Right]` stores actual RIGHT neighbors
        CHECK(l.colorCounts[topLeftColor].direction[Right].size() == 1);
        CHECK(l.colorCounts[topLeftColor].direction[Right][actualRightNeighbor] == 1);

        // No actual TOP neighbor, Learner's `direction[Bottom]` should be empty
        CHECK(l.colorCounts[topLeftColor].direction[Bottom].empty());
        // No actual LEFT neighbor, Learner's `direction[Left]` should be empty
        CHECK(l.colorCounts[topLeftColor].direction[Left].empty());
    }

    TEST_CASE_FIXTURE(LearnerFixture, "Testing colorCounts for top-right corner pixel") {
        ColorTable ct(3, 2, colors); // 3 wide, 2 high
        Learner l(&ct);

        Color topRightColor = colors[0][2]; // Pixel at (0,2) in the grid
        Color actualLeftNeighbor = colors[0][1]; // Pixel at (0,1)
        Color actualBottomNeighbor = colors[1][2]; // Pixel at (1,2)

        // Learner's `direction[Top]` stores actual BOTTOM neighbors
        CHECK(l.colorCounts[topRightColor].direction[Top].size() == 1);
        CHECK(l.colorCounts[topRightColor].direction[Top][actualBottomNeighbor] == 1);

        // No actual RIGHT neighbor, Learner's `direction[Right]` should be empty
        CHECK(l.colorCounts[topRightColor].direction[Right].empty());

        // No actual TOP neighbor, Learner's `direction[Bottom]` should be empty
        CHECK(l.colorCounts[topRightColor].direction[Bottom].empty());

        // Learner's `direction[Left]` stores actual LEFT neighbors
        CHECK(l.colorCounts[topRightColor].direction[Left].size() == 1);
        CHECK(l.colorCounts[topRightColor].direction[Left][actualLeftNeighbor] == 1);
    }

    TEST_CASE_FIXTURE(LearnerFixture, "Testing colorCounts for bottom-left corner pixel") {
        ColorTable ct(3, 2, colors); // 3 wide, 2 high
        Learner l(&ct);

        Color bottomLeftColor = colors[1][0]; // Pixel at (1,0) in the grid
        Color actualTopNeighbor = colors[0][0]; // Pixel at (0,0)
        Color actualRightNeighbor = colors[1][1]; // Pixel at (1,1)

        // No actual BOTTOM neighbor, Learner's `direction[Top]` should be empty
        CHECK(l.colorCounts[bottomLeftColor].direction[Top].empty());

        // Learner's `direction[Right]` stores actual RIGHT neighbors
        CHECK(l.colorCounts[bottomLeftColor].direction[Right].size() == 1);
        CHECK(l.colorCounts[bottomLeftColor].direction[Right][actualRightNeighbor] == 1);

        // Learner's `direction[Bottom]` stores actual TOP neighbors
        CHECK(l.colorCounts[bottomLeftColor].direction[Bottom].size() == 1);
        CHECK(l.colorCounts[bottomLeftColor].direction[Bottom][actualTopNeighbor] == 1);

        // No actual LEFT neighbor, Learner's `direction[Left]` should be empty
        CHECK(l.colorCounts[bottomLeftColor].direction[Left].empty());
    }

    TEST_CASE_FIXTURE(LearnerFixture, "Testing colorCounts for bottom-right corner pixel") {
        ColorTable ct(3, 2, colors); // 3 wide, 2 high
        Learner l(&ct);

        Color bottomRightColor = colors[1][2]; // Pixel at (1,2) in the grid
        Color actualTopNeighbor = colors[0][2]; // Pixel at (0,2)
        Color actualLeftNeighbor = colors[1][1]; // Pixel at (1,1)

        // No actual BOTTOM neighbor, Learner's `direction[Top]` should be empty
        CHECK(l.colorCounts[bottomRightColor].direction[Top].empty());

        // No actual RIGHT neighbor, Learner's `direction[Right]` should be empty
        CHECK(l.colorCounts[bottomRightColor].direction[Right].empty());

        // Learner's `direction[Bottom]` stores actual TOP neighbors
        CHECK(l.colorCounts[bottomRightColor].direction[Bottom].size() == 1);
        CHECK(l.colorCounts[bottomRightColor].direction[Bottom][actualTopNeighbor] == 1);

        // Learner's `direction[Left]` stores actual LEFT neighbors
        CHECK(l.colorCounts[bottomRightColor].direction[Left].size() == 1);
        CHECK(l.colorCounts[bottomRightColor].direction[Left][actualLeftNeighbor] == 1);
    }

    TEST_CASE_FIXTURE(LearnerFixture, "Testing colorCounts for a middle-row pixel") {
        ColorTable ct(3, 2, colors); // 3 wide, 2 high
        Learner l(&ct);

        Color middleColor = colors[0][1]; // Pixel at (0,1) in the grid
        Color actualLeftNeighbor = colors[0][0]; // Pixel at (0,0)
        Color actualRightNeighbor = colors[0][2]; // Pixel at (0,2)
        Color actualBottomNeighbor = colors[1][1]; // Pixel at (1,1)

        // Learner's `direction[Top]` stores actual BOTTOM neighbors
        CHECK(l.colorCounts[middleColor].direction[Top].size() == 1);
        CHECK(l.colorCounts[middleColor].direction[Top][actualBottomNeighbor] == 1);

        // Learner's `direction[Right]` stores actual RIGHT neighbors
        CHECK(l.colorCounts[middleColor].direction[Right].size() == 1);
        CHECK(l.colorCounts[middleColor].direction[Right][actualRightNeighbor] == 1);

        // No actual TOP neighbor, Learner's `direction[Bottom]` should be empty
        CHECK(l.colorCounts[middleColor].direction[Bottom].empty());

        // Learner's `direction[Left]` stores actual LEFT neighbors
        CHECK(l.colorCounts[middleColor].direction[Left].size() == 1);
        CHECK(l.colorCounts[middleColor].direction[Left][actualLeftNeighbor] == 1);
    }

    TEST_CASE_FIXTURE(LearnerFixture, "Testing colorCounts with duplicate colors and complex relationships") {
        ColorTable ct(3, 3, colors3); // 3 wide, 3 high (first two rows are c1, last row is c2)
        Learner l(&ct);

        // Aliases for specific colors from the 'cols' array for clarity
        Color color_80_80_80 = cols[0];   // c1[0]
        Color color_200_100_100 = cols[1]; // c1[1]
        Color color_140_140_140 = cols[2]; // c1[2]
        Color color_10_20_30 = cols[3];   // c2[0]
        Color color_20_30_40 = cols[4];   // c2[1]

        // --- Test for color_80_80_80 (cols[0]), appearing at (0,0) and (1,0) ---
        // (0,0) has Right neighbor (0,1) = c1[1]; Bottom neighbor (1,0) = c1[0]
        // (1,0) has Right neighbor (1,1) = c1[1]; Top neighbor (0,0) = c1[0]; Bottom neighbor (2,0) = c2[0]

        // Actual Right Neighbors: (0,1) = c1[1] for (0,0); (1,1) = c1[1] for (1,0)
        CHECK(l.colorCounts[color_80_80_80].direction[Right].size() == 1);
        CHECK(l.colorCounts[color_80_80_80].direction[Right][color_200_100_100] == 2);

        // Actual Bottom Neighbors: (1,0) = c1[0] for (0,0); (2,0) = c2[0] for (1,0)
        // Stored in `direction[Top]` due to Learner's mapping
        CHECK(l.colorCounts[color_80_80_80].direction[Top].size() == 2);
        CHECK(l.colorCounts[color_80_80_80].direction[Top][color_80_80_80] == 1); // From (0,0) to (1,0)
        CHECK(l.colorCounts[color_80_80_80].direction[Top][color_10_20_30] == 1); // From (1,0) to (2,0)

        // Actual Top Neighbors: (0,0) = c1[0] for (1,0)
        // Stored in `direction[Bottom]` due to Learner's mapping
        CHECK(l.colorCounts[color_80_80_80].direction[Bottom].size() == 1);
        CHECK(l.colorCounts[color_80_80_80].direction[Bottom][color_80_80_80] == 1); // From (1,0) to (0,0)

        // Actual Left Neighbors: None for (0,0) or (1,0)
        CHECK(l.colorCounts[color_80_80_80].direction[Left].empty());

        // --- Test for color_200_100_100 (cols[1]), appearing at (0,1) and (1,1) ---
        // (0,1) has Left=(0,0)=c1[0]; Right=(0,2)=c1[2]; Bottom=(1,1)=c1[1]
        // (1,1) has Left=(1,0)=c1[0]; Right=(1,2)=c1[2]; Top=(0,1)=c1[1]; Bottom=(2,1)=c2[1]

        // Actual Left Neighbors: (0,0)=c1[0] for (0,1); (1,0)=c1[0] for (1,1)
        CHECK(l.colorCounts[color_200_100_100].direction[Left].size() == 1);
        CHECK(l.colorCounts[color_200_100_100].direction[Left][color_80_80_80] == 2);

        // Actual Right Neighbors: (0,2)=c1[2] for (0,1); (1,2)=c1[2] for (1,1)
        CHECK(l.colorCounts[color_200_100_100].direction[Right].size() == 1);
        CHECK(l.colorCounts[color_200_100_100].direction[Right][color_140_140_140] == 2);

        // Actual Bottom Neighbors: (1,1)=c1[1] for (0,1); (2,1)=c2[1] for (1,1)
        // Stored in `direction[Top]`
        CHECK(l.colorCounts[color_200_100_100].direction[Top].size() == 2);
        CHECK(l.colorCounts[color_200_100_100].direction[Top][color_200_100_100] == 1); // From (0,1) to (1,1)
        CHECK(l.colorCounts[color_200_100_100].direction[Top][color_20_30_40] == 1); // From (1,1) to (2,1)

        // Actual Top Neighbors: (0,1)=c1[1] for (1,1)
        // Stored in `direction[Bottom]`
        CHECK(l.colorCounts[color_200_100_100].direction[Bottom].size() == 1);
        CHECK(l.colorCounts[color_200_100_100].direction[Bottom][color_200_100_100] == 1); // From (1,1) to (0,1)
    }

    TEST_CASE_FIXTURE(LearnerFixture, "Testing colorCounts with a 4x4 repeating pattern") {
    ColorTable ct(4, 4, colors5); // 4 wide, 4 high
    Learner l(&ct);

    Color color_80_80_80 = cols[0];   // Top-left block color
    Color color_200_100_100 = cols[1]; // Its right neighbor
    Color color_10_20_30 = cols[3];   // Its bottom neighbor
    Color color_20_30_40 = cols[4];   // Diagonal neighbor from top-left block

    // Test for color_80_80_80 (cols[0])
    // Appears at (0,0), (0,2), (2,0), (2,2) - 4 instances
    {
        // Right neighbor is always cols[1]
        CHECK(l.colorCounts[color_80_80_80].direction[Right].size() == 1);
        CHECK(l.colorCounts[color_80_80_80].direction[Right][color_200_100_100] == 4);

        // Bottom neighbor (stored in direction[Top]) is always cols[3]
        CHECK(l.colorCounts[color_80_80_80].direction[Top].size() == 1);
        CHECK(l.colorCounts[color_80_80_80].direction[Top][color_10_20_30] == 4);

        // Left neighbor is cols[1] for instances at (0,2) and (2,2)
        CHECK(l.colorCounts[color_80_80_80].direction[Left].size() == 1);
        CHECK(l.colorCounts[color_80_80_80].direction[Left][color_200_100_100] == 2);

        // Top neighbor (stored in direction[Bottom]) is cols[3] for instances at (2,0) and (2,2)
        CHECK(l.colorCounts[color_80_80_80].direction[Bottom].size() == 1);
        CHECK(l.colorCounts[color_80_80_80].direction[Bottom][color_10_20_30] == 2);
    }

    // Test for color_200_100_100 (cols[1])
    // Appears at (0,1), (0,3), (2,1), (2,3) - 4 instances
    {
        // Left neighbor is always cols[0]
        CHECK(l.colorCounts[color_200_100_100].direction[Left].size() == 1);
        CHECK(l.colorCounts[color_200_100_100].direction[Left][color_80_80_80] == 4);

        // Bottom neighbor (stored in direction[Top]) is always cols[4]
        CHECK(l.colorCounts[color_200_100_100].direction[Top].size() == 1);
        CHECK(l.colorCounts[color_200_100_100].direction[Top][color_20_30_40] == 4);

        // Right neighbor is cols[0] for instances at (0,1) and (2,1)
        CHECK(l.colorCounts[color_200_100_100].direction[Right].size() == 1);
        CHECK(l.colorCounts[color_200_100_100].direction[Right][color_80_80_80] == 2);

        // Top neighbor (stored in direction[Bottom]) is cols[4] for instances at (2,1) and (2,3)
        CHECK(l.colorCounts[color_200_100_100].direction[Bottom].size() == 1);
        CHECK(l.colorCounts[color_200_100_100].direction[Bottom][color_20_30_40] == 2);
    }

    // Test for color_10_20_30 (cols[3])
    // Appears at (1,0), (1,2), (3,0), (3,2) - 4 instances
    {
        // Top neighbor (stored in direction[Bottom]) is always cols[0]
        CHECK(l.colorCounts[color_10_20_30].direction[Bottom].size() == 1);
        CHECK(l.colorCounts[color_10_20_30].direction[Bottom][color_80_80_80] == 4);

        // Right neighbor is always cols[4]
        CHECK(l.colorCounts[color_10_20_30].direction[Right].size() == 1);
        CHECK(l.colorCounts[color_10_20_30].direction[Right][color_20_30_40] == 4);

        // Left neighbor is cols[4] for instances at (1,2) and (3,2)
        CHECK(l.colorCounts[color_10_20_30].direction[Left].size() == 1);
        CHECK(l.colorCounts[color_10_20_30].direction[Left][color_20_30_40] == 2);

        // Bottom neighbor (stored in direction[Top]) is cols[0] for instances at (1,0) and (1,2)
        CHECK(l.colorCounts[color_10_20_30].direction[Top].size() == 1);
        CHECK(l.colorCounts[color_10_20_30].direction[Top][color_80_80_80] == 2);
    }

    // Test for color_20_30_40 (cols[4])
    // Appears at (1,1), (1,3), (3,1), (3,3) - 4 instances
    {
        // Left neighbor is always cols[3]
        CHECK(l.colorCounts[color_20_30_40].direction[Left].size() == 1);
        CHECK(l.colorCounts[color_20_30_40].direction[Left][color_10_20_30] == 4);

        // Top neighbor (stored in direction[Bottom]) is always cols[1]
        CHECK(l.colorCounts[color_20_30_40].direction[Bottom].size() == 1);
        CHECK(l.colorCounts[color_20_30_40].direction[Bottom][color_200_100_100] == 4);

        // Right neighbor is cols[3] for instances at (1,1) and (3,1)
        CHECK(l.colorCounts[color_20_30_40].direction[Right].size() == 1);
        CHECK(l.colorCounts[color_20_30_40].direction[Right][color_10_20_30] == 2);

        // Bottom neighbor (stored in direction[Top]) is cols[1] for instances at (1,1) and (1,3)
        CHECK(l.colorCounts[color_20_30_40].direction[Top].size() == 1);
        CHECK(l.colorCounts[color_20_30_40].direction[Top][color_200_100_100] == 2);
    }
    }

    TEST_CASE_FIXTURE(LearnerFixture, "Testing colorCounts with a 3x3 alternating pattern") {
        ColorTable ct(3, 3, colors6); // 3 wide, 3 high
        Learner l(&ct);

        Color color_80_80_80 = cols[0];   // Center pixel color
        Color color_200_100_100 = cols[1]; // Surrounding pixel color

        // Test for color_80_80_80 (cols[0])
        // Appears at (0,0), (0,2), (1,1), (2,0), (2,2) - 5 instances
        {
            // Right neighbors: (0,1) [cols[1]], (1,2) [cols[1]], (2,1) [cols[1]]
            CHECK(l.colorCounts[color_80_80_80].direction[Right].size() == 1);
            CHECK(l.colorCounts[color_80_80_80].direction[Right][color_200_100_100] == 3);

            // Left neighbors: (0,1) [cols[1]], (1,0) [cols[1]], (2,1) [cols[1]]
            CHECK(l.colorCounts[color_80_80_80].direction[Left].size() == 1);
            CHECK(l.colorCounts[color_80_80_80].direction[Left][color_200_100_100] == 3);

            // Bottom neighbors (stored in direction[Top]):
            // From (0,0) -> (1,0) [cols[1]]
            // From (0,2) -> (1,2) [cols[1]]
            // From (1,1) -> (2,1) [cols[1]]
            CHECK(l.colorCounts[color_80_80_80].direction[Top].size() == 1);
            CHECK(l.colorCounts[color_80_80_80].direction[Top][color_200_100_100] == 3);

            // Top neighbors (stored in direction[Bottom]):
            // From (1,1) -> (0,1) [cols[1]]
            // From (2,0) -> (1,0) [cols[1]]
            // From (2,2) -> (1,2) [cols[1]]
            CHECK(l.colorCounts[color_80_80_80].direction[Bottom].size() == 1);
            CHECK(l.colorCounts[color_80_80_80].direction[Bottom][color_200_100_100] == 3);
        }

        // Test for color_200_100_100 (cols[1])
        // Appears at (0,1), (1,0), (1,2), (2,1) - 4 instances
        {
            // Right neighbors: (0,2) [cols[0]], (1,1) [cols[0]], (2,2) [cols[0]]
            CHECK(l.colorCounts[color_200_100_100].direction[Right].size() == 1);
            CHECK(l.colorCounts[color_200_100_100].direction[Right][color_80_80_80] == 3);

            // Left neighbors: (0,0) [cols[0]], (1,1) [cols[0]], (2,0) [cols[0]]
            CHECK(l.colorCounts[color_200_100_100].direction[Left].size() == 1);
            CHECK(l.colorCounts[color_200_100_100].direction[Left][color_80_80_80] == 3);

            // Bottom neighbors (stored in direction[Top]):
            // From (0,1) -> (1,1) [cols[0]]
            // From (1,0) -> (2,0) [cols[0]]
            // From (1,2) -> (2,2) [cols[0]]
            CHECK(l.colorCounts[color_200_100_100].direction[Top].size() == 1);
            CHECK(l.colorCounts[color_200_100_100].direction[Top][color_80_80_80] == 3);

            // Top neighbors (stored in direction[Bottom]):
            // From (1,0) -> (0,0) [cols[0]]
            // From (1,2) -> (0,2) [cols[0]]
            // From (2,1) -> (1,1) [cols[0]]
            CHECK(l.colorCounts[color_200_100_100].direction[Bottom].size() == 1);
            CHECK(l.colorCounts[color_200_100_100].direction[Bottom][color_80_80_80] == 3);
        }
    }
}

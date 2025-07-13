#include <doctest.hpp>
#include <algorithm/Color.hpp>

#include "algorithm/ColorTable.hpp"
#include "algorithm/Learner.hpp"

class LearnerFixture {
public:
    Color** colors;

    LearnerFixture() {
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

    ~LearnerFixture() {
        free(colors[0]);
        free(colors[1]);
        free(colors);
    }
};

TEST_SUITE("Learner tests") {
    TEST_CASE_FIXTURE(LearnerFixture, "Testing constructor") {
        ColorTable ct(3, 2, colors);

        Learner l(&ct);

        CHECK_EQ(ct, l.data);
    }


}

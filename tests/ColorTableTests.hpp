#pragma once

#include <cmocka.h>

static void t1(void** state) {

}

void ColorTableTests(){
    const struct CMUnitTest ColorTable_tests[] = {
        cmocka_unit_test(t1),
    };

    cmocka_run_group_tests(ColorTable_tests, NULL, NULL);
}

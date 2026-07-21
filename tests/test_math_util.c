#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "types.h"
#include "engine/math_util.h"

// Define the required globals and stubs
Vec3f gVec3fZero = { 0.0f, 0.0f, 0.0f };
Vec3f gVec3fOne = { 1.0f, 1.0f, 1.0f };

// Stub for find_floor
f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    if (pfloor) {
        *pfloor = NULL;
    }
    return yPos;
}

// Stub for guMtxF2L (only called when AVOID_UB is defined and mtxf_to_mtx is used)
void guMtxF2L(Mat4 src, Mtx *dest) {
    // Basic stub, not used in our unit tests directly
}

// Test tracking
static int g_tests_run = 0;
static int g_tests_failed = 0;

#define ASSERT_TRUE(expr, msg) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "FAIL: %s:%d: %s\n", __FILE__, __LINE__, msg); \
            g_tests_failed++; \
            return; \
        } \
    } while (0)

#define ASSERT_FLOAT_EQ(val1, val2, tol, msg) \
    do { \
        if (fabsf((val1) - (val2)) > (tol)) { \
            fprintf(stderr, "FAIL: %s:%d: %s (expected %f, got %f)\n", __FILE__, __LINE__, msg, (double)(val2), (double)(val1)); \
            g_tests_failed++; \
            return; \
        } \
    } while (0)

void test_vec3f_copy(void) {
    g_tests_run++;
    Vec3f src = { 1.5f, -2.5f, 3.0f };
    Vec3f dest = { 0.0f, 0.0f, 0.0f };
    vec3f_copy(dest, src);
    ASSERT_FLOAT_EQ(dest[0], 1.5f, 1e-5f, "vec3f_copy: X mismatch");
    ASSERT_FLOAT_EQ(dest[1], -2.5f, 1e-5f, "vec3f_copy: Y mismatch");
    ASSERT_FLOAT_EQ(dest[2], 3.0f, 1e-5f, "vec3f_copy: Z mismatch");
}

void test_vec3f_set(void) {
    g_tests_run++;
    Vec3f dest = { 0.0f, 0.0f, 0.0f };
    vec3f_set(dest, 10.0f, -5.5f, 0.1f);
    ASSERT_FLOAT_EQ(dest[0], 10.0f, 1e-5f, "vec3f_set: X mismatch");
    ASSERT_FLOAT_EQ(dest[1], -5.5f, 1e-5f, "vec3f_set: Y mismatch");
    ASSERT_FLOAT_EQ(dest[2], 0.1f, 1e-5f, "vec3f_set: Z mismatch");
}

void test_vec3f_add(void) {
    g_tests_run++;
    Vec3f dest = { 1.0f, 2.0f, 3.0f };
    Vec3f a = { 0.5f, -1.0f, 2.5f };
    vec3f_add(dest, a);
    ASSERT_FLOAT_EQ(dest[0], 1.5f, 1e-5f, "vec3f_add: X mismatch");
    ASSERT_FLOAT_EQ(dest[1], 1.0f, 1e-5f, "vec3f_add: Y mismatch");
    ASSERT_FLOAT_EQ(dest[2], 5.5f, 1e-5f, "vec3f_add: Z mismatch");
}

void test_vec3f_sum(void) {
    g_tests_run++;
    Vec3f dest = { 0.0f, 0.0f, 0.0f };
    Vec3f a = { 1.0f, -2.0f, 3.0f };
    Vec3f b = { 4.0f, 5.0f, -6.0f };
    vec3f_sum(dest, a, b);
    ASSERT_FLOAT_EQ(dest[0], 5.0f, 1e-5f, "vec3f_sum: X mismatch");
    ASSERT_FLOAT_EQ(dest[1], 3.0f, 1e-5f, "vec3f_sum: Y mismatch");
    ASSERT_FLOAT_EQ(dest[2], -3.0f, 1e-5f, "vec3f_sum: Z mismatch");
}

void test_vec3s_copy(void) {
    g_tests_run++;
    Vec3s src = { 10, -20, 30 };
    Vec3s dest = { 0, 0, 0 };
    vec3s_copy(dest, src);
    ASSERT_TRUE(dest[0] == 10, "vec3s_copy: X mismatch");
    ASSERT_TRUE(dest[1] == -20, "vec3s_copy: Y mismatch");
    ASSERT_TRUE(dest[2] == 30, "vec3s_copy: Z mismatch");
}

void test_vec3s_set(void) {
    g_tests_run++;
    Vec3s dest = { 0, 0, 0 };
    vec3s_set(dest, 4, -5, 6);
    ASSERT_TRUE(dest[0] == 4, "vec3s_set: X mismatch");
    ASSERT_TRUE(dest[1] == -5, "vec3s_set: Y mismatch");
    ASSERT_TRUE(dest[2] == 6, "vec3s_set: Z mismatch");
}

void test_vec3s_add(void) {
    g_tests_run++;
    Vec3s dest = { 1, 2, 3 };
    Vec3s a = { 10, -5, 20 };
    vec3s_add(dest, a);
    ASSERT_TRUE(dest[0] == 11, "vec3s_add: X mismatch");
    ASSERT_TRUE(dest[1] == -3, "vec3s_add: Y mismatch");
    ASSERT_TRUE(dest[2] == 23, "vec3s_add: Z mismatch");
}

void test_vec3s_sum(void) {
    g_tests_run++;
    Vec3s dest = { 0, 0, 0 };
    Vec3s a = { 1, 2, 3 };
    Vec3s b = { 10, 20, 30 };
    vec3s_sum(dest, a, b);
    ASSERT_TRUE(dest[0] == 11, "vec3s_sum: X mismatch");
    ASSERT_TRUE(dest[1] == 22, "vec3s_sum: Y mismatch");
    ASSERT_TRUE(dest[2] == 33, "vec3s_sum: Z mismatch");
}

void test_vec3s_sub(void) {
    g_tests_run++;
    Vec3s dest = { 10, 20, 30 };
    Vec3s a = { 1, 2, 3 };
    vec3s_sub(dest, a);
    ASSERT_TRUE(dest[0] == 9, "vec3s_sub: X mismatch");
    ASSERT_TRUE(dest[1] == 18, "vec3s_sub: Y mismatch");
    ASSERT_TRUE(dest[2] == 27, "vec3s_sub: Z mismatch");
}

void test_vec3s_to_vec3f(void) {
    g_tests_run++;
    Vec3f dest = { 0.0f, 0.0f, 0.0f };
    Vec3s a = { -10, 20, -30 };
    vec3s_to_vec3f(dest, a);
    ASSERT_FLOAT_EQ(dest[0], -10.0f, 1e-5f, "vec3s_to_vec3f: X mismatch");
    ASSERT_FLOAT_EQ(dest[1], 20.0f, 1e-5f, "vec3s_to_vec3f: Y mismatch");
    ASSERT_FLOAT_EQ(dest[2], -30.0f, 1e-5f, "vec3s_to_vec3f: Z mismatch");
}

void test_vec3f_to_vec3s(void) {
    g_tests_run++;
    Vec3s dest = { 0, 0, 0 };
    Vec3f a = { 1.4f, 2.6f, -3.5f };
    vec3f_to_vec3s(dest, a);
    ASSERT_TRUE(dest[0] == 1, "vec3f_to_vec3s: X mismatch");
    ASSERT_TRUE(dest[1] == 3, "vec3f_to_vec3s: Y mismatch");
    ASSERT_TRUE(dest[2] == -4, "vec3f_to_vec3s: Z mismatch");
}

void test_vec3f_cross(void) {
    g_tests_run++;
    Vec3f dest = { 0.0f, 0.0f, 0.0f };
    Vec3f a = { 1.0f, 0.0f, 0.0f };
    Vec3f b = { 0.0f, 1.0f, 0.0f };
    vec3f_cross(dest, a, b);
    ASSERT_FLOAT_EQ(dest[0], 0.0f, 1e-5f, "vec3f_cross: X mismatch");
    ASSERT_FLOAT_EQ(dest[1], 0.0f, 1e-5f, "vec3f_cross: Y mismatch");
    ASSERT_FLOAT_EQ(dest[2], 1.0f, 1e-5f, "vec3f_cross: Z mismatch");
}

void test_vec3f_normalize(void) {
    g_tests_run++;
    Vec3f dest = { 3.0f, 0.0f, 4.0f };
    vec3f_normalize(dest);
    ASSERT_FLOAT_EQ(dest[0], 0.6f, 1e-5f, "vec3f_normalize: X mismatch");
    ASSERT_FLOAT_EQ(dest[1], 0.0f, 1e-5f, "vec3f_normalize: Y mismatch");
    ASSERT_FLOAT_EQ(dest[2], 0.8f, 1e-5f, "vec3f_normalize: Z mismatch");
}

int main(void) {
    printf("Running math utility tests...\n");

    test_vec3f_copy();
    test_vec3f_set();
    test_vec3f_add();
    test_vec3f_sum();
    test_vec3s_copy();
    test_vec3s_set();
    test_vec3s_add();
    test_vec3s_sum();
    test_vec3s_sub();
    test_vec3s_to_vec3f();
    test_vec3f_to_vec3s();
    test_vec3f_cross();
    test_vec3f_normalize();

    printf("Tests run: %d, Tests failed: %d\n", g_tests_run, g_tests_failed);

    if (g_tests_failed > 0) {
        printf("SOME TESTS FAILED!\n");
        return 1;
    }

    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    return 0;
}

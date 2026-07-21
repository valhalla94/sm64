#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "types.h"
#include "engine/math_util.h"

// Define the required external variables and stubs
Vec3f gVec3fZero = { 0.0f, 0.0f, 0.0f };

f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    if (pfloor != NULL) {
        *pfloor = NULL;
    }
    return 0.0f;
}

void guMtxF2L(Mat4 src, Mtx *dest) {
    // Stub implementation of libultra guMtxF2L if needed
    (void)src;
    (void)dest;
}

// Helper to fill a matrix with non-zero dummy values
void fill_dummy_matrix(Mat4 m) {
    int i, j;
    float val = 99.0f;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m[i][j] = val;
            val += 1.0f;
        }
    }
}

// Helper to print matrix for debugging
void print_matrix(Mat4 m) {
    int i, j;
    for (i = 0; i < 4; i++) {
        printf("[ ");
        for (j = 0; j < 4; j++) {
            printf("%f ", m[i][j]);
        }
        printf("]\n");
    }
}

// Core assertion to verify a translation matrix
void verify_translation_matrix(Mat4 dest, Vec3f b) {
    int i, j;

    // Verify identity components for the upper-left 3x3 submatrix
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == j) {
                if (dest[i][j] != 1.0f) {
                    fprintf(stderr, "Error: Expected diagonal dest[%d][%d] to be 1.0, got %f\n", i, j, dest[i][j]);
                    exit(1);
                }
            } else {
                if (dest[i][j] != 0.0f) {
                    fprintf(stderr, "Error: Expected non-diagonal dest[%d][%d] to be 0.0, got %f\n", i, j, dest[i][j]);
                    exit(1);
                }
            }
        }
    }

    // Verify the w-column components (dest[i][3])
    for (i = 0; i < 3; i++) {
        if (dest[i][3] != 0.0f) {
            fprintf(stderr, "Error: Expected dest[%d][3] to be 0.0, got %f\n", i, dest[i][3]);
            exit(1);
        }
    }

    // Verify translation components on the 4th row
    if (isnan(b[0])) {
        if (!isnan(dest[3][0])) {
            fprintf(stderr, "Error: Expected dest[3][0] to be NaN, got %f\n", dest[3][0]);
            exit(1);
        }
    } else {
        if (dest[3][0] != b[0]) {
            fprintf(stderr, "Error: Expected dest[3][0] to be %f, got %f\n", b[0], dest[3][0]);
            exit(1);
        }
    }

    if (isnan(b[1])) {
        if (!isnan(dest[3][1])) {
            fprintf(stderr, "Error: Expected dest[3][1] to be NaN, got %f\n", dest[3][1]);
            exit(1);
        }
    } else {
        if (dest[3][1] != b[1]) {
            fprintf(stderr, "Error: Expected dest[3][1] to be %f, got %f\n", b[1], dest[3][1]);
            exit(1);
        }
    }

    if (isnan(b[2])) {
        if (!isnan(dest[3][2])) {
            fprintf(stderr, "Error: Expected dest[3][2] to be NaN, got %f\n", dest[3][2]);
            exit(1);
        }
    } else {
        if (dest[3][2] != b[2]) {
            fprintf(stderr, "Error: Expected dest[3][2] to be %f, got %f\n", b[2], dest[3][2]);
            exit(1);
        }
    }

    // Verify dest[3][3] is exactly 1.0f
    if (dest[3][3] != 1.0f) {
        fprintf(stderr, "Error: Expected dest[3][3] to be 1.0, got %f\n", dest[3][3]);
        exit(1);
    }
}

// Scenario 1: Standard positive/negative translation (Happy Path)
void test_happy_path(void) {
    printf("  Running test_happy_path...\n");
    Mat4 dest;
    Vec3f b = { 1.5f, -2.0f, 3.75f };

    fill_dummy_matrix(dest);
    mtxf_translate(dest, b);
    verify_translation_matrix(dest, b);
    printf("  test_happy_path passed!\n");
}

// Scenario 2: Zero translation (Identity preservation)
void test_zero_translation(void) {
    printf("  Running test_zero_translation...\n");
    Mat4 dest;
    Vec3f b = { 0.0f, 0.0f, 0.0f };

    fill_dummy_matrix(dest);
    mtxf_translate(dest, b);
    verify_translation_matrix(dest, b);
    printf("  test_zero_translation passed!\n");
}

// Scenario 3: Large translation values
void test_large_translation(void) {
    printf("  Running test_large_translation...\n");
    Mat4 dest;
    Vec3f b = { 1.2345e5f, -9.8765e5f, 5.5555e6f };

    fill_dummy_matrix(dest);
    mtxf_translate(dest, b);
    verify_translation_matrix(dest, b);
    printf("  test_large_translation passed!\n");
}

// Scenario 4: NaN and Infinity translation values (Extreme input)
void test_nan_inf_translation(void) {
    printf("  Running test_nan_inf_translation...\n");
    Mat4 dest;
    Vec3f b = { (float)NAN, (float)INFINITY, (float)-INFINITY };

    fill_dummy_matrix(dest);
    mtxf_translate(dest, b);
    verify_translation_matrix(dest, b);
    printf("  test_nan_inf_translation passed!\n");
}

int main(void) {
    printf("=== Starting Math Utility Unit Tests ===\n");

    test_happy_path();
    test_zero_translation();
    test_large_translation();
    test_nan_inf_translation();

    printf("=== All Math Utility Unit Tests Passed! ===\n");
    return 0;
}

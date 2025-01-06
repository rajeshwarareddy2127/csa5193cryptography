#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LANES 25
#define LANE_SIZE 64 // 64-bit lanes (512 bits capacity part)

typedef uint64_t lane; // 64-bit lane for each matrix element

// Define the state size (5x5 matrix)
lane state[NUM_LANES] = {0};

// Function to display the state (for debugging)
void printState() {
    for (int i = 0; i < NUM_LANES; i++) {
        printf("Lane %d: %016llx\n", i, state[i]);
    }
}

// Function to check if all capacity lanes have at least one nonzero bit
bool areCapacityLanesNonZero() {
    for (int i = 12; i < NUM_LANES; i++) { // Capacity is the last 8 lanes (lanes 12-19)
        if (state[i] == 0) {
            return false;
        }
    }
    return true;
}

// Simple simulation of absorbing one block of data (simplified)
void absorbMessageBlock(uint64_t *messageBlock) {
    // Absorb the message into the state
    for (int i = 0; i < NUM_LANES; i++) {
        state[i] ^= messageBlock[i]; // XOR the message block into the state
    }
}

// Function to simulate how long it will take before all capacity lanes are nonzero
int simulateAbsorptionProcess(uint64_t *messageBlock) {
    int step = 0;

    // Absorb the message block and track when capacity lanes are nonzero
    while (!areCapacityLanesNonZero()) {
        absorbMessageBlock(messageBlock);
        step++;
        printState(); // Optional: to observe how the state evolves
    }

    return step;
}

int main() {
    // Simulated message block (1024 bits, broken into 16 lanes of 64 bits)
    uint64_t messageBlock[NUM_LANES] = {0};

    // Initial setup: set the message block to non-zero values to simulate data input
    messageBlock[0] = 0x1234567890abcdef;
    messageBlock[1] = 0xabcdef1234567890;
    messageBlock[2] = 0x1111111111111111;
    messageBlock[3] = 0x2222222222222222;
    messageBlock[4] = 0x3333333333333333;
    messageBlock[5] = 0x4444444444444444;
    messageBlock[6] = 0x5555555555555555;
    messageBlock[7] = 0x6666666666666666;
    // Fill more as needed...

    // Simulate the process and track when the capacity lanes are all non-zero
    int steps = simulateAbsorptionProcess(messageBlock);

    printf("It took %d steps to make all capacity lanes nonzero.\n", steps);

    return 0;
}


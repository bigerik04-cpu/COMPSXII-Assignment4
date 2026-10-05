/*
 * Stack Explorer Assignment
 * Computer Science XII - Computer Systems
 *
 * This program explores how function calls work at the stack level,
 * demonstrating recursion, stack growth, stack overflow, and callbacks.
 */

#include <stdio.h>
#include <stdlib.h>

// Global variable for tracking maximum recursion depth
int max_depth = 0;

// =============================================================================
// PART 1: BASIC RECURSION
// =============================================================================

int factorial(int n) {
    printf("Entering factorial(%d)\n", n);

    if (n <= 1) {
        printf("Base case reached\n");
        printf("Returning from factorial(%d) = 1\n", n);
        return 1;
    }

    int result = n * factorial(n - 1);

    printf("Returning from factorial(%d) = %d\n", n, result);

    return result;
}

// =============================================================================
// PART 2: STACK DEPTH TRACKING
// =============================================================================

int fibonacci(int n, int depth) {

    if (depth > max_depth) {
        max_depth = depth;
    }

    printf("Depth %d: fibonacci(%d)\n", depth, n);

    if (n <= 1) {
        return n;
    }

    return fibonacci(n - 1, depth + 1)
         + fibonacci(n - 2, depth + 1);
}

// =============================================================================
// PART 3: STACK OVERFLOW DEMONSTRATION
// =============================================================================

void infinite_recursion(int n) {
    printf("Call %d\n", n);

    // No base case intentionally.
    // Calling this function will eventually cause stack overflow.
    infinite_recursion(n + 1);
}

void safe_recursion(int n, int limit) {

    printf("Call %d\n", n);

    if (n >= limit) {
        printf("Stopping at max depth\n");
        return;
    }

    safe_recursion(n + 1, limit);
}

// =============================================================================
// PART 4: FUNCTION POINTERS AND CALLBACKS
// =============================================================================

int double_value(int n) {
    return n * 2;
}

int square_value(int n) {
    return n * n;
}

int negate_value(int n) {
    return -n;
}

void process_array(int* arr, int size, int (*callback)(int)) {

    for (int i = 0; i < size; i++) {
        int result = callback(arr[i]);
        printf("%d ", result);
    }

    printf("\n");
}

// =============================================================================
// PART 5: EVENT CALLBACK SYSTEM
// =============================================================================

#define MAX_CALLBACKS 10

typedef struct EventSystem {
    void (*callbacks[MAX_CALLBACKS])(int);
    int callback_count;
} EventSystem;

void event_system_init(EventSystem* es) {

    es->callback_count = 0;

    for (int i = 0; i < MAX_CALLBACKS; i++) {
        es->callbacks[i] = NULL;
    }
}

void event_system_register(EventSystem* es, void (*callback)(int)) {

    if (es->callback_count < MAX_CALLBACKS) {

        es->callbacks[es->callback_count] = callback;
        es->callback_count++;

        printf("Callback registered\n");

    } else {

        printf("Max callbacks reached\n");
    }
}

void event_system_trigger(EventSystem* es, int value) {

    printf(
        "Triggering %d callbacks with value %d\n",
        es->callback_count,
        value
    );

    for (int i = 0; i < es->callback_count; i++) {

        if (es->callbacks[i] != NULL) {
            es->callbacks[i](value);
        }
    }
}

// =============================================================================
// EVENT CALLBACK FUNCTIONS
// =============================================================================

void on_score_update(int score) {
    printf("  Score callback: New score is %d\n", score);
}

void on_level_change(int level) {
    printf("  Level callback: Now entering level %d\n", level);
}

void on_health_change(int health) {
    printf("  Health callback: Health is now %d\n", health);
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {

    printf("=============================================================\n");
    printf("            STACK EXPLORER: Function Call Mechanics\n");
    printf("=============================================================\n");

    // -------------------------------------------------------------------------
    // PART 1
    // -------------------------------------------------------------------------

    printf("\n--- Part 1: Factorial with Stack Visualization ---\n");

    int factorial_result = factorial(5);

    printf("Factorial result: %d\n", factorial_result);

    // -------------------------------------------------------------------------
    // PART 2
    // -------------------------------------------------------------------------

    printf("\n--- Part 2: Fibonacci with Depth Tracking ---\n");

    max_depth = 0;
    int fib5 = fibonacci(5, 1);

    printf("Fibonacci(5) = %d\n", fib5);
    printf("Maximum recursion depth: %d\n", max_depth);

    max_depth = 0;
    int fib10 = fibonacci(10, 1);

    printf("Fibonacci(10) = %d\n", fib10);
    printf("Maximum recursion depth: %d\n", max_depth);

    max_depth = 0;
    int fib15 = fibonacci(15, 1);

    printf("Fibonacci(15) = %d\n", fib15);
    printf("Maximum recursion depth: %d\n", max_depth);

    // -------------------------------------------------------------------------
    // PART 3
    // -------------------------------------------------------------------------

    printf("\n--- Part 3: Stack Overflow Demo (comment out after testing!) ---\n");

    /*
     * Uncomment these two lines only when intentionally testing stack overflow.
     * The program will eventually crash because infinite_recursion has no
     * base case.
     *
     * printf("Attempting infinite recursion...\n");
     * infinite_recursion(0);
     */

    printf("Infinite recursion call is commented out after testing.\n");

    printf("\n--- Part 3: Safe Recursion (Fixed Version) ---\n");

    safe_recursion(0, 10);

    // -------------------------------------------------------------------------
    // PART 4
    // -------------------------------------------------------------------------

    printf("\n--- Part 4: Function Pointers and Callbacks ---\n");

    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("Original values: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("Double values: ");
    process_array(numbers, size, double_value);

    printf("Square values: ");
    process_array(numbers, size, square_value);

    printf("Negated values: ");
    process_array(numbers, size, negate_value);

    // -------------------------------------------------------------------------
    // PART 5
    // -------------------------------------------------------------------------

    printf("\n--- Part 5: Event System ---\n");

    EventSystem event_system;

    event_system_init(&event_system);

    event_system_register(&event_system, on_score_update);
    event_system_register(&event_system, on_level_change);
    event_system_register(&event_system, on_health_change);

    event_system_trigger(&event_system, 50);

    printf("\n=============================================================\n");
    printf("Stack exploration complete!\n");
    printf("=============================================================\n");

    return 0;
}

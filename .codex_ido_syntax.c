#ifndef TEST
#define TEST 0
#endif

#if TEST == 0
float syntax_test(float a) {
    register float value = a;
    return value;
}
#elif TEST == 1
float syntax_test(float a) {
    register float value asm("$f20") = a;
    return value;
}
#elif TEST == 2
float syntax_test(float a) {
    register float value __asm("$f20") = a;
    return value;
}
#elif TEST == 3
float syntax_test(float a) {
    register float value __asm__("$f20") = a;
    return value;
}
#elif TEST == 4
float syntax_test(float a) {
    asm("");
    return a;
}
#elif TEST == 5
float syntax_test(float a) {
    asm volatile("");
    return a;
}
#elif TEST == 6
float syntax_test(float a) {
    asm volatile("" : : : "$f18");
    return a;
}
#elif TEST == 7
float syntax_test(float a) {
    __asm("");
    return a;
}
#elif TEST == 8
float syntax_test(float a) {
    __asm__("");
    return a;
}
#endif

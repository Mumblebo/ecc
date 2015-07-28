#include "ecc.c"

static Number _0;
static Number _1;
static Number _2;
static Number _3;
static Number _128;
static Number _255;

void setup() {
    _0 = to_number(0, 4);
    _1 = to_number(1, 4);
    _2 = to_number(2, 4);
    _3 = to_number(3, 4);
    _128 = to_number(128, 4);
    _255 = to_number(255, 4);
}

void testSanity() {
    assert(cmp(to_number(1, 4), to_number(1, 5)) == 0);
    assert(cmp(to_number(2, 4), to_number(1, 5)) == 1);
    assert(cmp(to_number(2, 4), to_number(1, 5)) == 1);

    assert(cmp(parse("0002"), to_number(2, 2)) == 0);
    assert(cmp(parse("00FF"), to_number(255, 2)) == 0);
}

void testAddSub() {
    Number a = new_number(4);
    add(_1, _0, a);
    assert(cmp(a, _1) == 0);
    add(_1, _1, a);
    assert(cmp(a, _2) == 0);
    add(_1, _255, a);
    sub(a, _255, a);
    assert(cmp(a, _1) == 0);
    sub(_2, _1, a);
    assert(cmp(a, _1) == 0);
}

void testMul() {
    Number p = new_number(8);
    Number q = new_number(16);
    mul(_0, _0, p);
    assert(cmp(p, _0) == 0);
    mul(_0, _1, p);
    assert(cmp(p, _0) == 0);
    mul(_1, _1, p);
    assert(cmp(p, _1) == 0);
    mul(_2, _2, p);
    mul(p, p, q);
    assert(cmp(q, to_number(16, 4)) == 0);

    mul(_255, _3, p);
    assert(cmp(p, parse("02FD")) == 0);

    mul(parse("55"), _3, p);
    assert(cmp(p, _255) == 0);

    mul(_128, _3, p);
    assert(cmp(p, parse("0180")) == 0);
}

void testDiv2() {
    Number quotient = new_number(4);
    int remainder2;

    remainder2 = div2(_128, quotient);
    assert(cmp(quotient, parse("40")) == 0);
    assert(remainder2 == 0);

    remainder2 = div2(parse("0FFF"), quotient);
    assert(cmp(quotient, parse("07FF")) == 0);
    assert(remainder2 == 1);
}

void testDiv() {
    Number quotient = new_number(4);
    Number remainder = new_number(4);

    divmod(_1, _128, quotient, remainder);
    assert(cmp(quotient, _0) == 0);
    assert(cmp(remainder, _1) == 0);

    divmod(_255, _128, quotient, remainder);
    assert(cmp(quotient, _1) == 0);
    assert(cmp(remainder, parse("7F")) == 0);

    divmod(_255, _3, quotient, remainder);
    assert(cmp(quotient, parse("55")) == 0);
    assert(cmp(remainder, _0) == 0);

    divmod(_128, _2, quotient, remainder);
    assert(cmp(quotient, parse("40")) == 0);
    assert(cmp(remainder, _0) == 0);
}

int main(void) {
    setup();
    testSanity();
    testAddSub();
    testMul();
    testDiv2();
    testDiv();

    return 0;
}
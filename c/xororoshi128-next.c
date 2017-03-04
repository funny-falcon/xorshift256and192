/*

This code implements multiplication by the matrix underlying a xorshift128 generator.
It assumes that the state has been declared as

uint64_t s[2];

The parameters that must be defined are:

- A: the first shift (left).
- B: the second shift (right).
- C: the third shift (right).

*/

#define ROTL(x,a) ((x<<a)|(x>>(64-a)))
#define ROTR(x,a) ((x>>a)|(x<<(64-a)))
const uint64_t s1 = s[0];
const uint64_t s0 = s[1];
s[0] = s0;
s[1] = s1 ^ s0 ^ ROTL(s0, A) ^ ROTL(s0, B) ^ (s1 >> C);

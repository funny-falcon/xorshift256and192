xorshift256 and xorshift192
===========================

Xorshift is a simple and fast high quality random generator.

Algorithm is simple as:

```
  const A,B,C; // shift values
  intx_t state[N]; // state
  intx_t p, q;
  p = state[0];
  state[0] = state[1];
  state[1] = state[2];
  ...
  state[N-2] = state[N-1];
  q = state[N-1];
  p ^= p << A;
  p ^= p >> B;
  q ^= q >> C;
  state[N-1] = p ^ q;
```

Original xorshift [site](http://xoroshiro.di.unimi.it/) and
[tarball](http://xoroshiro.di.unimi.it/xorshift-1.2.tgz) misses calculations for
shift values A,B and C for generators with 256 and 192 bit state implemented
using 64bit integer arithmetic.

This repository is just result of calulations using original tools from
xorshift tarball and [Fermat](http://home.bway.net/lewis/) using instructions
from xorshift tarball.

So you can find here all A,B,C tripples which produces full period
generators

(at the moment, i didn't run statistical tests, so no recomendation for "best tripple")

XorshiftMX note:
==========

Folders `256shift64` and `192shift64` is for classic xorshift permutation
with code above and produced by matrix (for 256bit case):

```
 0 0 0 (I+L^a)(I+R^b)
 1 0 0 0
 0 1 0 0
 0 0 1 (I+R^c)
```

Folder `256shift64mx` is for alternative permutation, produced by matrix


```
 0 0 0 (I+R^c)
 1 0 0 0
 0 1 0 0
 0 0 1 (I+L^a)(I+R^b)
```

So the code is

```
  const A,B,C; // shift values
  intx_t state[N]; // state
  intx_t p, q;
  p = state[0];
  state[0] = state[1];
  state[1] = state[2];
  ...
  state[N-2] = state[N-1];
  q = state[N-1];
  q ^= q >> A; // here is different
  q ^= q << B;
  p ^= p >> C;
  state[N-1] = p ^ q;
```

Looks like, with presence of loop unrolling, compilators are less smart
in optimizing this permutation.
(in other words, if you generate 4 random numbers at once, gcc is able
to optimize standard permutation, but sucks at optimizing this one).

On the other hand, this permutation may escapes from zero faster (with certain
shift tripples), and does more permutations of current value.

LICENSE
=======

same as for xorshift sources and data, cause I just used their tools.


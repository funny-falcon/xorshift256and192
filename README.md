xorshift256 and xorshift192
===========================

Xorshift is a simple and fast high quality random generator.

Algorithm is simple as:

````
  const A,B,C; // shift values
  intx_t state[N]; // state
  intx_t t;
  t = state[0];
  state[0] = state[1];
  state[1] = state[2];
  ...
  state[N-2] = state[N-1];
  t ^= t << A;
  state[N-1] = t ^ (t >> B) ^ state[N-1] ^ (state[N-1] >> C);
````

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

LICENSE
=======

same as for xorshift sources and data, cause I just used their tools.


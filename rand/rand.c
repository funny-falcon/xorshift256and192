#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

uint64_t state[21]; 
uint64_t *xs1024 = state;
uint64_t *sip = state+16;
uint64_t *xs64 = state+20;
int p;

/* xorshift1024
 * Written in 2014 by Sebastiano Vigna (vigna@acm.org)
 * http://xoroshiro.di.unimi.it/xorshift1024star.c
 * To the extent possible under law, the author has dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * See <http://creativecommons.org/publicdomain/zero/1.0/>. */
static uint64_t xorshift1024_next(void) {
	const uint64_t s0 = xs1024[p];
	uint64_t s1 = xs1024[p = (p + 1) & 15];
	s1 ^= s1 << 31; // a
	xs1024[p] = s1 ^ s0 ^ (s1 >> 11) ^ (s0 >> 30); // b,c
	return xs1024[p];
}

static uint64_t xorshift64_next(void) {
	uint64_t s = *xs64;
	s ^= s << 13;
	s ^= s >> 7;
	s ^= s << 17;
	return *xs64 = s;
}

#define ROTL64(a,b) (((a)<<(b))|((a)>>(64-b)))

/* SipHash's cryptographically safe permutation */
static void sip_mix(void) {
	sip[0] += sip[1];
	sip[2] += sip[3];
	sip[1] = ROTL64(sip[1],13) ^ sip[0];
	sip[3] = ROTL64(sip[3],16) ^ sip[2];
	sip[0] = ROTL64(sip[0],32);
	sip[2] += sip[1];
	sip[0] += sip[3];
	sip[1] = ROTL64(sip[1],17) ^ sip[2];
	sip[3] = ROTL64(sip[3],21) ^ sip[0];
	sip[2] = ROTL64(sip[2],32);
}

uint64_t rnd_next() {
	uint64_t res;
	sip_mix();
	res = sip[3] ^ xorshift64_next();
	sip[3] ^= xorshift1024_next();
	return res;
}

int main() {
	int i;
	int fd = open("/dev/urandom", O_RDONLY);
	int n = sizeof(state)/sizeof(state[0]);
	int rd = read(fd, state, sizeof(state));
	assert(rd == sizeof(state));
	close(fd);
	for (i = 2*n; i; i--) rnd_next();
	for (;;) {
		uint64_t v[1024];
		for (i=0; i<1024; i++) {
			v[i] = rnd_next();
		}
		rd = write(1, v, sizeof(v));
		if (rd != sizeof(v))
			break;
	}
}

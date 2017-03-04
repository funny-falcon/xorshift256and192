#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define ROTL64(a,b) (((a)<<(b))|((a)>>(64-b)))
#define ROTR64(a,b) (((a)<<(64-b))|((a)>>(b)))

static uint64_t xorshift256_next(uint64_t state[4], int *p) {
	uint64_t s0 = state[*p];
	uint64_t s1 = state[*p = (*p + 1) & 3];
	uint64_t res = s0+s1;
	state[*p] = s1 ^ s0 ^ ROTL64(s0, 11) ^ ROTR64(s0, 20) ^ (s1 >> 5); // a,b,c
	return res;
}

/* SipHash's cryptographically safe permutation */
static void sip_mix(uint64_t sip[4]) {
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

uint64_t rnd_next(uint64_t state[8], int *p) {
	uint64_t res;
	uint64_t *xorshift = state+0;
	uint64_t *sip = state+4;
	sip_mix(sip);
	res = sip[3];
	sip[3] ^= xorshift256_next(xorshift, p);
	return res;
}

void ciph_next(uint64_t state[8], int *p, uint64_t *v) {
	uint64_t res;
	uint64_t *xorshift = state+0;
	uint64_t *sip = state+4;
	sip_mix(sip);
	sip[3] ^= *v;
	*v += sip[0];
	sip[0] ^= xorshift256_next(xorshift, p);
}

void ciph_next_dec(uint64_t state[8], int *p, uint64_t *v) {
	uint64_t res;
	uint64_t *xorshift = state+0;
	uint64_t *sip = state+4;
	sip_mix(sip);
	*v -= sip[0];
	sip[3] ^= *v;
	sip[0] ^= xorshift256_next(xorshift, p);
}

void init(uint64_t state[8]) {
	int i, j, p = 0;
	uint64_t v[2];
	for (j=0; j<2; j++) {
		for (i=0; i<4; i++) {
			xorshift256_next(state, &p);
			xorshift256_next(state, &p);
			xorshift256_next(state, &p);
			xorshift256_next(state, &p);
		}
		state[4] ^= state[0];
		state[5] ^= state[1];
		state[6] ^= state[2];
		state[7] ^= state[3];
		for (i=0; i<4; i++) {
			sip_mix(state+4);
		}
		state[0] ^= state[4];
		state[1] ^= state[5];
		state[2] ^= state[6];
		state[3] ^= state[7];
	}
}

int main(int argc, char** argv) {
	int i, p=0;
	uint64_t state[8] = {0};
	int n = sizeof(state)/sizeof(state[0]);
	int rd;
	if (argc > 1 && argv[1]) {
		if (strlen(argv[1]) > 0) {
			strncpy((char*)state, argv[1], sizeof(state));
			init(state);
		} else {
			state[0] = 1;
		}
	} else {
		int fd = open("/dev/urandom", O_RDONLY);
		rd = read(fd, state, sizeof(state));
		assert(rd == sizeof(state));
		close(fd);
	}

#define N (1024*8)
#define V 1
#if V == 2
	uint64_t v[N] = {0};
#endif
#ifdef CNT
	int cnt = 1024*256;
	for (;cnt--;) {
#else
	for(;;) {
#endif
		int wt;
#if V == 1
		uint64_t v[N] = {0};
#endif
#if READ
		rd = read(0, v, sizeof(v));
#endif
		//for (i=0; i<N; i++) {
		//	v[N] = i;
		//}
		for (i=0; i<N; i+=4) {
#ifndef C
#define C 3
#endif
#if C == 1
			v[i] = xorshift256_next(state, &p);
			v[i+1] = xorshift256_next(state, &p);
			v[i+2] = xorshift256_next(state, &p);
			v[i+3] = xorshift256_next(state, &p);
#elif C == 2
			v[i] = rnd_next(state, &p);
			v[i+1] = rnd_next(state, &p);
			v[i+2] = rnd_next(state, &p);
			v[i+3] = rnd_next(state, &p);
#elif C == 3
#ifndef DECODE
			ciph_next(state, &p, v+i);
			ciph_next(state, &p, v+i+1);
			ciph_next(state, &p, v+i+2);
			ciph_next(state, &p, v+i+3);
#else
			ciph_next_dec(state, &p, v+i);
			ciph_next_dec(state, &p, v+i+1);
			ciph_next_dec(state, &p, v+i+2);
			ciph_next_dec(state, &p, v+i+3);
#endif
#endif
		}
#if !READ
		rd = sizeof(v);
#endif
		wt = write(1, v, rd);
		if (rd != wt || rd != sizeof(v))
			break;
	}
}

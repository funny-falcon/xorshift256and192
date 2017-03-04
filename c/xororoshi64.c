/*		 
 * Copyright (C) 2014-2015 Sebastiano Vigna 
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 3 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "reverse.h"

#ifdef TESTU01
#include <unif01.h>
#include <bbattery.h>
#endif

/* The internal state of the generator. */
static uint64_t x = 0x1LL;

/* The current 64-bit value output by the generator (this is not x if STAR32/STAR8/STAR2/STAR5 is defined.) */
static uint64_t y;

/* The three shifts. */
static int A, B, C;

/* Panneton/L’Ecuyer

X1 = (I+Lc)(I+Rb)(I+La),
X2 = (I+La)(I+Rb)(I+Lc),

X3 = (I+Rc)(I+Lb)(I+Ra),
X4 = (I+Ra)(I+Lb)(I+Rc),

X5 = (I+Rb)(I+Lc)(I+La),
X6 = (I+Lb)(I+Ra)(I+Rc),

X7 = (I+Lc)(I+La)(I+Rb),
X8 = (I+Ra)(I+Rc)(I+Lb),
*/
#define ROTL(x,a) ((x<<a)|(x>>(64-a)))
#define ROTR(x,a) ((x>>a)|(x<<(64-a)))

#if defined(STAR32) || defined(STAR8) || defined(STAR2) || defined(STAR5)

#ifdef STAR32
#define NAME "xororoshi64*32"
// Composed with M_32.
const int64_t M = 2685821657736338717LL;
#endif

#ifdef STAR8
#define NAME "xororoshi64*8"
// Composed with M_8.
const int64_t M = 1181783497276652981LL;
#endif

#ifdef STAR2
#define NAME "xororoshi64*2"
// Composed with M_2.
const int64_t M = 8372773778140471301LL;
#endif

#ifdef STAR5
#define NAME "xororoshi64*5"
// Composed with 0x5555555555555555
const int64_t M = 5555555555555555LL;
#endif

void next(void) { x ^= ROTL(x,A) ^ ROTL(x,B); x ^= x >> C; y = REV(x * M); } // X1
#elif defined(ADD)

#define NAME "xororoshi64+"

void next(void) { y = x; x ^= ROTL(x,A) ^ ROTL(x,B); x ^= x >> C; y += x;
	y = REV(y);
} // X1

#else

#define NAME "xororoshi64"

void next(void) { x ^= ROTL(x,A) ^ ROTL(x,B); x ^= x >> C; y = x; } // X1

#endif

/* True if the lower part of y has already been returned. */
static int lower;

/* Note that this function returns a 32-bit number. */
unsigned long xororoshi(void *unused0, void *unused1) {
	if (lower ^= 1) return (uint32_t)y;
	const uint32_t result = y >> 32;
	next();
	return result;
}

#define NORM_64 ((1./4) / (1LL << 62))

double xororoshi01(void *unused0, void *unused1) {
	if (lower) next(); // Refresh y (lower part has already been used).
	const double result = y * NORM_64;
	next();
	lower = 0;
	return result;
}

void write_state(void *unused) {
	printf (" x = %llx\n", (unsigned long long)x);
}

int main(int argc, char *argv[]) {
	if (argc < 5) exit(1);

	A = atoi(argv[1]);
	B = atoi(argv[2]);
	C = atoi(argv[3]);
	x = strtoull(argv[4], NULL, 0);
	next(); // So y has a sensible initial value.
	//next(); // So y has a sensible initial value.

#ifdef TESTU01
	char s[100];
	sprintf(s, NAME REVERSE_INFIX "-%d-%d-%d", A, B, C);

	unif01_Gen gen;
	gen.name = s;
	gen.Write = write_state;
	gen.GetBits = xororoshi;
	gen.GetU01 = xororoshi01;
	TESTU01(&gen);
	return 0;
#else
	assert(freopen(NULL, "wb", stdout));

	for(;;) {
		const uint32_t z = xororoshi(NULL, NULL);
		fwrite(&z, sizeof z, 1, stdout);
	}
#endif
}

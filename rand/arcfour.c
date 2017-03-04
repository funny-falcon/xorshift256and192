#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>


static uint8_t * initialize_key_vector(uint8_t key[], int len, int n);
static uint8_t K[256];
int main(int argc, uint8_t * argv[])
{
	uint8_t k[40];
	int fd = open("/dev/urandom", O_RDONLY);
	int rd = read(fd, k, sizeof(k));
	assert(rd == sizeof(k));
	uint8_t * K = initialize_key_vector(k, sizeof(k), 1);

	uint8_t v[1024*8];
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t q, t;
	int x;

	for (;;) {
		for(x = 0; x < sizeof(v); x++)
		{
			i++;
			j += K[i];
			q = K[i] + K[j];
			t = K[i]; K[i] = K[j]; K[j] = t;
			v[x] = K[q];
		}
		rd = write(1, v, sizeof(v));
		if (rd != sizeof(v))
			break;
	}
};


static uint8_t *  initialize_key_vector(uint8_t *key, int len, int n)
{
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t t;
	for(i= 0; i < 255; i++)
	{
		K[i] = i;
	}
	for(;n; n--) 
	for(i= 0; i < 255; i++)
	{
		j += K[i] + key[i % len];
		t = K[i];
		K[i] = K[j];
		K[j] = t;
	}
	return K;
};


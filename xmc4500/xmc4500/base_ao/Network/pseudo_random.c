
#include "pseudo_random.h"

#define RND_AMOUNT_SHIFTS sizeof(int)
#define RND_BITS_PER_CHAR 8

static unsigned char rnd_num_val[MD5_HASH_SIZE] = {0xa1, 0x11, 0x33, 0x53, 0x65, 0xdf, 0xea, 0xbb, 0x89, 0x10, 0xee, 0x21, 0xee, 0xcc, 0x51, 0x88};
static MD5_CTX rnd_obj;

void rnd_init(char* c) 
{
	int i;
	for (i = 0; i < MD5_HASH_SIZE; i++) rnd_num_val[i] = c[i];
}

void rnd_gen_next_val()
{
	MD5_Init(&rnd_obj);
	MD5_Update(&rnd_obj, rnd_num_val, MD5_HASH_SIZE);
	MD5_Final(rnd_num_val, &rnd_obj);
}

char rnd_nextChar()
{
	rnd_gen_next_val();
	return (char) rnd_num_val[0];
}

int rnd_nextInt()
{
	rnd_gen_next_val();
	
	return ((int*) rnd_num_val)[0];
}

void rnd_fillArray(char* c, unsigned int ui)
{
	unsigned int i;
	unsigned int j = MD5_HASH_SIZE;
	for (i = 0; i < ui; i++, j++)
	{
		if (j == MD5_HASH_SIZE)
		{
			rnd_gen_next_val();
			j = 0;
		}
		c[i] = rnd_num_val[j];
	}
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


const unsigned char permute[] = {
  0x76,0x63,0x37,0x8e,0xdd,0x6e,0xfd,0xc6,
  0xc8,0x3c,0x1f,0xf7,0xb0,0xdb,0xe0,0xf1,
  0xed,0x0d,0x6c,0x21,0x80,0x05,0xfe,0x94,
  0xdc,0x1c,0xa2,0x6a,0xf8,0x56,0x02,0xc9,
  0x20,0xc1,0x08,0x73,0xa6,0x90,0x93,0xf2,
  0xc3,0xb8,0x91,0x4c,0x82,0x8d,0xeb,0x2f,
  0xd2,0xf6,0x7b,0x2d,0x96,0x8a,0x4e,0x99,
  0x31,0xe2,0xcc,0x06,0x5b,0x6b,0x2b,0x22,
  0x5e,0x0c,0x4b,0xf3,0x0e,0xd9,0x69,0x86,
  0x71,0x24,0x50,0xaf,0x7a,0x43,0xd6,0x15,
  0x33,0x61,0x0a,0xa0,0x4a,0x60,0x58,0x1d,
  0x7e,0xa3,0x11,0xa4,0xe7,0xd8,0xf4,0x39,
  0xc5,0xd1,0x26,0x6d,0x47,0xd7,0xce,0xba,
  0x67,0xf9,0x5c,0x04,0x16,0x84,0xe9,0x64,
  0xfa,0xd3,0x8b,0x65,0xe4,0xea,0x3f,0xa8,
  0xaa,0x12,0xad,0x66,0x70,0x36,0x49,0x81,
  0x07,0x1a,0x78,0x29,0xcb,0x77,0x98,0x5f,
  0xf0,0x92,0x28,0xfc,0x5a,0xca,0xb6,0x27,
  0xb3,0x85,0x18,0xb9,0x87,0xe8,0x01,0x5d,
  0xbf,0x45,0xb5,0x51,0x8c,0xbc,0x34,0xbe,
  0xd5,0xec,0x41,0x40,0x95,0x1b,0xa9,0x2c,
  0x3a,0x88,0x35,0x83,0x9c,0x19,0x9e,0x30,
  0xe3,0x17,0xda,0x79,0x9a,0x72,0x42,0x59,
  0x44,0xe5,0x13,0x48,0x38,0x00,0xa1,0xd4,
  0xdf,0x6f,0x14,0x7d,0xac,0xb1,0x74,0xb2,
  0x8f,0x32,0x3e,0x9d,0x4f,0x23,0xae,0x9b,
  0x09,0xa5,0xb4,0x2a,0xc0,0x25,0x1e,0x0f,
  0xd0,0x62,0x54,0x10,0x4d,0x89,0x03,0x55,
  0x53,0x7c,0xee,0x2e,0xa7,0x3b,0xc4,0xfb,
  0x46,0xcf,0x52,0xff,0xc7,0x68,0x75,0xe6,
  0x97,0xde,0xb7,0xef,0xe1,0x0b,0xc2,0x7f,
  0x57,0xcd,0x3d,0xab,0xbb,0xbd,0xf5,0x9f
};
  
int main(int argc, char** argv) {

  printf("Hello!\n");
  if (argc != 2) {
    printf("Provide <key-file> as argument\n");
    return -1;
  }

  FILE* f = fopen(argv[1], "r");
  if (!f) {
    perror("Unable to open file");
    return -2;
  }

  volatile char result = 0;

  /* Read key from file */
  unsigned char value;
  while (fread(&value, 1, 1, f) == 1) {

    /* Key-dependent data access */
    unsigned char perm = permute[value];

    /* Key-dependent branch */
    if (perm > 128) {
      result -= perm;
    } else {
      result += perm;
    }
  }

  /* Initialize random numbers */
  srand((unsigned int)getpid());

  for (size_t i = 0; i < 1024; i++) {
    value = rand();

    /* Key-independent data access */
    unsigned char perm = permute[value];

    /* Key-independent branch */
    if (perm > 128) {
      result -= perm;
    } else {
      result += perm;
    }
  }

  fclose(f);
  return 0;
}

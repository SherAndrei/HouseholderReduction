#include <stdio.h>

int main(int argc, char** argv)
{
  unsigned N = 0;
  if (argc != 2) {
    printf("Usage: %s N\n", argv[0]);
    return 1;
  }

  if (sscanf(argv[1], "%u", &N) != 1) {
    printf("N should be unsigned int\n");
    return 2;
  }

  printf("%u\n", N);
  for (unsigned i = 0; i < N; ++i) {
    for (unsigned j = 0; j < N; ++j) {
      if (j > i)
        printf("  0 ");
      if (j == i)
        printf("  1 ");
      if (j < i)
        printf(" -1 ");
    }
    printf(" 1\n");
  }
}

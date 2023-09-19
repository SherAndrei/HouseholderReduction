#include <stdio.h>

int main(int argc, char** argv)
{
  unsigned N = 0;
  unsigned i, j;
  if (argc != 2) {
    printf("Usage: %s N\n", argv[0]);
    return 1;
  }

  if (sscanf(argv[1], "%u", &N) != 1) {
    printf("N should be unsigned int\n");
    return 2;
  }

  printf("%u\n", N);
  for (i = 0; i < N; ++i) {
    for (j = 0; j < N - i - 1; ++j)
      printf(" -1 ");

    printf("  1 ");

    for (j = 0; j < i; ++j)
        printf("  0 ");

    printf(" 1\n");
  }
}

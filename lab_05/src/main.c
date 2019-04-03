#include "position.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

int main(int argc, char** argv) {
  intrusive_list *l = malloc(sizeof(intrusive_list));
  init_list(l);

  for (int i = 1; i < argc; i++) {
    char *command = argv[i];
    if (strcmp(command, "loadtext") == 0)
    {
      remove_all_positions(l);
      FILE *infile;
      infile = fopen(argv[++i], "r");
      loadtext(l, infile);
      fclose(infile);
    }
    else if (strcmp(command, "loadbin") == 0)
    {
      remove_all_positions(l);
      FILE *infile;
      infile = fopen(argv[++i], "rb");
      loadbin(l, infile);
      fclose(infile);
    }
    else if (strcmp(command, "count") == 0)
    {
      int cnt = 0;
      apply(l, count, &cnt);
      printf("%d\n", cnt);
    }
    else if (strcmp(command, "print") == 0)
    {
      apply_fprint(l, stdout, argv[++i]);
      printf("\n");
    }
    else if (strcmp(command, "savetext") == 0)
    {
      FILE *outfile = fopen(argv[++i], "w");
      apply_fprint(l, outfile, "%d %d\n");
      fclose(outfile);
    }
    else if (strcmp(command, "savebin") == 0)
    {
      FILE *outfile = fopen(argv[++i], "wb");
      apply(l, fprintbin, outfile);
      fclose(outfile);
    }
  }

  remove_all_positions(l);
  free(l);

  return 0;
}

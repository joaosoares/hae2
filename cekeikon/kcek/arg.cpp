#include <cekeikon.h>

void arg(int argc, char** argv)
{ printf("Argc=%d\n",argc);
  for (int i=0; i<argc; i++)
    printf("Argv[%d]=%s\n",i,argv[i]);
  printf("\n");
  printf("Expandindo argv:\n");
  for (int i=1; i<argc; i++) {
    vector<string> vs;
    vsWildCard(argv[i],vs);
    printf("Argv[%d]:\n",i);
    for (unsigned j=0; j<vs.size(); j++)
      printf("  %s\n",vs[j].c_str());
  }
}

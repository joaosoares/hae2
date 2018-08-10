#include <cekeikon.h>

void minusc(int argc, char** argv) { 
  if (argc<2) {
    printf("minusc: Renomeia nomes dos arquivos para minuscula\n");
    printf("minusc NOMEARQ1.EXT NOMEARQ2.EXT ...\n");
    printf("minusc NOME1*.* NOME1*.* ...\n");
    erro("Erro: Numero de argumentos invalido");
  }
  for (int i=1; i<argc; i++) {
    int result = rename( argv[i], minuscula(argv[i]).c_str() );
    if (result==0)
      cout << "Renomeei " + string(argv[i]) + " para " + minuscula(argv[i]) + "\n";
    else {
      erro("Nao consegui renomear " + string(argv[i]) + " para " + minuscula(argv[i]));
    }
  }
}

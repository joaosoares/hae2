#include <cekeikon.h>

void quebrac(int argc, char** argv)
{ if (argc!=6) {
    printf("QuebraC: Quebra Mat_<COR> em subimagens\n");
    printf("QuebraC ent.ppm sai nl nc [ul, ur, dl, dr]\n");
    printf("  ul, ur, dl, dr: Onde vai grudar. Default=ul\n");
    erro("Erro: Numero de argumentos invalido");
  }

  Mat_<COR> ent; le(ent,argv[1]);
  int nl; convArg(nl,argv[3]);
  int nc; convArg(nc,argv[4]);
  assert(nl<ent.rows && nc<ent.cols);

  string modo=argv[5];
  assert(modo=="ul" || modo=="ur" || modo=="dl" || modo=="dr");
 
  int ql=ent.rows/nl; // quantidade de imagens nas linhas
  int qc=ent.cols/nc; // quantidade de imagens nas linhas
  int sl=ent.rows%nl; // quantas linhas vao sobrar
  int sc=ent.cols%nc; // quantas colunas vao sobrar

  int li=0; int ci=0; // linha inicial e coluna inicial
  if      (modo=="ul") {  } // nao faz nada
  else if (modo=="ur") { ci=sc; }
  else if (modo=="dl") { li=sl; }
  else if (modo=="dr") { ci=sc; li=sl; }

  int i=0;
  for (int l=0; l<ql; l++)
    for (int c=0; c<qc; c++) {
      Mat_<COR> roi=ent(Rect(ci+c*nc,li+l*nl,nc,nl));
      string st=format("%s%03d.ppm",argv[2],i);
      cout << st << endl;
      imp(roi,st);
      i++;
    }
}
  
  

    

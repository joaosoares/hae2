#include <cekeikon.h>

void rndtrain(int argc, char** argv)
{ if (argc<3) erro("Erro: RndTrain treino.img boo.xml (ou .yaml)");

  Mat_<FLT> tr; le(tr,argv[1]);
  { // se tem menos de 20 linhas, copia para dar pelo menos 20 linhas.
    int nl=tr.rows;
    int i=0;
    while (tr.rows<20) {
      tr.push_back(tr.row(i));
      i++;
      if (i>=nl) i=0;  
    }
  }

  Mat_<FLT> trent=tr(Rect(0,0,tr.cols-1,tr.rows));
  Mat_<FLT> trsai=tr(Rect(tr.cols-1,0,1,tr.rows));

  printf("Treinando...\n");
  CvRTrees ind;
  ind.train(trent,CV_ROW_SAMPLE,trsai);
  ind.save(argv[2]);
}


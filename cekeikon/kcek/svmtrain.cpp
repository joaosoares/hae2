#include <cekeikon.h>
void svmtrain(int argc, char** argv)
{ if (argc<3) erro("Erro: DtTrain treino.img boo.xml (ou .yaml)");

  Mat_<FLT> tr; le(tr,argv[1]);
  Mat_<FLT> trent=tr(Rect(0,0,tr.cols-1,tr.rows));
  Mat_<FLT> trsai=tr(Rect(tr.cols-1,0,1,tr.rows));
  CvMat pfeatures=trent;
  CvMat psaidas=trsai;

  printf("Treinando...\n");

  CvSVM ind;
  ind.train(&pfeatures,&psaidas);
  //ind.train_auto(&pfeatures,&psaidas);
  ind.save(argv[2]);
}


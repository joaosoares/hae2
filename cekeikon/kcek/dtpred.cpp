#include <cekeikon.h>
void dtpred(int argc, char** argv)
{ if (argc<3) erro("Erro: DtPred boo.xml teste.img");

  CvDTree ind;
  ind.load(argv[1]);

  Mat_<FLT> te; le(te,argv[2]);
  Mat_<FLT> query(1,te.cols-1); 
  CvMat pquery=query;
  float p,r;
  CvDTreeNode* result;
  int acertos=0;
  printf("Classificando...\n");
  for (int l=0; l<te.rows; l++) {
    for (int c=0; c<query.cols; c++)
      query(0,c)=te(l,c);
    result=ind.predict(&pquery);
    p=result->value;
    r=te(l,te.cols-1);
    if (p==r) acertos++;
    //cout << "prediccao=" << p << "correto=" << r << endl;
  }
  printf("Total=%d acertos=%d taxa_acerto=%8.1f%%\n",te.rows,acertos,100.0*acertos/te.rows);
}


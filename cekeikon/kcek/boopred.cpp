#include <cekeikon.h>

/*
void boopred(int argc, char** argv)
{ if (argc<3) erro("Erro: BooPred boo.xml teste.img");

  CvBoost ind;
  ind.load(argv[1]);

  Mat_<FLT> te; le(te,argv[2]);
  Mat_<FLT> query(1,te.cols-1); 
  CvMat pquery=query;
  float p,r;
  int acertos=0;
  printf("Classificando...\n");
  for (int l=0; l<te.rows; l++) {
    for (int c=0; c<query.cols; c++)
      query(0,c)=te(l,c);
    p=ind.predict(&pquery);
    r=te(l,te.cols-1);
    if (p==r) acertos++;
    //cout << "prediccao=" << p << "correto=" << r << endl;
  }
  printf("Total=%d acertos=%d taxa_acerto=%8.1f%%\n",te.rows,acertos,100.0*acertos/te.rows);
}
*/

// Lista weak predictors:
void boopred(int argc, char** argv)
{ if (argc<3) erro("Erro: BooPred boo.xml teste.img");

  CvBoost ind;
  ind.load(argv[1]);

  //CvSeq* weak=ind.get_weak_predictors();
  //cout << weak->total << endl;
  //CvSeqBlock* b=weak->first; 
  //cout << b->count << endl;
  //return 0;

  Mat_<FLT> te; le(te,argv[2]);
  Mat_<FLT> query(1,te.cols-1); 
  CvMat pquery=query;
  float p,r;
  int acertos=0;

  int weak_count=ind.get_params().weak_count;
  Mat_<FLT> weak_responses(1,weak_count);
  CvMat pweak_responses=weak_responses;
  printf("Classificando...\n");
  for (int l=0; l<te.rows; l++) {
    for (int c=0; c<query.cols; c++)
      query(0,c)=te(l,c);
    p=ind.predict(&pquery,0,&pweak_responses);
    r=te(l,te.cols-1);
    if (p==r) acertos++;
    //imp(query,"con");
    cout << "indice=" << l+1 << " prediccao=" << p << " correto=" << r << endl;
    //double soma=0.0;
    //for (int i=0; i<weak_responses.cols; i++) {
    //  soma += weak_responses(0,i);
      //printf("%10g",weak_responses(0,i));
    //}
    //printf("%10g\n",soma);
  }
  printf("Total=%d acertos=%d taxa_acerto=%8.1f%%\n",te.rows,acertos,100.0*acertos/te.rows);
}



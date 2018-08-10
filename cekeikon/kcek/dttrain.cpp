#include <cekeikon.h>

void dttrain(int argc, char** argv)
{ if (argc<3) erro("Erro: DtTrain treino.img boo.xml (ou .yaml)");

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
  CvMat pfeatures=trent;
  CvMat psaidas=trsai;

  printf("Treinando...\n");
  CvDTree ind;
  CvDTreeParams param( 16, // max depth
                       10, // min sample count
                       0, // regression accuracy: N/A here
                       false, // compute surrogate split, as we have missing data
                       2, // max number of categories (use sub-optimal algorithm for larger numbers)
                       30, // the number of cross-validation folds
                       false, // use 1SE rule => smaller tree
                       true, // throw away the pruned tree branches
                       0 // array or priors
                      ); // 99.2%
  /*
  CvDTreeParams param( 10, // max depth
                       10, // min sample count
                       1e-4, // regression accuracy: N/A here
                       true, // compute surrogate split, as we have missing data
                       2, // max number of categories (use sub-optimal algorithm for larger numbers)
                       50, // the number of cross-validation folds
                       false, // use 1SE rule => smaller tree
                       false, // throw away the pruned tree branches
                       0 // array or priors
                      ); // 99.2%
  */

  Mat_<GRY> var_types(tr.cols,1,GRY(CV_VAR_ORDERED)); 
  var_types(tr.cols-1,0)=CV_VAR_CATEGORICAL;
  CvMat pvar_types=var_types;
  ind.train(&pfeatures,CV_ROW_SAMPLE,&psaidas,0,0,&pvar_types,0,param);
  ind.save(argv[2]);
}


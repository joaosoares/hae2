#include <cekeikon.h>

void bootrain(int argc, char** argv)
{ if (argc<3) erro("Erro: BooTrain treino.img boo.xml (ou .yaml)");

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
  Boost ind;
  //CvBoostParams param(CvBoost::REAL, 600, 0.95, 3, false, 0); //99.9% com peso
  //CvBoostParams param(CvBoost::REAL, 600, 0.95, 4, false, 0); //99.9% com peso
  //CvBoostParams param(CvBoost::REAL, 200, 0.95, 4, false, 0); //99.9% com peso
  //CvBoostParams param(CvBoost::REAL, 100, 0.95, 2, false, 0); //100% sem peso
  //CvBoostParams param(CvBoost::REAL, 100, 0.95, 1, false, 0); //99.9% sem peso, 99.8% com peso
  //CvBoostParams param(CvBoost::REAL, 200, 0.95, 1, false, 0); //99.9%
  //CvBoostParams param(CvBoost::REAL, 200, 0.95, 1, false, 0); //99.9% sem peso
  //CvBoostParams param(CvBoost::REAL, 50, 0.95, 1, false, 0); //99.9% sem peso
  //CvBoostParams param(CvBoost::REAL, 12, 0.95, 1, false, 0); //?% sem peso
  //CvBoostParams param(CvBoost::REAL, 50, 0.95, 2, false, 0); //100% sem peso
  //CvBoostParams param(CvBoost::REAL, 25, 0.95, 2, false, 0); //100% sem peso
  //CvBoostParams param(CvBoost::REAL, 12, 0.95, 2, false, 0); //100% sem peso, 99.8% com peso
  //CvBoostParams param(CvBoost::REAL, 5, 0.95, 1, false, 0); //?% sem peso
  //CvBoostParams param(CvBoost::GENTLE, 200, 0.95, 4, false, 0); //99.1% com peso
  //CvBoostParams param(CvBoost::GENTLE, 200, 0.95, 3, false, 0); //99.9% com peso
  //CvBoostParams param(CvBoost::GENTLE, 100, 0.95, 2, false, 0); //100% de verdade! 2012
  //CvBoostParams param(CvBoost::GENTLE, 100, 0.95, 1, false, 0); //100% de verdade! 2012
  //CvBoostParams param(CvBoost::DISCRETE, 200, 0.95, 3, false, 0); //99.9% com peso
  //CvBoostParams param(CvBoost::LOGIT, 200, 0.95, 3, false, 0); //99.5% com peso
  //CvBoostParams param(CvBoost::LOGIT, 200, 0.95, 4, false, 0); //
  //(  int  boost_type,  int  weak_count,  double  weight_trim_rate,
  //int  max_depth,  bool  use_surrogates,  const  float*  priors  )

  //2012 dados para ep2
  //CvBoostParams param(CvBoost::REAL, 100, 0.95, 1, false, 0); //75%
  //CvBoostParams param(CvBoost::GENTLE, 100, 0.95, 1, false, 0); //75%
  CvBoostParams param(CvBoost::GENTLE, 200, 0.95, 2, false, 0); //75% // 82.6% treinando com tudo.

  Mat_<GRY> var_types(tr.cols,1,GRY(CV_VAR_ORDERED)); 
  var_types(tr.cols-1,0)=CV_VAR_CATEGORICAL;
  CvMat pvar_types=var_types;
  ind.train(&pfeatures,CV_ROW_SAMPLE,&psaidas,0,0,&pvar_types,0,param);
  //ind.train(&pfeatures,CV_ROW_SAMPLE,&psaidas,0,0,&pvar_types,0);
  ind.save(argv[2]);
}


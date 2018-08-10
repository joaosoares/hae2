#include "cekeikon.h"

namespace cek {

//<<< especializacao vector<int> <<<<<<<<<<<<<<<<<
void le(vector<int>& a, string nome, bool nInicial)
{ FILE* arq=fopen(nome.c_str(),"rt");
  if (arq==NULL) erro("Erro le(vector<int>,nome) - abertura de ",nome);
  if (setvbuf(arq,NULL,_IOFBF,maxbuf)!=0)
    erro("Erro le(vector<int>,nome) - Faltou memoria setvbuf");
  
  if (nInicial) {
    int n;
    leNum(arq,n);
    a.resize(n);
    int b;
    for (int i=0; i<n; i++) {
      leNum(arq,b); a[i]=b;
    }
  } else {
    int b; leNumIgnEOF(arq,b);
    while (b!=minint) {
      a.push_back(b);
      leNumIgnEOF(arq,b);
    }
  }

  fclose(arq);
}

void imp(vector<int> a, string nome, bool nInicial)
{ FILE* arq=fopen(nome.c_str(),"wt");
  if (arq==NULL) erro("Erro imp(vector<int>,nome) - abertura de ",nome);
  if (setvbuf(arq,NULL,_IOFBF,maxbuf)!=0)
    erro("Erro vector<T>::ImpTxt - Faltou memoria setvbuf");
  if (nInicial) 
    fprintf(arq,"%u\n\n",unsigned(a.size()));
  for (unsigned i=0; i<a.size(); i++)
    fprintf(arq,"%d\n",a[i]);
  fclose(arq);
}

double weightedCorrelation(vector<double> x, vector<double> y, vector<double>& w)
{ if (x.size()!=y.size() || y.size()!=w.size()) erro("Erro weightedCorrelation: Tamanhos diferentes");
  double wsx=0.0; // weighted sum x
  double wsy=0.0; // weighted sum y
  double sw=0.0;  // sum w
  for (unsigned i=0; i<x.size(); i++) {
    wsx += w[i]*x[i];
    wsy += w[i]*y[i];
    sw += w[i];
  }
  double wmx=wsx/sw; // weighted mean x
  double wmy=wsy/sw; // weighted mean y
  // weighted dc reject
  for (unsigned i=0; i<x.size(); i++) {
    x[i] -= wmx;
    y[i] -= wmy;
  }  
  // weighted covariance
  double wcxy=0.0; // weighted covariance x y
  double wcxx=0.0; // weighted covariance x x
  double wcyy=0.0; // weighted covariance y y
  for (unsigned i=0; i<x.size(); i++) {
    wcxy += w[i]*x[i]*y[i];
    wcxx += w[i]*x[i]*x[i];
    wcyy += w[i]*y[i]*y[i];
  }  
  wcxy /= sw;
  wcxx /= sw;
  wcyy /= sw;
  return ( wcxy+FLT_EPSILON ) / ( sqrt(wcxx*wcyy)+FLT_EPSILON );
  //return wcxy / sqrt(wcxx*wcyy);
}

double ssimgry(vector<double>& Y, double y2, double my, vector<double>& X, double x2, double mx,
               double ssalpha, double ssbeta, double ssgama)
// vectores Y e X tem que vir mean-corrected.
// alpha=brilho beta=contraste gama=estrutura(correlacao)
// O resultado pode ser negativo
{ static double epsilonc=1e-8;
  double l=(2*mx*my+epsilonc)/(mx*mx+my*my+epsilonc);
  double c=(2*sqrt(x2*y2)+epsilonc)/(x2+y2+epsilonc);
  double xy=X*Y;
  if (xy<0) {
    double s=(xy-epsilonc)/(sqrt(x2*y2)+epsilonc);
    return -pow(l,ssalpha)*pow(c,ssbeta)*pow(-s,ssgama);
  } else {
    double s=(xy+epsilonc)/(sqrt(x2*y2)+epsilonc);
    return pow(l,ssalpha)*pow(c,ssbeta)*pow(s,ssgama);
  }
}

double ssimgry(vector<double> Y, vector<double> X, double ssalpha, double ssbeta, double ssgama)
// vectores Y e X nao precisam vir mean-corrected.
// Saida: Entre -1 e +1
{ double my=dcReject(Y);
  double mx=dcReject(X);
  double y2=Y*Y;
  double x2=X*X;
  return ssimgry(Y,y2,my,X,x2,mx,ssalpha,ssbeta,ssgama);
}

} // namespace cek

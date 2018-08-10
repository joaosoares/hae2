#include "cekeikon.h"

//int _CRT_glob = 0;   // Para impedir expansao de wildcard
//  Nao adianta colocar aqui. Tem que colocar no main

namespace cek {

//<<<<<<<<<<<<<<<<<<<< Definicao de constantes <<<<<<<<<<<<<<<<<<<<<<
const double epsilon=FLT_EPSILON; 
const double infinito=1e30;
const short maxsht=0x7fff;
const short minsht=short(0x8000);
const int maxint=0x7fffffff;
const int minint=int(0x80000000);
//const int maxbuf=0x10000; //GCC

//<<<<<<<<<<<<<<<<<<<< Cores <<<<<<<<<<<<<<<<<<<<<<

//<<<<<<<<<<<<<<<<<<<< Erro e tempo <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

bool abortaErro=true;

void colorPrint(string st, int f, int b) {
// f de 0 a 15
// b de 0 a 7 no Linux e 0 a 15 no Windows
  rlutil::saveDefaultColor();
  if (f>=0) rlutil::setColor(f);
  if (b>=0) rlutil::setBackgroundColor(b);
  cout << st;
  rlutil::resetColor();
}

void erro(string s1, string s2, string s3)
{ //CV_Error(-1,s1+s2);
  //printf("%s %s\n",s1.c_str(),s2.c_str());
  if (abortaErro) {
    cout << s1 << s2 << s3 << endl;
    exit(1);
  } else {
    throw s1+s2+s3;
  }
}

bool debugon=true;

void debug(string s1, string s2)
{ if (debugon) printf("Debug: %s %s\n",s1.c_str(),s2.c_str()); }

void debug(int i)
{ if (debugon) printf("Debug: %d\n",i); }

clock_t centseg() // consertar para usar chrono
{ return (100*clock()+50)/CLOCKS_PER_SEC;
}

clock_t miliseg() // consertar para usar chrono
{ return (1000*clock()+500)/CLOCKS_PER_SEC; 
}

TimePoint timePoint() {
  return chrono::high_resolution_clock::now();
}

double timeSpan(TimePoint t1, TimePoint t2) {
  return chrono::duration_cast<chrono::duration<double>>(t2-t1).count();
}

void meanStdDev(vector<double>& t, double& mean, double& stddev) {
  double soma=0;
  for (unsigned i=0; i<t.size(); i++) soma += t[i];
  mean = soma / t.size();
  double desvquad=0;
  for (unsigned i=0; i<t.size(); i++) desvquad += (t[i]-mean)*(t[i]-mean);
  stddev=sqrt(desvquad/t.size());
}

} // namespace cek

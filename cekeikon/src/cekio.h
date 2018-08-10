#ifndef __CEKIO__
#define __CEKIO__

#include "cekcg.h"

namespace cek {
using namespace std;
using namespace cv;

EXPORTA void convArg(int& i, string arg);
EXPORTA void convArg(double& i, string arg);
EXPORTA void convArg(float& i, string arg);
EXPORTA void convArg(bool& b, string arg);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

EXPORTA int fGetBit(FILE* arq);
EXPORTA void fPutBit(int d, FILE* arq);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//int mostra(Mat a, bool espera=true, string nome="", char modo='n', double fator=1, int espaco=20);
const int screenRows=768;
const int screenCols=1290;
EXPORTA void mostra(Mat_<COR> entp, string nomep="");
EXPORTA void mostra(Mat_<CORF> entp, string nomep="", double alpha=1.0);
EXPORTA void mostra(Mat_<GRY> entp, string nomep="");
EXPORTA void mostra(Mat_<FLT> entp, string nomep="", double alpha=1.0);
EXPORTA void mostra(Mat_<CPX> entp, string nomep="", char modo='h');
EXPORTA void mostra(Mat_<SHT> entp, string nomep="");
EXPORTA void mostra(Mat_<DBL> entp, string nomep="");

EXPORTA void mostra(Mat entp, string nomep="");

inline void mostra(IMG_<COR> entp, string nomep="") { mostra(entp.mat,nomep); }
inline void mostra(IMG_<CORF> entp, string nomep="") { mostra(entp.mat,nomep); }
inline void mostra(IMG_<GRY> entp, string nomep="") { mostra(entp.mat,nomep); }
inline void mostra(IMG_<FLT> entp, string nomep="") { mostra(entp.mat,nomep); }
inline void mostra(IMG_<CPX> entp, string nomep="", char modo='h') { mostra(entp.mat,nomep,modo); }
inline void mostra(IMG_<SHT> entp, string nomep="") { mostra(entp.mat,nomep); }
inline void mostra(IMG_<DBL> entp, string nomep="") { mostra(entp.mat,nomep); }

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

EXPORTA void le(Mat_<GRY>& a, string nome);
EXPORTA void le(Mat_<COR>& a, string nome);
EXPORTA void le(Mat_<FLT>& a, string nome);
EXPORTA void le(Mat_<CPX>& a, string nome);
EXPORTA void le(Mat_<SHT>& d, string nome);
EXPORTA void le(Mat_<DBL>& d, string nome);
EXPORTA void le(Mat& a, string nome, int type);

EXPORTA void imp(Mat_<GRY> d, string nome);
EXPORTA void imp(Mat_<COR> d, string nome);
EXPORTA void imp(Mat_<CORF> d, string nome);
EXPORTA void imp(Mat_<FLT> d, string nome);
EXPORTA void imp(Mat_<CPX> d, string nome);
EXPORTA void imp(Mat_<SHT> d, string nome);
EXPORTA void imp(Mat_<DBL> d, string nome); 
EXPORTA void imp(Mat d, string nome);

inline void imp(IMG_<GRY> d, string nome) { imp(d.mat,nome); }
inline void imp(IMG_<COR> d, string nome) { imp(d.mat,nome); }
inline void imp(IMG_<FLT> d, string nome) { imp(d.mat,nome); }
inline void imp(IMG_<CPX> d, string nome) { imp(d.mat,nome); }
inline void imp(IMG_<SHT> d, string nome) { imp(d.mat,nome); }
inline void imp(IMG_<DBL> d, string nome) { imp(d.mat,nome); }

/*
inline ostream& operator<< (ostream& sai, Mat_<GRY> a) { imp(a,"con"); return sai; }
inline ostream& operator<< (ostream& sai, Mat_<COR> a) { imp(a,"con"); return sai; }
inline ostream& operator<< (ostream& sai, Mat_<FLT> a) { imp(a,"con"); return sai; }
inline ostream& operator<< (ostream& sai, Mat_<CPX> a) { imp(a,"con"); return sai; }
inline ostream& operator<< (ostream& sai, Mat_<DBL> a) { imp(a,"con"); return sai; }
inline ostream& operator<< (ostream& sai, Mat a)       { imp(a,"con"); return sai; }
*/
inline ostream& operator<< (ostream& sai, IMG_<GRY> a) { return (sai << a.mat); }
inline ostream& operator<< (ostream& sai, IMG_<COR> a) { return (sai << a.mat); }
inline ostream& operator<< (ostream& sai, IMG_<FLT> a) { return (sai << a.mat); }
inline ostream& operator<< (ostream& sai, IMG_<CPX> a) { return (sai << a.mat); }
inline ostream& operator<< (ostream& sai, IMG_<SHT> a) { return (sai << a.mat); }
inline ostream& operator<< (ostream& sai, IMG_<DBL> a) { return (sai << a.mat); }

//<<<<<<<<<<<<<<< vector como conjunto <<<<<<<<<<<<<<<<<<<<<<<<<
template<class T>
ostream& operator<< (ostream& saida, vector<T> x)
{ //saida << "n=" << x.size() << ' ';
  saida << '[';
  for (auto p=x.begin(); p!=x.end(); p++) {
    if (p!=x.begin()) saida << ", ";
    saida << (*p);
  }
  saida << ']';
  return saida;
}

template<class T>
vector<T> uniao(vector<T> a, vector<T> b) {
  vector<T> d;
  sort(a.begin(),a.end());
  sort(b.begin(),b.end());
  set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(d,d.begin()) );
  return d;
}

template<class T>
vector<T> interseccao(vector<T> a, vector<T> b) {
  vector<T> d;
  sort(a.begin(),a.end());
  sort(b.begin(),b.end());
  set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(d,d.begin()) );
  return d;
}

//<<<<<<<<<<<<<<<<<< set como conjunto <<<<<<<<<<<<<<<<<<<<<<<<<<<
template<class T, class U>
ostream& operator<< (ostream& saida, set<T> x)
{ //saida << "size=" << x.size() << ' ';
  saida << '{';
  for (auto p=x.begin(); p!=x.end(); p++) {
    if (p!=x.begin()) saida << ", ";
    saida << (*p);
  }
  saida << '}';
  return saida;
}

template<class T, class U>
set<T,U> uniao(set<T,U> a, set<T,U> b) {
  set<T,U> d;
  set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(d,d.begin()) );
  return d;
}

template<class T, class U>
set<T,U> interseccao(set<T,U> a, set<T,U> b) {
  set<T,U> d;
  set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(d,d.begin()) );
  return d;
}

} //namespace cek

#endif

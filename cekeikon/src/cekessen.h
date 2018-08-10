#ifndef __CEKESSEN__
#define __CEKESSEN__

// #if !(__GNUC__ && (__x86_64__ || __ppc64__))
//   #error Deve compilar com GCC 64 bits, linux ou windows
// #endif

#ifdef _WIN64
  #include <windows.h>
#endif

#include <opencv2/opencv.hpp>
#include <rlutil.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cfloat>
#include <chrono>

namespace cek {
using namespace std;
using namespace cv;

#ifdef _MSC_VER
  #ifdef _WINDLL
     #define EXPORTA __declspec(dllexport)
  #else 
     #define EXPORTA __declspec(dllimport)
  #endif
#endif

#ifdef __GNUC__
  #define EXPORTA 
#endif

//<<<<<<<<<<<<<<<<<<<< Definicao de constantes <<<<<<<<<<<<<<<<<<<<<<
EXPORTA extern const double epsilon;
EXPORTA extern const double infinito;
EXPORTA extern const short maxsht;
EXPORTA extern const short minsht;
EXPORTA extern const int maxint;
EXPORTA extern const int minint;
//extern const int maxbuf; //GCC
#define maxbuf 0x10000

//<<<<<<<<<<<<<<<<<<<< Definicao dos tipos <<<<<<<<<<<<<<<<<<<<<<<<<<
typedef uchar GRY;

#ifndef _WIN32
  // Para ter definicoes equivalentes a VC-Windows em Linux
  typedef uint8_t BYTE;
  typedef uint16_t WORD;
  typedef uint32_t DWORD; 
  typedef uint64_t QWORD; 
#endif

//#ifdef _MSC_VER
//#else
//#endif
//#ifdef __GNUC__
//#endif

typedef short SHT;
typedef float FLT; // FLT deve estar no intervalo [0..1]
typedef double DBL; // DBL deve estar no intervalo [0..1]
typedef Vec3b COR;
typedef Vec3f CORF;

#define xprint(x) { ostringstream os; os << #x " = " << x << '\n'; colorPrint(os.str(),0xa); }

#define xerro { string st = "xerro: file="+string(__FILE__)+" line="+to_string(__LINE__)+"\n"; colorPrint(st,0xc); exit(1); }
//#define xerro(st1)  { string st = "File="+string(__FILE__)+" line="+to_string(__LINE__)+" "+#st1+"\n"; colorPrint(st,0xc); exit(1); }
#define xerro1(st1) { string st = "File="+string(__FILE__)+" line="+to_string(__LINE__)+" "+st1+"\n"; colorPrint(st,0xc); exit(1); }

#define xdebug { string st = "File="+string(__FILE__)+" line="+to_string(__LINE__)+"\n"; colorPrint(st,0xa); } 
//#define xdebug(st1)  { string st = "File="+string(__FILE__)+" line="+to_string(__LINE__)+" "+#st1+"\n"; colorPrint(st,0xa); } 
#define xdebug1(st1) { string st = "File="+string(__FILE__)+" line="+to_string(__LINE__)+" "+st1+"\n"; colorPrint(st,0xa); } 

//     0 = Preto        8 = Cinza
//     1 = Azul         9 = Azul claro
//     2 = Verde        A = Verde claro
//     3 = Verde-�gua   B = Verde-�gua claro
//     4 = Vermelho     C = Vermelho claro
//     5 = Roxo         D = Lil�s
//     6 = Amarelo      E = Amarelo claro
//     7 = Branco       F = Branco brilhante
// f de 0 a 15
// b de 0 a 7 no Linux e 0 a 15 no Windows
EXPORTA void colorPrint(string st, int f=-1, int b=-1);
  
EXPORTA void erro(string s1, string s2="", string st3="");
EXPORTA extern bool abortaErro;
EXPORTA extern bool debugon;
EXPORTA void debug(string s1, string s2="");
EXPORTA void debug(int i);
EXPORTA clock_t centseg();
EXPORTA clock_t miliseg();

typedef chrono::high_resolution_clock::time_point TimePoint;
EXPORTA TimePoint timePoint();
EXPORTA double timeSpan(TimePoint t1, TimePoint t2);
#define impTempo(t1) { \
  TimePoint t2=timePoint(); \
  double t=timeSpan(t1,t2); \
  printf("%10.3f s\n",t); \
}

void meanStdDev(vector<double>& t, double& mean, double& stddev);

#define chronometer( _argv0, _function, _n, _m ) \
{ vector<double> t(_n); \
  for (int i=0; i<_n; i++) { \
    fprintf(stderr,"Iteration %d\r",i); \
    TimePoint t1=timePoint(); \
    for (int j=0; j<_m; j++) { \
      _function; \
    } \
    TimePoint t2=timePoint(); \
    t[i]=timeSpan(t1,t2); \
  } \
  fprintf(stderr,"\n"); \
  double me,sd; \
  meanStdDev(t,me,sd); \
  printf("%s %s: %10.3f+-%5.3f\n",_argv0,#_function,me,sd); \
}
//Exemplo:   chronometer( argv[0], b=negative(a), 5, 1000 );

} //namespace cek

#endif

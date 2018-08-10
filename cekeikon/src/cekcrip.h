#ifndef __CEKCRIP__
#define __CEKCRIP__

#include "cekvideo.h"

namespace cek {
using namespace std;
using namespace cv;

EXPORTA string lesenha();

//<<<<<<<<<<<<<<<< myrandom class <<<<<<<<<<<<<<<<<<<<<
class EXPORTA RANDOM {
  int idum;
public:
  RANDOM(int semente=7);
  void srand(int semente); // Usar numeros positivos ou zero. Nao usar numero igual a MASK=123459876
  // Implementa I_{j+1} = a * I_j (mod m), com a=7^5=16807 m=2^31-1=2147483647
  // Consequentemente, retorna numeros entre 1 e 2^31-2
  int rand();
  DWORD dwordrand(); // Retorna numero de 0 a 0xffffffff, chamando rand duas vezes
  BYTE byterand(); // Retorna numero de 0 a 0xff
  double uniform(); // Retorna numero real de 0 a 1
  double gauss(); // Retorna gaussiana com media 0 e desvio 1
};

// As declaracoes abaixo estao so para compatibilidade
// com versoes antigas.
extern RANDOM myrandom;
inline void mysrand(int semente) { myrandom.srand(semente); }
inline int myrand() { return myrandom.rand(); }
inline DWORD mydwordrand() { return myrandom.dwordrand(); }
inline double myuniform() { return myrandom.uniform(); }
inline double mygauss() { return myrandom.gauss(); }

} //namespace cek

#endif

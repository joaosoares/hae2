#include "cekeikon.h"

namespace cek {

string lesenha()
{ string st;
  int ch;
  while (true) {
    ch=getch();
    if (ch=='\r') break;
    else putchar('*');
    st += ch;
  }
  putchar('\n');
  return st;
}

//<<<<<<<<<<<<<<< random numbers <<<<<<<<<<<<<<<<<<<<<<<

RANDOM::RANDOM(int semente)
{ (*this).srand(semente); }

void RANDOM::srand(int semente)
// Usar numeros positivos ou zero. Nao usar numero igual a MASK
{ idum=semente; (*this).rand(); }

int RANDOM::rand()
// Implementa I_{j+1} = a * I_j (mod m), com a=7^5=16807 m=2^31-1=2147483647
// Consequentemente, retorna numeros entre 1 e 2^31-2
{ const int IA=16807;
  const int IM=2147483647; // 0x7fffffff
  const int IQ=127773;
  const int IR=2836;
  const int MASK=123459876;

  int k;
  int ans;

  idum ^= MASK;
  k=idum/IQ;
  idum=IA*(idum-k*IQ)-IR*k;
  if (idum<0) idum+=IM;
  ans=idum;
  idum ^= MASK;
  return ans;
}

DWORD RANDOM::dwordrand()
{ return DWORD( rand() ^ (rand()<<8) ); }

BYTE RANDOM::byterand()
{ return BYTE(rand()); }

double RANDOM::uniform()
{ const int IM=2147483647; // 0x7fffffff
  const double AM=1.0/IM;

  return AM*rand();
}

double RANDOM::gauss()
{ static int iset=0;
  static float gset;
  float fac,rsq,v1,v2;

  if (idum<0) iset=0;
  if (iset==0) {
    do {
      v1=2.0*uniform()-1.0;
      v2=2.0*uniform()-1.0;
      rsq=v1*v1+v2*v2;
    } while (rsq>=1.0 || rsq==0.0);
    fac=sqrt(-2.0*log(rsq)/rsq);
    gset=v1*fac;
    iset=1;
    return v2*fac;
  } else {
    iset=0;
    return gset;
  }
}

// As declaracoes abaixo estao so para compatibilidade
// com versoes antigas.
RANDOM myrandom(7);
/*
void mysrand(int semente) { myrandom.srand(semente); }
int myrand() { return myrandom.rand(); }
DWORD mydwordrand() { return myrandom.dwordrand(); }
double myuniform() { return myrandom.uniform(); }
double mygauss() { return myrandom.gauss(); }
*/

} // namespace cek

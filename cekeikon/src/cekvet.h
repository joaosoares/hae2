#ifndef __CEKVET__
#define __CEKVET__

#include "cekarq.h"
#include <iostream>
#include <memory>
#include <cstdarg>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

namespace cek {
using namespace std;
using namespace cv;

struct EXPORTA BOX {
  int l1,c1,l2,c2;
};

inline bool dentroBox(int l, int c, BOX b)
{ if (b.l1<=l && l<=b.l2 && b.c1<=c && c<=b.c2) return true;
  else return false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

inline double norm1(Vec3f v)
{ return abs(v[0])+abs(v[1])+abs(v[2]); }

inline Vec3f versorl1(Vec3f v)
{ return v/norm1(v); }

inline Vec3f versor(Vec3f v) 
{ return (1.0/norm(v)) * v; }

inline float operator*(Vec3f v, Vec3f w)
{ return v[0]*w[0]+v[1]*w[1]+v[2]*w[2]; }

inline Vec3f multee(Vec3f a, Vec3f b)
// Multiplicacao elemento a elemento
{ Vec3f d;
  d[0]=a[0]*b[0];
  d[1]=a[1]*b[1];
  d[2]=a[2]*b[2];
  return d;
}

inline Vec3f produtoVet(Vec3f a, Vec3f b)
// Produto vetorial
{ Vec3f d;
  d[0]=a[1]*b[2]-a[2]*b[1];
  d[1]=a[2]*b[0]-a[0]*b[2];
  d[2]=a[0]*b[1]-a[1]*b[0];
  return d;
}

inline Vec3f normalTri(Vec3f a, Vec3f b, Vec3f c)
{ Vec3f d1=b-a;
  Vec3f d2=c-a;
  Vec3f d=versor(produtoVet(d1,d2));
  return d;
}

//<<< especializacao vector<int> <<<<<<<<<<<<<<<<<
EXPORTA void le(vector<int>& a, string nome, bool nInicial=false);
EXPORTA void imp(vector<int> a, string nome, bool nInicial=false);

//<<<<<<<<<<<<<<<<<<<<<<<<<< vector <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
template<class T>
T operator* (const vector<T>& a, const vector<T>& b)
{ T d=0.0;
  if (a.size()!=b.size()) erro("Erro operator*: os vectores nao tem mesmo tamanho");
  for (unsigned i=0; i<a.size(); i++) d+=a[i]*b[i];
  return d;
}

template<class T>
vector<T> operator- (const vector<T>& a, const vector<T>& b)
{ if (a.size()!=b.size()) erro("Erro operator-");
  vector<T> d(a.size());
  for (unsigned i=0; i<a.size(); i++)
    d[i]=a[i]-b[i];
  return d;
}

template<class T>
T comprimentol1(const vector<T>& p)
{ T d=0.0;
  for (unsigned i=0; i<p.size(); i++) d += abs(p[i]);
  return d;
}

template<class T>
vector<T> versorl1(const vector<T>& p)
{ T r=comprimentol1(p);
  if (r>epsilon) {
    vector<T> d(p.size());
    r=1.0/r;
    for (unsigned i=0; i<d.size(); i++) d[i]=r*p[i];
    return d;
  } else return vector<T>(p.size(),0.0);
}

template<class T>
void versorl1(const vector<T>& a, vector<T>& d)
{ if (a.size()!=d.size()) d.resize(a.size());
  T r=comprimentol1(a);
  if (r>epsilon) {
    r=1.0/r;
    for (unsigned i=0; i<d.size(); i++) d[i]=r*a[i];
  } else {
    for (unsigned i=0; i<d.size(); i++) d[i]=0;
  } 
}

template<class T>
T distancial1(const vector<T>& a, const vector<T>& b) 
{ return comprimentol1(a-b); }

EXPORTA double ssimgry(vector<double>& Y, double y2, double my, vector<double>& X, double x2, double mx,
               double ssalpha, double ssbeta, double ssgama);
// vectores Y e X tem que vir mean-corrected.
// alpha=brilho beta=contraste gama=estrutura(correlacao)
// O resultado pode ser negativo
EXPORTA double ssimgry(vector<double> Y, vector<double> X, double ssalpha, double ssbeta, double ssgama);
// vectores Y e X nao precisam vir mean-corrected.
// Saida: Entre -1 e +1

template<class T>
T mediana(vector<T>& a)
{ if (a.size()==0) erro("Erro mediana");
  int n=((int)a.size()-1)/2;
  nth_element(a.begin(), a.begin()+n, a.end());
  return *(a.begin()+n);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< VECTOR
// classe para acessar pixels de vector mais facilmente - mais facil de usar mas lento
template<class T> class VECTOR
{public:
  vector<T>* vet; 
  T backg;
  unsigned n,size;
  int c,max,min; // centro

  VECTOR<T>(vector<T>& _vet, int _c=0)
  { if (_vet.size()==0) erro("Erro: VECTOR::constructor _vet nulo");
    vet=&_vet; c=_c; 
    n=size=(*vet).size();
    max=n-c-1; min=-c;
  }

  T& operator() (unsigned i) {
    if (n<=i) return backg;
    else return (*vet)[i];
  }
  T& atf(unsigned i) {
    return (*vet)[i];
  }
  T& atn(unsigned i) {
    if (n<=i) return backg;
    else return (*vet)[i];
  }
  T& ate(unsigned i) {
    if (n<=i) erro("Erro VECTOR::ate(i) - Indice invalido");
    else return (*vet)[i];
  }
  T& atr(int i) {
    return (*vet)[modulo(i,n)];
  }
  T& atc(int i) {
    i=i+c;
    if (i<0 || n<=i) return backg;
    else return (*vet)[i];
  }
};

//<<<<<<<<<<<<<<<<<< MATRIZ <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// Esta classe ainda nao foi debugada suficientemente
template<typename T>
class MATRIZ {
 public:
  unsigned rows,cols,total;
  T backgv;
  vector<T> vet; 

  void fill(T e1)
  { for (unsigned i=0; i<total; i++) vet[i]=e1; 
    backgv=e1;
  }

  void resize(unsigned par_nl, unsigned par_nc)
  { rows=par_nl; cols=par_nc; total=par_nl*par_nc;  
    vet.resize(total); 
  }

  void resize(unsigned par_nl, unsigned par_nc, T e1)
  { resize(par_nl,par_nc); fill(e1); 
  }

  //<<< ctors
  MATRIZ<T>(unsigned par_nl, unsigned par_nc)
    : rows(par_nl), cols(par_nc), total(par_nl*par_nc)  
  { vet.resize(total); 
  }

  MATRIZ<T>(): MATRIZ<T>(0,0)  
  { //cout << "default ctor" << endl;
  }

  MATRIZ<T>(unsigned par_nl, unsigned par_nc, T e1): MATRIZ<T>(par_nl,par_nc)
  { fill(e1);
  }

  MATRIZ<T>(unsigned par_nl, unsigned par_nc, initializer_list<T> args)
    : MATRIZ<T>(par_nl,par_nc) 
  { auto it=begin(args);
    for (unsigned i=0; i<total; i++) {
      assert(it!=end(args));
      vet[i]=*it;
      it++;
    }
    assert(it==end(args));
    //cout << "initializer ctor" << endl << *this << endl;
  }

//   ~MATRIZ<T>() // vet vai chamar dtor automaticamente
//   { //cout << "dtor" << endl << *this << endl;
//   }
  
  //<<< copy ctor
  MATRIZ<T>(const MATRIZ<T>& a) : MATRIZ<T>(a.rows,a.cols) 
  { vet=a.vet; // copia vet.
    backgv=a.backgv;
    //cout << "copy ctor" << endl << *this << endl;
  }

  //<<< copy assign
  MATRIZ<T>& operator=(const MATRIZ<T>& a)
  { if (this == &a) {
      //cout << "self copy assign" << endl << *this << endl;
      return *this; // beware of self-assignment: x=x
    }
    if (a.total!=(*this).total) {
      vet.resize(a.total);
    }
    vet=a.vet; // copia vet
    backgv=a.backgv;
    //cout << "copy assign" << endl << *this << endl;
    return *this;
  }

  //<<< move ctor
  MATRIZ<T>(MATRIZ<T>&& a)
  { rows=a.rows; cols=a.cols; total=a.total; backgv=a.backgv;
    vet=move(a.vet);
    a.rows=a.cols=a.total=0;
    //cout << "move ctor" << endl << *this << endl;
  }

  //<<<move assign
  MATRIZ<T>& operator=(MATRIZ<T>&& a)
  { if (this == &a) {
      //cout << "self move assign" << endl << *this << endl;
      return *this; // beware of self-assignment: x=x
    }
    vet=move(a.vet);
    rows=a.rows; cols=a.cols; total=a.total; backgv=a.backgv;
    a.rows=a.cols=a.total=0;
    //cout << "move assign" << endl << *this << endl;
    return *this;
  }

  //<<<funcoes reserve, push, pop
  unsigned capacity() const 
  // Retorna numero de linhas reservadas
  { return vet.capacity() / cols;
  }

  void reserve(unsigned sz)
  // sz e' numero de linhas
  { vet.reserve(sz*cols);
  }

  void push_back(const MATRIZ<T>& a)
  { if (total>0) {
      assert(a.nc()==nc()); 
      vet.resize(total+a.total);
      for (unsigned i=0; i<a.total; i++)
        vet[i+total] = a.vet[i];
      rows += a.rows;
      total += a.total;
    } else {
      rows=a.rows; cols=a.cols; total=a.total; backgv=a.backgv;
      vet=a.vet;
    }
  }

  void pop_back(unsigned nrows=1)
  { assert(nrows>=1 && nrows<=rows);
    rows=rows-nrows;
    total=rows*cols;
    vet.resize(total);
  }

  //<<< Funcoes de acesso
  T& operator() (unsigned l, unsigned c)
  { assert(l<rows && c<cols);
    return vet[l*cols+c]; 
  }
  T& operator() (unsigned i)
  { assert(i<total);
    return vet[i]; 
  }

  T& atf(unsigned i) { // Free - Sem verificacao de indice invalido
    return vet[i];
  }
  T& ate(unsigned i) { // Modo geracao de erro se indexar fora do dominio
    if (i<total) return vet[i];
    else erro("Erro MATRIZ Indice invalido");
  }
  T& atf(unsigned l, unsigned c) { // Free - Sem verificacao de indice invalido
    return vet[l*cols+c];
  }
  T& atn(unsigned l, unsigned c) { // Modo normal com backg
    if (rows<=l || cols<=c) return backgv;
    else return vet[l*cols+c];
  }
  T& ate(unsigned l, unsigned c) { // Modo geracao de erro se indexar fora do dominio
    if (rows<=l || cols<=c)
      erro("Erro MATRIZ Indice invalido");
    return vet[l*cols+c];
  }
  T& atr(int l, int c) { // Modo replicado
    return vet[modulo(l,rows)*cols+modulo(c,cols)];
  }

//   const T& operator() (unsigned l, unsigned c) const
//   { assert(l<rows && c<cols);
//     cout << "const operator(l,c)" << endl;
//     return vet[l*cols+c]; 
//   }

//   const T& operator() (unsigned i) const
//   { assert(i<n);
//     return vet[i]; 
//   }

  unsigned nl() const { return rows; }
  unsigned nc() const { return cols; }
  unsigned n() const { return total; }
  T& backg() { return backgv; }
  const T* data() const { return vet.data(); }
};

template<typename T>
ostream& operator<< (ostream& saida, MATRIZ<T>& x)
{ for (unsigned l=0; l<x.rows; l++) {
    for (unsigned c=0; c<x.cols-1; c++) 
      saida << x(l,c) << ", ";
    saida << x(l,x.cols-1) << ";" << endl;
  }
  return saida;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<< class BITREF <<<<<<<<<<<<<<<<<<<<<<<<<
class EXPORTA BITREF {
  DWORD* p;
  DWORD mask;
public:                              //b[i] refers to (i+1)'th bit
  BITREF(DWORD* x, DWORD y): p(x), mask(y) {}
  BITREF(): p(0), mask(0) {}
  operator bool() const              //for x=b[i]
    { return !(!(*p & mask)); }
  BITREF& operator=(bool x) {        //for b[i]=x
    if (x)  *p |= mask;
    else    *p &= ~mask;
    return  *this;
  }
  BITREF& operator=(const BITREF& x) //for b[i]=b[j]
    { return *this = bool(x); }
  bool operator==(const BITREF& x) const
    { return bool(*this) == bool(x); }
  bool operator<(const BITREF& x) const
    { return !bool(*this) && bool(x); }
  void flip() { *p ^= mask; }
};

inline BITREF bit(DWORD& d, int i)
{ if (i<0 || 32<=i) erro("Erro: bit inexistente");
  return BITREF( &d, 0x80000000 >> i );
}

inline BITREF bit(BYTE& d, int i)
{ if (i<0 || 8<=i) erro("Erro: bit inexistente");
  return BITREF( (DWORD*)(&d), 0x00000080 >> i );
}

// Acha o argumento (indice) do maior valor de um vetor a(0) .. a(n-1)
template<class T>
int argMax(vector<T>& a, int n=-1)
{ if (n==-1) n=a.size();
  T maximo=a[0]; int indmax=0;
  for (int i=1; i<n; i++)
    if (a[i]>maximo) {
      maximo=a[i]; indmax=i;
    }
  return indmax;
}

// Acha o argumento (indice) do menor valor de um vetor a(0) .. a(n-1)
template<class T>
int argMin(vector<T>& a, int n=-1)
{ if (n==-1) n=a.size();
  T minimo=a[0]; int indmin=0;
  for (int i=1; i<n; i++)
    if (a[i]<minimo) {
      minimo=a[i]; indmin=i;
    }
  return indmin;
}

} //namespace cek

#endif


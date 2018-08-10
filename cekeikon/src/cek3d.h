#ifndef __CEK3D__
#define __CEK3D__

#include "cekio.h"

namespace cek {
using namespace std;
using namespace cv;

// Sinonimo para deixar claro que se trata de matriz 3D
// Nao use M3d_. Deprecated. Use M3d 
#define M3d_ Mat_
typedef M3d_<COR> Vol_COR;
typedef M3d_<GRY> Vol_GRY;
typedef M3d_<FLT> Vol_FLT;

template<class T>
Mat fatia(M3d_<T> m, int s)
{ if (m.dims!=3) erro("Erro slice: dimensao deve ser 3");
  if (s<0 || m.size[0]<=s) erro("Erro slice: indice invalido");
  Mat d=Mat(m.size[1],m.size[2],m.type(),(void*)m.ptr(s),m.step[1]);
  return d;
}

EXPORTA void converte3d(M3d_<FLT> f, M3d_<GRY>& g);
EXPORTA void converte3d(M3d_<GRY> g, M3d_<FLT>& f);

EXPORTA void impAvi(M3d_<GRY> a, string nome);
EXPORTA void leAvi(M3d_<GRY>& a, string nome);
EXPORTA void impAvi(M3d_<FLT> a, string nome);
EXPORTA void leAvi(M3d_<FLT>& a, string nome);

EXPORTA void imp3dTxt(M3d_<FLT> a, string nome);
EXPORTA void le3dImg(M3d_<FLT>& a, string nome);
EXPORTA void imp3dImg(M3d_<FLT> a, string nome);

//EXPORTA void le(Vol_FLT& a, string nome);
//EXPORTA void imp(Vol_FLT a, string nome);

//void ImpAvi(I3DGRY& a, string nome);
//void LeAvi(I3DGRY& a, string nome);
//void ImpAvi(I3DCOR& a, string nome);
//void LeAvi(I3DCOR& a, string nome);

//<<<<<<<<<<<<<<<<< vector< Mat >  para criar imagem 3D ou video <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
template<class T>
void create(vector< Mat_<T> >& a, int ns, int nl, int nc)
{ a.resize(ns);
  for (int s=0; s<ns; s++)
    a[s].create(nl,nc);
}

//<<<<<<<<<<<<<<<<<<<< M3d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 3d usando vector< Mat_<T> >
template<typename T> 
class M3d {
 public:
  int ns, nl, nc, rows, cols;
  vector< Mat_<T> > vet; 

  void fill(T e1) {
    for (int s=0; s<ns; s++)
      for (int l=0; l<nl; l++)
        for (int c=0; c<nc; c++)
          vet[s](l,c)=e1; 
  }

  void create(int _ns, int _nl, int _nc) {
    // ctor must call this function
    if (vet.size()>0) vet.clear();
    ns=_ns; nl=_nl; nc=_nc; rows=nl; cols=nc; 
    vet.resize(ns); 
    for (int i=0; i<ns; i++) vet[i].create(nl,nc);
  }

  void destruct() {
    if (vet.size()>0) vet.clear();
    ns=nl=nc=0;
  }

  //dtor
  ~M3d<T>() { destruct(); }

  //<<< ctors
  M3d<T>(int _ns, int _nl, int _nc) { 
    create(_ns,_nl,_nc); 
  }

  M3d<T>(): M3d<T>(0,0,0) { 
  }

  M3d<T>(int _ns, int _nl, int _nc, T e1): M3d<T>(_ns,_nl,_nc) {
    fill(e1);
  }

  M3d<T>(int _ns, int _nl, int _nc, initializer_list<T> args)
    : M3d<T>(_ns,_nl,_nc) { 
    auto it=begin(args);
    for (int s=0; s<ns; s++)
      for (int l=0; l<nl; l++)
        for (int c=0; c<nc; c++) {
          if (it==end(args)) erro("Erro: M3d initializer_list ctor 1"); 
          (*this)(s,l,c)=*it;
          it++;
        }
    if (it!=end(args)) erro("Erro: M3d initializer_list ctor 2");
  }

  //<<< copy ctor
  M3d<T>(const M3d<T>& a) : M3d<T>(a.ns,a.nl,a.nc) {
    //debug("cp ctor");
    for (int i=0; i<ns; i++) 
      a.vet[i].copyTo(vet[i]);
  }

  //<<< copy assign
  M3d<T>& operator=(const M3d<T>& a) {
    //debug("cp assign");
    if (this == &a) {
      return *this; // beware of self-assignment: x=x
    }
    create(a.ns,a.nl,a.nc);
    for (int i=0; i<ns; i++) 
      a.vet[i].copyTo(vet[i]);
    return *this;
  }

  //<<< move ctor
  M3d<T>(M3d<T>&& a) {
    //debug("mv ctor");
    create(a.ns,a.nl,a.nc);
    for (int i=0; i<ns; i++) { 
      vet[i]=a.vet[i];
    }
    a.destruct();
  }

  //<<<move assign
  M3d<T>& operator=(M3d<T>&& a) {
    //debug("mv assign");
    if (this == &a) {
      return *this; // beware of self-assignment: x=x
    }
    create(a.ns,a.nl,a.nc);
    for (int i=0; i<ns; i++) { 
      vet[i]=a.vet[i];
    }
    a.destruct();
    return *this;
  }

  //<<< Access functions
  T& operator() (int s, int l, int c) {
    return vet[s](l,c); 
  }
  Mat_<T>& operator() (int i) {
    return vet[i]; 
  }

  //<<< Const access functions
  const T& operator() (int s, int l, int c) const {
    return vet[s](l,c); 
  }
  const Mat_<T>& operator() (int i) const {
    return vet[i]; 
  }
};

//<<<<<<<<<<<<<<<<<<<<< IO functions <<<<<<<<<<<<<<<<<<<<<<<
template<typename T>
ostream& operator<< (ostream& saida, const M3d<T>& x) {
  saida << x.ns << ", " << x.nl << ", " << x.nc << ";" << endl;
  for (int s=0; s<x.ns; s++) { 
    saida << "=========" << endl;
    saida << x(s) << endl;
  }
  saida << endl;
  return saida;
}

//<<<<<<<<<<<<<<<<<<<< I3d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
template<class T> 
class I3d {
 public:
  int slices, rows, cols;
  vector< Mat_<T> > vet; 

  void setTo(T e1) { //OK
    //xdebug1("setTo");
    for (int i=0; i<slices; i++) vet[i].setTo(e1);
  }

  void create(int _slices, int _rows, int _cols) { //OK
    // ctor must call this function
    //xdebug1("create");
    slices=_slices; rows=_rows; cols=_cols;  
    vet.resize(slices); 
    for (int i=0; i<slices; i++) vet[i].create(rows,cols);
  }

  void destruct() { //OK
    //dtor must call this function
    //xdebug1("destruct");
    if (vet.size()>0) vet.clear();
    slices=rows=cols=0;
  }

  //dtor
  ~I3d<T>() { //OK
    //xdebug1("dtor");
    destruct(); 
  }

  //<<< ctors 
  I3d<T>(int _slices, int _rows, int _cols) { //OK
    //xdebug1("ctor 3 parametros"); 
    create(_slices,_rows,_cols); 
  }

  I3d<T>(): I3d<T>(0,0,0) { //OK
    //xdebug1("ctor 0 parametros = default");
  }

  I3d<T>(int _slices, int _rows, int _cols, T e1): I3d<T>(_slices,_rows,_cols) { //OK
    //xdebug1("ctor 4 parametros");
    setTo(e1);
  }

  //<<< copy ctor
  I3d<T>(const I3d<T>& a) { //OK
    //xdebug1("cp ctor");
    slices=a.slices; rows=a.rows; cols=a.cols;
    vet=a.vet;
  }

  //<<< copy assign
  I3d<T>& operator=(const I3d<T>& a) { //OK
    //xdebug1("cp assign");
    if (this == &a) {
      return *this; // beware of self-assignment: x=x
    }
    slices=a.slices; rows=a.rows; cols=a.cols;
    vet=a.vet;
    return *this;
  }

  //<<< move ctor
  I3d<T>(I3d<T>&& a) { //OK
    //xdebug1("mv ctor");
    slices=a.slices; rows=a.rows; cols=a.cols;
    vet=move(a.vet);
    a.destruct();
  }

  //<<<move assign
  I3d<T>& operator=(I3d<T>&& a) { //OK
    //xdebug1("mv assign");
    if (this == &a) {
      return *this; // beware of self-assignment: x=x
    }
    slices=a.slices; rows=a.rows; cols=a.cols;
    vet=move(a.vet);
    a.destruct();
    return *this;
  }

  //<<< Access functions
  T& operator() (int s, int l, int c) { //OK
    return vet[s](l,c); 
  }
  Mat_<T>& operator() (int i) { //OK
    return vet[i]; 
  }

  //<<< Const access functions
  const T& operator() (int s, int l, int c) const { //OK
    return vet[s](l,c); 
  }
  const Mat_<T>& operator() (int i) const { //OK
    return vet[i]; 
  }
};

template<typename T>
ostream& operator<< (ostream& saida, const I3d<T>& x) {
  saida << x.slices << ", " << x.rows << ", " << x.cols << ";" << endl;
  for (int s=0; s<x.slices; s++) { 
    saida << "=========" << endl;
    saida << x(s) << endl;
  }
  saida << endl;
  return saida;
}

} //namespace cek

#endif

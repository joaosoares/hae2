#ifndef __CEKEIK__
#define __CEKEIK__

#include "cekimg.h"

namespace cek {
using namespace std;
using namespace cv;

EXPORTA string depth2str(int t); // converte depth (ex: CV_8U em string)
EXPORTA string tipo(Mat a); // devolve depth e channel de um Mat. Ex:  CV_16SC3

template<class T> class IMG_ {
// classe para acessar pixels de Mat_ mais facilmente - mais facil de usar mas lento
// Deprecated. Use Img_
 public:
  Mat_<T> mat; 
  T backg;
  int nl, nc, n, nx, ny;
  int rows, cols;
  int lc, cc, maxl, minl, maxc, minc, maxx, minx, maxy, miny;

  void inicializa(Mat_<T>& _mat, int _lc=-1, int _cc=-1)
  { if (_mat.data==0) erro("Erro: IMG_::constructor _mat nulo");
    mat=_mat; 
    if (_lc==-1) {
      lc=(mat.rows-1)/2; cc=(mat.cols-1)/2; 
    } else {
      lc=_lc; cc=_cc; 
    }
    nl=mat.rows; nc=mat.cols;
    rows=mat.rows; cols=mat.cols;
    n=nl*nc;
    nx=nc; ny=nl;
    maxl=int(nl)-lc-1; minl=-lc;
    maxc=int(nc)-cc-1; minc=-cc;
    maxx=int(nc)-cc-1; minx=-cc;
    maxy=lc; miny=-(int(nl)-lc-1);
  }

  IMG_<T>(Mat_<T>& _mat, int _lc=-1, int _cc=-1) { inicializa(_mat,_lc,_cc); }
  IMG_<T>() {}

  Size size() { return mat.size(); }

  // Argumento Point
  T& operator() (Point p) {
    if (unsigned(p.y)<unsigned(nl) && unsigned(p.x)<unsigned(nc)) return mat(p);
    else return backg;
  }

  // Um argumento
  T& operator() (int i) {
    if (unsigned(i)<unsigned(n)) return *(mat.begin()+i);
    else return backg;
  }
  T& atf(int i) { // Free - Sem verificacao de indice invalido
    return *(mat.begin()+i);
  }
  T& ate(int i) { // Modo geracao de erro se indexar fora do dominio
    if (unsigned(i)<unsigned(n)) return *(mat.begin()+i);
    else erro("Erro: Indice invalido");
  }

  // Dois argumentos modo LC sem centralizacao
  T& operator() (int l, int c) {
    if (unsigned(l)<unsigned(nl) && unsigned(c)<unsigned(nc)) return mat(l,c);
    else return backg;
  }
  T& atf(int l, int c) { 
    // Free - Sem verificacao de indice invalido sem centralizacao
    return mat(l,c);
  }

  // Dois argumentos modo LC com centralizacao
  T& atx(int l, int c) { // Modo extendido e centralizado
    l=l+lc; c=c+cc;
    if (0<=l && l<int(nl) && 0<=c && c<int(nc)) return mat(l,c);
    if (l<0) {
      if (c<0) return mat(0,0);
      else if (c>=int(nc)) return mat(0,int(nc)-1);
      else return mat(0,c);
    } else if (l>=int(nl)) {
      if (c<0) return mat(int(nl)-1,0);
      else if (c>=int(nc)) return mat(int(nl)-1,int(nc)-1);
      else return mat(int(nl)-1,c);
    } else {
      if (c<0) return mat(l,0);
      else if (c>=int(nc)) return mat(l,int(nc)-1);
      else erro("Erro inesperado");
    }
    return backg;
  }
  T& ate(int l, int c) { // Modo geracao de erro se indexar fora do dominio, centralizado
    unsigned li=l+lc; unsigned ci=c+cc;
    if (li<unsigned(nl) && ci<unsigned(nc)) return mat(li,ci);
    else erro("Indice invalido");
  }
  T& atr(int l, int c) { // Modo replicado e centralizado
    l=l+lc; c=c+cc;
    return mat(modulo(l,nl),modulo(c,nc));
  }
  T& atc(int l, int c) { // modo LC centralizado
    unsigned li=l+lc; unsigned ci=c+cc;
    if (li<unsigned(nl) && ci<unsigned(nc)) return mat(li,ci);
    else return backg;
  }
  T& ati(int l, int c) { // Modo integral. backg acima ou a esquerda. Sem centralizacao. Modo x abaixo ou a direita.
    if (0<=l && l<int(nl) && 0<=c && c<int(nc)) {
      return mat(l,c);
    } else if (l<0 || c<0) {
      return backg;
    } else if (l>=int(nl)) {
      if (c>=int(nc)) return mat(nl-1,nc-1);
      else return mat(nl-1,c);
    } else if (c>=int(nc)) {
      return mat(l,nc-1);
    } else { 
      erro("Erro inesperado");
      return backg;
    }
  }

  // Dois argumentos modo XY com centralizacao
  T& atC(int x, int y) { // modo XY centralizado
    unsigned li=lc-y; unsigned ci=cc+x;
    if (li<unsigned(nl) && ci<unsigned(nc)) return mat(li,ci);
    else return backg;
  }
  T& atX(int x, int y) { // modo XY centralizado e extendido - nao testado.
    int l=lc-y; int c=cc+x;
    if (0<=l && l<int(nl) && 0<=c && c<int(nc)) return mat(l,c);
    if (l<0) {
      if (c<0) return mat(0,0);
      else if (c>=int(nc)) return mat(0,int(nc)-1);
      else return mat(0,c);
    } else if (l>=int(nl)) {
      if (c<0) return mat(int(nl)-1,0);
      else if (c>=int(nc)) return mat(int(nl)-1,int(nc)-1);
      else return mat(int(nl)-1,c);
    } else {
      if (c<0) return mat(l,0);
      else if (c>=int(nc)) return mat(l,int(nc)-1);
      else erro("Erro inesperado");
    }
    return backg;
  }
  T& atE(int x, int y) { // Modo geracao de erro se indexar fora do dominio
    unsigned li=lc-y; unsigned ci=cc+x;
    if (li<unsigned(nl) && ci<unsigned(nc)) return mat(li,ci);
    else erro("Indice invalido");
  }
  T& atR(int l, int c) { // Modo replicado
    int t=l; l=lc-c; c=cc+t;
    return mat(modulo(l,int(nl)),modulo(c,int(nc)));
  }

  void atC2atn(int x, int y, int& l, int& c) { // converte XY centralizado para LC sem centralizacao
    l=lc-y; c=cc+x;
  }
};

template<class T> class QIMG_ {
// classe para acessar pixels de Mat_ mais facilmente - mais chato de usar mas mais rapido
 public:
  Mat_<T> mat,roi,cen; 
  int tborda;
  int nl, nc, n, nx, ny;
  int rows, cols;
  int lc, cc, maxl, minl, maxc, minc, maxx, minx, maxy, miny;

  void inicializa(Mat_<T>& _mat, int _lc=0, int _cc=0, unsigned _tborda=0, 
                  int borderType=BORDER_REPLICATE, Scalar value=Scalar(0,0,0,0))
  // BORDER_REPLICATE, ?IPL_BORDER_REFLECT? ?IPL_BORDER_WRAP?
  { if (_mat.data==0) erro("Erro: QIMG::constructor _mat nulo");
    if (_tborda==0) {
      mat=_mat;
      tborda=_tborda;
      nl=_mat.rows; nc=_mat.cols;
      rows=_mat.rows; cols=_mat.cols;
      n=nl*nc;
      nx=nc; ny=nl;
      lc=_lc; cc=_cc;
      maxl=nl-lc-1; minl=-lc;
      maxc=nc-cc-1; minc=-cc;
      maxx=nc-cc-1; minx=-cc;
      maxy=lc; miny=-(nl-lc-1);
      roi=mat(Rect(tborda,tborda,nc,nl));
      cen=roi(Rect(cc,lc,maxc+1,maxl+1));
    } else if (_tborda>0) {
      copyMakeBorder(_mat,mat,_tborda,_tborda,_tborda,_tborda,borderType,value);
      tborda=_tborda;
      nl=_mat.rows; nc=_mat.cols;
      rows=_mat.rows; cols=_mat.cols;
      n=nl*nc;
      nx=nc; ny=nl;
      lc=_lc; cc=_cc;
      maxl=nl-lc-1; minl=-lc;
      maxc=nc-cc-1; minc=-cc;
      maxx=nc-cc-1; minx=-cc;
      maxy=lc; miny=-(nl-lc-1);
      roi=mat(Rect(tborda,tborda,nc,nl));
      cen=roi(Rect(cc,lc,maxc+1,maxl+1));
      //_mat=roi;
    } else erro("Erro: tborda<0");
  }

  QIMG_<T>(Mat_<T>& _mat, int _lc=0, int _cc=0, unsigned _tborda=0, int borderType=BORDER_REPLICATE, Scalar value=Scalar(0,0,0,0))
  { inicializa(_mat,_lc,_cc,_tborda,borderType,value); }

  QIMG_<T>() {} // default constructor

  // Um argumento sem verificacao
  T& operator() (int i) { return *(roi.begin()+i); }

  // Dois argumentos modo LC com centralizacao sem verificacao
  T& operator() (int l, int c) { return cen(l,c); }

  // Dois argumentos modo XY com centralizacao
  T& atC(int x, int y) { return cen(-y,x); }
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Img <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//Acho que tem que declarar funcoes de acesso constantes
//Nao foi suficientemente testado 
inline void atribui(Mat& a, const Mat& m) {  a=m; }

template<typename T> class Img: public Mat_<T> {
// Classe para acessar pixels de Mat_ usando outro sistema de coordenadas
public:
  using Mat_<T>::Mat_; //inherit constructors

  T backg;
  int& nl=this->rows;
  int& nc=this->cols; 
  int& nx=this->cols;
  int& ny=this->rows;
  int lc=0, cc=0;
  int minl=0, maxl=nl-1, minc=0, maxc=nc-1, minx=0, maxx=nx-1, miny=1-ny, maxy=0;

  void centro(int _lc=INT_MIN, int _cc=INT_MIN) { // testado - OK
  // centro() - origem do sistema no centro da imagem
  // centro(0,0) - origem do sistema no canto superior esquerdo - default.
    if (_lc==INT_MIN) {
      lc=(nl-1)/2; cc=(nc-1)/2; 
    } else {
      lc=_lc; cc=_cc; 
    }
    minl=-lc; maxl=nl-lc-1; 
    minc=-cc; maxc=nc-cc-1; 
    minx=-cc; maxx=nx-cc-1; 
    miny=-(ny-lc-1); maxy=lc; 
  }

  void impAtributos() {
    //cout << "backg=" << backg << endl;
    cout << "nl=" << nl << " nc=" << nc << endl;
    cout << "nx=" << nx << " ny=" << ny << endl;
    cout << "lc=" << lc << " cc=" << cc << endl;
    printf("minl=%d maxl=%d minc=%d maxc=%d\n",minl,maxl,minc,maxc); 
    printf("minx=%d maxx=%d miny=%d maxy=%d\n",minx,maxx,miny,maxy); 
  }

  //============================================

  Img<T>() : Mat_<T>() {}

  Img<T>(int _nl, int _nc, initializer_list<T> args): Mat_<T>(_nl, _nc) { 
    auto it=begin(args);
    for (int i=0; i<_nl*_nc; i++) {
      (*this)(i)=*it;
      it++;
    }
    if (it!=end(args)) erro("Erro initializer_list");
  }

  //<<< copy ctor
  Img<T>(const Img<T>& a) : Mat_<T>(a.rows,a.cols) {
    //debug("cp ctor");
    a.copyTo(*this); 
    backg=a.backg; lc=a.lc; cc=a.cc;
    minl=a.minl; maxl=a.maxl; minc=a.minc; maxc=a.maxc; minx=a.minx; maxx=a.maxx; miny=a.miny; maxy=a.maxy;
  }

  //<<< copy assign
  Img<T>& operator=(const Img<T>& a) {
    //debug("cp assign");
    if (this == &a) {
      return *this; // beware of self-assignment: x=x
    }
    a.copyTo(*this); 
    backg=a.backg; lc=a.lc; cc=a.cc;
    minl=a.minl; maxl=a.maxl; minc=a.minc; maxc=a.maxc; minx=a.minx; maxx=a.maxx; miny=a.miny; maxy=a.maxy;
    return *this;
  }

  //<<< move ctor
  Img<T>(Img<T>&& a) {
    //debug("mv ctor");
    atribui(*this,a);
    backg=a.backg; lc=a.lc; cc=a.cc;
    minl=a.minl; maxl=a.maxl; minc=a.minc; maxc=a.maxc; minx=a.minx; maxx=a.maxx; miny=a.miny; maxy=a.maxy;
    a.release();
  }

  //<<<move assign
  Img<T>& operator=(Img<T>&& a) {
    //debug("mv assign");
    if (this == &a) {
      return *this; // beware of self-assignment: x=x
    }
    atribui(*this,a);
    backg=a.backg; lc=a.lc; cc=a.cc;
    minl=a.minl; maxl=a.maxl; minc=a.minc; maxc=a.maxc; minx=a.minx; maxx=a.maxx; miny=a.miny; maxy=a.maxy;
    a.release();
    return *this;
  }

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Um argumento Point <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  // Cuidado: Use minl maxl minc maxc nl nc. Nao use maxx minx etc
  T& atb(Point p) {   // Argumento Point sem centralizacao - testado OK
    if (unsigned(p.y)<unsigned(nl) && unsigned(p.x)<unsigned(nc)) return (*this)(p);
    else return backg;
  }
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Um argumento int <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  T& atb(int i) { // Um argumento - testado OK
    if (unsigned(i)<unsigned(this->total())) return *(this->begin()+i);
    else return backg;
  }

  T& atf(int i) { // Free - Sem verificacao de indice invalido - testado OK
    return (*this)(i);
  }

  T& ate(int i) { // Modo geracao de erro se indexar fora do dominio - testado OK
    if (unsigned(i)<unsigned(this->total())) return *(this->begin()+i);
    else erro("Erro ate: Indice invalido");
    return backg; // isto nunca e' executado
  }

  //<<<<<<<<<<<<<< Dois argumentos int LC sem centralizacao <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  // Dois argumentos modo LC sem centralizacao
  T& atb(int l, int c) { // testado OK
    if (unsigned(l)<unsigned(nl) && unsigned(c)<unsigned(nc)) return (*this)(l,c);
    else return backg;
  }

  T& ate(int l, int c) { // testado OK
    if (unsigned(l)<unsigned(nl) && unsigned(c)<unsigned(nc)) return (*this)(l,c);
    else erro("Ate: indice invalido");
  }

  // Sem centralizacao
  T& atf(int l, int c) { // OK
    // Free - Sem verificacao de indice invalido sem centralizacao
    return (*this)(l,c);
  }
  // T& (& lcf)(int l, int c) { atf }; 
  
  //<<<<<<<<<<<<<< Dois argumentos int LC centralizado <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  T& lcb(int l, int c) { // modo LC centralizado - testado OK
    unsigned li=l+lc; unsigned ci=c+cc;
    if (li<unsigned(nl) && ci<unsigned(nc)) return (*this)(li,ci);
    else return backg;
  }
  // T& (& lcc)(int l, int c) { atc }; 

  T& lcx(int l, int c) { // Modo extendido e centralizado - testado OK
    l=l+lc; c=c+cc;
    if (0<=l && l<nl && 0<=c && c<nc) return (*this)(l,c);
    if (l<0) {
      if (c<0) return (*this)(0,0);
      else if (c>=nc) return (*this)(0,nc-1);
      else return (*this)(0,c);
    } else if (l>=nl) {
      if (c<0) return (*this)(nl-1,0);
      else if (c>=nc) return (*this)(nl-1,nc-1);
      else return (*this)(nl-1,c);
    } else {
      if (c<0) return (*this)(l,0);
      else if (c>=nc) return (*this)(l,nc-1);
      else erro("Erro inesperado");
    }
    return backg;
  }
  // T& (& lcx)(int l, int c) { atx }; 

  T& lce(int l, int c) { // Modo geracao de erro se indexar fora do dominio, centralizado
    unsigned li=l+lc; unsigned ci=c+cc;
    if (li<unsigned(nl) && ci<unsigned(nc)) return (*this)(li,ci);
    else erro("Lce: Indice invalido");
  }

  T& lcf(int l, int c) { // Modo geracao de erro se indexar fora do dominio, centralizado
    unsigned li=l+lc; unsigned ci=c+cc;
    return (*this)(li,ci);
  }

  T& lcr(int l, int c) { // Modo replicado e centralizado - testado OK
    l=l+lc; c=c+cc;
    return (*this)(modulo(l,nl),modulo(c,nc));
  }
  // T& (& lcr)(int l, int c) { atr }; 

  //<<<<<<<<<<<<<< Dois argumentos int XY centralizado <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  T& xyb(int x, int y) { // modo XY centralizado - testado OK
    unsigned li=lc-y; unsigned ci=cc+x;
    if (li<unsigned(nl) && ci<unsigned(nc)) return (*this)(li,ci);
    else return backg;
  }

  T& xyx(int x, int y) { // modo XY centralizado e extendido - testado OK
    int l=lc-y; int c=cc+x;
    if (0<=l && l<nl && 0<=c && c<nc) return (*this)(l,c);
    if (l<0) {
      if (c<0) return (*this)(0,0);
      else if (c>=nc) return (*this)(0,nc-1);
      else return (*this)(0,c);
    } else if (l>=nl) {
      if (c<0) return (*this)(nl-1,0);
      else if (c>=nc) return (*this)(nl-1,nc-1);
      else return (*this)(nl-1,c);
    } else {
      if (c<0) return (*this)(l,0);
      else if (c>=nc) return (*this)(l,nc-1);
      else erro("Erro inesperado");
    }
    return backg;
  }

  T& xye(int x, int y) { // Modo geracao de erro se indexar fora do dominio - testado OK
    unsigned li=lc-y; unsigned ci=cc+x;
    if (li<unsigned(nl) && ci<unsigned(nc)) return (*this)(li,ci);
    else erro("Indice invalido");
  return backg;
  }

  T& xyf(int x, int y) { // modo XY centralizado
    int l=lc-y; int c=cc+x;
    return (*this)(l,c);
  }

  T& xyr(int l, int c) { // Modo replicado - testado OK
    // int t=l; l=lc-c; c=cc+t;
    // return (*this)(modulo(l,nl),modulo(c,nc));  
    int li=lc-c; int ci=cc+l; 
    return (*this)(modulo(li,nl),modulo(ci,nc));
  }

  //<<<<<<<<<<<<<< Outros modos <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  T& ati(int l, int c) { // Modo integral. backg acima ou a esquerda. 
    //Sem centralizacao. Modo x abaixo ou a direita.
    if (0<=l && l<nl && 0<=c && c<nc) {
      return (*this)(l,c);
    } else if (l<0 || c<0) {
      return backg;
    } else if (l>=nl) {
      if (c>=nc) return (*this)(nl-1,nc-1);
      else return (*this)(nl-1,c);
    } else if (c>=nc) {
      return (*this)(l,nc-1);
    } else { 
      erro("Erro inesperado");
      return backg;
    }
  }

  //<<<<<<<<<<<<<<<<<<<< Outras funcoes <<<<<<<<<<<<<<<<<<<<<<<<<<<
  void xy2at(int x, int y, int& l, int& c) { // converte XY centralizado para LC sem centralizacao
    l=lc-y; c=cc+x;
  }
};

template<typename T> class ImgAtb: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->atb(l,c);
  }
  T& operator() (int i) {
    return this->atb(i);
  }
};

template<typename T> class ImgAte: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->ate(l,c);
  }
  T& operator() (int i) {
    return this->ate(i);
  }
};

template<typename T> class ImgLcb: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->lcb(l,c);
  }
  T& operator() (int i) {
    return this->lcb(i);
  }
};

template<typename T> class ImgLcx: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->lcx(l,c);
  }
  T& operator() (int i) {
    return this->lcx(i);
  }
};

template<typename T> class ImgLce: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->lce(l,c);
  }
  T& operator() (int i) {
    return this->lce(i);
  }
};

template<typename T> class ImgLcf: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->lcf(l,c);
  }
  T& operator() (int i) {
    return this->lcf(i);
  }
};

template<typename T> class ImgLcr: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->lcr(l,c);
  }
  T& operator() (int i) {
    return this->lcr(i);
  }
};

template<typename T> class ImgXyb: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->xyb(l,c);
  }
  T& operator() (int i) {
    return this->xyb(i);
  }
};

template<typename T> class ImgXyx: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->xyx(l,c);
  }
  T& operator() (int i) {
    return this->xyx(i);
  }
};

template<typename T> class ImgXye: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->xye(l,c);
  }
  T& operator() (int i) {
    return this->xye(i);
  }
};

template<typename T> class ImgXyf: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->xyf(l,c);
  }
  T& operator() (int i) {
    return this->xyf(i);
  }
};

template<typename T> class ImgXyr: public Img<T> {
public:
  using Img<T>::Img;
  T& operator() (int l, int c) {
    return this->xyr(l,c);
  }
  T& operator() (int i) {
    return this->xyr(i);
  }
};

} //namespace cek

#endif

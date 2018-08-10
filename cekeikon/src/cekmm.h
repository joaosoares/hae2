#ifndef __CEKMM__
#define __CEKMM__

#include "cek3d.h"
#include <queue>

namespace cek {
using namespace std;
using namespace cv;

//<<<<<<<<<<<<<<<<<<<<<< morfologia <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
namespace Morphology {

const GRY wh=255;
const GRY gr=128;
const GRY bk=0;

inline Mat_<GRY> operator~(Mat_<GRY> a)
{ Mat_<GRY> d; flip(a,d,-1); return d; }

inline Mat_<GRY> operator+(Mat_<GRY> a, Mat_<GRY> b)
{ Mat_<GRY> d; dilate(a,d,~b); return d; }

inline Mat_<GRY> operator-(Mat_<GRY> a, Mat_<GRY> b)
{ Mat_<GRY> d; erode(a,d,b); return d; }

inline Mat_<GRY> operator&&(Mat_<GRY> a, Mat_<GRY> b)
{ Mat_<GRY> d=min(a,b); return d; }

inline Mat_<GRY> operator||(Mat_<GRY> a, Mat_<GRY> b)
{ Mat_<GRY> d=max(a,b); return d; }

inline Mat_<GRY> operator^(Mat_<GRY> a, Mat_<GRY> b)
{ Mat_<GRY> d; bitwise_xor(a,b,d); return d; }

inline Mat_<GRY> operator-(Mat_<GRY> a)
{ Mat_<GRY> d; d=255-a; return d; }

inline Mat_<GRY> operator+(Mat_<GRY> a)
{ Mat_<GRY> d=a.clone(); return d; }

EXPORTA Mat_<GRY> operator!(Mat_<GRY> a);

EXPORTA bool operator==(Mat_<GRY> a, Mat_<GRY> b);

inline bool operator!=(Mat_<GRY> a, Mat_<GRY> b)
{ return !(a==b); }

EXPORTA Mat_<GRY> operator*(Mat_<GRY> a, Mat_<GRY> b);
// Para imagem a com 0 ou 255.
// Para imagem b 0 ou 128 ou 255
// Calcula hit-miss binario de a com elemento estruturante b.
// Na imagem b, valores 0 e 255 tornam-se obrigatorios.
// Qualquer valor diferente de 0 e 255 sao "don't care".
// Se bate, fica branco (255). Nao batendo, fica preto (0).
// A implementacao e' lenta

EXPORTA Mat_<GRY> operator%(Mat_<GRY> a, Mat_<GRY> b);
// Para imagem a com 0 ou 1.
// Para imagem b 0 ou 128 ou 255
// Calcula hit-miss binario de a com elemento estruturante b.
// Na imagem b, valores 0 e 255 tornam-se obrigatorios.
// Qualquer valor diferente de 0 e 255 sao "don't care".
// Se bate, fica branco (1). Nao batendo, fica preto (0).
// A implementacao e' lenta

EXPORTA Mat_<GRY> rot90(Mat_<GRY> a); // Rotaciona 90 graus sentido anti-horario.

EXPORTA Mat_<GRY> strel(double len, double deg, string tipo="line");

} // namespace Morphology

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA int soma(Mat_<GRY> a);
 
// EXPORTA void copia(Mat_<GRY> ent, Mat_<GRY>& sai, int li, int ci);
// // Copia ent para sai a partir de sai(li,ci)
// EXPORTA void copia(Mat_<COR> ent, Mat_<COR>& sai, int li, int ci);
// //Copia ent para sai a partir da posicao sai(li,ci)

template<class T>
void copia(Mat_<T> ent, Mat_<T>& sai, int li, int ci) {
// Copia ent para dentro de sai a partir de d(li,ci). 
// ent deve ser normalmente menor que sai
// Ha protecao para o caso de ent nao caber dentro de sai
  int lisai=max(0,li); 
  int cisai=max(0,ci);
  int lfsai=min(sai.rows-1,li+ent.rows-1); 
  int cfsai=min(sai.cols-1,ci+ent.cols-1);
  Rect rectsai=Rect(cisai,lisai,cfsai-cisai+1,lfsai-lisai+1);
  
  int lient=max(0,-li);
  int cient=max(0,-ci);
  int lfent=min(ent.rows-1, sai.rows-1-li); 
  int cfent=min(ent.cols-1, sai.cols-1-ci); 
  Rect rectent=Rect(cient,lient,cfent-cient+1,lfent-lient+1);
  
  if (rectsai.width>0 && rectsai.height>0 && rectent.width>0 && rectent.height>0) {
    Mat_<T> sairoi=sai(rectsai);
    Mat_<T> entroi=ent(rectent);
    entroi.copyTo(sairoi);
  }
}

template<class T>
void copia(Mat_<T> ent, Mat_<T>& sai, int li, int ci, T dontcopy) {
// Copia ent para dentro de sai a partir de d(li,ci). 
// ent deve ser normalmente menor que sai
// Ha protecao para o caso de ent nao caber dentro de sai
// Nao copia pixels de ent com valor dontcopy
  int lisai=max(0,li); 
  int cisai=max(0,ci);
  int lfsai=min(sai.rows-1,li+ent.rows-1); 
  int cfsai=min(sai.cols-1,ci+ent.cols-1);
  Rect rectsai=Rect(cisai,lisai,cfsai-cisai+1,lfsai-lisai+1);
  
  int lient=max(0,-li);
  int cient=max(0,-ci);
  int lfent=min(ent.rows-1, sai.rows-1-li); 
  int cfent=min(ent.cols-1, sai.cols-1-ci); 
  Rect rectent=Rect(cient,lient,cfent-cient+1,lfent-lient+1);
  
  if (rectsai.width>0 && rectsai.height>0 && rectent.width>0 && rectent.height>0) {
    //assert(rectsai.width==rectent.width && rectsai.height==rectent.height);
    Mat_<T> sairoi=sai(rectsai);
    Mat_<T> entroi=ent(rectent);
    for (int l=0; l<rectent.height; l++)
      for (int c=0; c<rectent.width; c++)
        if (entroi(l,c)!=dontcopy)
          sairoi(l,c)=entroi(l,c);
  }
}

EXPORTA double dcReject(vector<double>& a); // Elimina nivel DC (subtrai media) e retorna media
EXPORTA Mat_<FLT> dcReject(Mat_<FLT> a); // Elimina nivel DC (subtrai media)
EXPORTA Mat_<FLT> dcReject(Mat_<FLT> a, FLT dontcare); // Elimina nivel DC (subtrai media) com dontcare
Mat_<FLT> dcRejectCol(Mat_<FLT>& S); // Calcula media coluna a coluna. Subtrai media de cada coluna. Retorna a media

EXPORTA Mat_<DBL> dcReject(Mat_<DBL> a); // Elimina nivel DC (subtrai media)
EXPORTA Mat_<FLT> somatoriaUm(Mat_<FLT> a); // Faz somatoria absoluta da imagem dar um
EXPORTA Mat_<DBL> somatoriaUm(Mat_<DBL> a); // Faz somatoria absoluta da imagem dar um
EXPORTA Mat_<FLT> somaAbsDois(Mat_<FLT> a); // Faz somatoria absoluta da imagem dar dois
EXPORTA Mat_<DBL> somaAbsDois(Mat_<DBL> a); // Faz somatoria absoluta da imagem dar dois
EXPORTA void mediaDesvio(Mat_<FLT> a, double& media, double& desvio); //Calcula media e desvio de A
EXPORTA double normal01(Mat_<FLT>& a, double newMedia=0.0, double newDesvio=1.0) ;
//Faz a imagem A ser normal(newMedia,newDesvio)
//Retorna oldDesvio

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<GRY> normaliza(Mat_<GRY> a); // Normaliza Mat_<GRY> para intevalo [0..255]
EXPORTA Mat_<FLT> normaliza(Mat_<FLT> a); // Normaliza Mat_<FLT> para intevalo [0,1]
EXPORTA Mat_<DBL> normaliza(Mat_<DBL> a); // Normaliza Mat_<DBL> para intevalo [0,1]
EXPORTA Mat_<CPX> normaliza(Mat_<CPX> a);
// Normaliza Mat_<CPX> para o modulo ficar no intevalo [0,1]
// Divide todos pixels pelo maior modulo

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<GRY> binariza(Mat_<GRY> g, int limiar=127);
EXPORTA Mat_<GRY> binariza(Mat_<FLT> g, float limiar=0.5);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<CPX> ret2pol(Mat_<CPX> a);
EXPORTA Mat_<CPX> pol2ret(Mat_<CPX> a);

//void CPX2flecha(Mat a, Mat& b, double fator=1.0, int espaco=20);
EXPORTA Mat_<FLT> modulo(Mat_<CPX> a);
EXPORTA Mat_<FLT> real(Mat_<CPX> a);
EXPORTA Mat_<FLT> imag(Mat_<CPX> a);
EXPORTA Mat_<CPX> versor(Mat_<CPX> a);
// Todos pixels terao comprimento 1, exceto os pixels quase nulos.

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<FLT> elev2(Mat_<FLT> a);
EXPORTA Mat_<FLT> raiz(Mat_<FLT> a);
EXPORTA Mat_<FLT> modulo(Mat_<FLT> a);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
struct FI2 { FLT v; int l,c; };

struct FI2menor {
  bool operator() (const FI2& a, const FI2& b) const
    { return (a.v<b.v); }
};
typedef priority_queue<FI2,vector<FI2>,FI2menor> FI2DEC; // Ordena em ordem decrescente

struct FI2maior {
  bool operator() (const FI2& a, const FI2& b) const
    { return (a.v>b.v); }
};
typedef priority_queue<FI2,vector<FI2>,FI2maior> FI2INC; // Ordena em ordem crescente

EXPORTA vector<Point> kmax(Mat_<FLT> a, int k, double d=0.0);
// Acha k maximos que estao separados por mais de d pixels
// Elementos <=0.0 nao sao levados em conta, e portanto a saida pode ter menos que k elementos.
EXPORTA vector<Point> kmin(Mat_<FLT> a, int k, double d=0.0);
// Acha k minimos que estao separados por mais de d pixels
// Nota: pixels >=1.0 nao sao levados em conta, e portanto a saida pode ter menos que k elementos.

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// Acha o maior elemento
template<class T>
T maximo(const Mat_<T>& a)
{ T maximoV=a(0); int indmax=0;
  for (int i=1; i<a.total(); i++)
    if (a(i)>maximoV) {
      maximoV=a(i); indmax=i;
    }
  return maximoV;
}

// Acha o menor elemento
template<class T>
T minimo(const Mat_<T>& a)
{ T minimoV=a(0); int indmin=0;
  for (int i=1; i<a.total(); i++)
    if (a(i)<minimoV) {
      minimoV=a(i); indmin=i;
    }
  return minimoV;
}

// Multiplica elemento a elemento (multiplicacao de Hadamard)
template<class T>
Mat_<T> multee(const Mat_<T>& a, const Mat_<T>& b)
{ if (a.size()!=b.size()) xerro1("Erro multee: tamanhos diferentes");
  Mat_<T> d(a.size());
  for (int i=0; i<a.total(); i++)
    d(i)=a(i)*b(i);
  return d;
}

// Divide elemento a elemento
template<class T>
Mat_<T> divee(const Mat_<T>& a, const Mat_<T>& b)
{ if (a.size()!=b.size()) xerro1("Erro divee: tamanhos diferentes");
  Mat_<T> d(a.size());
  for (int i=0; i<a.total(); i++)
    d(i)=a(i)/b(i);
  return d;
}

// Todos de a devem ser menores que b
template<class T>
bool todosMenores(const Mat_<T>& a, const Mat_<T>& b)
{ assert(a.size()==b.size());
  for (int i=0; i<a.total(); i++)
    if (!(a(i)<b(i))) return false;
  return true;
}

// Todos de a devem ser menores que b
template<class T>
bool todosMenores(const Mat_<T>& a, T b)
{ for (int i=0; i<a.total(); i++)
    if (!(a(i)<b)) return false;
  return true;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//void maximo(vector< Mat_<GRY> >& bc, vector< Mat_<GRY> >& bl, Mat_<GRY>& dc, Mat_<GRY>& dl);

EXPORTA Mat_<CPX> criaCPX(Mat_<SHT> dc, Mat_<SHT> dl);
EXPORTA Mat_<CPX> criaCPX(Mat_<FLT> dc, Mat_<FLT> dl);
EXPORTA Mat_<CPX> gradiente2(Mat_<GRY> a, bool yParaCima=false);
// x ->  
// y |
//   V
EXPORTA Mat_<CPX> gradienteScharr(Mat_<GRY> a, bool yParaCima=false);
// x ->  
// y |
//   V
// Saida entre -1 e +1
// Usa kernel 3x3 de Scharr
EXPORTA Mat_<CPX> gradiente(Mat_<COR> ap); // Eixo y aponta para baixo. Pega maior gradiente entre R, G e B
EXPORTA void gradienteLC(Mat_<COR> ap, Mat_<SHT>& gl, Mat_<SHT>& gc); // Eixo y aponta para baixo. Pega maior gradiente entre R, G e B

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class EXPORTA HOG {
 public:
  M3d_<FLT> blo; // I3D
  int nBins, cellSizeL, cellSizeC; // nBins=nAngulos, cellSize em pixels
  
  void CPX2his(Mat_<CPX> b, M3d_<FLT>& his); // his = I3D
  void his2blo(M3d_<FLT> his, M3d_<FLT>& cell); // his,cell = I3D

  HOG(Mat_<COR> a, int _nBins=8, int _cellSizeL=8, int _cellSizeC=0);
  void exporta(Mat_<GRY>& d, int zoom=4, double mult=1.0);
  void show(int zoom=4, double mult=1.0, string nome="");
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DENSEHOG <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class EXPORTA DENSEHOG {
 public:
  Mat_<CPX> grad;
  M3d_<FLT> his; 
  int nBins; // nBins=nAngulos
  int tlCell, tcCell; // tamanho de cell
  int lc,cc; // tamanho de cell
  
  void grad2his();
  DENSEHOG(Mat_<COR> a, int _nBins=8, int _tlCell=5, int _tcCell=5);
  vector<double> hog(int l, int c);
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA void myPyrDown(Mat_<GRY> ent, Mat_<GRY>& sai);
EXPORTA void myPyrDown(Mat_<COR> ent, Mat_<COR>& sai);
EXPORTA void myPyrDown(Mat_<FLT> ent, Mat_<FLT>& sai);
//First it blurs using 3x3 gaussian blur
//void  GaussianBlur(  const  Mat&  src,  Mat&  dst,  Size  ksize,
//  double  sigmaX,  double  sigmaY=0,
//  int  borderType=BORDER DEFAULT  );
//and then downsamples the image by rejecting even rows and columns.

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< piramide <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//To produce layer (i+1) in the Gaussian pyramid (we denote this layer Gi+1) from layer Gi
//of the pyramid, we first convolve Gi with a Gaussian kernel and then remove every even-numbered
//row and column
//nl=1 -> 0    .....
//nl=2 -> 1    .*.*.
//nl=3 -> 1    .....
//nl=4 -> 2    .*.*.

template<class T>
class RECPIR {
 public:
  vector<BOX> cx;
  Mat_<T> rec;
  RECPIR() {}
  void inicializa(Mat_<T> a);
  RECPIR(Mat_<T> a) { inicializa(a); }
  bool r2p(int lr, int cr, int& lp, int& cp, int& sp);
  bool p2r(int lp, int cp, int sp, int& lr, int& cr);
};

template<class T>
void RECPIR<T>::inicializa(Mat_<T> a)
{ int nl=a.rows; int nc=a.cols;
  rec.create(nl,nc+nc/2); rec.setTo(Scalar(0,0,0,0)); 
  if (!cx.empty()) cx.clear();

  // Nivel G0:
  BOX b; 
  b.l1=0; b.c1=0; b.l2=a.rows-1; b.c2=a.cols-1;
  cx.push_back(b);
  copia(a,rec,b.l1,b.c1);
  Mat_<T> temp;
  myPyrDown(a,temp); a=temp;

  b.c1=nc; 
  while (a.rows>1 && a.cols>1) {
    b.l2=b.l1+a.rows-1; b.c2=b.c1+a.cols-1;
    cx.push_back(b);
    copia(a,rec,b.l1,b.c1);
    b.l1+=a.rows;
    myPyrDown(a,temp); a=temp;
  }
} 

template<class T>
bool RECPIR<T>::r2p(int lr, int cr, int& lp, int& cp, int& sp)
// Coordenada de recursivo(lr,cr) para piramide(lp,cp,sp)
// sp e' escala. 0=resolucao fina.
{ lp=cp=sp=0;
  if (dentroBox(lr,cr,cx[0])) { lp=lr; cp=cr; sp=0; return true; }
  for (unsigned i=1; i<cx.size(); i++) {
    if (dentroBox(lr,cr,cx[i])) { 
      lp=(lr-cx[i].l1+1)*pow(2,i)-1; 
      cp=(cr-cx[i].c1+1)*pow(2,i)-1; 
      sp=i; 
      return true;
    }
  }
  return false;
}

template<class T>
bool RECPIR<T>::p2r(int lp, int cp, int sp, int& lr, int& cr)
// Coordenada de piramide(lp,cp,sp) para recursivo(lr,cr)
// sp e' escala. 0=resolucao fina.
{ BOX b=cx[sp];
  lr=arredonda(lp+1,pow(2,sp))+b.l1-1; if (lr<0) lr=0;
  cr=arredonda(cp+1,pow(2,sp))+b.c1-1; if (cr<0) cr=0;
  if (lr>b.l2 || cr>b.c2) return false;
  else return true;
}

//<<<<<<<<<<<<<<<<<<<<<<<< PIRAMIDE <<<<<<<<<<<<<<<<<<<<<<<<<<
template<class T>
class PIRAMIDE {
 public:
  vector< Mat_<T> > v;
  PIRAMIDE() {}
  void inicializa(Mat_<T> a, int niveis=0);
  PIRAMIDE(Mat_<T> a, int niveis=0) { inicializa(a,niveis); }
  // niveis 0 indica niveis ate virar um pixel
  bool i2p(int li, int ci, int sp, int& lp, int& cp);
  bool p2i(int lp, int cp, int sp, int& li, int& ci);
};

template<class T>
void PIRAMIDE<T>::inicializa(Mat_<T> a, int niveis)
{ if (!v.empty()) v.clear();
  if (niveis<=0) niveis=maxint;
  v.push_back(a); int n=1;
  Mat_<T> temp; 
  while (a.rows>1 && a.cols>1 && n<niveis) {
    myPyrDown(a,temp); a=temp; 
    v.push_back(a); n++;
  }
} 

//To produce layer (i+1) in the Gaussian pyramid (we denote this layer Gi+1) from layer Gi
//of the pyramid, we first convolve Gi with a Gaussian kernel and then remove every even-numbered
//row and column
// ..... li=  0 lp0=  0 lp1=  0 lp2=  0 li0=  0 li1=  1 li2=  3
// .*.*. li=  1 lp0=  1 lp1=  0 lp2=  0 li0=  1 li1=  1 li2=  3
// ..... li=  2 lp0=  2 lp1=  1 lp2=  0 li0=  2 li1=  3 li2=  3
// .*.X. li=  3 lp0=  3 lp1=  1 lp2=  0 li0=  3 li1=  3 li2=  3
// ..... li=  4 lp0=  4 lp1=  2 lp2=  0 li0=  4 li1=  5 li2=  3
// .*.*. li=  5 lp0=  5 lp1=  2 lp2=  1 li0=  5 li1=  5 li2=  7
// ..... li=  6 lp0=  6 lp1=  3 lp2=  1 li0=  6 li1=  7 li2=  7
// .*.X. li=  7 lp0=  7 lp1=  3 lp2=  1 li0=  7 li1=  7 li2=  7
// ..... li=  8 lp0=  8 lp1=  4 lp2=  1 li0=  8 li1=  9 li2=  7
// .*.*. li=  9 lp0=  9 lp1=  4 lp2=  2 li0=  9 li1=  9 li2= 11
// int main()
// { for (int li=0; li<32; li++) {
//     int lp0=arredonda(li+1,pow(2,0))-1; if (lp0<0) lp0=0;
//     int lp1=arredonda(li+1,pow(2,1))-1; if (lp1<0) lp1=0;
//     int lp2=arredonda(li+1,pow(2,2))-1; if (lp2<0) lp2=0;
//     printf("li=%3d lp0=%3d lp1=%3d lp2=%3d ",li,lp0,lp1,lp2);
//     int li0=(lp0+1)*pow(2,0)-1; 
//     int li1=(lp1+1)*pow(2,1)-1; 
//     int li2=(lp2+1)*pow(2,2)-1; 
//     printf("li0=%3d li1=%3d li2=%3d\n",li0,li1,li2);
//   }
// }

template<class T>
bool PIRAMIDE<T>::i2p(int li, int ci, int sp, int& lp, int& cp)
// Coordenada de img(li,ci) para pyr[sp](lp,cp)
// sp e' escala. 0=resolucao fina original.
{ if (li<0 || v[0].rows<=li || ci<0 || v[0].cols<=ci || sp<0 || int(v.size())<=sp) return false;
  lp=arredonda(li+1,pow(2,sp))-1; if (lp<0) lp=0;
  cp=arredonda(ci+1,pow(2,sp))-1; if (cp<0) cp=0;
  if (lp<0 || v[sp].rows<=lp || cp<0 || v[sp].cols<=cp) return false;
  return true;
}

template<class T>
bool PIRAMIDE<T>::p2i(int lp, int cp, int sp, int& li, int& ci)
// Coordenada de pyr(lp,cp,sp) para img(li,ci)
// sp e' escala. 0=resolucao fina.
{ 
  if (sp<0 || int(v.size())<=sp) return false;
  if (lp<0 || v[sp].rows<=lp || cp<0 || v[sp].cols<=cp) return false; 
  li=(lp+1)*pow(2,sp)-1; 
  ci=(cp+1)*pow(2,sp)-1; 
  if (li<0 || v[0].rows<=li || ci<0 || v[0].cols<=ci) return false;
  return true;
}

template<class T>
void imp(PIRAMIDE<T>& p, string nome, bool vertical=true)
{ Mat_<T> a;
  for (unsigned i=0; i<p.v.size(); i++) {
    if (vertical) a=grudaV(a,p.v[i],1);
    else          a=grudaH(a,p.v[i],1);
  }
  imp(a,nome);
} 

template<class T>
void imp(PIRAMIDE<T>& p, Mat_<T>& sai, bool vertical=true)
{ sai.create(0,0);
  for (unsigned i=0; i<p.v.size(); i++) {
    if (vertical) sai=grudaV(sai,p.v[i],1);
    else          sai=grudaH(sai,p.v[i],1);
  }
}

template<class T1, class T2>
void cria(const PIRAMIDE<T1>& ent, PIRAMIDE<T2>& sai, T2 enche)
// cria piramide sai com mesmas dimensoes de ent e enche-a
{ if (!sai.v.empty()) sai.v.clear();
  for (unsigned i=0; i<ent.v.size(); i++) {
    Mat_<T2> a; sai.v.push_back(a);
    sai.v.back().create(ent.v[i].size());
    sai.v.back().setTo(enche);
  }
} 

template<class T1, class T2>
void cria(const PIRAMIDE<T1>& ent, PIRAMIDE<T2>& sai)
// cria piramide sai com mesmas dimensoes de ent
{ if (!sai.v.empty()) sai.v.clear();
  for (unsigned i=0; i<ent.v.size(); i++) {
    Mat_<T2> a; sai.v.push_back(a);
    sai.v.back().create(ent.v[i].size());
  }
} 

template<class T1, class T2>
void converte(const PIRAMIDE<T1>& ent, PIRAMIDE<T2>& sai)
// copia ent para sai
{ if (!sai.v.empty()) sai.v.clear();
  Mat_<T2> a; 
  for (unsigned i=0; i<ent.v.size(); i++) {
    converte(ent.v[i],a);
    sai.v.push_back(a);
  }
} 

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<GRY> grudaH(Mat_<GRY> a1, Mat_<GRY> a2, int nespaco=0, GRY backg=255);
EXPORTA Mat_<GRY> grudaV(Mat_<GRY> a1, Mat_<GRY> a2, int nespaco=0, GRY backg=255);
EXPORTA Mat_<COR> grudaH(Mat_<COR> a1, Mat_<COR> a2, int nespaco=0, COR backg=COR(255,255,255));
EXPORTA Mat_<COR> grudaV(Mat_<COR> a1, Mat_<COR> a2, int nespaco=0, COR backg=COR(255,255,255));

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<FLT> filtLin(Mat_<FLT> ent, Mat_<FLT> ker, int borderType=BORDER_REPLICATE);
// BORDER_CONSTANT para background zero.
// BORDER_DEFAULT nao se sabe o que faz.
EXPORTA void multFiltLin(Mat_<FLT> ent, vector< Mat_<FLT> >& ker, Mat_<FLT>& maxcorr, Mat_<int>& ind, 
                 int borderType=BORDER_REPLICATE);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA void calcAlinha(Mat_<COR> ref, Mat_<COR> a, int borda, Point& desloca, double& corr);
EXPORTA Mat_<COR> alinha(Mat_<COR> a, Point desloca);
EXPORTA Mat_<COR> alinha(Mat_<COR> ref, Mat_<COR> a, int borda);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// Retorna o elemento que estaria na posicao k se o vetor fosse ordenado.
// Estraga a imagem
template<class T>
T kth_element(Mat_<T>& a, int l, int k, int r)
{ if (!(l<=k && k<=r)) erro("Erro: deveria ter l<=k<=r");
  if (!(0<=l && r<int(a.total()))) erro("Erro: deveria estar entre 0 e total");
  MatIterator_<T> ai=a.begin();
  while (l<r) {
    T x=*(ai+k); int i=l; int j=r;
    do {
      while (*(ai+i)<x) i++;
      while (x<*(ai+j)) j--;
      if (i<=j) { swap( *(ai+i), *(ai+j) ); i++; j--; }
    } while (i<=j);
    if (j<k) l=i;
    if (k<i) r=j;
  }
  return *(ai+k);
}

// Retorna o elemento que estaria na posicao k se o vetor fosse ordenado.
template<class T>
T kth_element(Mat_<T>& a, int k)
{ Mat_<T> b; a.copyTo(b); return kth_element(b,0,k,b.total()-1); }

// Acha o valor mediana de um vetor.
// Retorna o elemento que estaria na posicao (n-1)/2 se o vetor fosse ordenado,
// onde n e' numero de elementos do vetor.
template<class T>
T mediana(Mat_<T>& a, int n=-1)
{ Mat_<T> b;
  a.copyTo(b);
  if (n==-1) n=a.total();
  return kth_element(a,0,(n-1)/2,n-1);
}

// Estraga a imagem
template<class T>
T percentil(Mat_<T>& a, double pct, int n=-1)
{ Mat_<T> v;
  a.copyTo(v);
  if (n==-1) n=v.total();
  int k=arredonda(pct*n/100.0);
  if (k<0) k=0;
  if (k>=n) k=n-1;
  return kth_element(v,0,k,n-1);
}

//<<<<<<< Difusao anisotropica em IMGDBL <<<<<<<<<<<<<<<<<<<<<
inline double perona1(double x, double sigma)
{ return 1 / (1+ (x*x/sigma*sigma) ); }

inline double perona2(double x, double sigma)
{ return exp( -(x*x)/(2*sigma*sigma) ); }

inline double tukey(double x, double sigma)
{ double sigma2=sigma*sigma; double x2=x*x;
  if (x2<=5.0*sigma2) {
    return elev2( 1 - (x2)/(5*sigma2) );
  } else return 0.0;
}

inline double isotro(double x, double sigma)
{ return 1.0; }

inline double degrau(double x, double sigma)
{ if (abs(x)<sigma) return 1.0;
  else return 0.0;
}

inline double linear(double x, double sigma)
{ if (abs(x)<sigma) return -abs(x)/sigma+1.0;
  else return 0.0;
}

inline double derivflux(double x, double sigma)
{ double sigma2=sigma*sigma; x=0.5507604246*x; double x2=x*x;
  if (x2<=sigma2) {
    return 1 - (6.0*x2)/(5.0*sigma2) + (x2*x2)/(5.0*sigma2*sigma2);
  } else return 0.0;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA M3d_<FLT> multEscala(Mat_<FLT> a, double escFim, int nEsc);
// Gera M3d da imagem a em multi-escala.
// Recomenda-se que a seja zero-mean corrected. Deve ter nl e nc impares.
// escInic e' sempre 1.0
// escFim deve ser menor que 1.0
// O resultado vai ter nEsc slices.

EXPORTA Mat_<FLT> aumentaCanvas(Mat_<FLT> a, int nl, int nc, int li=0, int ci=0, FLT backg=0.0);
// Cria imagem d(nl,nc), preenche com backg, e copia a a partir de d(li,ci)

EXPORTA Mat_<GRY> aumentaCanvas(Mat_<GRY> a, int nl, int nc, int li=0, int ci=0, GRY backg=0);
// Cria imagem d(nl,nc), preenche com backg, e copia a a partir de d(li,ci)

EXPORTA Mat_<FLT> matchTemplateSame(Mat_<FLT> a, Mat_<FLT> q, int method, FLT backg=0.0);
// Calcula matchTemplate, mantendo imagem de saida do mesmo tamanho que imagem de entrada
// Se nl de q for impar, marca no centro (o mesmo vale para nc)
// Se nl de q for par, marca no centro deslocado meio pixel para cima.
// Exemplo: Digamos que o ponto de maximo e' maxLoc
// Sejam int qxc=(q.cols-1)/2; int qyc=(q.rows-1)/2;
// Entao, q se ajusta em Rect(maxLoc-Point(qxc,qyc),q.size())

EXPORTA void multCorr(Mat_<FLT> a, M3d_<FLT> q, Mat_<FLT>& coef, Mat_<SHT>& ind);
// Chama matchTemplate( a, q[i], result, CV_TM_CCOEFF_NORMED ) para cada i

EXPORTA void multMatch(Mat_<FLT> a, Mat_<FLT> q, double escFim, int nEsc, FLT dontcare, Mat_<FLT>& coef, Mat_<SHT>& ind);
// Multi-scale match: Redimensiona q e procura todos em a.

EXPORTA void multMatch1(Mat_<FLT> a, Mat_<FLT> q, double escFim, int nEsc, FLT dontcare, FLT& maxVal, Point& maxLoc, int& maxS, double& scale);
// Multi-scale match: Redimensiona q e procura todos em a. Devolve somente o melhor match


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA M3d_<CORF> multEscala(Mat_<CORF> a, double escFim, int nEsc);
// Gera M3d da imagem a em multi-escala.
// Recomenda-se que a seja zero-mean corrected. Deve ter nl e nc impares.
// escInic e' sempre 1.0
// escFim deve ser menor que 1.0
// O resultado vai ter nEsc slices.
EXPORTA Mat_<CORF> dcReject(Mat_<CORF> a, CORF dontcare); // Elimina nivel DC (subtrai media) com dontcare
EXPORTA Mat_<CORF> dcReject(Mat_<COR> a, COR pseudodontcare); // Elimina nivel DC (subtrai media) com dontcare
EXPORTA void multCorr(Mat_<CORF> a, M3d_<CORF> q, Mat_<FLT>& coef, Mat_<SHT>& ind);
// Chama matchTemplate( a, q[i], result, CV_TM_CCOEFF_NORMED ) para cada i

inline CORF modulo(CORF a) { return CORF(abs(a[0]),abs(a[1]),abs(a[2])); }

EXPORTA Mat_<CORF> somatoriaUm(Mat_<CORF> a); // Faz somatoria absoluta da imagem dar um
EXPORTA void multMatch(Mat_<CORF> a, Mat_<CORF> q, double escFim, int nEsc, CORF dontcare, Mat_<FLT>& coef, Mat_<SHT>& ind);
EXPORTA void multMatch1(Mat_<CORF> a, Mat_<CORF> q, double escFim, int nEsc, CORF dontcare, FLT& maxVal, Point& maxLoc, int& maxS, double& scale);
EXPORTA void multMatch1(Mat_<COR> a, Mat_<COR> q, double escFim, int nEsc, COR dontcare, FLT& maxVal, Point& maxLoc, int& maxS, double& scale);

//<<<<<<<<<<<<<<<<<<<< ScaleMatchFLT <<<<<<<<<<<<<<<<<<<<<<
class ScaleMatchFLT { 
  // Scale-invariant matching for Mat_<FLT>. 
 public:
  vector< Mat_<FLT> > q; // scale-invariant query image q
  vector< Point > centro; 
  // centro de cada fatia de q (em deslocamento a partir do canto superior esquerdo)
  double escFim;
  int nEsc;
  FLT dontCare;

  void multEscala(Mat_<FLT> _q, double _escFim, int _nEsc, FLT _dontCare=-1);
  // Gera multi-escala da imagem _q e guarda em q
  // escInic e' sempre 1.0
  // escFim deve ser menor que 1.0
  // O resultado vai ter nEsc slices.
  // O tamanho da imagem em cada slice e' diferente.
  ScaleMatchFLT(Mat_<FLT> _q, double _escFim, int _nEsc, FLT _dontCare=-1) 
    { multEscala(_q,_escFim,_nEsc,_dontCare); }
  void match(Mat_<FLT> a, Mat_<FLT>& coef, Mat_<SHT>& ind, int method=CV_TM_CCORR);
  void match1(Mat_<FLT> a, FLT& maxVal, Point& maxLoc, int& maxS, double& scale, 
    int method1=CV_TM_CCORR);
  void matchVerify(Mat_<FLT> a, FLT& maxVal1, FLT& maxVal2, Point& maxLoc, 
    int& maxS, double& scale, int method1=CV_TM_CCORR, int method2=CV_TM_CCORR_NORMED);
  // Faz template matching por method1 obtendo maxVal1 em maxLoc. 
  // Depois, faz template matching por method2 em maxLoc obtendo maxVal2.
  void matchLocationVerify(Mat_<FLT> a, 
    FLT& maxVal1, FLT& maxVal2, Point& maxLoc1, Point& maxLoc2, 
    int& maxS, double& scale, int method1=CV_TM_CCORR, int method2=CV_TM_CCORR_NORMED);
  // Faz template matching por method1 obtendo maxVal1, maxLoc1, maxS e scale.
  // Depois, faz template matching por method2 na escala maxS, obtendo maxVal2, maxLoc2.
  void desenha(Mat_<COR>& a, FLT val, Point loc, int s, COR cor=COR{0,0,255}); 
};

// Isto deve ser reescrito
/*
class ScaleMatchCOR { //Scale-invariant matching for Mat_<CORF>. Utiliza CV_TM_CCORR (depende de contraste)
 public:
  vector< Mat_<CORF> > q; // scale-invariant query image q
  vector< Point > centro; // centro de cada fatia de q
  double escFim;
  int nEsc;
  CORF dontCare;

  void multEscala(Mat_<COR> _q, double _escFim, int _nEsc, CORF _dontCare=COR(-1,-1,-1));
  // Gera multi-escala da imagem _q e guarda em q
  // escInic e' sempre 1.0
  // escFim deve ser menor que 1.0
  // O resultado vai ter nEsc slices.
  // O tamanho da imagem em cada slice e' diferente.
  ScaleMatchCOR(Mat_<COR> _q, double _escFim, int _nEsc, CORF _dontCare=COR(-1,-1,-1)) { multEscala(_q,_escFim,_nEsc,_dontCare); }
  // Tem que atualizar as funcoes abaixo para ficarem iguais as de ScaleMatchFLT
  void match(Mat_<COR> a, Mat_<FLT>& coef, Mat_<SHT>& ind);
  void match1(Mat_<COR> a, FLT& maxVal, Point& maxLoc, int& maxS, double& scale);
};
*/

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<FLT> haar(const Mat_<FLT> a);
EXPORTA Mat_<FLT> unhaar(const Mat_<FLT> a);
EXPORTA Mat_<COR> haar2imc(const Mat_<FLT> f);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<GRY> filtro2d(Mat_<GRY> a, Mat_<FLT> k, int borderType=BORDER_DEFAULT);

EXPORTA Mat_<FLT> filtro2d(Mat_<FLT> a, Mat_<FLT> k, int borderType=BORDER_DEFAULT);

EXPORTA Mat_<FLT> trataModelo(Mat_<FLT> k, FLT dontcare=-1);
// Calcula 2*somatoriaUm(dcReject(k))

inline Mat_<GRY> filtroBorda0(Mat_<GRY> a, Mat_<FLT> ker)
{ return filtro2d(a,ker,BORDER_CONSTANT); }

inline Mat_<FLT> filtroBorda0(Mat_<FLT> a, Mat_<FLT> ker)
{ return filtro2d(a,ker,BORDER_CONSTANT); }

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
template<class T>
Mat_<T> cshift(const Mat_<T>& a, int n) 
// Circular shift de colunas de n posicoes. n>0: shift right. n<0: shift left
{ Mat_<T> d(a.size());
  for (int c=0; c<a.cols; c++)
    for (int l=0; l<a.rows; l++)
      d(l,modulo(c+n,a.cols))=a(l,c);
  return d;
}

/*
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA CvMat* pvConv(CvMat* A, CvMat* B, char modo); // modo: f:full s:same v:valid. Para modo=v, use pvConvV
EXPORTA CvMat* pvConvV(CvMat* A, CvMat* B); // modo valid +rapido

EXPORTA Mat_<FLT> pvConv(Mat_<FLT> a, Mat_<FLT> b, char modo); // modo: f:full s:same v:valid
EXPORTA Mat_<CPX> pvConv(Mat_<CPX> a, Mat_<CPX> b, char modo); // modo: f:full s:same v:valid

EXPORTA void pvMultConvV(Mat_<CPX> a, vector< Mat_<CPX> >& b, vector< Mat_<CPX> >& d); // modo valid
EXPORTA void pvMultConv(Mat_<CPX> a, vector< Mat_<CPX> >& b, vector< Mat_<CPX> >& d, char modo); // modo: f:full s:same v:valid

EXPORTA Mat_<CPX> pvPreConvV(Mat_<CPX> a, int b_rows, int b_cols); // modo valid
Mat_<CPX> pvPreConvV(Mat_<CPX> a, Mat_<CPX> b) { return pvPreConvV(a,b.rows,b.cols); }
EXPORTA Mat_<CPX> pvPosConvV(Mat_<CPX> a, Mat_<CPX> DFT_A, Mat_<CPX> b); // modo valid

EXPORTA Mat_<CPX> pvPreConv(Mat_<CPX> a, int b_rows, int b_cols, char modo); // modo: f:full s:same v:valid
Mat_<CPX> pvPreConv(Mat_<CPX> a, Mat_<CPX> b, char modo) { return pvPreConv(a,b.rows,b.cols,modo); }
EXPORTA Mat_<CPX> pvPosConv(Mat_<CPX> a, Mat_<CPX> DFT_A, Mat_<CPX> b, char modo); // modo: f:full s:same v:valid
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/

//<<<<<<<<<<<<<<<<<<<<<<<< FFT com resultado CPX <<<<<<<<<<<<<<<<<<<<<<<
//Se quiser fazer convolucao rapida, use conv2 ou convV
EXPORTA Mat_<CPX> fft2(Mat_<CPX> w, int nl=0, int nc=0);
EXPORTA Mat_<CPX> ifft2(Mat_<CPX> W, int nl=0, int nc=0);
EXPORTA Mat_<CPX> fft2(Mat_<FLT> w, int nl=0, int nc=0);
EXPORTA Mat_<CPX> ifft2(Mat_<FLT> W, int nl=0, int nc=0);

//<<<<<<<<<<<<<<<<<<<<<<<< DFT-based convolution <<<<<<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<FLT> conv2(Mat_<FLT> A, Mat_<FLT> B, char modo); // modo: f:full s:same v:valid. Para modo=v, tambem pode usar convV(A,B);
EXPORTA Mat_<CPX> conv2(Mat_<CPX> A, Mat_<CPX> B, char modo); // modo: f:full s:same v:valid. Para modo=v, tambem pode usar convV(A,B);
EXPORTA Mat_<FLT> convV(const Mat_<FLT>& A, const Mat_<FLT>& B); 
  // tambem pode usar conv2(A,B,'v');
EXPORTA Mat_<CPX> convV(const Mat_<CPX>& A, const Mat_<CPX>& B);
// EXPORTA M3d<FLT> multConvV(const M3d<FLT>& A, const Mat_<FLT>& B);
// EXPORTA M3d<CPX> multConvV(const M3d<CPX>& A, const Mat_<CPX>& B);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class EXPORTA STEPCONVFLT {
 public:
  Size dftSize; // optimal size
  char modo; // modo=f,s,v
  Size asize,bsize;
  void inicializa(int arows, int acols, int brows, int bcols, char pmodo); 
  void inicializa(Mat_<FLT> a, Mat_<FLT> b, char pmodo);
  STEPCONVFLT() { dftSize=Size(0,0); modo=' '; }
  STEPCONVFLT(int arows, int acols, int brows, int bcols, char pmodo) { inicializa(arows,acols,brows,bcols,pmodo); }
  STEPCONVFLT(Mat_<FLT> a, Mat_<FLT> b, char pmodo) { inicializa(a,b,pmodo); }
  Mat_<FLT> dftA(Mat_<FLT> a);
  Mat_<FLT> dftB(Mat_<FLT> b);
  Mat_<FLT> idft(Mat_<FLT> A, Mat_<FLT> B);
};

class EXPORTA STEPCONVCPX {
 public:
  Size dftSize; // optimal size
  char modo; // modo=f,s,v
  Size asize,bsize;
  void inicializa(int arows, int acols, int brows, int bcols, char pmodo); 
  void inicializa(Mat_<CPX> a, Mat_<CPX> b, char pmodo);
  STEPCONVCPX() { dftSize=Size(0,0); modo=' '; }
  STEPCONVCPX(int arows, int acols, int brows, int bcols, char pmodo) { inicializa(arows,acols,brows,bcols,pmodo); }
  STEPCONVCPX(Mat_<CPX> a, Mat_<CPX> b, char pmodo) { inicializa(a,b,pmodo); }
  Mat_<CPX> dftA(Mat_<CPX> a);
  Mat_<CPX> dftB(Mat_<CPX> b);
  Mat_<CPX> idft(Mat_<CPX> A, Mat_<CPX> B);
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//Nota: A funcao construcao (chamada por train) e' recursiva.
//Se esta funcao travar, aumente stack com a opcao de compilacao:
// "-Wl,-stack=5000000" no compilador GCC, 
// onde 5000000 é o tamanho do stack em bytes. 
// É necessário usar realmente os colchetes na chamada do compilador.
class EXPORTA CUTTREE {
  const int FIM=255;

  typedef struct { BYTE v,e; int r; } NOFILT;
  // e=indice do ee. Valor 255 (FIM) indica folha da arvore.
  // v=linha de corte < >=. Na folha v indica o valor de saida.
  // a subarvore a esquerda sempre comeca na proxima posicao do vetor filt
  // r=indice da subarvore a direita.

 public:
  Mat_<GRY> features;
  Mat_<GRY> saidas; // uma coluna
  vector<int> ee; 
  unsigned iee;
  vector<int> ind;
  vector<NOFILT> filt; 

  int folhas, repeticoescs, pixelsrepcs, pixelsolit;
  int np; // numero de amostras por folha
  char modoconf; // Pode ser m (media), f (mais frequente) ou a (minimiza erro absoluto)

  CUTTREE() {} // default constructor

  int insereFilt(void) {
    filt.push_back(NOFILT{0,0,0});
    return filt.size()-1;
  }

  void save(string st);
  void load(string st);
  void impFilt(void);

  BYTE valindee(int i);
  BYTE valind(int i); 
  int compara(int a, int b);
  int mediana(int l, int r);
  BYTE valor(int l, int r);
  void construcao(int l, int r, int pf);
  void train(Mat_<GRY> par_features, Mat_<GRY> par_saidas, vector<int> par_ee, char par_modoconf='f', int par_np=1);
  BYTE predict(Mat_<GRY> qu);
 // Faz interpolacao linear de FLT para GRY na entrada e saida
 private: double minx,maxx,miny,maxy,alphax,betax,alphay,betay;
 public:
  void train(Mat_<FLT> par_features, Mat_<FLT> par_saidas, vector<int> par_ee, char par_modoconf='f', int par_np=1);
  FLT predict(Mat_<FLT> qu);
};

//<<<<<<<<<<<<<<<<<<<<< ordena lexicografico <<<<<<<<<<<<<<<<<<<<<<<<<<<<
template<typename T>
bool linhaMenor(Mat_<T>& a, int p, int q)
{ for (int i=0; i<a.cols; i++) {
    if (a(p,i)<a(q,i)) return true;
    else if (a(p,i)>a(q,i)) return false;
  }
  return false;
}

template<typename T>
void trocaLinhas(Mat_<T>& a, int p, int q)
{ for (int i=0; i<a.cols; i++) 
    swap(a(p,i),a(q,i));
}

// Ordena do indice l a indice r.
template<typename T>
void ordenaLinhas(Mat_<T>& a, int l=0, int r=0)
{ if (l==0 && r==0) r=a.rows-1;
  assert(l<=r);
  int i=l; int j=r;
  int x=(l+r)/2;
  do {
    while (linhaMenor(a,i,x)) i++;
    while (linhaMenor(a,x,j)) j--;
    if (i<=j) { trocaLinhas(a,i,j); i++; j--; }
  } while (i<=j);
  if (l<j) ordenaLinhas(a,l,j);
  if (i<r) ordenaLinhas(a,i,r);
}

// Retorna a linha que estaria na posicao k se a matriz fosse ordenado linha a linha.
template<typename T>
Mat_<T> kesimaLinha(Mat_<T>& a, int k, int l=0, int r=0)
{ if (l==0 && r==0) r=a.rows-1;
  assert(l<=k && k<=r);
  Mat_<T> b; a.copyTo(b); // Para nao estragar a
  while (l<r) {
    int x=k; int i=l; int j=r;
    do {
      while (linhaMenor(b,i,x)) i++;
      while (linhaMenor(b,x,j)) j--;
      if (i<=j) { trocaLinhas(b,i,j); i++; j--; }
    } while (i<=j);
    if (j<k) l=i;
    if (k<i) r=j;
  }
  Mat_<T> d; b.row(k).copyTo(d);
  return d;
}

//<<<<<<<<<<<<<<< Gaussian noise: soma ruido gaussiano
EXPORTA Mat_<FLT> GaussianNoise(Mat_<FLT> a, double desvio, int semente=7); // desvio na escala de 0 a 1
EXPORTA Mat_<GRY> GaussianNoise(Mat_<GRY> a, double desvio, int semente=7); // desvio na escala de 0 a 255
EXPORTA Mat_<COR> GaussianNoise(Mat_<COR> a, double desvio, int semente=7); // desvio na escala de 0 a 255

//<<<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<GRY> rotacao(Mat_<GRY> ent, double deg);

EXPORTA Mat_<GRY> GaussianBlur(Mat_<GRY> ent, double sigma);
//void  GaussianBlur(  const  Mat&  src,  Mat&  dst,  Size  ksize,
//  double  sigmaX,  double  sigmaY=0,
//  int  borderType=BORDER DEFAULT  );

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// Acha o argumento (indice) do maior valor
template<class T>
int argMax(Mat_<T> a) { 
  T maximo=a(0); int indmax=0;
  for (int i=1; i<a.total(); i++)
    if (a(i)>maximo) {
      maximo=a(i); indmax=i;
    }
  return indmax;
}

// Acha o argumento (indice) do menor valor
template<class T>
int argMin(Mat_<T> a) { 
  T minimo=a(0); int indmin=0;
  for (int i=1; i<a.total(); i++)
    if (a[i]<minimo) {
      minimo=a(i); indmin=i;
    }
  return indmin;
}

//<<<<<<<<<<<<<<<<< MNIST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class MNIST {
 public:
  int nlado; bool inverte; bool ajustaBbox; string metodo;
  int na; vector< Mat_<GRY> > AX; vector<int> AY; Mat_<FLT> ax; Mat_<FLT> ay;
  int nq; vector< Mat_<GRY> > QX; vector<int> QY; Mat_<FLT> qx; Mat_<FLT> qy;
  Mat_<FLT> qp;

  MNIST(int _nlado=28, bool _inverte=true, bool _ajustaBbox=true, string _metodo="flann") {
    nlado=_nlado; inverte=_inverte; 
    ajustaBbox=_ajustaBbox; metodo=_metodo;
  }
  Mat_<GRY> bbox(Mat_<GRY> a); // Ajusta para bbox
  Mat_<FLT> bbox(Mat_<FLT> a); // Ajusta para bbox
  void leX(string nomeArq, int n, vector< Mat_<GRY> >& X, Mat_<FLT>& x); // funcao interna
  void leY(string nomeArq, int n, vector<int>& Y, Mat_<FLT>& y); // f. interna
  void le(string caminho="", int _na=60000, int _nq=10000);
  // Le banco de dados MNIST que fica no path caminho
  // ex: mnist.le("."); mnist.le("c:/diretorio");
  // Se _na ou _nq for zero, nao le o respectivo
  // ex: mnist.le(".",60000,0); 
  int contaErros(); 
  Mat_<GRY> geraSaida(Mat_<GRY> q, int qy, int qp); // f. interna
  Mat_<GRY> geraSaidaErros(int maxErr=0); 
  // Conta erros e gera imagem com maxErr primeiros erros
  Mat_<GRY> geraSaidaErros(int nl, int nc);
  // Gera uma imagem com os primeiros nl*nc digitos classificados erradamente
};

//<<<<<<<<<<<<<<<<<<< MnistFlann <<<<<<<<<<<<<<<<<<<<<<<<<<<
class MnistFlann : public MNIST {
 public:
  using MNIST::MNIST;
  flann::Index* ind=0;
  void train();
  FLT predictInterno(Mat_<FLT> query); //f. interna
  FLT predict(Mat_<FLT> query);
  void predict(); // Faz predicao de qx e armazena em qp
  void save(string nomeArq);
  void load(string nomeArq);
};

//Cifar10
EXPORTA void leCifar10(const string& nomearq,
             vector< Mat_<COR> >& images, vector<BYTE>& rotulos);


//<<<<<<<<<<<<<<<<<<<<<< descritores como sift <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
COR corAleat(int i); // Devolve uma cor aleatoria, comecando com RGBCMY
Mat_<COR> matMyShow(Mat_<GRY> im1, Mat_<GRY> im2, 
  const vector<DMatch>& matches,
  const vector<KeyPoint>& k1,
  const vector<KeyPoint>& k2,
  char modo='R',
  double raioKey=1.0);
//modo=r/n/R/N r=rich n=normal minuscula=azul maiuscula=multicor

Mat_<COR> keyMyShow(Mat_<GRY> a, const vector<KeyPoint>& k,
  char modo='R',
  double raioKey=1.0);
  //modo=r/n/R/N r=rich n=normal minuscula=azul maiuscula=multicor

} //namespace cek

#endif

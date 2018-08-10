#ifndef __CEKCG__
#define __CEKCG__

#include "cekeik.h"

namespace cek {
using namespace std;
using namespace cv;

//<<<<<<<<<<<<<<<< ponto <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
inline void dot(Mat_<GRY>& b, int l, int c, BYTE cor)
{ if (0<=l && l<b.rows && 0<=c && c<b.cols) b(l,c)=cor; }

inline void dot(Mat_<COR>& b, int l, int c, COR cor)
{ if (0<=l && l<b.rows && 0<=c && c<b.cols) b(l,c)=cor; }

inline void dot(Mat_<FLT>& b, int l, int c, FLT cor)
{ if (0<=l && l<b.rows && 0<=c && c<b.cols) b(l,c)=cor; }

inline void ponto(Mat_<GRY>& b, int l, int c, BYTE cor=0, int t=1)
{ if (t==1 && 0<=l && l<b.rows && 0<=c && c<b.cols) b(l,c)=cor;
  else {
    int t2=t/2;
    int linic=max(l-t2,0); int lfim=min(linic+t,b.rows-1);
    int cinic=max(c-t2,0); int cfim=min(cinic+t,b.cols-1);
    for (int ll=linic; ll<lfim; ll++)
      for (int cc=cinic; cc<cfim; cc++)
        b(ll,cc)=cor;
  }
}

inline void ponto(Mat_<COR>& b, int l, int c, COR cor=COR(0,0,0), int t=1)
{ if (t==1 && 0<=l && l<b.rows && 0<=c && c<b.cols) b(l,c)=cor;
  else {
    int t2=t/2;
    int linic=max(l-t2,0); int lfim=min(linic+t,b.rows-1);
    int cinic=max(c-t2,0); int cfim=min(cinic+t,b.cols-1);
    for (int ll=linic; ll<lfim; ll++)
      for (int cc=cinic; cc<cfim; cc++)
        b(ll,cc)=cor;
  }
}

inline void ponto(Mat_<FLT>& b, int l, int c, FLT cor=0.0, int t=1)
{ if (t==1 && 0<=l && l<b.rows && 0<=c && c<b.cols) b(l,c)=cor;
  else {
    int t2=t/2;
    int linic=max(l-t2,0); int lfim=min(linic+t,b.rows-1);
    int cinic=max(c-t2,0); int cfim=min(cinic+t,b.cols-1);
    for (int ll=linic; ll<lfim; ll++)
      for (int cc=cinic; cc<cfim; cc++)
        b(ll,cc)=cor;
  }
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
inline void pontoC(IMG_<GRY>& b, int x, int y, BYTE cor=0, int t=1)
{ int l,c; b.atC2atn(x,y,l,c);
  if (t==1 && 0<=l && l<b.mat.rows && 0<=c && c<b.mat.cols) b.mat(l,c)=cor;
  else {
    int t2=t/2;
    int linic=max(l-t2,0); int lfim=min(linic+t,b.rows-1);
    int cinic=max(c-t2,0); int cfim=min(cinic+t,b.cols-1);
    for (int ll=linic; ll<lfim; ll++)
      for (int cc=cinic; cc<cfim; cc++)
        b.mat(ll,cc)=cor;
  }
}

inline void pontoC(IMG_<COR>& b, int x, int y, COR cor=COR(0,0,0), int t=1)
{ int l,c; b.atC2atn(x,y,l,c);
  if (t==1 && 0<=l && l<b.mat.rows && 0<=c && c<b.mat.cols) b.mat(l,c)=cor;
  else {
    int t2=t/2;
    int linic=max(l-t2,0); int lfim=min(linic+t,b.rows-1);
    int cinic=max(c-t2,0); int cfim=min(cinic+t,b.cols-1);
    for (int ll=linic; ll<lfim; ll++)
      for (int cc=cinic; cc<cfim; cc++)
        b.mat(ll,cc)=cor;
  }
}

inline void pontoC(IMG_<FLT>& b, int x, int y,  FLT cor=0.0, int t=1)
{ int l,c; b.atC2atn(x,y,l,c);
  if (t==1 && 0<=l && l<b.mat.rows && 0<=c && c<b.mat.cols) b.mat(l,c)=cor;
  else {
    int t2=t/2;
    int linic=max(l-t2,0); int lfim=min(linic+t,b.rows-1);
    int cinic=max(c-t2,0); int cfim=min(cinic+t,b.cols-1);
    for (int ll=linic; ll<lfim; ll++)
      for (int cc=cinic; cc<cfim; cc++)
        b.mat(ll,cc)=cor;
  }
}

//<<<<<<<<<<<<<<<< Retas modo 'n' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA void reta(Mat_<GRY>& b, int l1, int c1, int l2, int c2, GRY cor=0, int largura=1);
EXPORTA void reta(Mat_<COR>& b, int l1, int c1, int l2, int c2, COR cor=COR(0,0,0), int largura=1);
EXPORTA void reta(Mat_<FLT>& b, int l1, int c1, int l2, int c2, FLT cor=0.0, int largura=1);

//<<<<<<<<<<<<<<<< Retas modo 'C' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA void retaC(IMG_<GRY>& b, int x1, int y1, int x2, int y2, GRY cor=0, int largura=1);
EXPORTA void retaC(IMG_<COR>& b, int x1, int y1, int x2, int y2, COR cor=COR(0,0,0), int largura=1);
EXPORTA void retaC(IMG_<FLT>& b, int x1, int y1, int x2, int y2, FLT cor=0.0, int largura=1);

//<<<<<<<<<<<<<<<< Caneta modo 'n' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA void moveTo(int l, int c);
EXPORTA void lineTo(Mat_<GRY>& a, int l, int c, GRY cor);
EXPORTA void lineTo(Mat_<COR>& a, int l, int c, COR cor);
EXPORTA void lineTo(Mat_<FLT>& a, int l, int c, FLT cor);

//<<<<<<<<<<<<<<<< Circulos modo 'n' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA void circulo(Mat_<GRY>& a, int l, int c, int r, GRY cor=0, int t=1);
//negative thickness means a filled circle
EXPORTA void circulo(Mat_<COR>& a, int l, int c, int r, COR cor=COR(0,0,0), int t=1);
EXPORTA void circuloC(IMG_<GRY>& a, int x, int y, int r, GRY cor=0, int t=1);
EXPORTA void circuloC(IMG_<COR>& a, int x, int y, int r, COR cor=COR(0,0,0), int t=1);

//<<<<<<<<<<<<<<<< Marcadores <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA void xis(Mat_<GRY>& b, int l, int c, int t=2, GRY cor=0);
EXPORTA void xis(Mat_<COR>& b, int l, int c, int t=2, COR cor=COR(0,0,0));
EXPORTA void cruz(Mat_<GRY>& b, int l, int c, int t=2, GRY cor=0);
EXPORTA void cruz(Mat_<COR>& b, int l, int c, int t=2, COR cor=COR(0,0,0));
EXPORTA void retang(Mat_<GRY>& a, int l1, int c1, int l2, int c2, GRY cor=0, int largura=1);
//negative thickness means a filled rectangle
EXPORTA void retang(Mat_<COR>& a, int l1, int c1, int l2, int c2, COR cor=COR(0,0,0), int largura=1);
EXPORTA void rotRetang(Mat_<GRY>& a, int lc, int cc, int eixol, int eixoc, GRY cor=0, int largura=1, double ang=0.0);
EXPORTA void rotRetang(Mat_<COR>& a, int lc, int cc, int eixol, int eixoc, COR cor=COR(0,0,0), int largura=1, double ang=0.0);
EXPORTA void rotRetang(Mat_<FLT>& a, int lc, int cc, int eixol, int eixoc, FLT cor=0.0, int largura=1, double ang=0.0);
EXPORTA void elipse(Mat_<GRY>& a, int lc, int cc, int dl, int dc, GRY cor=0, int largura=1, double ang=0.0);
EXPORTA void elipse(Mat_<COR>& a, int lc, int cc, int dl, int dc, COR cor=COR(0,0,0), int largura=1, double ang=0.0);
EXPORTA void drawRect(Mat_<COR>& a, Rect r, COR cor);

EXPORTA void marcaXadrez(Mat_<COR>& a, int l, int c, int t=4, COR cor1=COR(0,0,0), COR cor2=COR(255,255,255));
// O centro esta no canto inferior direito do quadrante superior esquerda
// Cores superior-esquerda, superior-direita

EXPORTA void marcaXadrez(Mat_<COR>& a, int l, int c, int t, COR cor1, COR cor2, COR cor3, COR cor4);
// O centro esta no canto inferior direito do quadrante superior esquerda
// Cores superior-esquerda, superior-direita, inferior-direita, inferior-esquerda

/*
//<<<<<<<<<<<<<<<< fill <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// versao lenta/correta pela definicao
EXPORTA void myFillCirculo(Mat_<GRY>& a, double lc, double cc, double raio, GRY cor=0); 
EXPORTA void myFillCirculo(Mat_<COR>& a, double lc, double cc, double raio, COR cor=COR(0,0,0));
EXPORTA void myFillCirculo(Mat_<FLT>& a, double lc, double cc, double raio, FLT cor=0.0);

EXPORTA void fillRetang(Mat_<GRY>& a, int l1, int c1, int l2, int c2, GRY cor=0);
EXPORTA void fillRetang(Mat_<COR>& a, int l1, int c1, int l2, int c2, COR cor=COR(0,0,0));

EXPORTA void fillRotRetang(Mat_<GRY>& a, int lc, int cc, int eixol, int eixoc, GRY cor=0, double ang=0.0);
EXPORTA void fillRotRetang(Mat_<COR>& a, int lc, int cc, int eixol, int eixoc, COR cor=COR(0,0,0), double ang=0.0);
EXPORTA void fillRotRetang(Mat_<FLT>& a, int lc, int cc, int eixol, int eixoc, FLT cor=0.0, double ang=0.0);
EXPORTA void myFillRotRetang(Mat_<GRY>& a, double lc, double cc, double eixol, double eixoc, GRY cor, double ang);
EXPORTA void myFillRotRetang(Mat_<COR>& a, double lc, double cc, double eixol, double eixoc, COR cor, double ang);
EXPORTA void myFillRotRetang(Mat_<FLT>& a, double lc, double cc, double eixol, double eixoc, FLT cor, double ang);

// versao rapida/ligeiramente errada OpenCV
EXPORTA void fillRotElipse(Mat_<GRY>& a, int lc, int cc, int dl, int dc, GRY cor=0, double ang=0.0); 
EXPORTA void fillRotElipse(Mat_<COR>& a, int lc, int cc, int dl, int dc, COR cor=COR(0,0,0), double ang=0.0);

// versao lenta/correta pela definicao
EXPORTA void myFillRotElipse(Mat_<GRY>& a, double lc, double cc, double eixol, double eixoc, GRY cor=0, double ang=0.0); 
EXPORTA void myFillRotElipse(Mat_<COR>& a, double lc, double cc, double eixol, double eixoc, COR cor=COR(0,0,0), double ang=0.0);
EXPORTA void myFillRotElipse(Mat_<FLT>& a, double lc, double cc, double eixol, double eixoc, FLT cor=0.0, double ang=0.0);
*/

//<<<<<<<<<<<<<<<< Flechas modo 'n' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA void flecha(Mat_<GRY>& a, int l1, int c1, int l2, int c2, GRY cor=0, int largura=1); // modo 'n'
EXPORTA void flecha(Mat_<COR>& a, int l1, int c1, int l2, int c2, COR cor=COR(0,0,0), int largura=1); // modo 'n'
EXPORTA void flecha(Mat_<FLT>& a, int l1, int c1, int l2, int c2, FLT cor=0.0, int largura=1); // modo 'n'

// Angulo zero = meio dia. O angulo cresce sentido anti-horario.
EXPORTA void relogioCircular(Mat_<GRY>& b, int l, int c, int r, double deg=0.0, BYTE cor=0, int t=1);
EXPORTA void relogioCircular(Mat_<COR>& b, int l, int c, int r, double deg=0.0, COR cor=COR(0,0,0), int t=1);
EXPORTA void relogioRetangular(Mat_<GRY>& a, int l, int c, int nl, int nc, double deg=0.0, BYTE cor=0, int t=1);
EXPORTA void relogioRetangular(Mat_<COR>& a, int l, int c, int nl, int nc, double deg=0.0, COR cor=COR(0,0,0), int t=1);

//<<<<<<<<<<<<<<<< puttxt <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//Cada caracter impresso ocupa 24-2*borda linhas e 18-2*borda colunas
//No caso default (fixedsys com borda=5), ocupa 14x8 pixels, com ampl=1.
EXPORTA void putTxt(Mat_<GRY>& ap, int la, int ca, string st, BYTE fore=0,         int ampl=1, bool transp=true, BYTE back=255);
EXPORTA void putTxt(Mat_<COR>& ap, int la, int ca, string st, COR fore=COR(0,0,0), int ampl=1, bool transp=true, COR back=COR(255,255,255));
EXPORTA void putTxtC(IMG_<GRY>& ap, int xa, int ya, string st, BYTE fore=0,         int ampl=1, bool transp=true, BYTE back=255);
EXPORTA void putTxtC(IMG_<COR>& ap, int xa, int ya, string st, COR fore=COR(0,0,0), int ampl=1, bool transp=true, COR back=COR(255,255,255));
EXPORTA void lefont(string nome, int bordap=5);

/*
//<<<<<<<<<<<<<< TSH <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// anti-horario:+1, alinhados:0 horario:-1
int tsh(PONTOI2 a, PONTOI2 b, PONTOI2 c);
int tsh(PONTO2 a, PONTO2 b, PONTO2 c);
// Devolve 0 se nao-cruza, 1 se cruza, -1 se alinhados
int cruza(PONTOI2 a, PONTOI2 b, PONTOI2 c, PONTOI2 d);
double pseudoangulo(PONTO2 v);
inline double pseudoangulo(PONTOI2 v) { return pseudoangulo(PONTO2(v.x(),v.y())); }
double pseudoangl1(PONTO2 p);
// Entre 0 e 4
// Caminho percorrido sobre losango (1,0) (0,1) (-1,0) (0,-1) ate' achar a interseccao com vetor
*/

//<<<<<<<<<<<<<<<<<< ret2esf <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
double arg(double x, double y);
// Calcula o angulo do ponto (x,y). M_PI_2=pi/2 e M_PI=3.14...
// Retorna valor entre 0 e 2*M_PI
/*
PONTO3 ret2esf(PONTO3 p);
// Converte coordenada retangular para esferica
// esf.x=rho (comprimento do vetor)
// esf.y=theta (ang no plano xy, entre 0 e 2*M_PI)
// esf.z=phi (descida, entre 0 e M_PI)
*/

Vec3f ret2esf(Vec3f p);
// Converte coordenada retangular para esferica
// esf.x=rho (comprimento do vetor)
// esf.y=theta (ang no plano xy, entre 0 e 2*M_PI)
// esf.z=phi (descida, entre 0 e M_PI)
Vec3f esf2ret(Vec3f esf);

/*
PONTO4 ret2esf(PONTO4 p);
// Converte coordenada retangular para esferica
// esf.x=rho (comprimento do vetor)
// esf.y=theta (ang no plano xy, entre 0 e 2*M_PI)
// esf.z=phi (descida de z, entre 0 e M_PI)
// esf.w=psi (descida de w, entre 0 e M_PI)
PONTO4 ret2esfl1(PONTO4 p);
// Converte coordenada retangular para esferica
// esf.x=rho (comprimento do vetor)
// esf.y=theta (ang no plano xy, entre 0 e 4) Nota: 0 e 4 sao iguais!
// esf.z=phi (descida de z, entre 0 e 2)
// esf.w=psi (descida de w, entre 0 e 2)

PONTO3 ret2esfz(PONTO3 p);
PONTO3 esfz2ret(PONTO3 esf);
PONTO3 ret2esfx(PONTO3 p);
PONTO3 esfx2ret(PONTO3 esf);
PONTO3 ret2esfy(PONTO3 p);
PONTO3 esfy2ret(PONTO3 esf);
*/

//<<<<<<<<<<<<<<<< POLYGON <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
typedef vector<Point> POLYGON;

EXPORTA void polygon(Mat_<GRY>& a, POLYGON p, GRY cor=0, int largura=1);
EXPORTA void polygon(Mat_<COR>& a, POLYGON p, COR cor=COR(0,0,0), int largura=1);
EXPORTA void polygon(Mat_<FLT>& a, POLYGON p, FLT cor=0.0, int largura=1);
EXPORTA void fillPolygon(Mat_<GRY>& a, POLYGON p, GRY cor=0);
EXPORTA void fillPolygon(Mat_<COR>& a, POLYGON p, COR cor=COR(0,0,0));
EXPORTA void fillPolygon(Mat_<FLT>& a, POLYGON p, FLT cor=0);

// Convgon = Polygon convexo. As rotinas abaixo so funcionam para poligonos convexos
EXPORTA void fillConvgon(Mat_<GRY>& a, POLYGON p, GRY cor);
EXPORTA void fillConvgon(Mat_<COR>& a, POLYGON p, COR cor);
EXPORTA void fillConvgon(Mat_<FLT>& a, POLYGON p, FLT cor);

EXPORTA void rotatePolygon(POLYGON& p, Point centro, double ang, POLYGON& q);
// permite processamento in-place (p==q)

/*
//<<<<<<<<<<<<<<<< thickline <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void thickline(IMGBIN& a, int l1, int c1, int l2, int c2, bool cor, int largura);
void thickline(IMG_<GRY>& a, int l1, int c1, int l2, int c2, BYTE cor, int largura);
void thickline(IMG_<COR>& a, int l1, int c1, int l2, int c2, COR cor,  int largura);
*/

typedef Mat_<FLT> SHAPEF; //deve ter 2 colunas: x e y
typedef Mat_<CPX> SHAPEX; //deve ter 1 coluna: real e imag

EXPORTA SHAPEX SHAPEF2X(SHAPEF zf);
EXPORTA SHAPEF SHAPEX2F(SHAPEX zx);
EXPORTA void mostraShape(SHAPEF z);

// SHAPE derivada1(SHAPE u); // Supondo h==1.0
// SHAPE derivada2(SHAPE u); // Supondo h==1.0

class MapU2D {
 public:
  Point2f MinU, MaxU;
  Point2i MaxD; // Para ter imagem cheia: MaxD.x=nc-1 e MaxD.y=nl-1.
                // Para ter 2 linhas/colunas brancas: MaxD.x=nc-5 e MaxD.y=nl-5.
  bool GrudaY;
  double fatx,faty;
  Point2i Desloc;
  int borda;

  MapU2D() { MinU=Point2f(infinito,infinito); MaxU=Point2f(-infinito,-infinito); borda=0; }

  void show();
  Point2i u2d(Point2f p);
  void inicshape(SHAPEF& u, int nl, int nc, int bordap, bool keepar=true);
};

EXPORTA void shapeVert(SHAPEF& u, Mat_<GRY>& b, bool cor);
EXPORTA void shape2img(MapU2D m, SHAPEF& u, Mat_<GRY>& b, bool cor, bool fechado);
EXPORTA void shape2img(SHAPEF& u, Mat_<GRY>& b, bool cor, bool fechado, bool vert);
EXPORTA void shapeGrade(MapU2D m, Mat_<GRY>& b, double gradex, double gradey, bool cor);

/*
//<<<<<<<<<<<<< SHAPE IMG_<COR> <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void shapevert(MapU2D m, SHAPE& u, IMG_<COR>& b, COR cor=COR(255,0,0));
void shapevert(SHAPE& u, IMG_<COR>& b, COR cor=COR(255,0,0));
// Marca vertices de shape com ponto

void shape2img(MapU2D m, SHAPE& u, IMG_<COR>& b, COR cor=COR(0,0,0), bool fechado=true);
void shape2img(SHAPE& u, IMG_<COR>& b, COR cor=COR(0,0,0), bool fechado=true, bool vert=false);
// Desenha o shape como poligono

void shapegrade(MapU2D m, IMG_<COR>& sai, double gradex, double gradey, COR cor=COR(0,0,0));
// Desenha grade

//<<<<<<<<<<<<<< bspline de shape <<<<<<<<<<<<<<<<<<<<<
double L(double x); // Funcao base de bspline
double L1(double x); // Primeira derivada da funcao base de bspline
double L2(double x); // Segunda derivada da funcao base de bspline
double Lg(double t, int gr); // Funcao base de bspline de grau generico (1 2 ou 3)
PONTO2 bspline(SHAPE& v, double t, char modo='n'); // 0<=t<1
PONTO2 bspline1(SHAPE& v, double t, char modo='n'); // Primeira derivada de bspline, 0<=t<1
PONTO2 bspline2(SHAPE& v, double t, char modo='n'); // Segunda derivada de bspline, 0<=t<1
PONTO2 bsplineg(SHAPE& v, double t, int gr, char modo='n'); // Bspline de grau generico (1 2 ou 3)
*/

//<<<<<<<<<<<<<< funcao real <<<<<<<<<<<<<<<<<<<<<<<<<<
typedef vector<double> FUNCAO;
EXPORTA void FuncaoMinMax(FUNCAO& u, double& MinU, double& MaxU);
// void funcao2imgbin(FUNCAO& u, IMGBIN& b,
//                bool cor=preto, bool vertice=true,
//                double MinU=-infinito, double MaxU=infinito, double grade=infinito);
// Deixa 1 linha/coluna branca nos cantos.
// Imagem b deve ter 2 colunas/linhas a mais do que o tamanho desejado
// Se MinU != -infinito, MinU nao e' alterado
// Se MaxU != +infinito, MaxU nao e' alterado
EXPORTA Mat_<GRY> simpleFuncao2matgry(FUNCAO u, int nl, char modo=':');
// Imagem de saida sempre tem nc=u.n
// modo: '.'=tracejado  '-'=continuo  ':'=barras(default)
EXPORTA Mat_<COR> simpleFuncao2matcor(FUNCAO u, int nl, char modo=':', COR cor=COR(0,0,0));
// Imagem de saida sempre tem nc=u.n
// modo: '.'=tracejado  '-'=continuo  ':'=barras(default)
//void fun2shp(FUNCAO f, SHAPE& s);
// Converte FUNCAO em SHAPE

//<<<<<<<<<<<<<<  RST 2D: devolve matrizes 3x3 <<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<FLT> matrizTranslacao(double x, double y);
EXPORTA Mat_<FLT> matrizTranslacao(Point2f p);
EXPORTA Mat_<FLT> matrizRotacao(double angDeg);
EXPORTA Mat_<FLT> matrizRotacaoCentro(double angDeg, Point2f p);
EXPORTA Point3f operator*(Mat_<FLT> M, Point3f p);

} //namespace cek

#endif



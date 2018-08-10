#include "cekeikon.h"
#include <queue>

namespace cek {

//<<<<<<<<<<<<<<<< Retas modo 'n' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void reta(Mat_<GRY>& b, int l1, int c1, int l2, int c2, GRY cor, int largura)
{ line(b, Point(c1,l1), Point(c2,l2), toScalar(cor), largura, 8, 0);
}

void reta(Mat_<COR>& b, int l1, int c1, int l2, int c2, COR cor, int largura)
{ line(b, Point(c1,l1), Point(c2,l2), toScalar(cor), largura, 8, 0);
}

void reta(Mat_<FLT>& b, int l1, int c1, int l2, int c2, FLT cor, int largura)
{ line(b, Point(c1,l1), Point(c2,l2), toScalar(cor), largura, 8, 0);
}

//<<<<<<<<<<<<<<<< Retas modo 'C' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void retaC(IMG_<GRY>& b, int x1, int y1, int x2, int y2, GRY cor, int largura)
{ int l1,c1;
  b.atC2atn(x1,y1,l1,c1);
  int l2,c2;
  b.atC2atn(x2,y2,l2,c2);
  line(b.mat, Point(c1,l1), Point(c2,l2), toScalar(cor), largura, 8, 0);
}

void retaC(IMG_<COR>& b, int x1, int y1, int x2, int y2, COR cor, int largura)
{ int l1,c1;
  b.atC2atn(x1,y1,l1,c1);
  int l2,c2;
  b.atC2atn(x2,y2,l2,c2);
  line(b.mat, Point(c1,l1), Point(c2,l2), toScalar(cor), largura, 8, 0);
}

void retaC(IMG_<FLT>& b, int x1, int y1, int x2, int y2, FLT cor, int largura)
{ int l1,c1;
  b.atC2atn(x1,y1,l1,c1);
  int l2,c2;
  b.atC2atn(x2,y2,l2,c2);
  line(b.mat, Point(c1,l1), Point(c2,l2), toScalar(cor), largura, 8, 0);
}

//<<<<<<<<<<<<<<<< Retas usando caneta modo 'n' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int lcaneta=0;
int ccaneta=0;

void moveTo(int l, int c)
{ lcaneta=l; ccaneta=c; }

void lineTo(Mat_<GRY>& a, int l, int c, GRY cor)
{ reta(a,lcaneta,ccaneta,l,c,cor); lcaneta=l; ccaneta=c; }

void lineTo(Mat_<COR>& a, int l, int c, COR cor)
{ reta(a,lcaneta,ccaneta,l,c,cor); lcaneta=l; ccaneta=c; }

void lineTo(Mat_<FLT>& a, int l, int c, FLT cor)
{ reta(a,lcaneta,ccaneta,l,c,cor); lcaneta=l; ccaneta=c; }

//<<<<<<<<<<<<<<<< Circulos modo 'n' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void circulo(Mat_<GRY>& a, int l, int c, int r, GRY cor, int t)
{ circle(a, Point(c,l), r, toScalar(cor), t); }

void circulo(Mat_<COR>& a, int l, int c, int r, COR cor, int t)
{ circle(a, Point(c,l), r, toScalar(cor), t); }

void circuloC(IMG_<GRY>& a, int x, int y, int r, GRY cor, int t)
{ int l,c;
  a.atC2atn(x,y,l,c);
  circle(a.mat, Point(c,l), r, toScalar(cor), t); 
}

void circuloC(IMG_<COR>& a, int x, int y, int r, COR cor, int t)
{ int l,c;
  a.atC2atn(x,y,l,c);
  circle(a.mat, Point(c,l), r, toScalar(cor), t); 
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*
void fillCircle(Mat& a, Point center, int radius, const Scalar& color)
{ if (a.type()==CV_8UC1) {
    uchar cor=scalar2g(color);
    for (int y=min(center.y-radius,0); y<=max(center.y+radius,a.rows); y++)
      for (int x=min(center.x-radius,0); x<=max(center.x+radius,a.cols); x++)
        if (elev2(x-center.x)+elev2(y-center.y)<elev2(radius)) 
          a.acg(y,x)=cor;
  } else if (a.type()==CV_8UC3) {
    Vec3b cor=scalar2c(color);
    for (int y=min(center.y-radius,0); y<=max(center.y+radius,a.rows); y++)
      for (int x=min(center.x-radius,0); x<=max(center.x+radius,a.cols); x++)
        if (elev2(x-center.x)+elev2(y-center.y)<elev2(radius)) 
          a.acc(y,x)=cor;
  }
}
*/

//<<<<<<<<<<<<<<<<<< marcadores <<<<<<<<<<<<<<<<<<<<<<<<
void xis(Mat_<GRY>& b, int l, int c, int t, BYTE cor)
{ reta(b,l-t,c-t,l+t,c+t,cor); 
  reta(b,l-t,c+t,l+t,c-t,cor); 
}

void xis(Mat_<COR>& b, int l, int c, int t, COR cor)
{ reta(b,l-t,c-t,l+t,c+t,cor); 
  reta(b,l-t,c+t,l+t,c-t,cor); 
}

void cruz(Mat_<GRY>& b, int l, int c, int t, BYTE cor)
{ reta(b,l,c-t,l,c+t,cor); 
  reta(b,l-t,c,l+t,c,cor); 
}

void cruz(Mat_<COR>& b, int l, int c, int t, COR cor)
{ reta(b,l,c-t,l,c+t,cor); 
  reta(b,l-t,c,l+t,c,cor); 
}

void retang(Mat_<GRY>& a, int l1, int c1, int l2, int c2, GRY cor, int largura)
{ reta(a,l1,c1,l1,c2,cor,largura);
  reta(a,l1,c2,l2,c2,cor,largura);
  reta(a,l2,c2,l2,c1,cor,largura);
  reta(a,l2,c1,l1,c1,cor,largura);
}

void retang(Mat_<COR>& a, int l1, int c1, int l2, int c2, COR cor, int largura)
{ reta(a,l1,c1,l1,c2,cor,largura);
  reta(a,l1,c2,l2,c2,cor,largura);
  reta(a,l2,c2,l2,c1,cor,largura);
  reta(a,l2,c1,l1,c1,cor,largura);
}

void rotRetang(Mat_<GRY>& a, int lc, int cc, int eixol, int eixoc, GRY cor, int largura, double ang)
{ POLYGON ret(4);
  ret[0]=Point(cc-eixoc,lc-eixol);
  ret[1]=Point(cc+eixoc,lc-eixol);
  ret[2]=Point(cc+eixoc,lc+eixol);
  ret[3]=Point(cc-eixoc,lc+eixol);
  rotatePolygon(ret,Point(cc,lc),ang,ret);
  polygon(a,ret,cor);
}

void rotRetang(Mat_<COR>& a, int lc, int cc, int eixol, int eixoc, COR cor, int largura, double ang)
{ POLYGON ret(4);
  ret[0]=Point(cc-eixoc,lc-eixol);
  ret[1]=Point(cc+eixoc,lc-eixol);
  ret[2]=Point(cc+eixoc,lc+eixol);
  ret[3]=Point(cc-eixoc,lc+eixol);
  rotatePolygon(ret,Point(cc,lc),ang,ret);
  polygon(a,ret,cor);
}

void rotRetang(Mat_<FLT>& a, int lc, int cc, int eixol, int eixoc, FLT cor, int largura, double ang)
{ POLYGON ret(4);
  ret[0]=Point(cc-eixoc,lc-eixol);
  ret[1]=Point(cc+eixoc,lc-eixol);
  ret[2]=Point(cc+eixoc,lc+eixol);
  ret[3]=Point(cc-eixoc,lc+eixol);
  rotatePolygon(ret,Point(cc,lc),ang,ret);
  polygon(a,ret,cor);
}

void elipse(Mat_<GRY>& a, int lc, int cc, int dl, int dc, GRY cor, int largura, double ang)
{ ellipse(a,Point(cc,lc),Size(dc/2,dl/2),ang,0,360,Scalar(cor),largura);
}

void elipse(Mat_<COR>& a, int lc, int cc, int dl, int dc, COR cor, int largura, double ang)
{ ellipse(a,Point(cc,lc),Size(dc/2,dl/2),ang,0,360,Scalar(cor[0],cor[1],cor[2]),largura);
}

void drawRect(Mat_<COR>& a, Rect r, COR cor)
{ reta(a, r.y,          r.x,         r.y,          r.x+r.width, cor);
  reta(a, r.y,          r.x+r.width, r.y+r.height, r.x+r.width, cor);
  reta(a, r.y+r.height, r.x+r.width, r.y+r.height, r.x,         cor);
  reta(a, r.y+r.height, r.x,         r.y,          r.x,         cor);
}

void marcaXadrez(Mat_<COR>& a, int l, int c, int t, COR cor1, COR cor2)
// O centro esta no canto inferior direito do quadrante superior esquerda
{ 
  rectangle(a, Rect(c-t+1,l-t+1,t,t), Scalar(cor1),CV_FILLED);
  rectangle(a, Rect(c+1,  l-t+1,t,t), Scalar(cor2),CV_FILLED);
  rectangle(a, Rect(c+1,  l+1,  t,t), Scalar(cor1),CV_FILLED);
  rectangle(a, Rect(c-t+1,l+1,  t,t), Scalar(cor2),CV_FILLED);
}  

void marcaXadrez(Mat_<COR>& a, int l, int c, int t, COR cor1, COR cor2, COR cor3, COR cor4)
// O centro esta no canto inferior direito do quadrante superior esquerda
{ 
  rectangle(a, Rect(c-t+1,l-t+1,t,t), Scalar(cor1),CV_FILLED);
  rectangle(a, Rect(c+1,  l-t+1,t,t), Scalar(cor2),CV_FILLED);
  rectangle(a, Rect(c+1,  l+1,  t,t), Scalar(cor3),CV_FILLED);
  rectangle(a, Rect(c-t+1,l+1,  t,t), Scalar(cor4),CV_FILLED);
}  

/*
//<<<<<<<<<<<<<<<< fill <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void myFillCirculo(Mat_<GRY>& a, double lc, double cc, double raio, GRY cor)
{ int r=teto(raio);
  for (int l=-r; l<=r; l++)
    for (int c=-r; c<=r; c++) {
      if (elev2(l)+elev2(c)<=elev2(r)+epsilon) {
        dot(a,arredonda(lc+l),arredonda(cc+c),cor);
      }
    }
}

void myFillCirculo(Mat_<COR>& a, double lc, double cc, double raio, COR cor)
{ int r=teto(raio);
  for (int l=-r; l<=r; l++)
    for (int c=-r; c<=r; c++) {
      if (elev2(l)+elev2(c)<=elev2(r)+epsilon) {
        dot(a,arredonda(lc+l),arredonda(cc+c),cor);
      }
    }
}

void myFillCirculo(Mat_<FLT>& a, double lc, double cc, double raio, FLT cor)
{ int r=teto(raio);
  for (int l=-r; l<=r; l++)
    for (int c=-r; c<=r; c++) {
      if (elev2(l)+elev2(c)<=elev2(r)+epsilon) {
        dot(a,arredonda(lc+l),arredonda(cc+c),cor);
      }
    }
}

void fillRetang(Mat_<GRY>& a, int l1, int c1, int l2, int c2, GRY cor)
{ rectangle(a, Point(c1,l1), Point(c2,l2), Scalar(cor),  CV_FILLED); }
// { for (int l=l1; l<=l2; l++)
//     for (int c=c1; c<=c2; c++)
//       a(l,c)=cor;
// }

void fillRetang(Mat_<COR>& a, int l1, int c1, int l2, int c2, COR cor)
{ rectangle(a, Point(c1,l1), Point(c2,l2), toScalar(cor),  CV_FILLED); }
// { for (int l=l1; l<=l2; l++)
//     for (int c=c1; c<=c2; c++)
//       a(l,c)=cor;
// }

void fillRotRetang(Mat_<GRY>& a, int lc, int cc, int eixol, int eixoc, GRY cor, double ang)
{ POLYGON ret(4);
  ret[0]=Point(cc-eixoc,lc-eixol);
  ret[1]=Point(cc+eixoc,lc-eixol);
  ret[2]=Point(cc+eixoc,lc+eixol);
  ret[3]=Point(cc-eixoc,lc+eixol);
  rotatePolygon(ret,Point(cc,lc),ang,ret);
  fillConvgon(a,ret,cor);
}

void fillRotRetang(Mat_<COR>& a, int lc, int cc, int eixol, int eixoc, COR cor, double ang)
{ POLYGON ret(4);
  ret[0]=Point(cc-eixoc,lc-eixol);
  ret[1]=Point(cc+eixoc,lc-eixol);
  ret[2]=Point(cc+eixoc,lc+eixol);
  ret[3]=Point(cc-eixoc,lc+eixol);
  rotatePolygon(ret,Point(cc,lc),ang,ret);
  fillConvgon(a,ret,cor);
}

void fillRotRetang(Mat_<FLT>& a, int lc, int cc, int eixol, int eixoc, FLT cor, double ang)
{ POLYGON ret(4);
  ret[0]=Point(cc-eixoc,lc-eixol);
  ret[1]=Point(cc+eixoc,lc-eixol);
  ret[2]=Point(cc+eixoc,lc+eixol);
  ret[3]=Point(cc-eixoc,lc+eixol);
  rotatePolygon(ret,Point(cc,lc),ang,ret);
  fillConvgon(a,ret,cor);
}

void myFillRotRetang(Mat_<GRY>& a, double lc, double cc, double eixol, double eixoc, GRY cor, double ang)
// versao lenta/correta pela definicao
{ int maxeixo=teto(sqrt(2.0)*max(eixol,eixoc));
  Mat_<double> R=getRotationMatrix2D(Point(0,0),-ang,1.0); // R1_{2x3}
  Mat_<DBL> p(3,1); Mat_<DBL> q(2,1);
  for (int l=-maxeixo; l<maxeixo; l++)
    for (int c=-maxeixo; c<maxeixo; c++) {
      p(0,0)=c; p(1,0)=l; p(2,0)=1;
      q=R*p;
      if (-eixoc<=q(0,0) && q(0,0)<=eixoc && -eixol<=q(1,0) && q(1,0)<=eixol) {
        dot(a,arredonda(lc+l),arredonda(cc+c),cor);
      }
    }
}

void myFillRotRetang(Mat_<COR>& a, double lc, double cc, double eixol, double eixoc, COR cor, double ang)
// versao lenta/correta pela definicao
{ int maxeixo=teto(sqrt(2.0)*max(eixol,eixoc));
  Mat_<double> R=getRotationMatrix2D(Point(0,0),-ang,1.0); // R1_{2x3}
  Mat_<DBL> p(3,1); Mat_<DBL> q(2,1);
  for (int l=-maxeixo; l<maxeixo; l++)
    for (int c=-maxeixo; c<maxeixo; c++) {
      p(0,0)=c; p(1,0)=l; p(2,0)=1;
      q=R*p;
      if (-eixoc<=q(0,0) && q(0,0)<=eixoc && -eixol<=q(1,0) && q(1,0)<=eixol) {
        dot(a,arredonda(lc+l),arredonda(cc+c),cor);
      }
    }
}

void myFillRotRetang(Mat_<FLT>& a, double lc, double cc, double eixol, double eixoc, FLT cor, double ang)
// versao lenta/correta pela definicao
{ int maxeixo=teto(sqrt(2.0)*max(eixol,eixoc));
  Mat_<double> R=getRotationMatrix2D(Point(0,0),-ang,1.0); // R1_{2x3}
  Mat_<DBL> p(3,1); Mat_<DBL> q(2,1);
  for (int l=-maxeixo; l<maxeixo; l++)
    for (int c=-maxeixo; c<maxeixo; c++) {
      p(0,0)=c; p(1,0)=l; p(2,0)=1;
      q=R*p;
      if (-eixoc<=q(0,0) && q(0,0)<=eixoc && -eixol<=q(1,0) && q(1,0)<=eixol) {
        dot(a,arredonda(lc+l),arredonda(cc+c),cor);
      }
    }
}

void fillRotElipse(Mat_<GRY>& a, int lc, int cc, int dl, int dc, GRY cor, double ang)
// versao rapida/ligeiramente errada OpenCV
{ ellipse(a,Point(cc,lc),Size(dc/2,dl/2),ang,0,360,Scalar(cor),-1);
}

void fillRotElipse(Mat_<COR>& a, int lc, int cc, int dl, int dc, COR cor, double ang)
// versao rapida/ligeiramente errada OpenCV
{ ellipse(a,Point(cc,lc),Size(dc/2,dl/2),ang,0,360,Scalar(cor[0],cor[1],cor[2]),-1);
}

void myFillRotElipse(Mat_<GRY>& a, double lc, double cc, double eixol, double eixoc, GRY cor, double ang)
// versao lenta/correta pela definicao
{ int maxeixo=teto(max(eixol,eixoc));
  Mat_<double> R=getRotationMatrix2D(Point(0,0),-ang,1.0); // R1_{2x3}
  Mat_<DBL> p(3,1); Mat_<DBL> q(2,1);
  for (int l=-maxeixo; l<=maxeixo; l++)
    for (int c=-maxeixo; c<=maxeixo; c++) {
      p(0,0)=c; p(1,0)=l; p(2,0)=1;
      q=R*p;
      if (elev2(q(0,0)/eixoc)+elev2(q(1,0)/eixol)<=1.0) {
        dot(a,arredonda(lc+l),arredonda(cc+c),cor);
      }
    }
}

void myFillRotElipse(Mat_<COR>& a, double lc, double cc, double eixol, double eixoc, COR cor, double ang)
// versao lenta/correta pela definicao
{ int maxeixo=teto(max(eixol,eixoc));
  Mat_<double> R=getRotationMatrix2D(Point(0,0),-ang,1.0); // R1_{2x3}
  Mat_<DBL> p(3,1); Mat_<DBL> q(2,1);
  for (int l=-maxeixo; l<=maxeixo; l++)
    for (int c=-maxeixo; c<=maxeixo; c++) {
      p(0,0)=c; p(1,0)=l; p(2,0)=1;
      q=R*p;
      if (elev2(q(0,0)/eixoc)+elev2(q(1,0)/eixol)<=1.0) {
        dot(a,arredonda(lc+l),arredonda(cc+c),cor);
      }
    }
}

void myFillRotElipse(Mat_<FLT>& a, double lc, double cc, double eixol, double eixoc, FLT cor, double ang)
// versao lenta/correta pela definicao
{ int maxeixo=teto(max(eixol,eixoc));
  Mat_<double> R=getRotationMatrix2D(Point(0,0),-ang,1.0); // R1_{2x3}
  Mat_<DBL> p(3,1); Mat_<DBL> q(2,1);
  for (int l=-maxeixo; l<=maxeixo; l++)
    for (int c=-maxeixo; c<=maxeixo; c++) {
      p(0,0)=c; p(1,0)=l; p(2,0)=1;
      q=R*p;
      if (elev2(q(0,0)/eixoc)+elev2(q(1,0)/eixol)<=1.0) {
        dot(a,arredonda(lc+l),arredonda(cc+c),cor);
      }
    }
}
*/

//<<<<<<<<<<<<<<<< Flechas modo 'n' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void flecha(Mat_<GRY>& a, int l1, int c1, int l2, int c2, GRY cor, int largura)
{ reta(a,l1,c1,l2,c2,cor,largura);
  if (l1==l2 && c1==c2) return;

  CPXD x=CPXD(c1,-l1)-CPXD(c2,-l2);
  double ang=arg(x);
  double dis=5.0;
  CPXD x3=CPXD(dis*cos(ang-M_PI/4.0),dis*sin(ang-M_PI/4.0));
  CPXD x4=CPXD(dis*cos(ang+M_PI/4.0),dis*sin(ang+M_PI/4.0));

  int l3=l2-arredonda(imag(x3));
  int c3=c2+arredonda(real(x3));
  reta(a,l2,c2,l3,c3,cor,largura);

  int l4=l2-arredonda(imag(x4));
  int c4=c2+arredonda(real(x4));
  reta(a,l2,c2,l4,c4,cor,largura);
}

void flecha(Mat_<COR>& a, int l1, int c1, int l2, int c2, COR cor, int largura)
{ reta(a,l1,c1,l2,c2,cor,largura);
  if (l1==l2 && c1==c2) return;

  CPXD x=CPXD(c1,-l1)-CPXD(c2,-l2);
  double ang=arg(x);
  double dis=5.0;
  CPXD x3=CPXD(dis*cos(ang-M_PI/4.0),dis*sin(ang-M_PI/4.0));
  CPXD x4=CPXD(dis*cos(ang+M_PI/4.0),dis*sin(ang+M_PI/4.0));

  int l3=l2-arredonda(imag(x3));
  int c3=c2+arredonda(real(x3));

  reta(a,l2,c2,l3,c3,cor,largura);

  int l4=l2-arredonda(imag(x4));
  int c4=c2+arredonda(real(x4));
  reta(a,l2,c2,l4,c4,cor,largura);
}

void flecha(Mat_<FLT>& a, int l1, int c1, int l2, int c2, FLT cor, int largura)
{ reta(a,l1,c1,l2,c2,cor,largura);
  if (l1==l2 && c1==c2) return;

  CPXD x=CPXD(c1,-l1)-CPXD(c2,-l2);
  double ang=arg(x);
  double dis=5.0;
  CPXD x3=CPXD(dis*cos(ang-M_PI/4.0),dis*sin(ang-M_PI/4.0));
  CPXD x4=CPXD(dis*cos(ang+M_PI/4.0),dis*sin(ang+M_PI/4.0));

  int l3=l2-arredonda(imag(x3));
  int c3=c2+arredonda(real(x3));
  reta(a,l2,c2,l3,c3,cor,largura);

  int l4=l2-arredonda(imag(x4));
  int c4=c2+arredonda(real(x4));
  reta(a,l2,c2,l4,c4,cor,largura);
}

void relogioCircular(Mat_<GRY>& b, int l, int c, int r, double deg, BYTE cor, int t)
{ circulo(b, l, c, r, cor, t);
  double rad=deg2rad(deg);
  reta(b, l, c, -arredonda(r*sin(rad+M_PI_2))+l, arredonda(r*cos(rad+M_PI_2))+c, cor, t);
}

void relogioCircular(Mat_<COR>& b, int l, int c, int r, double deg, COR cor, int t)
{ circulo(b, l, c, r, cor, t);
  double rad=deg2rad(deg);
  reta(b, l, c, -arredonda(r*sin(rad+M_PI_2))+l, arredonda(r*cos(rad+M_PI_2))+c, cor, t);
}

void relogioRetangular(Mat_<GRY>& a, int l, int c, int nl, int nc, double deg, BYTE cor, int t)
{ double rad=-deg2rad(deg);
  double co=cos(rad); double si=sin(rad);
  int lc=(nl-1)/2; int cc=(nc-1)/2;

  int dl0=arredonda(-co*lc             - si*cc);
  int dc0=arredonda( si*lc             - co*cc);
  int dl1=arredonda(-co*lc             + si*(nc-cc-1) );
  int dc1=arredonda( si*lc             + co*(nc-cc-1) );
  int dl2=arredonda( co*(nl-lc-1) - si*cc);
  int dc2=arredonda(-si*(nl-lc-1) - co*cc);
  int dl3=arredonda( co*(nl-lc-1) + si*(nc-cc-1) );
  int dc3=arredonda(-si*(nl-lc-1) + co*(nc-cc-1) );
  int dl=arredonda(-co*lc);
  int dc=arredonda( si*lc);

  reta(a,l+dl0,c+dc0,l+dl1,c+dc1,cor,t);
  reta(a,l+dl1,c+dc1,l+dl3,c+dc3,cor,t);
  reta(a,l+dl3,c+dc3,l+dl2,c+dc2,cor,t);
  reta(a,l+dl2,c+dc2,l+dl0,c+dc0,cor,t);
  reta(a,l,c,l+dl,c+dc,cor,t);
  //ponto(a,l,c,cor,t);
}

void relogioRetangular(Mat_<COR>& a, int l, int c, int nl, int nc, double deg, COR cor, int t)
{ double rad=-deg2rad(deg);
  double co=cos(rad); double si=sin(rad);
  int lc=(nl-1)/2; int cc=(nc-1)/2;

  int dl0=arredonda(-co*lc             - si*cc);
  int dc0=arredonda( si*lc             - co*cc);
  int dl1=arredonda(-co*lc             + si*(nc-cc-1) );
  int dc1=arredonda( si*lc             + co*(nc-cc-1) );
  int dl2=arredonda( co*(nl-lc-1) - si*cc);
  int dc2=arredonda(-si*(nl-lc-1) - co*cc);
  int dl3=arredonda( co*(nl-lc-1) + si*(nc-cc-1) );
  int dc3=arredonda(-si*(nl-lc-1) + co*(nc-cc-1) );
  int dl=arredonda(-co*lc);
  int dc=arredonda( si*lc);

  reta(a,l+dl0,c+dc0,l+dl1,c+dc1,cor,t);
  reta(a,l+dl1,c+dc1,l+dl3,c+dc3,cor,t);
  reta(a,l+dl3,c+dc3,l+dl2,c+dc2,cor,t);
  reta(a,l+dl2,c+dc2,l+dl0,c+dc0,cor,t);
  reta(a,l,c,l+dl,c+dc,cor,t);
  //ponto(a,l,c,cor,t);
}

//<<<<<<<<<<<<<<<< puttxt <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*
A imagem de fontes e' obtida de programa "character map"
Imagem de fonte tem 20 caracteres em cada linha
Normalmente, tem 10 linhas de fontes (mas pode ter mais ou menos)
Cada caracter tem 24 linhas e 18 colunas
Ha uma linha e coluna separando caracteres
A posicao upper-left de primeiro caracter esta em (1,1)

Cada caracter impresso ocupa 24-2*borda linhas e 18-2*borda colunas
No caso default (fixedsys com borda=5), ocupa 14x8 pixels
*/

namespace PutTxt {

Mat_<GRY> f;
#include "cekcg.inc"

int borda;

class __PutTxt {
public:
  __PutTxt();
} __puttxt;

__PutTxt::__PutTxt() 
{ Mat_<GRY> t(251,381,fixedsys); t.copyTo(f); borda=5; }

void PosicaoInicial(int ch, int& lf, int& cf)
{ if (ch==32) ch=160;
  else if (ch<32) ch=183;

  ch=ch-33;
  lf=ch/20; lf=25*lf+1;
  cf=ch%20; cf=19*cf+1;
}

}

void putTxt(Mat_<GRY>& a, int la, int ca, string st, BYTE fore, int ampl, bool transp, BYTE back)
{ using namespace PutTxt;
  //IMG_<GRY> a(ap);
  int i=0;
  while (st[i]!=0) {
    int ch=st[i]; int lf,cf; PosicaoInicial(ch,lf,cf);

    for (int l=0; l<ampl*(24-2*borda); l++)
      for (int c=0; c<ampl*(18-2*borda); c++) {
        int l2=l/ampl;
        int c2=c/ampl;
        if (f(lf+borda+l2,cf+borda+c2)==0) {
          dot(a,la+l,ca+c,fore);
        } else if (transp==false) {
          dot(a,la+l,ca+c,back);
        }
      }
    ca=ca+ampl*(18-2*borda);
    i++;
  }
}

void putTxtC(IMG_<COR>& a, int xa, int ya, string st, COR fore, int ampl, bool transp, COR back)
{ int la,ca;
  a.atC2atn(xa,ya,la,ca);
  putTxt(a.mat,la,ca,st,fore,ampl,transp,back);
}

void putTxtC(IMG_<GRY>& a, int xa, int ya, string st, BYTE fore, int ampl, bool transp, BYTE back)
{ int la,ca;
  a.atC2atn(xa,ya,la,ca);
  putTxt(a.mat,la,ca,st,fore,ampl,transp,back);
}

void putTxt(Mat_<COR>& a, int la, int ca, string st, COR fore, int ampl, bool transp, COR back)
{ using namespace PutTxt;
  //IMG_<COR> a(ap);
  int i=0;
  while (st[i]!=0) {
    int ch=st[i]; int lf,cf; PosicaoInicial(ch,lf,cf);

    for (int l=0; l<ampl*(24-2*borda); l++)
      for (int c=0; c<ampl*(18-2*borda); c++) {
        int l2=l/ampl;
        int c2=c/ampl;
        if (f(lf+borda+l2,cf+borda+c2)==0) {
          dot(a,la+l,ca+c,fore);
        } else if (transp==false) {
          dot(a,la+l,ca+c,back);
        }
      }
    ca=ca+ampl*(18-2*borda);
    i++;
  }
}

//void le(Mat_<GRY>& a, string nome);

void lefont(string nome, int bordap)
{ using namespace PutTxt;
  le(f,nome); borda=bordap;
}

/*
//<<<<<<<<<<<<<< TSH <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// anti-horario:+1, alinhados:0 horario:-1
int tsh(PONTOI2 a, PONTOI2 b, PONTOI2 c)
{ return sign( (b.x()-a.x())*(c.y()-a.y())
             - (b.y()-a.y())*(c.x()-a.x()) );
}

int tsh(PONTO2 a, PONTO2 b, PONTO2 c)
{ double d=(b.x()-a.x())*(c.y()-a.y()) - (b.y()-a.y())*(c.x()-a.x());
  if (abs(d)<epsilon) return 0;
  else return sign(d);
}

int cruza(PONTOI2 a, PONTOI2 b, PONTOI2 c, PONTOI2 d)
// Devolve 0 se nao-cruza, 1 se cruza, -1 se alinhados
{ int t1=tsh(b,a,d); int t2=tsh(b,a,c);
  if (t1==0 || t2==0) return -1;
  int t3=tsh(c,d,a); int t4=tsh(c,d,b);
  if (t3==0 || t4==0) return -1;
  if (t1*t2==-1 && t3*t4==-1) return 1;
  else return 0;
}

double pseudoangulo(PONTO2 v)
{ double ax,ay,p;
  ax=abs(v.x()); ay=abs(v.y());
  if (ax<epsilon && ay<epsilon) erro("Erro: Vetor nulo");
  if (ax>ay) {
    if (v.x()>0.0) { p=v.y()/v.x(); if (p<0.0) p=p+8.0; }
    else p=v.y()/v.x()+4.0;
  } else {
    if (v.y()>0.0) p=2.0-v.x()/v.y();
    else p=6.0-v.x()/v.y();
  }
  return p;
}

double pseudoangl1(PONTO2 p)
// Entre 0 e 4
// Caminho percorrido sobre losango (1,0) (0,1) (-1,0) (0,-1) ate' achar a interseccao com vetor
{ p=versorl1(p);
  if (p.x()>0.0 && p.y()>=0.0) return p.y(); // quadrante 1
  else if (p.x()<=0.0 && p.y()>0.0) return 1.0-p.x(); // quadrante 2
  else if (p.x()<0.0 && p.y()<=0.0) return 2.0-p.y(); // quadrante 3
  else if (p.x()>=0.0 && p.y()<0.0) return 3.0+p.x(); // quadrante 3
  else return 0.0; // Vetor nulo
}
*/

//<<<<<<<<<<<<<<<<<< ret2esf <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
double arg(double x, double y)
// Calcula o angulo do ponto (x,y). M_PI_2=pi/2 e M_PI=3.14...
// Retorna valor entre 0 e 2*M_PI
{ return modulo(atan2(x,y),M_2PI); }

/*
PONTO3 ret2esf(PONTO3 p)
// Converte coordenada retangular para esferica
// esf.x=rho (comprimento do vetor)
// esf.y=theta (ang no plano xy, entre 0 e 2*M_PI)
// esf.z=phi (descida, entre 0 e M_PI)
{ PONTO3 esf;
  esf.rho()=comprimento(p);
  //if (esf.x()<epsilon) erro("Eye=foco");
  if (esf.rho()<epsilon) return PONTO3(0.0,0.0,0.0);
  esf.theta()=arg(p.x(),p.y()); // Entre 0 e 2*M_PI
  esf.phi()=acos(p.z()/esf.rho()); // Entre 0 e M_PI
  return esf;
}

PONTO3 esf2ret(PONTO3 esf)
// O que acontece se phi>M_PI?
{ PONTO3 p;
  p.z()=esf.rho()*cos(esf.phi());
  double xy=esf.rho()*sin(esf.phi());
  p.y()=xy*sin(esf.theta());
  p.x()=xy*cos(esf.theta());
  return p;
}
*/

Vec3f ret2esf(Vec3f p)
// Converte coordenada retangular para esferica
// esf.x=rho (comprimento do vetor)
// esf.y=theta (ang no plano xy, entre 0 e 2*M_PI)
// esf.z=phi (descida, entre 0 e M_PI)
{ Vec3f esf;
  esf[0]=norm(p);
  if (esf[0]<epsilon) return Vec3f(0.0,0.0,0.0);
  esf[1]=arg(p[0],p[1]); // Entre 0 e 2*M_PI
  esf[2]=acos(p[2]/esf[0]); // Entre 0 e M_PI
  return esf;
}

Vec3f esf2ret(Vec3f esf)
// O que acontece se phi>M_PI?
{ Vec3f p;
  p[2]=esf[0]*cos(esf[2]);
  float xy=esf[0]*sin(esf[2]);
  p[1]=xy*sin(esf[1]);
  p[0]=xy*cos(esf[1]);
  return p;
}

/*
PONTO4 ret2esf(PONTO4 p)
// Converte coordenada retangular para esferica
// esf.x=rho (comprimento do vetor)
// esf.y=theta (ang no plano xy, entre 0 e 2*M_PI)
// esf.z=phi (descida de z, entre 0 e M_PI)
// esf.w=psi (descida de w, entre 0 e M_PI)
{ PONTO4 esf;
  esf.x()=comprimento(p);
  //if (esf.x()<epsilon) erro("Eye=foco");
  if (esf.x()<epsilon) return PONTO4(0.0,0.0,0.0,0.0);
  esf.y()=arg(p.x(),p.y()); // Entre 0 e 2*M_PI
  esf.z()=acos(p.z()/esf.x()); // Entre 0 e M_PI
  esf.w()=acos(p.w()/esf.x()); // Entre 0 e M_PI
  return esf;
}

PONTO4 ret2esfl1(PONTO4 p)
// Converte coordenada retangular para esferica
// esf.x=rho (comprimento do vetor)
// esf.y=theta (ang no plano xy, entre 0 e 4)
// esf.z=phi (descida de z, entre 0 e 2)
// esf.w=psi (descida de w, entre 0 e 2)
{ PONTO4 esf;
  esf.x()=comprimentol1(p);
  if (esf.x()<epsilon) return PONTO4(0.0,0.0,0.0,0.0);
  esf.y()=pseudoangl1(PONTO2(p.x(),p.y())); // Entre 0 e 4
  esf.z()=1.0-p.z()/esf.x(); // Entre 0 e 2
  esf.w()=1.0-p.w()/esf.x(); // Entre 0 e 2
  return esf;
}

////////////////////////////
PONTO3 ret2esfz(PONTO3 p)
// Converte coordenada retangular para esferica descida z
// esf.x=rho (comprimento do vetor)
// esf.y=theta (ang no plano xy, entre 0 e 2*M_PI)
// esf.z=phi (descida, entre 0 e M_PI)
{ PONTO3 esf;
  esf.rho()=comprimento(p);
  if (esf.rho()<epsilon) return PONTO3(0.0,0.0,0.0);
  esf.theta()=arg(p.x(),p.y()); // Entre 0 e 2*M_PI
  esf.phi()=acos(p.z()/esf.rho()); // Entre 0 e M_PI
  //if (esf.theta()>M_PI) { 
  //  esf.theta()-=M_PI; // Entre 0 e M_PI
  //  esf.phi()=M_2PI-esf.phi(); // Entre 0 e M_2PI
  //}
  return esf;
}

PONTO3 esfz2ret(PONTO3 esf)
// O que acontece se phi>180?
{ PONTO3 p;
  p.z()=esf.rho()*cos(esf.phi());
  double xy=esf.rho()*sin(esf.phi());
  p.y()=xy*sin(esf.theta());
  p.x()=xy*cos(esf.theta());
  return p;
}

// Do esfz, trocar z por x; x por y; e y por z.
PONTO3 ret2esfx(PONTO3 p)
{ PONTO3 esf;
  esf.rho()=comprimento(p);
  if (esf.rho()<epsilon) return PONTO3(0.0,0.0,0.0);
  esf.theta()=arg(p.y(),p.z()); // Entre 0 e 2*M_PI
  esf.phi()=acos(p.x()/esf.rho()); // Entre 0 e M_PI
  //if (esf.theta()>M_PI) { 
  //  esf.theta()-=M_PI; // Entre 0 e M_PI
  //  esf.phi()=M_2PI-esf.phi(); // Entre 0 e M_2PI
  //}
  return esf;
}

PONTO3 esfx2ret(PONTO3 esf)
{ PONTO3 p;
  p.x()=esf.rho()*cos(esf.phi());
  double yz=esf.rho()*sin(esf.phi());
  p.z()=yz*sin(esf.theta());
  p.y()=yz*cos(esf.theta());
  return p;
}

// Do esfz, trocar z por y; x por z; e y por x.
PONTO3 ret2esfy(PONTO3 p)
{ PONTO3 esf;
  esf.rho()=comprimento(p);
  if (esf.rho()<epsilon) return PONTO3(0.0,0.0,0.0);
  esf.theta()=arg(p.z(),p.x()); // Entre 0 e 2*M_PI
  esf.phi()=acos(p.y()/esf.rho()); // Entre 0 e M_PI
  //if (esf.theta()>M_PI) { 
  //  esf.theta()-=M_PI; // Entre 0 e M_PI
  //  esf.phi()=M_2PI-esf.phi(); // Entre 0 e M_2PI
  //}
  return esf;
}

PONTO3 esfy2ret(PONTO3 esf)
{ PONTO3 p;
  p.y()=esf.rho()*cos(esf.phi());
  double zx=esf.rho()*sin(esf.phi());
  p.x()=zx*sin(esf.theta());
  p.z()=zx*cos(esf.theta());
  return p;
}
*/

//<<<<<<<<<<<<<<<< POLYGON <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void polygon(Mat_<GRY>& a, POLYGON p, GRY cor, int largura)
{ const Point* pts=&p[0];
  int npts=(int)p.size();
  Scalar color(cor);
  polylines(a,&pts,&npts,1,true,color,largura);
  //void  polylines(Mat&  img,  const  Point**  pts,  const  int*  npts,
  //int  ncontours,  bool  isClosed,  const  Scalar&  color,
  //int  thickness=1,  int  lineType=8,  int  shift=0  );
}

void polygon(Mat_<COR>& a, POLYGON p, COR cor, int largura)
{ const Point* pts=&p[0];
  int npts=(int)p.size();
  Scalar color(cor[0],cor[1],cor[2]);
  fillPoly(a,&pts,&npts,1,color);
}

void polygon(Mat_<FLT>& a, POLYGON p, FLT cor, int largura)
{ const Point* pts=&p[0];
  int npts=(int)p.size();
  Scalar color(cor);
  fillPoly(a,&pts,&npts,1,color);
}

void fillPolygon(Mat_<GRY>& a, POLYGON p, GRY cor)
{ const Point* pts=&p[0];
  int npts=(int)p.size();
  Scalar color(cor);
  fillPoly(a,&pts,&npts,1,color);
  //void  fillPoly(Mat&  img,  const  Point**  pts,
  //const  int*  npts,  int  ncontours,
  //const  Scalar&  color,  int  lineType=8,
  //int  shift=0,  Point  offset=Point()  );
}

void fillPolygon(Mat_<COR>& a, POLYGON p, COR cor)
{ const Point* pts=&p[0];
  int npts=(int)p.size();
  Scalar color(cor[0],cor[1],cor[2]);
  fillPoly(a,&pts,&npts,1,color);
}

void fillPolygon(Mat_<FLT>& a, POLYGON p, FLT cor)
{ const Point* pts=&p[0];
  int npts=(int)p.size();
  Scalar color(cor);
  fillPoly(a,&pts,&npts,1,color);
}

// Convgon = Polygon convexo. As rotinas abaixo so funcionam para poligonos convexos
void fillConvgon(Mat_<GRY>& a, POLYGON p, GRY cor)
{ Scalar color(cor);
  fillConvexPoly(a,&p[0],(int)p.size(),color);
  //void  fillConvexPoly(Mat&  img,  const  Point*  pts,  int  npts,
  //const  Scalar&  color,  int  lineType=8,
  //int  shift=0);
}

void fillConvgon(Mat_<COR>& a, POLYGON p, COR cor)
{ Scalar color(cor[0],cor[1],cor[2]);
  fillConvexPoly(a,&p[0],(int)p.size(),color);
}

void fillConvgon(Mat_<FLT>& a, POLYGON p, FLT cor)
{ Scalar color(cor);
  fillConvexPoly(a,&p[0],(int)p.size(),color);
}

void POLYGON2Mat(POLYGON& p, Mat_<double>& m)
// retorna matriz 3*p.size()
{ m.create(3,(int)p.size());
  for (unsigned i=0; i<p.size(); i++) {
    m(0,i)=p[i].x; m(1,i)=p[i].y; m(2,i)=1;
  }
}

void Mat2POLYGON(Mat_<double> m, POLYGON& p)
// Entra: m_{2,size} e retorna POLYGON
{ p.resize(m.cols);
  for (unsigned i=0; i<p.size(); i++) {
    p[i].x=m(0,i); p[i].y=m(1,i);
  }
}

void rotatePolygon(POLYGON& p, Point centro, double ang, POLYGON& q)
// rotaciona p em torno do centro ang degrees
{ Point2f center=centro;
  Mat_<double> R=getRotationMatrix2D(center,ang,1.0); // r_{2x3}
  Mat_<double> P; POLYGON2Mat(p,P);
  Mat_<double> Q=R*P;
  Mat2POLYGON(Q,q);
}


/*
//<<<<<<<<<<<<<<<< thickline <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void thickline(IMGBIN& a, int l1, int c1, int l2, int c2, bool cor, int largura)
{ CPXD x=CPXD(c1,-l1)-CPXD(c2,-l2);
  double ang=arg(x);
  double dis=largura/2.0;
  CPXD x3=CPXD(dis*cos(ang-M_PI/2.0),dis*sin(ang-M_PI/2.0));
  CPXD x4=CPXD(dis*cos(ang+M_PI/2.0),dis*sin(ang+M_PI/2.0));

  POLYGON p(4);
  p(0)=PONTOI2(l1-arredonda(imag(x3)),c1+arredonda(real(x3)));
  p(1)=PONTOI2(l1-arredonda(imag(x4)),c1+arredonda(real(x4)));
  p(2)=PONTOI2(l2-arredonda(imag(x4)),c2+arredonda(real(x4)));
  p(3)=PONTOI2(l2-arredonda(imag(x3)),c2+arredonda(real(x3)));
  ConvgonFill(a,p,cor);
}

void thickline(IMGGRY& a, int l1, int c1, int l2, int c2, BYTE cor, int largura)
{ CPXD x=CPXD(c1,-l1)-CPXD(c2,-l2);
  double ang=arg(x);
  double dis=largura/2.0;
  CPXD x3=CPXD(dis*cos(ang-M_PI/2.0),dis*sin(ang-M_PI/2.0));
  CPXD x4=CPXD(dis*cos(ang+M_PI/2.0),dis*sin(ang+M_PI/2.0));

  POLYGON p(4);
  p(0)=PONTOI2(l1-arredonda(imag(x3)),c1+arredonda(real(x3)));
  p(1)=PONTOI2(l1-arredonda(imag(x4)),c1+arredonda(real(x4)));
  p(2)=PONTOI2(l2-arredonda(imag(x4)),c2+arredonda(real(x4)));
  p(3)=PONTOI2(l2-arredonda(imag(x3)),c2+arredonda(real(x3)));
  ConvgonFill(a,p,cor);
  //Codigo abaixo para acessar os pontos do poligono
  //POLYGON q=ConvgonBorda(p);
  //if (q.n()%2==1) erro("Erro: q impar");
  //for (int i=0; i<q.n(); i+=2) {
  //  PONTOI2 p1=q(i); PONTOI2 p2=q(i+1);
  //  if (p1.l()!=p2.l()) erro("Erro: p1.l()!=p2.l()");
  //  for (int c=p1.c(); c<=p2.c(); c++) {
  //    a(p1.l(),c)=cor;
  //  }
  //}
}

void thickline(IMGCOR& a, int l1, int c1, int l2, int c2, COR cor,  int largura)
{ CPXD x=CPXD(c1,-l1)-CPXD(c2,-l2);
  double ang=arg(x);
  double dis=largura/2.0;
  CPXD x3=CPXD(dis*cos(ang-M_PI/2.0),dis*sin(ang-M_PI/2.0));
  CPXD x4=CPXD(dis*cos(ang+M_PI/2.0),dis*sin(ang+M_PI/2.0));

  POLYGON p(4);
  p(0)=PONTOI2(l1-arredonda(imag(x3)),c1+arredonda(real(x3)));
  p(1)=PONTOI2(l1-arredonda(imag(x4)),c1+arredonda(real(x4)));
  p(2)=PONTOI2(l2-arredonda(imag(x4)),c2+arredonda(real(x4)));
  p(3)=PONTOI2(l2-arredonda(imag(x3)),c2+arredonda(real(x3)));
  ConvgonFill(a,p,cor);
}

//<<<<<<<<<<<<<< SHAPE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
SHAPE derivada1(SHAPE u)
// Supondo h==1.0
{ int n=u.n();
  SHAPE v(n);
  for (int i=0; i<n; i++)
    v(i)=0.5*(u(i+1,'r')-u(i-1,'r'));
  return v;
}

SHAPE derivada2(SHAPE u)
// Supondo h==1.0
{ int n=u.n();
  SHAPE v(n);
  for (int i=0; i<n; i++)
    v(i)=u(i+1,'r')-2.0*u(i,'r')+u(i-1,'r');
  return v;
}
*/

SHAPEX SHAPEF2X(SHAPEF zf)
{ assert(zf.cols==2);
  SHAPEX zx(zf.rows,1);
  for (int l=0; l<zf.rows; l++) {
    zx(l)=CPX(zf(l,0),zf(l,1));
  }
  return zx;
}

SHAPEF SHAPEX2F(SHAPEX zx)
{ assert(zx.cols==1);
  SHAPEF zf(zx.rows,2);
  for (int l=0; l<zx.rows; l++) {
    zf(l,0)=zx(l).real();
    zf(l,1)=zx(l).imag();
  }
  return zx;
}

void mostraShape(SHAPEF z)
{ Mat_<GRY> b(400,400,255);
  shape2img(z,b,0,true,false); // cor, fechado, vertice
  mostra(b);
}

Point2i MapU2D::u2d(Point2f p)
{ Point2i q; // y de cima para baixo
  q.y=MaxD.y-(Desloc.y+arredonda(faty*(p.y-MinU.y)))+borda;
  q.x=Desloc.x+arredonda(fatx*(p.x-MinU.x))+borda; // Testar se arredonda funciona
  return q;
}

void MapU2D::show()
{ cout << "MinU=" << MinU << endl;
  cout << "MaxU=" << MaxU << endl;
  cout << "MaxD=" << MaxD << endl;
  cout << "GrudaY=" << GrudaY << endl;
  cout << "fatx=" << fatx << endl;
  cout << "faty=" << faty << endl;
  cout << "Desloc=" << Desloc << endl;
}

void MapU2D::inicshape(SHAPEF& u, int nl, int nc, int bordap, bool keepar)
{ MinU=Point2f(infinito,infinito);
  MaxU=Point2f(-infinito,-infinito);
  borda=bordap;
  for (int i=0; i<u.rows; i++) {
    if (u(i,0)>MaxU.x) MaxU.x=u(i,0);
    if (u(i,1)>MaxU.y) MaxU.y=u(i,1);
    if (u(i,0)<MinU.x) MinU.x=u(i,0);
    if (u(i,1)<MinU.y) MinU.y=u(i,1);
  }
  if (MinU.x>=MaxU.x || MinU.y>=MaxU.y) erro("Erro inesperado ShapeMinMax");

  if (nc<=2*borda+1 || nl<=2*borda+1) erro("Erro: Borda muito grande");
  MaxD=Point2i(nc-2*borda-1,nl-2*borda-1);

  if (keepar==true) {
    if ( (MaxU.y-MinU.y)/(MaxU.x-MinU.x) > double(MaxD.y)/double(MaxD.x) ) GrudaY=true;
    else GrudaY=false;

    if (GrudaY) fatx=MaxD.y/(MaxU.y-MinU.y);
    else fatx=MaxD.x/(MaxU.x-MinU.x);

    if (GrudaY) {
      Desloc.y=0;
      Desloc.x=(MaxD.x-chao(fatx*(MaxU.x-MinU.x)))/2;
    } else {
      Desloc.x=0;
      Desloc.y=(MaxD.y-chao(fatx*(MaxU.y-MinU.y)))/2;
    }

    faty=fatx;
  } else {
    fatx=MaxD.x/(MaxU.x-MinU.x);
    faty=MaxD.y/(MaxU.y-MinU.y);
    Desloc.x=(MaxD.x-chao(fatx*(MaxU.x-MinU.x)))/2;
    Desloc.y=(MaxD.y-chao(faty*(MaxU.y-MinU.y)))/2;
  }
}

void shapeVert(MapU2D m, SHAPEF& u, Mat_<GRY>& b, bool cor)
{ if (m.MinU.x==infinito) erro("Erro shapevert: MapU2D nao inicializado");
  for (int i=0; i<u.rows; i++) {
    Point2i p=m.u2d(Point2f(u(i,0),u(i,1)));
    if (i==0) ponto(b,p.y,p.x,cor,5);
    else if (i==u.rows-1) xis(b,p.y,p.x,3,cor);
    else xis(b,p.y,p.x,2,cor);
  }
}

void shapeVert(SHAPEF& u, Mat_<GRY>& b, bool cor)
{ MapU2D m;
  m.inicshape(u,b.rows,b.cols,3);
  shapeVert(m,u,b,cor);
}

void shape2img(MapU2D m, SHAPEF& u, Mat_<GRY>& b, bool cor, bool fechado)
{ if (m.MinU.x==infinito) erro("Erro shape2img: MapU2D nao inicializado");
  Point2i p=m.u2d(Point2f(u(0,0),u(0,1))); moveTo( p.y, p.x );
  for (int i=0; i<u.rows; i++) {
    p=m.u2d(Point2f(u(i,0),u(i,1))); lineTo( b, p.y, p.x, cor );
  }
  if (fechado) {
    p=m.u2d(Point2f(u(0,0),u(0,1)));
    lineTo( b, p.y, p.x, cor );
  }
}

void shape2img(SHAPEF& u, Mat_<GRY>& b, bool cor, bool fechado, bool vert)
{ MapU2D m;
  m.inicshape( u, b.rows, b.cols, 3);
  shape2img(m,u,b,cor,fechado);
  if (vert) shapeVert(m,u,b,cor);
}

void shapeGrade(MapU2D m, Mat_<GRY>& b, double gradex, double gradey, bool cor)
{ if (m.MinU.x==infinito) erro("Erro shapegrade: MapU2D nao inicializado");
  if (gradex==0.0 || gradey==0.0) return;

  int minx=chao(m.MinU.x/gradex);
  int miny=chao(m.MinU.y/gradey);
  int maxx=teto(m.MaxU.x/gradex);
  int maxy=teto(m.MaxU.y/gradey);

  for (int x=minx; x<=maxx; x++)
    for (int y=miny; y<=maxy; y++) {
      Point2i p=m.u2d(Point2f(gradex*x,gradey*y));
      b(p.y,p.x)=cor;
    }
  Point2i p=m.u2d(Point2f(0.0,0.0));
  ponto(b,p.y,p.x,cor,3);
}

/*
//<<<<<<<<<<<<< SHAPE IMGCOR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void shapevert(MapU2D m, SHAPE& u, IMGCOR& b, COR cor)
{ if (m.MinU.x()==infinito) erro("Erro shapevert: MapU2D nao inicializado");
  PONTOI2 p;
  for (int i=0; i<u.n(); i++) {
    p=m.u2d(u(i));
    b(p.l(),p.c())=cor;
  }
  p=m.u2d(u(0)); b(p.l(),p.c())=COR(0,255,0);
  p=m.u2d(u(u.n()-1)); b(p.l(),p.c())=COR(0,0,255);
}

void shapevert(SHAPE& u, IMGCOR& b, COR cor)
{ MapU2D m;
  m.inicshape(u,b.nl(),b.nc(),0);
  shapevert(m,u,b,cor);
}

void shape2img(MapU2D m, SHAPE& u, IMGCOR& b, COR cor, bool fechado)
{ if (m.MinU.x()==infinito) erro("Erro shape2img: MapU2D nao inicializado");
  PONTOI2 p=m.u2d(u(0)); moveto( p.l(), p.c() );
  for (int i=0; i<u.n(); i++) {
    p=m.u2d(u(i)); lineto( b, p.l(), p.c(), cor );
  }
  if (fechado) {
    p=m.u2d(u(0));
    lineto( b, p.l(), p.c(), cor );
  }
}

void shape2img(SHAPE& u, IMGCOR& b, COR cor, bool fechado, bool vert)
{ MapU2D m;
  m.inicshape( u, b.nl(), b.nc(), 0 );
  shape2img(m,u,b,cor,fechado);
  if (vert) shapevert(m,u,b,cor);
}

void shapegrade(MapU2D m, IMGCOR& sai, double gradex, double gradey, COR cor)
{ if (m.MinU.x()==infinito) erro("Erro shapegrade: MapU2D nao inicializado");
  if (gradex==0.0 || gradey==0.0) return;

  int minx=chao(m.MinU.x()/gradex);
  int miny=chao(m.MinU.y()/gradey);
  int maxx=teto(m.MaxU.x()/gradex);
  int maxy=teto(m.MaxU.y()/gradey);

  for (int x=minx; x<=maxx; x++)
    for (int y=miny; y<=maxy; y++) {
      PONTOI2 p=m.u2d(PONTO2(gradex*x,gradey*y));
      sai(p.l(),p.c())=cor;
    }
  PONTOI2 p=m.u2d(PONTO2(0.0,0.0));
  ponto(sai,p.l(),p.c(),cor,3);
}

//<<<<<<<<<<<<<< bspline de shape <<<<<<<<<<<<<<<<<<<<<
double L(double x)
// Funcao base de bspline
{ x=abs(x);
  if (2.0<=x) return 0.0;
  else if (1.0<=x) return elev3(2.0-x)/6.0;
  else return (4.0-6.0*elev2(x)+3.0*elev3(x))/6.0;
}

double L1(double x)
// Primeira derivada da funcao base de bspline
{ if (2.0<=x) return 0.0;
  else if (1.0<=x) return -0.5*elev2(2.0-x);
  else if (0.0<=x) return -2.0*x+1.5*elev2(x);
  else if (-1.0<=x) return -2.0*x-1.5*elev2(x);
  else if (-2.0<=x) return 0.5*elev2(2.0+x);
  else return 0.0;
}

double L2(double x)
// Segunda derivada da funcao base de bspline
{ if (2.0<=x) return 0.0;
  else if (1.0<=x) return 2.0-x;
  else if (0.0<=x) return -2.0+3.0*x;
  else if (-1.0<=x) return -2.0-3.0*x;
  else if (-2.0<=x) return 2.0+x;
  else return 0.0;
}

PONTO2 bspline(SHAPE& v, double t, char modo)
// bspline cubico
// 0<=t<1
// 1<=tl<n-2
{ if (modo=='n') {
    if (t>1.0) t=1.0-epsilon;
    if (t<0.0) t=0.0;
  } else if (modo=='r') {
    t=modulo(t,1.0);
  } else erro("Erro: modo invalido");
  double tl=t*(v.n()-3)+1;
  int w=chao(tl);

  PONTO2 f(0,0);
  for (int i=w-1; i<=w+2; i++) {
    double r=L(tl-i);
    f.x()=f.x()+r*v(i).x();
    f.y()=f.y()+r*v(i).y();
  }
  return f;
}

PONTO2 bspline1(SHAPE& v, double t, char modo)
// Primeira derivada de bspline cubico
// 0<=t<1
// 1<=tl<n-2
{ if (modo=='n') {
    if (t>1.0) t=1.0-epsilon;
    if (t<0.0) t=0.0;
  } else if (modo=='r') {
    t=modulo(t,1.0);
  } else erro("Erro: modo invalido");
  double tl=t*(v.n()-3)+1;
  int w=chao(tl);

  PONTO2 f(0,0);
  for (int i=w-1; i<=w+2; i++) {
    double r=L1(tl-i);
    f.x()=f.x()+r*v(i).x();
    f.y()=f.y()+r*v(i).y();
  }
  return double(v.n()-3)*f;
}

PONTO2 bspline2(SHAPE& v, double t, char modo)
// Segunda derivada de bspline cubico
// 0<=t<1
// 1<=tl<n-2
{ if (modo=='n') {
    if (t>1.0) t=1.0-epsilon;
    if (t<0.0) t=0.0;
  } else if (modo=='r') {
    t=modulo(t,1.0);
  } else erro("Erro: modo invalido");
  double tl=t*(v.n()-3)+1;
  int w=chao(tl);

  PONTO2 f(0,0);
  for (int i=w-1; i<=w+2; i++) {
    double r=L2(tl-i);
    f.x()=f.x()+r*v(i).x();
    f.y()=f.y()+r*v(i).y();
  }
  return double(elev2(v.n()-3))*f;
}

double Lg(double t, int gr)
// Funcao base de bspline de grau generico (1 2 ou 3)
{ double r;
  t=abs(t);
  switch (gr) {
    case 1: {
         if (t<1.0) return 1.0-t;
         else return 0.0;
      }
    case 2: {
         if (1.5<=t) return 0.0;
         else if (0.5<=t) return 0.5*t*t-1.5*t+1.125;
         else return -t*t+0.75;
      }
    case 3: {
         if (2.0<=t) return 0.0;
         else if (1.0<=t && t<2.0) { r=2.0-t; return r*r*r/6.0; }
         else { r=t*t; return (4.0-6.0*r+3.0*r*t)/6.0; }
      }
    default: { erro("Erro: bs grau deve ser 1, 2 ou 3"); return 0.0; }
  }
}

PONTO2 bsplineg(SHAPE& v, double t, int gr, char modo)
// Bspline de grau generico (1 2 ou 3)
// 0<=t<1
// gr2<=tl<n-gr2-1
{ if (modo=='n') {
    if (t>1.0) t=1.0-epsilon;
    if (t<0.0) t=0.0;
  } else if (modo=='r') {
    t=modulo(t,1.0);
  } else erro("Erro: modo invalido");
  int gr2=gr/2; double tl=t*(v.n()-1-2*gr2)+gr2;
  int w=chao(tl);

  PONTO2 f(0,0);
  for (int i=w-gr2; i<=w+gr2+1; i++) {
    double r=Lg(tl-i,gr);
    f.x()=f.x()+r*v(i).x();
    f.y()=f.y()+r*v(i).y();
  }
  return f;
}
*/

//<<<<<<<<<<<<<< FUNCAO <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void FuncaoMinMax(FUNCAO& u, double& MinU, double& MaxU)
{ MinU= infinito;
  MaxU=-infinito;
  for (unsigned i=0; i<u.size(); i++) {
    if (u[i]>MaxU) MaxU=u[i];
    if (u[i]<MinU) MinU=u[i];
  }
  if (MinU>=MaxU) erro("Erro inesperado FuncaoMinMax");
}

/*
void funcao2imgbin(FUNCAO& u, IMGBIN& b,
               bool cor, bool vertice,
               double MinU, double MaxU, double grade)
// Deixa 1 linha/coluna branca nos cantos.
// Imagem b deve ter 2 colunas/linhas a mais do que o tamanho desejado
{ PONTOI2 MaxD(b.nc()-3,b.nl()-3);

  double MinU2,MaxU2;
  if (MinU==-infinito || MaxU==infinito) FuncaoMinMax(u,MinU2,MaxU2);
  if (MinU==-infinito) MinU=MinU2;
  if (MaxU==infinito) MaxU=MaxU2;

  double fatY=MaxD.y()/(MaxU-MinU);
  double fatX=MaxD.x()/double(u.n()-1);

  VETOR<PONTOI2> p(u.n());
  for (int i=0; i<u.n(); i++)
    p(i)=PONTOI2( chao(fatX*i)+1, MaxD.y()-chao(fatY*(u(i)-MinU))+1 );

  moveto( p(0).y(), p(0).x() );
  for (int i=1; i<p.n(); i++) lineto(b, p(i).y(), p(i).x(), cor);

  if (vertice)
    for (int i=0; i<p.n(); i++) ponto(b, p(i).y(), p(i).x(), cor, 3);

  if (grade<infinito) {
    PONTOI2 p1=PONTOI2( chao(fatX*0)+1, MaxD.y()-chao(fatY*(0.0-MinU))+1 );
    PONTOI2 p2=PONTOI2( chao(fatX*(u.n()-1))+1, MaxD.y()-chao(fatY*(0.0-MinU))+1 );
    reta(b,p1.y(),p1.x(),p2.y(),p2.x(),cor);
    for (double d=grade; d<MaxU; d=d+grade) {
      p1=PONTOI2( chao(fatX*0)+1, MaxD.y()-chao(fatY*(d-MinU))+1 );
      ponto(b,p1.y(),p1.x(),cor,3);
    }
    for (double d=-grade; d>MinU; d=d-grade) {
      p1=PONTOI2( chao(fatX*0)+1, MaxD.y()-chao(fatY*(d-MinU))+1 );
      ponto(b,p1.y(),p1.x(),cor,3);
    }
  }
}
*/

Mat_<GRY> simpleFuncao2matgry(FUNCAO u, int nl, char modo)
// Imagem de saida sempre tem nc=u.n
// modo: '.'=tracejado  '-'=continuo  ':'=barras(default)
{ double MinU,MaxU;
  FuncaoMinMax(u,MinU,MaxU);
  double fatY=(nl-1)/(MaxU-MinU);

  Mat_<GRY> sai(nl,u.size(),255);
  if (modo=='.')
    for (int c=0; c<sai.cols; c++)
      sai(nl-arredonda(fatY*(u[c]-MinU))-1,c)=0;
  else if (modo==':') {
    for (int c=0; c<sai.cols; c++) {
      moveTo(nl-1,c);
      lineTo(sai,nl-arredonda(fatY*(u[c]-MinU))-1,c,0);
    }
  } else if (modo=='-') {
    moveTo(nl-arredonda(fatY*(u[0]-MinU))-1,0);
    for (int c=1; c<sai.cols; c++) {
      lineTo(sai,nl-arredonda(fatY*(u[c-1]-MinU))-1,c,0);
      lineTo(sai,nl-arredonda(fatY*(u[c]-MinU))-1,c,0);
    }
  } else erro("Erro: modo invalido");
  return sai;
}

Mat_<COR> simpleFuncao2matcor(FUNCAO u, int nl, char modo, COR cor)
// Imagem de saida sempre tem nc=u.n
// modo: '.'=tracejado  '-'=continuo  ':'=barras(default)
{ double MinU,MaxU;
  FuncaoMinMax(u,MinU,MaxU);
  double fatY=(nl-1)/(MaxU-MinU);

  Mat_<COR> sai(nl,u.size(),COR(255,255,255));
  if (modo=='.')
    for (int c=0; c<sai.cols; c++)
      sai(nl-arredonda(fatY*(u[c]-MinU))-1,c)=cor;
  else if (modo==':') {
    for (int c=0; c<sai.cols; c++) {
      moveTo(nl-1,c);
      lineTo(sai,nl-arredonda(fatY*(u[c]-MinU))-1,c,cor);
    }
  } else if (modo=='-') {
    moveTo(nl-arredonda(fatY*(u[0]-MinU))-1,0);
    for (int c=1; c<sai.cols; c++) {
      lineTo(sai,nl-arredonda(fatY*(u[c-1]-MinU))-1,c,cor);
      lineTo(sai,nl-arredonda(fatY*(u[c]-MinU))-1,c,cor);
    }
  } else erro("Erro: modo invalido");
  return sai;
}

/*
void fun2shp(FUNCAO f, SHAPE& s)
{ s.resize(f.n());
  for (int i=0; i<f.n(); i++)
    s(i)=PONTO2(double(i),f(i));
}
*/

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< RST 2D <<<<<<<<<<<<<<<<<<<<<<
Mat_<FLT> matrizTranslacao(double x, double y)
{ Mat_<FLT> d =
    (Mat_<FLT>(3,3) << 1, 0, x,
                       0, 1, y,
                       0, 0, 1);
  return d;
}

Mat_<FLT> matrizTranslacao(Point2f p)
{ Mat_<FLT> d =
    (Mat_<FLT>(3,3) << 1, 0, p.x,
                       0, 1, p.y,
                       0, 0, 1);
  return d;
}

Mat_<FLT> matrizRotacao(double angDeg)
{ double angRad=deg2rad(angDeg);
  double c=cos(angRad);
  double s=sin(angRad);
  Mat_<FLT> d =
    (Mat_<FLT>(3,3) << c,  s, 0,
                       -s, c, 0,
                       0,  0, 1);
  return d;
}

Mat_<FLT> matrizRotacaoCentro(double angDeg, Point2f p)
{ Mat_<FLT> T1=matrizTranslacao(-p);
  Mat_<FLT> R=matrizRotacao(angDeg);
  Mat_<FLT> T2=matrizTranslacao(p);
  return T2*R*T1;
}

Point3f operator*(Mat_<FLT> M, Point3f p)
{ if (M.size()!=Size(3,3)) erro("Erro: Point3f operator*");
  Point3f d;
  d.x=M(0,0)*p.x+M(0,1)*p.y+M(0,2)*p.z;
  d.y=M(1,0)*p.x+M(1,1)*p.y+M(1,2)*p.z;
  d.z=M(2,0)*p.x+M(2,1)*p.y+M(2,2)*p.z;
  return d;
}

} // namespace cek
  

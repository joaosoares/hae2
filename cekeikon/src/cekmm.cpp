//compila cekmnist5_vidout.cpp -c -v2 -omp
#include "cekeikon.h"

namespace cek {

//<<<<<<<<<<<<<<<<<<<<<<<<< morfologia <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
namespace Morphology {

Mat_<GRY> operator!(Mat_<GRY> a) {
  Mat_<GRY> d(a.size(),0);
  for (unsigned i=0; i<a.total(); i++)
    if (a(i)==0) d(i)=1;
  return d;
}

bool operator==(Mat_<GRY> a, Mat_<GRY> b)
{ if (a.size()!=b.size()) return false;
  bool igual=true;
  MatIterator_<GRY> ai,bi;
  for (ai=a.begin(), bi=b.begin(); ai!=a.end(); ai++, bi++) 
    if (*ai!=*bi) { igual=false; break; }
  return igual;
}

Mat_<GRY> operator*(Mat_<GRY> a, Mat_<GRY> b)
// Para imagem a com 0 ou 255.
// Para imagem b 0 ou 128 ou 255
// Calcula hit-miss binario de a com elemento estruturante b.
// Na imagem b, valores 0 e 255 tornam-se obrigatorios.
// Qualquer valor diferente de 0 e 255 sao "don't care".
// Se bate, fica branco (255). Nao batendo, fica preto (0).
{ Mat_<GRY> d(a.rows,a.cols,bk); int blc=b.rows/2; int bcc=b.cols/2;
  for (int l=0; l<a.rows-b.rows+1; l++)
    for (int c=0; c<a.cols-b.cols+1; c++) {
      GRY bate=wh;
      for (int l2=0; l2<b.rows; l2++)
        for (int c2=0; c2<b.cols; c2++) {
          if ((b(l2,c2)==bk && a(l+l2,c+c2)!=bk) || (b(l2,c2)==wh && a(l+l2,c+c2)!=wh)) { 
            bate=bk; goto saida; 
          }
        }
      saida: d(l+blc,c+bcc)=bate;
    }
  return d;
}

Mat_<GRY> operator%(Mat_<GRY> a, Mat_<GRY> b)
// Para imagem a com 0 ou 1.
// Para imagem b 0 ou 128 ou 255
// Calcula hit-miss binario de a com elemento estruturante b.
// Na imagem b, valores 0 e 255 tornam-se obrigatorios.
// Qualquer valor diferente de 0 e 255 sao "don't care".
// Se bate, fica branco (255). Nao batendo, fica preto (0).
{ Mat_<GRY> d(a.rows,a.cols,bk); int blc=b.rows/2; int bcc=b.cols/2;
  for (int l=0; l<a.rows-b.rows+1; l++)
    for (int c=0; c<a.cols-b.cols+1; c++) {
      GRY bate=1;
      for (int l2=0; l2<b.rows; l2++)
        for (int c2=0; c2<b.cols; c2++) {
          if ((b(l2,c2)==0 && a(l+l2,c+c2)!=0) || (b(l2,c2)==255 && a(l+l2,c+c2)!=1)) { 
            bate=0; goto saida; 
          }
        }
      saida: d(l+blc,c+bcc)=bate;
    }
  return d;
}

Mat_<GRY> rot90(Mat_<GRY> a)
// Rotaciona 90 graus sentido anti-horario.
{ Mat_<GRY> d(a.cols,a.rows);
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++)
      d(a.cols-c-1,l) = a(l,c);
  return d;
}

Mat_<GRY> strel(double len, double deg, string tipo) {
  int n=ceilImpar(len);
  int nc=n/2;
  double rad=deg2rad(deg);
  ImgXyb<GRY> d(n,n,GRY(0)); d.centro(nc,nc);
  if (tipo=="line") {
    int xf=arredonda((len/2)*cos(rad));
    int yf=arredonda((len/2)*sin(rad));
    int xi=arredonda(-xf);
    int yi=arredonda(-yf);
    int li,ci,lf,cf;
    d.xy2at(xi,yi,li,ci);
    d.xy2at(xf,yf,lf,cf);
    reta(d,li,ci,lf,cf,255,1);
  } else {
    erro("Erro strel: tipo desconhecido");
  }
  return d;
}

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int soma(Mat_<GRY> a)
{ Scalar s=sum(a);
  return arredonda(s[0]);
}

/* implementacao antiga
void copia(Mat_<GRY> ent, Mat_<GRY>& sai, int li, int ci)
{ for (int l=0; l<ent.rows && l+li<sai.rows; l++)
    for (int c=0; c<ent.cols && c+ci<sai.cols; c++)
      sai(l+li,c+ci)=ent(l,c);
}

void copia(Mat_<COR> ent, Mat_<COR>& sai, int li, int ci)
{ for (int l=0; l<ent.rows && l+li<sai.rows; l++)
    for (int c=0; c<ent.cols && c+ci<sai.cols; c++)
      sai(l+li,c+ci)=ent(l,c);
}
*/

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
double dcReject(vector<double>& a)
{ double soma=0.0;
  for (unsigned i=0; i<a.size(); i++) soma+=a[i];
  soma/=a.size();
  for (unsigned i=0; i<a.size(); i++) a[i]-=soma;
  return soma;
}

Mat_<FLT> dcReject(Mat_<FLT> a) // Elimina nivel DC (subtrai media)
{ Mat_<FLT> d=a.clone();
  double soma=0.0;
  for (MatIterator_<FLT> di=d.begin(); di!=d.end(); di++) soma += (*di);
  double media=soma/d.total();
  for (MatIterator_<FLT> di=d.begin(); di!=d.end(); di++) (*di) -= media;
  return d;
}

Mat_<FLT> dcReject(Mat_<FLT> a, FLT dontcare) // Elimina nivel DC (subtrai media) com dontcare
{ Mat_<FLT> d=a.clone();
  double soma=0.0; int conta=0;
  for (MatIterator_<FLT> di=d.begin(); di!=d.end(); di++) {
    if ((*di)!=dontcare) { soma+=(*di); conta++; }
  }
  double media=soma/conta;
  for (MatIterator_<FLT> di=d.begin(); di!=d.end(); di++) {
    if ((*di)!=dontcare) (*di) -= media; 
    else (*di) = 0.0;
  }
  return d;
}

Mat_<FLT> dcRejectCol(Mat_<FLT>& S) { // Calcula media coluna a coluna. Subtrai media de cada coluna. Retorna a media
  Mat_<FLT> media(1,S.cols);
  for (int c=0; c<S.cols; c++) {
    media(c)=mean(S.col(c))[0];
    S.col(c) -= media(c);
  }
  return media;
}

Mat_<DBL> dcReject(Mat_<DBL> a) // Elimina nivel DC (subtrai media)
{ Mat_<DBL> d=a.clone();
  double soma=0.0;
  for (MatIterator_<DBL> di=d.begin(); di!=d.end(); di++) soma += (*di);
  double media=soma/d.total();
  for (MatIterator_<DBL> di=d.begin(); di!=d.end(); di++) (*di) -= media;
  return d;
}

Mat_<FLT> somatoriaUm(Mat_<FLT> a) // Faz somatoria absoluta da imagem dar um
{ Mat_<FLT> d=a.clone();
  double soma=0.0;
  for (MatIterator_<FLT> di=d.begin(); di!=d.end(); di++) soma += abs(*di);
  if (soma<epsilon) erro("Erro somatoriaUm: Divisao por zero"); 
  for (MatIterator_<FLT> di=d.begin(); di!=d.end(); di++) (*di) /= soma;
  return d;
}

Mat_<DBL> somatoriaUm(Mat_<DBL> a) // Faz somatoria absoluta da imagem dar um
{ Mat_<DBL> d=a.clone();
  double soma=0.0;
  for (MatIterator_<DBL> di=d.begin(); di!=d.end(); di++) soma += abs(*di);
  if (soma<epsilon) erro("Erro somatoriaUm: Divisao por zero"); 
  for (MatIterator_<DBL> di=d.begin(); di!=d.end(); di++) (*di) /= soma;
  return d;
}

Mat_<FLT> somaAbsDois(Mat_<FLT> a) // Faz somatoria absoluta da imagem dar dois
{ Mat_<FLT> d=a.clone();
  double soma=0.0;
  for (auto di=d.begin(); di!=d.end(); di++) soma += abs(*di);
  if (soma<epsilon) erro("Erro somatoriaUm: Divisao por zero"); 
  soma=soma/2.0;
  for (auto di=d.begin(); di!=d.end(); di++) (*di) /= soma;
  return d;
}

Mat_<DBL> somaAbsDois(Mat_<DBL> a) // Faz somatoria absoluta da imagem dar dois
{ Mat_<DBL> d=a.clone();
  double soma=0.0;
  for (auto di=d.begin(); di!=d.end(); di++) soma += abs(*di);
  if (soma<epsilon) erro("Erro somatoriaUm: Divisao por zero"); 
  soma=soma/2.0;
  for (auto di=d.begin(); di!=d.end(); di++) (*di) /= soma;
  return d;
}

void mediaDesvio(Mat_<FLT> a, double& media, double& desvio)
{ Scalar smedia,sdesvio;
  meanStdDev(a, smedia, sdesvio);
  media=smedia[0];
  desvio=sdesvio[0];
}

double normal01(Mat_<FLT>& a, double newMedia, double newDesvio) 
//Faz a imagem a ser normal(newMedia,newDesvio)
//Retorna oldDesvio
{ double oldMedia, oldDesvio;
  mediaDesvio(a,oldMedia,oldDesvio);

  a = (a-oldMedia) / oldDesvio; // a = normal(0,1)
  if (newDesvio!=1.0) a = newDesvio * a; // a = normal(0,newDesvio)
  if (newMedia!=0.0)  a = a + newMedia; // a = normal(newMedia,newDesvio)
  return oldDesvio;
}

//double normal01(Mat_<FLT>& a) 
// Elimina nivel DC e divide pelo desvio-padrao, para dar normal(0,1). Retorna desvio.
// { a=dcReject(a);
//   double desvio=0.0;
//   for (MatIterator_<FLT> ai=a.begin(); ai!=a.end(); ai++) desvio += elev2(*ai);
//   desvio = sqrt(desvio/a.total());
//   if (desvio<epsilon) 
//     for (MatIterator_<FLT> ai=a.begin(); ai!=a.end(); ai++) (*ai) = 0.0;
//   else 
//     for (MatIterator_<FLT> ai=a.begin(); ai!=a.end(); ai++) (*ai) /= desvio;
//   return desvio;
// }

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Mat_<GRY> normaliza(Mat_<GRY> a)
// Normaliza Mat_<GRY para intevalo [0..255]
{ GRY minimo,maximo;
  minimo=maximo=a(0,0);
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++) {
      minimo=min(a(l,c),minimo);
      maximo=max(a(l,c),maximo);
    }
  double delta=maximo-minimo;

  if (delta==0) return a;
  Mat_<GRY> d(a.rows,a.cols);
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++)
      d(l,c)=saturate_cast<GRY>(255.0*(a(l,c)-minimo)/delta);
  return d;
}

Mat_<FLT> normaliza(Mat_<FLT> a)
// Normaliza Mat_<FLT> para intevalo [0,1]
{ FLT minimo,maximo;
  minimo=maximo=a(0,0);
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++) {
      minimo=min(a(l,c),minimo);
      maximo=max(a(l,c),maximo);
    }
  double delta=maximo-minimo;
  if (delta<epsilon) return a;

  Mat_<FLT> d(a.rows,a.cols);
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++)
      d(l,c)=(a(l,c)-minimo)/delta;
  return d;
}

Mat_<DBL> normaliza(Mat_<DBL> a)
// Normaliza Mat_<DBL para intevalo [0,1]
{ DBL minimo,maximo;
  minimo=maximo=a(0,0);
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++) {
      minimo=min(a(l,c),minimo);
      maximo=max(a(l,c),maximo);
    }
  double delta=maximo-minimo;
  if (delta<epsilon) return a;

  Mat_<DBL> d(a.rows,a.cols);
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++)
      d(l,c)=(a(l,c)-minimo)/delta;
  return d;
}

Mat_<CPX> normaliza(Mat_<CPX> a)
// Normaliza Mat_<CPX para que modulo fique no intevalo [0,1]
{ FLT maximo=abs(a(0,0));
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++) {
      maximo=max(abs(a(l,c)),maximo);
    }
  if (maximo<epsilon) return a;

  Mat_<CPX> d(a.rows,a.cols);
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++)
      d(l,c)=a(l,c)/maximo;
  return d;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Mat_<GRY> binariza(Mat_<GRY> g, int limiar)
{ Mat_<GRY> b(g.size());
  for (unsigned i=0; i<g.total(); i++) {
    if (g(i)<=limiar) b(i)=0;
    else b(i)=255;
  }
  return b;
}

Mat_<GRY> binariza(Mat_<FLT> g, float limiar)
{ Mat_<GRY> b(g.size());
  for (unsigned i=0; i<g.total(); i++) {
    if (g(i)<=limiar) b(i)=0;
    else b(i)=255;
  }
  return b;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Mat_<CPX> ret2pol(Mat_<CPX> a)
{ Mat_<CPX> d(a.size());
  for (MatIterator_<CPX> ai=a.begin(), di=d.begin(); ai!=a.end(); ai++, di++) {
    (*di)=ret2pol(*ai);
  }
  return d;
}

Mat_<CPX> pol2ret(Mat_<CPX> a)
{ Mat_<CPX> d(a.size());
  for (MatIterator_<CPX> ai=a.begin(), di=d.begin(); ai!=a.end(); ai++, di++) {
    (*di)=pol2ret(*ai);
  }
  return d;
}

/* use funcao converte
void CPX2flecha(Mat a, Mat& b, double fator, int espaco)
// fator: Multiplica os numeros complexos;
// espaco: Distancia em pixels entre dois numeros complexos
{ 
  if (a.type()!=CV_32FC2) erro("Erro CPX2flecha");
  int espaco2=espaco/2;
  b.create(espaco*a.rows,espaco*a.cols,CV_8UC3); b.setTo(Scalar(255,255,255));
  Mat_<COR>pb=b;

  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++) {
      flecha(pb, l*espaco+espaco2, c*espaco+espaco2,
                (l*espaco+espaco2)-cvRound(fator*imag(a.at<CPX>(l,c))), (c*espaco+espaco2)+cvRound(fator*real(a.at<CPX>(l,c))), COR(0,0,0), 1 );
      b.at<Vec3b>(l*espaco+espaco2, c*espaco+espaco2)=Vec3b(0,0,255);
    }
}
*/

/* Esta funcao esta muito estranha. Reescrevi 
Mat_<FLT> modulo(Mat_<CPX> a)
{ if (a.type()!=CV_32FC2) erro("Erro: abs Mat_<CPX>");
  Mat_<CPX> b=abs(a);
  Mat_<float> d(b.size()); 
  int vint[]={0,0};
  mixChannels(&b, 1, &d, 1, vint, 1);
  //mixChannels(&b, 1, &d, 1, (int []){0,0}, 1);
  return d;
}
*/

Mat_<FLT> modulo(Mat_<CPX> a)
{ Mat_<FLT> d(a.size()); 
  for (unsigned i=0; i<a.total(); i++)
    d(i)=std::abs(a(i));
  return d;
}

Mat_<FLT> real(Mat_<CPX> a)
{ Mat_<FLT> d(a.size()); 
  for (unsigned i=0; i<a.total(); i++)
    d(i)=real(a(i));
  return d;
}

Mat_<FLT> imag(Mat_<CPX> a)
{ Mat_<FLT> d(a.size()); 
  for (unsigned i=0; i<a.total(); i++)
    d(i)=imag(a(i));
  return d;
}

Mat_<CPX> versor(Mat_<CPX> a) { 
// Todos pixels terao comprimento 1, exceto os pixels quase nulos.
  Mat_<CPX> b(a.size()); 
  for (unsigned i=0; i<a.total(); i++) {
    double d=abs(a(i));
    if (d>epsilon) b(i) = (1/d)*a(i);
    else b(i) = CPX(0.0,0.0);
  }
  return b;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Mat_<FLT> elev2(Mat_<FLT> a)
{ Mat_<FLT> d(a.rows,a.cols);
  for (unsigned i=0; i<a.total(); i++)
    d(i)=a(i)*a(i);
  return d;
}

Mat_<FLT> raiz(Mat_<FLT> a)
{ Mat_<FLT> d(a.rows,a.cols);
  for (unsigned i=0; i<a.total(); i++)
    d(i)=sqrt(a(i));
  return d;
}

Mat_<FLT> modulo(Mat_<FLT> a)
{ Mat_<FLT> d(a.rows,a.cols);
  for (unsigned i=0; i<a.total(); i++)
    d(i)=abs(a(i));
  return d;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
vector<Point> kmax(Mat_<FLT> a, int k, double d)
{ // Nota: pixels <=0.0 nao sao levados em conta
  FI2DEC pq;
  { FI2 f;
    for (int l=0; l<a.rows; l++)
      for (int c=0; c<a.cols; c++) {
        if (a(l,c)>0.0) {
          f.v=a(l,c); f.l=l; f.c=c;
          pq.push(f);
        }
      }
  }
  vector<Point> psai;
  if (d>0.0) {
    if (!pq.empty()) {
      for (int i=0; i<k; i++) {
        bool coloca=false;
        while (!coloca) {
          FI2 f=pq.top();
          //printf("v=%f l=%d c=%d\n",f.v,f.l,f.c);
          pq.pop();
          Point p(f.c,f.l);
          coloca=true;
          for (unsigned j=0; j<psai.size(); j++)
            if (norm(psai[j]-p)<=d) {
              coloca=false;
              break;
            }
          if (coloca) psai.push_back(p);
          if (pq.empty()) goto saida;
        }
      }
    }
  } else {
    if (!pq.empty()) {
      for (int i=0; i<k; i++) {
        FI2 f=pq.top();
        pq.pop();
        Point p(f.c,f.l);
        psai.push_back(p);
        if (pq.empty()) goto saida;
      }
    }
  }
  saida:
  return psai;
}

vector<Point> kmin(Mat_<FLT> a, int k, double d)
{ // Nota: pixels >=1.0 nao sao levados em conta
  FI2INC pq;
  { FI2 f;
    for (int l=0; l<a.rows; l++)
      for (int c=0; c<a.cols; c++) {
        if (a(l,c)<1.0) {
          f.v=a(l,c); f.l=l; f.c=c;
          pq.push(f);
        }
      }
  }
  vector<Point> psai;
  if (d>0.0) {
    if (!pq.empty()) {
      for (int i=0; i<k; i++) {
        bool coloca=false;
        while (!coloca) {
          FI2 f=pq.top();
          //printf("v=%f l=%d c=%d\n",f.v,f.l,f.c);
          pq.pop();
          Point p(f.c,f.l);
          coloca=true;
          for (unsigned j=0; j<psai.size(); j++)
            if (norm(psai[j]-p)<=d) {
              coloca=false;
              break;
            }
          if (coloca) psai.push_back(p);
          if (pq.empty()) goto saida;
        }
      }
    }
  } else {
    if (!pq.empty()) {
      for (int i=0; i<k; i++) {
        FI2 f=pq.top();
        pq.pop();
        Point p(f.c,f.l);
        psai.push_back(p);
        if (pq.empty()) goto saida;
      }
    }
  }
  saida:
  return psai;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Mat_<CPX> criaCPX(Mat_<SHT> dc, Mat_<SHT> dl)
{ if (dc.size()!=dl.size()) erro("Erro criaCPX");
  Mat_<CPX> b(dc.size());
  for (unsigned i=0; i<b.total(); i++)
    b(i)=CPX( (1.0/255.0)*dc(i), (1.0/255.0)*dl(i) );
  return b;
}

Mat_<CPX> criaCPX(Mat_<FLT> dc, Mat_<FLT> dl)
{ if (dc.size()!=dl.size()) erro("Erro criaCPX");
  Mat_<CPX> b(dc.size());
  for (unsigned i=0; i<b.total(); i++)
    b(i)=CPX( dc(i), dl(i) );
  return b;
}

Mat_<CPX> gradiente2(Mat_<GRY> a, bool yParaCima)
// x ->  
// y |
//   V
{ if (a.rows<=0 || a.cols<=0) erro("Erro gradiente: dimensao invalida");
  //FLT vflt[]={-1, 0, 1};
  Mat_<FLT> fc = (Mat_<FLT>(1,3) << -1, 0, 1);
  Mat_<SHT> bc;
  filter2D(a, bc, CV_16S, fc, Point(-1,-1), 0, BORDER_REPLICATE); // bc entre -255 e +255

  Mat_<FLT> fl;
  if (yParaCima) fl = (Mat_<FLT>(3,1) << 1, 0, -1);
  else fl = (Mat_<FLT>(3,1) << -1, 0, 1);
  Mat_<SHT> bl;
  filter2D(a, bl, CV_16S, fl, Point(-1,-1), 0, BORDER_REPLICATE); // bl entre -255 e +255

  Mat_<CPX> b=criaCPX(bc,bl);
  return b; // b.real entre -1 e +1. b.imag tambem
}

Mat_<CPX> gradienteScharr(Mat_<GRY> a, bool yParaCima)
// x ->  
// y |
//   V
{ Mat_<FLT> gradientex;
  Scharr(a, gradientex, CV_32F, 1, 0); 
  // gradientex entre -4080 e +4080 (255*16)?
  gradientex=(1.0/4080)*gradientex;

  Mat_<FLT> gradientey;
  Scharr(a, gradientey, CV_32F, 0, 1); 
  // bl entre -4080 e +4080?
  if (yParaCima) gradientey=(-1.0/4080)*gradientey;
  else gradientey=(1.0/4080)*gradientey;

  Mat_<CPX> b=criaCPX(gradientex,gradientey);
  return b; // b.real entre -1 e +1. b.imag tambem
}

void maximo(vector< Mat_<SHT> >& bc, vector< Mat_<SHT> >& bl, Mat_<SHT>& dc, Mat_<SHT>& dl)
{ dc.create(bc[0].size());
  dl.create(bl[0].size());
  for (int l=0; l<dc.rows; l++)
    for (int c=0; c<dc.cols; c++) {
      int a0=abs(bc[0](l,c))+abs(bl[0](l,c));
      int a1=abs(bc[1](l,c))+abs(bl[1](l,c));
      int a2=abs(bc[2](l,c))+abs(bl[2](l,c));
      if (a0>a1) {
        if (a0>a2) { dc(l,c)=bc[0](l,c); dl(l,c)=bl[0](l,c); }
        else       { dc(l,c)=bc[2](l,c); dl(l,c)=bl[2](l,c); }
      } else {
        if (a1>a2) { dc(l,c)=bc[1](l,c); dl(l,c)=bl[1](l,c); }
        else       { dc(l,c)=bc[2](l,c); dl(l,c)=bl[2](l,c); }
      }
    }
}

Mat_<CPX> gradiente(Mat_<COR> ap)
// x ->  
// y |
//   V
{ if (ap.rows<=0 || ap.cols<=0) erro("Erro gradiente: dimensao invalida");
  vector< Mat_<GRY> > a(3);
  split(ap,a);

  Mat_<FLT> fc = (Mat_<FLT>(1,3) << -1, 0, 1);
  vector< Mat_<SHT> > bc(3);
  filter2D(a[0], bc[0], CV_16S, fc, Point(-1,-1), 0, BORDER_REPLICATE); 
  filter2D(a[1], bc[1], CV_16S, fc, Point(-1,-1), 0, BORDER_REPLICATE); 
  filter2D(a[2], bc[2], CV_16S, fc, Point(-1,-1), 0, BORDER_REPLICATE); 
  
  Mat_<FLT> fl = (Mat_<FLT>(3,1) << -1, 0, 1);
  vector< Mat_<SHT> > bl(3);
  filter2D(a[0], bl[0], CV_16S, fl, Point(-1,-1), 0, BORDER_REPLICATE); 
  filter2D(a[1], bl[1], CV_16S, fl, Point(-1,-1), 0, BORDER_REPLICATE); 
  filter2D(a[2], bl[2], CV_16S, fl, Point(-1,-1), 0, BORDER_REPLICATE); 

  Mat_<SHT> dc;
  Mat_<SHT> dl; 
  maximo(bc,bl,dc,dl);

  Mat_<CPX> b=criaCPX(dc,dl);
  return b;
}

void gradienteLC(Mat_<COR> ap, Mat_<SHT>& gl, Mat_<SHT>& gc)
// Pega maior gradiente entre R, G e B
{ if (ap.rows<=0 || ap.cols<=0) erro("Erro gradiente: dimensao invalida");
  vector< Mat_<GRY> > a(3);
  split(ap,a);

  FLT vflt[]={-1, 0, 1};
  Mat_<FLT> fc(1,3, vflt);
  vector< Mat_<SHT> > bc(3);
  filter2D(a[0], bc[0], CV_16S, fc, Point(-1,-1), 0, BORDER_REPLICATE); 
  filter2D(a[1], bc[1], CV_16S, fc, Point(-1,-1), 0, BORDER_REPLICATE); 
  filter2D(a[2], bc[2], CV_16S, fc, Point(-1,-1), 0, BORDER_REPLICATE); 
  
  Mat_<FLT> fl(3,1, vflt);
  vector< Mat_<SHT> > bl(3);
  filter2D(a[0], bl[0], CV_16S, fl, Point(-1,-1), 0, BORDER_REPLICATE); 
  filter2D(a[1], bl[1], CV_16S, fl, Point(-1,-1), 0, BORDER_REPLICATE); 
  filter2D(a[2], bl[2], CV_16S, fl, Point(-1,-1), 0, BORDER_REPLICATE); 

  maximo(bc,bl,gc,gl);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void HOG::CPX2his(Mat_<CPX> b, M3d_<FLT>& his)
// Converte imagem de gradiente b para histograma de gradiente pixel-a-pixel his
// angulo gira em sentido horario
{ int vint[]={nBins,b.rows,b.cols};
  his.create(3,vint);
  his.setTo(0.0);

  FLT denominador=180.0/nBins;
  FLT denominador2=denominador/2;
  for (int l=0; l<b.rows; l++)
    for (int c=0; c<b.cols; c++) {
      CPX e=b(l,c);
      FLT v=abs(e);
      FLT a=fastAtan2(e.imag(),e.real()); // 0<=a<360
      a+=denominador2;
      if (a>=180) a=a-180; // 0<=a<180
      if (a>=180) a=a-180; // 0<=a<180
      int q=int(a/denominador);      
      //cout << a << " " << q << endl;
      if (!(0<=q && q<nBins)) erro("Erro HOG::CPX2his inesperado"); 
      his(q,l,c) += v;
    }
}

void HOG::his2blo(M3d_<FLT> his, M3d_<FLT>& cell)
// histograma para celula
{ int ns=his.size[0];
  int nl=his.size[1]/cellSizeL;
  int nc=his.size[2]/cellSizeC;
  int vint[]={ns,nl,nc};
  cell.create(3,vint);
  cell.setTo(0.0);

  for (int s=0; s<ns; s++)
    for (int l=0; l<nl; l++)
      for (int c=0; c<nc; c++) {
        for (int l2=0; l2<cellSizeL; l2++)
          for (int c2=0; c2<cellSizeC; c2++)
            cell(s,l,c) += his(s,cellSizeL*l+l2,cellSizeC*c+c2);
        cell(s,l,c) /= (cellSizeL*cellSizeC);
      }
}

HOG::HOG(Mat_<COR> a, int _nBins, int _cellSizeL, int _cellSizeC)
{ nBins=_nBins; cellSizeL=_cellSizeL; cellSizeC=_cellSizeC; 
  if (cellSizeC<=0) cellSizeC=cellSizeL;
  Mat_<CPX> b=gradiente(a);

  M3d_<FLT> his; // I3D
  CPX2his(b,his);

  his2blo(his,blo); // I3d
}

void HOG::exporta(Mat_<GRY>& d, int zoom, double mult)
{ int bsl=zoom*cellSizeL; // tamanho da celula na imagem
  int bsc=zoom*cellSizeC; // tamanho da celula na imagem
  int ns=blo.size[0];
  int nl=blo.size[1];
  int nc=blo.size[2];
  //printf("%d %d %d\n",ns,nl,nc);
  double angstep=180/nBins;
  int graystep=max(255/nBins,64);
  double bsl2=bsl/2.0;
  double bsc2=bsc/2.0;
  d.create(bsl*nl,bsc*nc); 
  d.setTo(0);

  for (int l=0; l<nl; l++)
    for (int c=0; c<nc; c++) {
      for (int s=0; s<ns; s++) {
        double angulo=angstep*s;
        if (angulo>=180) angulo -= 180;
        if (angulo>=180) angulo -= 180;
        angulo=deg2rad(angulo);
        double v=blo(s,l,c);
        if (v==0) continue;
        double x=mult*zoom*bsc2*v*cos(angulo);
        double y=mult*zoom*bsl2*v*sin(angulo);
        int px=cvRound(c*bsc+bsc2+x);
        int py=cvRound(l*bsl+bsl2+y);
        int qx=cvRound(c*bsc+bsc2-x);
        int qy=cvRound(l*bsl+bsl2-y);
        LineIterator it( d, Point(px,py), Point(qx,qy) );
        for (int i=0; i<it.count; i++, ++it) {
          **it = saturate_cast<GRY>(**it + graystep);
        }
      }        
    }
}

void HOG::show(int zoom, double mult, string nome)
{ Mat_<GRY> d; 
  exporta(d,zoom,mult); 
  if (nome=="") mostra(d); else mostra(d,nome);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< DENSEHOG <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void DENSEHOG::grad2his()
// Converte imagem de gradiente grad para histograma de gradiente pixel-a-pixel his
{ int vint[]={nBins,grad.rows,grad.cols};
  his.create(3,vint);
  his.setTo(0.0);

  FLT denominador=180.0/nBins;
  FLT denominador2=denominador/2;
  for (int l=0; l<grad.rows; l++)
    for (int c=0; c<grad.cols; c++) {
      CPX e=grad(l,c);
      FLT v=abs(e);
      FLT a=fastAtan2(e.imag(),e.real()); // 0<=a<360
      a+=denominador2;
      if (a>=180) a=a-180; // 0<=a<180
      if (a>=180) a=a-180; // 0<=a<180
      int q=int(a/denominador);      
      if (!(0<=q && q<nBins)) erro("Erro DENSEHOG::CPX2his inesperado"); 
      his(q,l,c) += v;
    }
}

DENSEHOG::DENSEHOG(Mat_<COR> a, int _nBins, int _tlCell, int _tcCell)
{ nBins=_nBins; tlCell=_tlCell; tcCell=_tcCell;
  lc=(tlCell-1)/2; cc=(tcCell-1)/2;
  grad=gradiente(a); // grad do mesmo tamanho que a
  grad2his(); // his do mesmo tamanho que grad (a)
}

vector<double> DENSEHOG::hog(int l, int c)
{ vector<double> v(nBins,0);
  int li=max(0,l-lc); int ci=max(0,c-cc);
  int lf=min(grad.rows-1,li+tlCell); int cf=min(grad.cols-1,ci+tcCell);
  for (int s=0; s<nBins; s++)
    for (int l=li; l<=lf; l++)
      for (int c=ci; c<=cf; c++) {
        v[s] += his(s,l,c);
      }
  return v;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void myPyrDown(Mat_<GRY> ent, Mat_<GRY>& sai)
{ Mat_<GRY> temp;
  GaussianBlur(ent,temp,Size(3,3),0);
  sai.create(ent.rows/2,ent.cols/2);
  for (int l=0; l<sai.rows; l++)
    for (int c=0; c<sai.cols; c++)
      sai(l,c)=temp(2*l+1,2*c+1);
}

void myPyrDown(Mat_<COR> ent, Mat_<COR>& sai)
{ Mat_<COR> temp;
  GaussianBlur(ent,temp,Size(3,3),0);
  sai.create(ent.rows/2,ent.cols/2);
  for (int l=0; l<sai.rows; l++)
    for (int c=0; c<sai.cols; c++)
      sai(l,c)=temp(2*l+1,2*c+1);
}

void myPyrDown(Mat_<FLT> ent, Mat_<FLT>& sai)
{ Mat_<FLT> temp;
  GaussianBlur(ent,temp,Size(3,3),0);
  sai.create(ent.rows/2,ent.cols/2);
  for (int l=0; l<sai.rows; l++)
    for (int c=0; c<sai.cols; c++)
      sai(l,c)=temp(2*l+1,2*c+1);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

Mat_<GRY> grudaH(Mat_<GRY> a1, Mat_<GRY> a2, int nespaco, GRY backg)
{ int nc=a1.cols+nespaco+a2.cols; int nl=max(a1.rows,a2.rows);
  Mat_<GRY> b(nl,nc,backg);
  for (int c=0; c<a1.cols; c++)
    for (int l=0; l<a1.rows; l++)
      b(l,c)=a1(l,c);
  for (int c=a1.cols+nespaco; c<nc; c++)
    for (int l=0; l<a2.rows; l++)
      b(l,c)=a2(l,c-a1.cols-nespaco);
  return b;
}

Mat_<GRY> grudaV(Mat_<GRY> a1, Mat_<GRY> a2, int nespaco, GRY backg)
{ int nl=a1.rows+nespaco+a2.rows; int nc=max(a1.cols,a2.cols);
  Mat_<GRY> b(nl,nc,backg);
  for (int l=0; l<a1.rows; l++)
    for (int c=0; c<a1.cols; c++)
      b(l,c)=a1(l,c);
  for (int l=a1.rows+nespaco; l<nl; l++)
    for (int c=0; c<a2.cols; c++)
      b(l,c)=a2(l-a1.rows-nespaco,c);
  return b;
}

Mat_<COR> grudaH(Mat_<COR> a1, Mat_<COR> a2, int nespaco, COR backg)
{ int nc=a1.cols+nespaco+a2.cols; int nl=max(a1.rows,a2.rows);
  Mat_<COR> b(nl,nc,backg);
  for (int c=0; c<a1.cols; c++)
    for (int l=0; l<a1.rows; l++)
      b(l,c)=a1(l,c);
  for (int c=a1.cols+nespaco; c<nc; c++)
    for (int l=0; l<a2.rows; l++)
      b(l,c)=a2(l,c-a1.cols-nespaco);
  return b;
}

Mat_<COR> grudaV(Mat_<COR> a1, Mat_<COR> a2, int nespaco, COR backg)
{ int nl=a1.rows+nespaco+a2.rows; int nc=max(a1.cols,a2.cols);
  Mat_<COR> b(nl,nc,backg);
  for (int l=0; l<a1.rows; l++)
    for (int c=0; c<a1.cols; c++)
      b(l,c)=a1(l,c);
  for (int l=a1.rows+nespaco; l<nl; l++)
    for (int c=0; c<a2.cols; c++)
      b(l,c)=a2(l-a1.rows-nespaco,c);
  return b;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Mat_<FLT> filtLin(Mat_<FLT> ent, Mat_<FLT> ker, int borderType)
// BORDER_CONSTANT para background zero.
// BORDER_DEFAULT nao se sabe o que faz.
// Saida tem mesmo tamanho que ent.
// Utiliza centro de ker como ancora.
{ Mat_<FLT> sai;
  filter2D(ent,sai,CV_32F,ker,Point(-1,-1),0,borderType);
  return sai;
}

void multFiltLin(Mat_<FLT> ent, vector< Mat_<FLT> >& ker, Mat_<FLT>& maxcorr, Mat_<int>& ind, int borderType)
// Filtro linear de ent com varios kernels.
// maxcorr tem a maior correlacao em cada pixel.
// ind tem o indice do kernel que deu a maior correlacao.
{ maxcorr.create(ent.size()); maxcorr.setTo(-1.0);
  ind.create(ent.size()); ind.setTo(-1);
  Mat_<FLT> temp;
  for (unsigned i=0; i<ker.size(); i++) {
    temp=filtLin(ent,ker[i]);
    for (int l=0; l<temp.rows; l++)
      for (int c=0; c<temp.cols; c++)
        if (temp(l,c)>maxcorr(l,c)) { maxcorr(l,c)=temp(l,c); ind(l,c)=i; }
  }      
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void calcAlinha(Mat_<COR> ref, Mat_<COR> a, int borda, Point& desloca, double& corr)
{ if (ref.size()!=a.size()) erro("Erro calcAlinha: Tamanhos de REF e A diferentes");
  if (borda<1) erro("Erro calcAlinha: borda<1");
  if (a.rows-2*borda<1 || a.cols-2*borda<1) erro("Erro calcAlinha: Imagem muito pequena");
  
  Mat_<COR> aroi = a( Rect(borda, borda, a.cols-2*borda, a.rows-2*borda) ); 
  Mat_<FLT> result; 
  matchTemplate( ref, aroi, result, CV_TM_CCOEFF_NORMED );
  double maxVal; Point maxLoc;
  minMaxLoc(result, 0, &maxVal, 0, &maxLoc);
  if (maxVal<-1.0 || 1.0<maxVal) erro("Erro calcAlinha: correlacao fora de [-1,+1]");
  corr=maxVal;

  desloca.x=maxLoc.x-borda; desloca.y=maxLoc.y-borda;
}

Mat_<COR> alinha(Mat_<COR> a, Point desloca)
{ IMG_<COR> aimg(a); aimg.backg=COR(255,255,255); aimg.lc=aimg.cc=0;
  Mat_<COR> sai(a.size());
  for (int l=0; l<sai.rows; l++)
    for (int c=0; c<sai.cols; c++)
      sai(l,c)=aimg.atx(l-desloca.y,c-desloca.x);
  return sai;
}

Mat_<COR> alinha(Mat_<COR> ref, Mat_<COR> a, int borda)
{ Point desloca; double corr;
  calcAlinha(ref,a,borda,desloca,corr);
  return alinha(a,desloca);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
M3d_<FLT> multEscala(Mat_<FLT> a, double escFim, int nEsc)
// Gera M3d da imagem a em multi-escala.
// Recomenda-se que a seja zero-mean corrected. Deve ter nl e nc impares.
// escInic e' sempre 1.0
// escFim deve ser menor que 1.0
// O resultado vai ter nEsc slices.
{ if (a.rows%2!=1 || a.cols%2!=1) erro("Erro multiEscala: nl e nc devem ser impares");
  if (escFim>=1) erro("Erro: escFim>=1");
  if (nEsc<=1) erro("Erro: nEsc<=1"); 
  int vd[]={nEsc,a.rows,a.cols};
  M3d_<FLT> d(3,vd); 
  d.setTo(0.0);

  double passoEsc=exp(log(escFim)/(nEsc-1));
  for (int s=0; s<d.size[0]; s++) {
    double mult=pow(passoEsc,s);
    Mat_<FLT> t;
    resize(a, t, Size(roundImpar(mult*a.cols),roundImpar(mult*a.rows)), 0, 0, INTER_AREA);
    Mat_<FLT> f=fatia(d,s);
    IMG_<FLT> ti(t,t.rows/2,t.cols/2); 
    IMG_<FLT> fi(f,f.rows/2,f.cols/2);
    for (int x=ti.minx; x<=ti.maxx; x++)
      for (int y=ti.miny; y<=ti.maxy; y++)
        fi.atC(x,y)=ti.atC(x,y); 
  }
  return d;
}

Mat_<FLT> aumentaCanvas(Mat_<FLT> a, int nl, int nc, int li, int ci, FLT backg)
// Cria imagem d(nl,nc), preenche com backg, e copia a a partir de d(li,ci)
{ Mat_<FLT> d(nl,nc,backg);
  int maxnl=min(a.rows,nl-li);
  int maxnc=min(a.cols,nc-ci);
  Mat_<FLT> droi=d(Rect(ci,li,maxnc,maxnl));
  Mat_<FLT> aroi=a(Rect(0,0,maxnc,maxnl));
  aroi.copyTo(droi);
  return d;
}

EXPORTA Mat_<GRY> aumentaCanvas(Mat_<GRY> a, int nl, int nc, int li, int ci, GRY backg)
// Cria imagem d(nl,nc), preenche com backg, e copia a a partir de d(li,ci)
{ Mat_<GRY> d(nl,nc,backg);
  int maxnl=min(a.rows,nl-li);
  int maxnc=min(a.cols,nc-ci);
  Mat_<GRY> droi=d(Rect(ci,li,maxnc,maxnl));
  Mat_<GRY> aroi=a(Rect(0,0,maxnc,maxnl));
  aroi.copyTo(droi);
  return d;
}

Mat_<FLT> matchTemplateSame(Mat_<FLT> a, Mat_<FLT> q, int method, FLT backg) {
  Mat_<FLT> p{ a.size(), backg };
  Rect rect{ (q.cols-1)/2, (q.rows-1)/2, a.cols-q.cols+1, a.rows-q.rows+1};
  Mat_<FLT> roi{ p, rect };
  matchTemplate(a, q, roi, method);
  return p;
}

/*
//Reescrever sem usar aumentaCanvas
void multCorr(Mat_<FLT> a, M3d_<FLT> q, Mat_<FLT>& coef, Mat_<SHT>& ind)
{ assert(q.dims==3);
  coef.create(a.size()); coef.setTo(-infinito);
  ind.create(a.size());  ind.setTo(-1);
  for (int s=0; s<q.size[0]; s++) {
    Mat_<FLT> f=fatia(q,s);
    Mat_<FLT> r;
    matchTemplate(a,f,r,CV_TM_CCORR); // correlacao 
    r=aumentaCanvas(r,a.rows,a.cols,(f.rows-1)/2,(f.cols-1)/2,0.0);
    for (int l=0; l<r.rows; l++) 
      for (int c=0; c<r.cols; c++) 
        if (r(l,c)>coef(l,c)) { 
          coef(l,c)=r(l,c);
          ind(l,c)=s;
        }
  }
}
*/

void multCorr(Mat_<FLT> a, M3d_<FLT> q, Mat_<FLT>& coef, Mat_<SHT>& ind)
{ assert(q.dims==3);
  int lc=q.size[1]/2; int cc=q.size[2]/2;
  coef.create(a.size()); coef.setTo(-infinito);
  ind.create(a.size());  ind.setTo(-1);
  for (int s=0; s<q.size[0]; s++) {
    Mat_<FLT> f=fatia(q,s);
    Mat_<FLT> r;
    matchTemplate(a,f,r,CV_TM_CCORR); // correlacao 
    for (int l=0; l<r.rows; l++) 
      for (int c=0; c<r.cols; c++) 
        if (r(l,c)>coef(l+lc,c+cc)) { 
          coef(l+lc,c+cc)=r(l,c);
          ind(l+lc,c+cc)=s;
        }
  }
}

void multMatch(Mat_<FLT> a, Mat_<FLT> q, double escFim, int nEsc, FLT dontcare, Mat_<FLT>& coef, Mat_<SHT>& ind)
// Multi-scale match: Redimensiona q e procura todos em a.
{ Mat_<FLT> qd=dcReject(q,dontcare);
  M3d_<FLT> qss=multEscala(qd,escFim,nEsc);
  Mat_<FLT> t;
  for (int s=0; s<qss.size[0]; s++) {
    t=2*somatoriaUm(Mat_<FLT>(fatia(qss,s)));
    t.copyTo(fatia(qss,s));
  }
  multCorr(a, qss, coef, ind);
}

void multMatch1(Mat_<FLT> a, Mat_<FLT> q, double escFim, int nEsc, FLT dontcare, FLT& maxVal, Point& maxLoc, int& maxS, double& scale)
// Multi-scale match: Redimensiona q e procura todos em a. Devolve somente o melhor match
{ Mat_<FLT> coef; Mat_<SHT> ind;
  multMatch(a,q,escFim,nEsc,dontcare,coef,ind);
  double maxValD;
  minMaxLoc(coef,NULL,&maxValD,NULL,&maxLoc);
  maxVal=maxValD;
  maxS=ind(maxLoc.y,maxLoc.x);
  double passoEsc=exp(log(escFim)/(nEsc-1));
  scale=pow(passoEsc,maxS);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
M3d_<CORF> multEscala(Mat_<CORF> a, double escFim, int nEsc)
// Gera M3d da imagem a em multi-escala.
// Recomenda-se que a seja zero-mean corrected. Deve ter nl e nc impares.
// escInic e' sempre 1.0
// escFim deve ser menor que 1.0
// O resultado vai ter nEsc slices.
{ if (a.rows%2!=1 || a.cols%2!=1) erro("Erro multiEscala: nl e nc devem ser impares");
  if (escFim>=1) erro("Erro: escFim>=1");
  if (nEsc<=1) erro("Erro: nEsc<=1"); 
  int vd[]={nEsc,a.rows,a.cols};
  M3d_<CORF> d(3,vd); 
  d.setTo(0.0);

  double passoEsc=exp(log(escFim)/(nEsc-1));
  for (int s=0; s<d.size[0]; s++) {
    double mult=pow(passoEsc,s);
    Mat_<CORF> t;
    resize(a, t, Size(roundImpar(mult*a.cols),roundImpar(mult*a.rows)), 0, 0, INTER_AREA);
    Mat_<CORF> f=fatia(d,s);
    IMG_<CORF> ti(t,t.rows/2,t.cols/2); 
    IMG_<CORF> fi(f,f.rows/2,f.cols/2);
    for (int x=ti.minx; x<=ti.maxx; x++)
      for (int y=ti.miny; y<=ti.maxy; y++)
        fi.atC(x,y)=ti.atC(x,y); 
  }
  return d;
}

Mat_<CORF> dcReject(Mat_<CORF> a, CORF dontcare) // Elimina nivel DC (subtrai media) com dontcare
{ Mat_<CORF> d=a.clone();
  CORF soma(0,0,0); 
  CORF zero(0,0,0); 
  int conta=0;
  for (unsigned i=0; i<d.total(); i++) {
    if (d(i)!=dontcare) { soma=soma+d(i); conta++; }
  }
  CORF media=soma/conta;
  for (unsigned i=0; i<d.total(); i++) {
    if (d(i)!=dontcare) d(i) -= media; 
    else d(i) = zero;
  }
  return d;
}

Mat_<CORF> dcReject(Mat_<COR> a, COR pseudodontcare) // Elimina nivel DC (subtrai media) com dontcare
{ CORF dontcare=pseudodontcare/255.0;
  Mat_<CORF> d; converte(a,d);
  CORF soma(0,0,0); 
  CORF zero(0,0,0); 
  int conta=0;
  for (unsigned i=0; i<d.total(); i++) {
    if (d(i)!=dontcare) { soma=soma+d(i); conta++; }
  }
  CORF media=soma/conta;
  for (unsigned i=0; i<d.total(); i++) {
    if (d(i)!=dontcare) d(i) -= media; 
    else d(i) = zero;
  }
  return d;
}

void multCorr(Mat_<CORF> a, M3d_<CORF> q, Mat_<FLT>& coef, Mat_<SHT>& ind)
// Chama matchTemplate( a, q[i], result, CV_TM_CCOEFF_NORMED ) para cada i
{ coef.create(a.size()); coef.setTo(-infinito);
  ind.create(a.size());  ind.setTo(-1);
  int lc=q.size[1]/2;
  int cc=q.size[2]/2;
  for (int s=0; s<q.size[0]; s++) {
    Mat_<CORF> f=fatia(q,s);
    Mat_<FLT> r;
    matchTemplate(a,f,r,CV_TM_CCORR); // correlacao 
    for (int l=0; l<r.rows; l++) 
      for (int c=0; c<r.cols; c++) 
        if (r(l,c)>coef(l+lc,c+cc)) { 
          coef(l+lc,c+cc)=r(l,c);
          ind(l+lc,c+cc)=s;
        }
  }
}

Mat_<CORF> somatoriaUm(Mat_<CORF> a) // Faz somatoria absoluta da imagem dar um
{ Mat_<CORF> d=a.clone();
  CORF soma(0,0,0);
  for (MatIterator_<CORF> di=d.begin(); di!=d.end(); di++) soma += modulo(*di);
  if (soma[0]<epsilon || soma[1]<epsilon || soma[2]<epsilon) erro("Erro somatoriaUm: Divisao por zero"); 
  for (MatIterator_<CORF> di=d.begin(); di!=d.end(); di++) {
    CORF& f=(*di);
    f[0] /= soma[0];
    f[1] /= soma[1];
    f[2] /= soma[2];
  }
  return d;
}

void multMatch(Mat_<CORF> a, Mat_<CORF> q, double escFim, int nEsc, CORF dontcare, Mat_<FLT>& coef, Mat_<SHT>& ind)
// Multi-scale match: Redimensiona q e procura todos em a.
{ Mat_<CORF> qd=dcReject(q,dontcare);
  M3d_<CORF> qss=multEscala(qd,escFim,nEsc);
  Mat_<CORF> t;
  for (int s=0; s<qss.size[0]; s++) {
    t=(2.0/3.0)*somatoriaUm(Mat_<CORF>(fatia(qss,s)));
    t.copyTo(fatia(qss,s));
  }
  multCorr(a, qss, coef, ind);
}

void multMatch1(Mat_<CORF> a, Mat_<CORF> q, double escFim, int nEsc, CORF dontcare, FLT& maxVal, Point& maxLoc, int& maxS, double& scale)
// Multi-scale match: Redimensiona q e procura todos em a. Devolve somente o melhor match
{ Mat_<FLT> coef; Mat_<SHT> ind;
  multMatch(a,q,escFim,nEsc,dontcare,coef,ind);
  double maxValD; minMaxLoc(coef,NULL,&maxValD,NULL,&maxLoc); maxVal=maxValD;
  maxS=ind(maxLoc.y,maxLoc.x);
  double passoEsc=exp(log(escFim)/(nEsc-1));
  scale=pow(passoEsc,maxS);
}

void multMatch1(Mat_<COR> a, Mat_<COR> q, double escFim, int nEsc, COR dontcare, FLT& maxVal, Point& maxLoc, int& maxS, double& scale)
// Multi-scale match: Redimensiona q e procura todos em a. Devolve somente o melhor match
{ Mat_<CORF> af; converte(a,af);
  Mat_<CORF> qf; converte(q,qf);
  CORF dontcaref; converte(dontcare,dontcaref);
  multMatch1(af,qf,escFim,nEsc,dontcaref,maxVal,maxLoc,maxS,scale);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void ScaleMatchFLT::multEscala(Mat_<FLT> _q, double _escFim, int _nEsc, FLT _dontCare) {
// Gera M3d da imagem q em multi-escala e guarda em q
// escInic e' sempre 1.0
// escFim deve ser menor que 1.0
// O resultado vai ter nEsc slices.
// O tamanho da imagem em cada slice e' diferente.
  escFim=_escFim; nEsc=_nEsc; dontCare=_dontCare;
  if (escFim>=1) xerro1("Erro: escFim>=1");
  if (nEsc<=1) xerro1("Erro: nEsc<=1"); 
  q.resize(nEsc); // As imagens ainda nao foram alocadas
  double passoEsc=exp(log(escFim)/(nEsc-1));
  Mat_<FLT> qd=dcReject(_q,dontCare);
  q[0]=somaAbsDois(qd);
  //#pragma omp parallel for
  for (unsigned s=1; s<q.size(); s++) {
    double mult=pow(passoEsc,s);
    Mat_<FLT> t;
    resize(qd, t, Size(cvRound(mult*qd.cols),cvRound(mult*qd.rows)), 0, 0, INTER_AREA);
    q[s]=somaAbsDois(t);
  }
  centro.resize(nEsc); 
  for (unsigned s=0; s<q.size(); s++) {
    centro[s].y=(q[s].rows-1)/2;
    centro[s].x=(q[s].cols-1)/2;
  }
}

void ScaleMatchFLT::match(Mat_<FLT> a, Mat_<FLT>& coef, Mat_<SHT>& ind, int method) { 
  coef.create(a.size()); coef.setTo(-1.01);
  ind.create(a.size());  ind.setTo(-1);
  //#pragma omp parallel for
  for (unsigned s=0; s<q.size(); s++) {
    Mat_<FLT> r;
    matchTemplate(a,q[s],r,method); 
    for (int l=0; l<r.rows; l++) 
      for (int c=0; c<r.cols; c++) {
        int lc=centro[s].y; int cc=centro[s].x;
        if (r(l,c)>coef(l+lc,c+cc)) { 
          coef(l+lc,c+cc)=r(l,c);
          ind(l+lc,c+cc)=s;
        }
      }
  }
}

void ScaleMatchFLT::match1(Mat_<FLT> a, FLT& maxVal, Point& maxLoc, int& maxS, double& scale, int method) {
// Devolve somente o melhor matching
  Mat_<FLT> coef; Mat_<SHT> ind;
  match(a,coef,ind,method);
  double maxValD;
  minMaxLoc(coef,NULL,&maxValD,NULL,&maxLoc);
  maxVal=FLT(maxValD);
  maxS=ind(maxLoc);
  double passoEsc=exp(log(escFim)/(nEsc-1));
  scale=pow(passoEsc,maxS);
}

void ScaleMatchFLT::matchVerify(Mat_<FLT> a, FLT& maxVal1, FLT& maxVal2, 
  Point& maxLoc, int& maxS, double& scale, int method1, int method2) {
// Calcula o melhor match pelo method1, descobrindo maxLoc e maxVal1. 
// Depois calcula o match pelo method2 no mesmo maxLoc, descobrindo maxVal2.
  match1(a,maxVal1,maxLoc,maxS,scale,method1);
  // Falta calcular maxVal2
  Mat_<FLT> roi(a,Rect(maxLoc-centro[maxS],q[maxS].size()));
  Mat_<FLT> r;
  matchTemplate(roi,q[maxS],r,method2); 
  if (r.size()!=Size(1,1)) xerro1("Tamanho nao e' unitario");
  maxVal2=r(0);
}

void ScaleMatchFLT::matchLocationVerify(Mat_<FLT> a, 
  FLT& maxVal1, FLT& maxVal2, Point& maxLoc1, Point& maxLoc2, 
  int& maxS, double& scale, int method1, int method2) {
// Faz template matching por method1 obtendo maxVal1, maxLoc1, maxS e scale.
// Depois, faz template matching por method2 na escala maxS, obtendo maxVal2, maxLoc2.
  match1(a,maxVal1,maxLoc1,maxS,scale,method1);
  Mat_<FLT> r;
  matchTemplate(a,q[maxS],r,method2); 
  double maxVal2D; 
  minMaxLoc(r,NULL,&maxVal2D,NULL,&maxLoc2);
  maxVal2=FLT(maxVal2D);
  maxLoc2.x+=centro[maxS].x;
  maxLoc2.y+=centro[maxS].y;
}

void ScaleMatchFLT::desenha(Mat_<COR>& a, FLT val, Point loc, int s, COR cor) {
  a(loc.y,loc.x)=cor;
  Rect rect(loc-centro[s], q[s].size());
  rectangle(a, rect, toScalar(cor));
  putText(a,format("%d %02d",s,arredonda(100*val)),loc+Point(centro[s].x,-4),
    0,1,toScalar(cor),1);

} 

//<<<<<<<<<<<<<<<<<<<<<<<<<<< Haar <<<<<<<<<<<<<<<<<<<<<<

Mat_<FLT> haar(const Mat_<FLT> a)
{ assert(nextExp2(a.cols)==a.cols && nextExp2(a.rows)==a.rows);
  Mat_<FLT> d=a.clone();
  Mat_<FLT> e(1,max(a.rows,a.cols));
  for (int l=0; l<d.rows; l++)    //rows=512
    for (int m=d.cols; m>1; m/=2) { //m=512, 256, ..., 2
      int m2=m/2;
      for (int c=0; c<m2; c++) { //c=256, 128, ..., 1
        e(c) = (d(l,2*c)+d(l,2*c+1)) /2; 
        e(m2+c) = d(l,2*c)-e(c);
      }
      for (int c=0; c<m; c++) d(l,c)=e(c);
    }
  //resultado em d
  for (int c=0; c<d.cols; c++)    
    for (int m=d.rows; m>1; m/=2) { 
      int m2=m/2;
      for (int l=0; l<m2; l++) { 
        e(l) = (d(2*l,c)+d(2*l+1,c)) /2;
        e(m2+l) = d(2*l,c)-e(l);
      }
      for (int l=0; l<m; l++) d(l,c)=e(l);
    }
  return d;
}

Mat_<FLT> unhaar(const Mat_<FLT> a)
{ assert(nextExp2(a.cols)==a.cols && nextExp2(a.rows)==a.rows);
  Mat_<FLT> d=a.clone();
  Mat_<FLT> e(1,max(a.rows,a.cols));
  for (int l=0; l<d.rows; l++)    //rows=512
    for (int m=2; m<=d.cols; m*=2) { //m=2, 4, ..., 512
      int m2=m/2;
      for (int c=0; c<m2; c++) { //c
        e(2*c)   = d(l,c)+d(l,m2+c);
        e(2*c+1) = d(l,c)-d(l,m2+c);
      }
      for (int c=0; c<m; c++) d(l,c)=e(c);
    }
  // resultado em d
  for (int c=0; c<d.cols; c++)    //cols=512
    for (int m=2; m<=d.rows; m*=2) { //m=2, 4, ..., 512
      int m2=m/2;
      for (int l=0; l<m2; l++) { //l
        e(2*l)   = d(l,c)+d(m2+l,c);
        e(2*l+1) = d(l,c)-d(m2+l,c);
      }
      for (int l=0; l<m; l++) d(l,c)=e(l);
    }
 return d;
}

Mat_<COR> haar2imc(const Mat_<FLT> f)
{ Mat_<COR> d(f.size());
  float max_neg=0.0, max_pos=0.0;
  for (int l=0; l<f.rows; l++)
    for (int c=0; c<f.cols; c++) {
        if (f(l,c) < max_neg) max_neg = f(l,c);
        if (f(l,c) > max_pos) max_pos = f(l,c);
      }
  for (int l=0; l<f.rows; l++)
    for (int c=0; c<f.cols; c++) {
      float v;
      if (f(l,c) < 0) v = f(l,c) / max_neg;
      else            v = f(l,c) / max_pos;
      GRY b = GRY(255 - sqrt(v)*255);
      if (f(l,c) < 0) d(l,c)=COR(b,b,255);
      else d(l,c)=COR(255,b,b);
    }
  return d;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Mat_<GRY> filtro2d(Mat_<GRY> a, Mat_<FLT> k, int borderType)
{ Mat_<GRY> b;
  filter2D(a,b,-1,k,Point(-1,-1),0.0,borderType);
  return b;
}

Mat_<FLT> filtro2d(Mat_<FLT> a, Mat_<FLT> k, int borderType)
{ Mat_<FLT> b;
  filter2D(a,b,-1,k,Point(-1,-1),0.0,borderType);
  return b;
}

Mat_<FLT> trataModelo(Mat_<FLT> k, FLT dontcare)
// Calcula 2*somatoriaUm(dcReject(k))
{ double soma=0.0;
  int conta=0;
  for (unsigned i=0; i<k.total(); i++) {
    if (k(i)!=dontcare) { soma+=k(i); conta++; }
  }  
  double media=soma/conta;
  Mat_<FLT> r(k.size());
  for (unsigned i=0; i<k.total(); i++) {
    if (k(i)!=dontcare) r(i)=k(i)-media; 
    else r(i)=0.0;
  }  

  double somaabs=0.0;
  for (unsigned i=0; i<r.total(); i++)
    somaabs+=abs(r(i));
  r = r / (somaabs/2);
  return r;
}

/*
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< pvConv <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
CvMat* pvConv(CvMat* A, CvMat* B, char modo) // modo: f:full s:same v:valid. Para modo=v, use pvConvV
{
  CvMat* conv=0;
  if ( ((A->type & 0xff)==CV_32F) && ((B->type & 0xff)==CV_32F) ) {
    if      (modo=='f') conv = cvCreateMat( A->rows + B->rows - 1, A->cols + B->cols - 1, A->type );
    else if (modo=='s') conv = cvCreateMat( A->rows, A->cols, A->type );
    else if (modo=='v') conv = cvCreateMat( abs(A->rows - B->rows)+1, abs(A->cols - B->cols)+1, A->type );
    else erro("Erro: Modo invalido");

    int dft_M = cvGetOptimalDFTSize( A->rows + B->rows - 1 );
    int dft_N = cvGetOptimalDFTSize( A->cols + B->cols - 1 );

    CvMat* dft_A = cvCreateMat( dft_M, dft_N, A->type );
    CvMat* dft_B = cvCreateMat( dft_M, dft_N, B->type );
    CvMat tmp;

    cvGetSubRect( dft_A, &tmp, cvRect(0,0,A->cols,A->rows));
    cvCopy( A, &tmp );
    cvGetSubRect( dft_A, &tmp, cvRect(A->cols,0,dft_A->cols - A->cols,A->rows));
    if (dft_A->cols - A->cols > 0) cvZero( &tmp );
    cvDFT( dft_A, dft_A, CV_DXT_FORWARD, A->rows );

    cvGetSubRect( dft_B, &tmp, cvRect(0,0,B->cols,B->rows));
    cvCopy( B, &tmp );
    cvGetSubRect( dft_B, &tmp, cvRect(B->cols,0,dft_B->cols - B->cols,B->rows));
    if (dft_B->cols - B->cols > 0) cvZero( &tmp );
    cvDFT( dft_B, dft_B, CV_DXT_FORWARD, B->rows );

    cvMulSpectrums( dft_A, dft_B, dft_A, 0); // or CV_DXT_MUL_CONJ to get correlation rather than convolution

    if      (modo=='f') {
      cvDFT( dft_A, dft_A, CV_DXT_INV_SCALE, conv->rows ); // calculate only the top part
      cvGetSubRect( dft_A, &tmp, cvRect(0, 0, conv->cols, conv->rows) );
    } else if (modo=='s') {
      cvDFT( dft_A, dft_A, CV_DXT_INV_SCALE, B->rows / 2 + conv->rows );
      cvGetSubRect( dft_A, &tmp, cvRect(B->cols / 2, B->rows / 2, conv->cols, conv->rows) );
    } else if (modo=='v') {
      cvDFT( dft_A, dft_A, CV_DXT_INV_SCALE, min(A->rows,B->rows)-1 + conv->rows );
      cvGetSubRect( dft_A, &tmp, cvRect(min(A->cols,B->cols)-1, min(A->rows,B->rows)-1, conv->cols, conv->rows) );
    } else erro("Erro inesperado");

    cvCopy( &tmp, conv );

    cvReleaseMat(&dft_A);
    cvReleaseMat(&dft_B);
  } else if ((A->type & 0xff)==CV_32FC2 && (B->type & 0xff)==CV_32FC2) {
    if      (modo=='f') conv = cvCreateMat( A->rows + B->rows - 1, A->cols + B->cols - 1, A->type );
    else if (modo=='s') conv = cvCreateMat( A->rows, A->cols, A->type );
    else if (modo=='v') conv = cvCreateMat( abs(A->rows - B->rows)+1, abs(A->cols - B->cols)+1, A->type );
    else erro("Erro: Modo invalido");

    int dft_M = cvGetOptimalDFTSize( A->rows + B->rows - 1 );
    int dft_N = cvGetOptimalDFTSize( A->cols + B->cols - 1 );

    CvMat* dft_A = cvCreateMat( dft_M, dft_N, A->type );
    CvMat* dft_B = cvCreateMat( dft_M, dft_N, B->type );
    CvMat tmp;

    cvGetSubRect( dft_A, &tmp, cvRect(0,0,A->cols,A->rows));
    cvCopy( A, &tmp );
    if (dft_A->cols - A->cols > 0) {
      cvGetSubRect( dft_A, &tmp, cvRect(A->cols,0,dft_A->cols - A->cols,A->rows));
      cvZero( &tmp );
    }
    cvDFT( dft_A, dft_A, CV_DXT_FORWARD, A->rows );

    cvGetSubRect( dft_B, &tmp, cvRect(0,0,B->cols,B->rows));
    cvCopy( B, &tmp );
    if (dft_B->cols - B->cols > 0) {
      cvGetSubRect( dft_B, &tmp, cvRect(B->cols,0,dft_B->cols - B->cols,B->rows));
      cvZero( &tmp );
    }
    cvDFT( dft_B, dft_B, CV_DXT_FORWARD, B->rows );

    cvMulSpectrums( dft_A, dft_B, dft_A, 0); // or CV_DXT_MUL_CONJ to get correlation rather than convolution

    //cvDFT( dft_A, dft_A, CV_DXT_INV_SCALE, conv->rows ); // calculate only the top part. Da' erro.
    cvDFT( dft_A, dft_A, CV_DXT_INV_SCALE); // calculate all rows

    if      (modo=='f') cvGetSubRect( dft_A, &tmp, cvRect(0, 0, conv->cols, conv->rows) );
    else if (modo=='s') cvGetSubRect( dft_A, &tmp, cvRect(B->cols / 2, B->rows / 2, conv->cols, conv->rows) );
    else if (modo=='v') cvGetSubRect( dft_A, &tmp, cvRect(min(A->cols,B->cols)-1, min(A->rows,B->rows)-1, conv->cols, conv->rows) );
    else erro("Erro inesperado");

    cvCopy( &tmp, conv );

    cvReleaseMat(&dft_A);
    cvReleaseMat(&dft_B);
  } else erro("Erro pvConv: tipo de matriz invalido");
  return conv;
}

CvMat* pvConvV(CvMat* A, CvMat* B) // modo valid +rapido
{ if (A->rows<B->rows || A->cols<B->cols) erro("Erro pvConvV: A menor que B");
  CvMat* conv=0;
  if ( ((A->type & 0xff)==CV_32F) && ((B->type & 0xff)==CV_32F) ) {
    conv = cvCreateMat( A->rows - B->rows + 1, A->cols - B->cols + 1, A->type );

    int dft_M = cvGetOptimalDFTSize( A->rows );
    int dft_N = cvGetOptimalDFTSize( A->cols );

    CvMat* dft_A = cvCreateMat( dft_M, dft_N, A->type );
    CvMat* dft_B = cvCreateMat( dft_M, dft_N, B->type );
    CvMat tmp;

    cvGetSubRect( dft_A, &tmp, cvRect(0,0,A->cols,A->rows));
    cvCopy( A, &tmp );
    if (dft_A->cols - A->cols > 0) {
      cvGetSubRect( dft_A, &tmp, cvRect(A->cols,0,dft_A->cols - A->cols,A->rows));
      cvZero( &tmp );
    }
    cvDFT( dft_A, dft_A, CV_DXT_FORWARD, A->rows );

    cvGetSubRect( dft_B, &tmp, cvRect(0,0,B->cols,B->rows));
    cvCopy( B, &tmp );
    if (dft_B->cols - B->cols > 0) {
      cvGetSubRect( dft_B, &tmp, cvRect(B->cols,0,dft_B->cols - B->cols,B->rows));
      cvZero( &tmp );
    }
    cvDFT( dft_B, dft_B, CV_DXT_FORWARD, B->rows );

    cvMulSpectrums( dft_A, dft_B, dft_A, 0); // or CV_DXT_MUL_CONJ to get correlation rather than convolution

    cvDFT( dft_A, dft_A, CV_DXT_INV_SCALE); // Compute all rows
    cvGetSubRect( dft_A, &tmp, cvRect(A->cols - conv->cols, A->rows - conv->rows, conv->cols, conv->rows) );
    cvCopy( &tmp, conv );

    cvReleaseMat(&dft_A);
    cvReleaseMat(&dft_B);
  } else if ((A->type & 0xff)==CV_32FC2 && (B->type & 0xff)==CV_32FC2) {
    conv = cvCreateMat( A->rows - B->rows + 1, A->cols - B->cols + 1, A->type );

    int dft_M = cvGetOptimalDFTSize( A->rows );
    int dft_N = cvGetOptimalDFTSize( A->cols );

    CvMat* dft_A = cvCreateMat( dft_M, dft_N, A->type );
    CvMat* dft_B = cvCreateMat( dft_M, dft_N, B->type );
    CvMat tmp;

    cvGetSubRect( dft_A, &tmp, cvRect(0,0,A->cols,A->rows));
    cvCopy( A, &tmp );
    if (dft_A->cols - A->cols > 0) {
      cvGetSubRect( dft_A, &tmp, cvRect(A->cols,0,dft_A->cols - A->cols,A->rows));
      cvZero( &tmp );
    }
    cvDFT( dft_A, dft_A, CV_DXT_FORWARD, A->rows );

    cvGetSubRect( dft_B, &tmp, cvRect(0,0,B->cols,B->rows));
    cvCopy( B, &tmp );
    if (dft_B->cols - B->cols > 0) {
      cvGetSubRect( dft_B, &tmp, cvRect(B->cols,0,dft_B->cols - B->cols,B->rows));
      cvZero( &tmp );
    }
    cvDFT( dft_B, dft_B, CV_DXT_FORWARD, B->rows );

    cvMulSpectrums( dft_A, dft_B, dft_A, 0); // or CV_DXT_MUL_CONJ to get correlation rather than convolution

    cvDFT( dft_A, dft_A, CV_DXT_INV_SCALE); // calculate all rows
    cvGetSubRect( dft_A, &tmp, cvRect(A->cols - conv->cols, A->rows - conv->rows, conv->cols, conv->rows) );
    cvCopy( &tmp, conv );

    cvReleaseMat(&dft_A);
    cvReleaseMat(&dft_B);
  } else erro("Erro pvConv: tipo de matriz invalido");
  return conv;
}

Mat_<FLT> pvConv(Mat_<FLT> a, Mat_<FLT> b, char modo) // modo: f:full s:same v:valid
{ CvMat Av=a; CvMat* A=&Av;
  CvMat Bv=b; CvMat* B=&Bv;

  CvMat* conv=0;
  if (modo=='f' || modo=='s') conv=pvConv(A,B,modo);
  else if (modo=='v') conv=pvConvV(A,B);
  else erro("Erro: pvConv modo invalido");

  Mat_<FLT> d(conv);
  return d;
}

Mat_<CPX> pvConv(Mat_<CPX> a, Mat_<CPX> b, char modo) // modo: f:full s:same v:valid
{ CvMat Av=a; CvMat* A=&Av;
  CvMat Bv=b; CvMat* B=&Bv;

  CvMat* conv=0;
  if (modo=='f' || modo=='s') conv=pvConv(A,B,modo);
  else if (modo=='v') conv=pvConvV(A,B);
  else erro("Erro: pvConv modo invalido");

  Mat_<FLT> d(conv);
  return d;
}

void pvMultConvV(Mat_<CPX> a, vector< Mat_<CPX> >& b, vector< Mat_<CPX> >& d) // modo valid
{ if (a.rows<b[0].rows || a.cols<b[0].cols) erro("Erro pvMultConvV: A menor que B");
  // Estou supondo que b e' em forma de paralelepipedo
  int conv_rows=a.rows-b[0].rows+1; int conv_cols=a.cols-b[0].cols+1;
  d.resize(b.size());

  int dft_M = cvGetOptimalDFTSize( a.rows );
  int dft_N = cvGetOptimalDFTSize( a.cols );

  CvMat* dft_A = cvCreateMat( dft_M, dft_N, CV_32FC2 );
  CvMat* dft_B = cvCreateMat( dft_M, dft_N, CV_32FC2 );
  CvMat tmp;

  CvMat Av=a; CvMat* A=&Av;
  cvGetSubRect( dft_A, &tmp, cvRect(0,0,A->cols,A->rows));
  cvCopy( A, &tmp );
  if (dft_A->cols - A->cols > 0) {
    cvGetSubRect( dft_A, &tmp, cvRect(A->cols,0,dft_A->cols - A->cols,A->rows));
    cvZero( &tmp );
  }
  cvDFT( dft_A, dft_A, CV_DXT_FORWARD, A->rows );

  CvMat Bv; CvMat* B; 
  for (unsigned s=0; s<b.size(); s++) {
    Bv = b[s]; B=&Bv;
    cvGetSubRect( dft_B, &tmp, cvRect(0,0,B->cols,B->rows));
    cvCopy( B, &tmp );
    if (dft_B->cols - B->cols > 0) {
      cvGetSubRect( dft_B, &tmp, cvRect(B->cols,0,dft_B->cols - B->cols,B->rows));
      cvZero( &tmp );
    }
    cvDFT( dft_B, dft_B, CV_DXT_FORWARD, B->rows );

    cvMulSpectrums( dft_A, dft_B, dft_B, 0); // or CV_DXT_MUL_CONJ to get correlation rather than convolution
    cvDFT( dft_B, dft_B, CV_DXT_INV_SCALE); // calculate all rows

    cvGetSubRect( dft_B, &tmp, cvRect(A->cols - conv_cols, A->rows - conv_rows, conv_cols, conv_rows) );
    (Mat_<CPX>(&tmp)).copyTo(d[s]);
  }
  cvReleaseMat(&dft_A);
  cvReleaseMat(&dft_B);
}

void pvMultConv(Mat_<CPX> a, vector< Mat_<CPX> >& b, vector< Mat_<CPX> >& d, char modo) // modo: f:full s:same v:valid
{ if (modo=='v') { pvMultConvV(a,b,d); return; }
  // Estou supondo que b e' em forma de paralelepipedo

  int conv_rows, conv_cols;
  if      (modo=='f') { conv_rows = a.rows + b[0].rows - 1; conv_cols = a.cols + b[0].cols - 1; }
  else if (modo=='s') { conv_rows = a.rows; conv_cols = a.cols; }
  else erro("Erro: Modo invalido");

  d.resize(b.size());

  int dft_M = cvGetOptimalDFTSize( a.rows+b[0].rows-1 );
  int dft_N = cvGetOptimalDFTSize( a.cols+b[0].rows-1 );

  CvMat* dft_A = cvCreateMat( dft_M, dft_N, CV_32FC2 );
  CvMat* dft_B = cvCreateMat( dft_M, dft_N, CV_32FC2 );
  CvMat tmp;

  CvMat Av=a; CvMat* A=&Av;
  cvGetSubRect( dft_A, &tmp, cvRect(0,0,A->cols,A->rows));
  cvCopy( A, &tmp );
  if (dft_A->cols - A->cols > 0) {
    cvGetSubRect( dft_A, &tmp, cvRect(A->cols,0,dft_A->cols - A->cols,A->rows));
    cvZero( &tmp );
  }
  cvDFT( dft_A, dft_A, CV_DXT_FORWARD, A->rows );

  CvMat Bv; CvMat* B; 
  for (unsigned s=0; s<b.size(); s++) {
    Bv = b[s]; B=&Bv;
    cvGetSubRect( dft_B, &tmp, cvRect(0,0,B->cols,B->rows));
    cvCopy( B, &tmp );
    if (dft_B->cols - B->cols > 0) {
      cvGetSubRect( dft_B, &tmp, cvRect(B->cols,0,dft_B->cols - B->cols,B->rows));
      cvZero( &tmp );
    }
    cvDFT( dft_B, dft_B, CV_DXT_FORWARD, B->rows );

    cvMulSpectrums( dft_A, dft_B, dft_B, 0); // or CV_DXT_MUL_CONJ to get correlation rather than convolution
    cvDFT( dft_B, dft_B, CV_DXT_INV_SCALE); // calculate all rows

    if      (modo=='f') cvGetSubRect( dft_B, &tmp, cvRect(0, 0, conv_cols, conv_rows) );
    else if (modo=='s') cvGetSubRect( dft_B, &tmp, cvRect(B->cols / 2, B->rows / 2, conv_cols, conv_rows) );
    else erro("Erro inesperado");

    (Mat_<CPX>(&tmp)).copyTo(d[s]);
  }
  cvReleaseMat(&dft_A);
  cvReleaseMat(&dft_B);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Mat_<CPX> pvPreConvV(Mat_<CPX> a, int b_rows, int b_cols) // modo valid
{ if (a.rows<b_rows || a.cols<b_cols) erro("Erro preConvV: A menor que B");
  int dft_M = cvGetOptimalDFTSize( a.rows );
  int dft_N = cvGetOptimalDFTSize( a.cols );
  CvMat* dft_A = cvCreateMat( dft_M, dft_N, CV_32FC2 );
  CvMat tmp;

  CvMat Av=a; CvMat* A=&Av;
  cvGetSubRect( dft_A, &tmp, cvRect(0,0,A->cols,A->rows));
  cvCopy( A, &tmp );
  if (dft_A->cols - A->cols > 0) {
    cvGetSubRect( dft_A, &tmp, cvRect(A->cols,0,dft_A->cols - A->cols,A->rows));
    cvZero( &tmp );
  }
  cvDFT( dft_A, dft_A, CV_DXT_FORWARD, A->rows );
  Mat_<CPX> DFT_A=Mat_<CPX>(dft_A);
  return DFT_A;
}

Mat_<CPX> pvPosConvV(Mat_<CPX> a, Mat_<CPX> DFT_A, Mat_<CPX> b) // modo valid
{ int conv_rows=a.rows-b.rows+1; int conv_cols=a.cols-b.cols+1;
  int dft_M = cvGetOptimalDFTSize( a.rows );
  int dft_N = cvGetOptimalDFTSize( a.cols );

  CvMat dft_Av=DFT_A; CvMat* dft_A=&dft_Av;
  CvMat* dft_B = cvCreateMat( dft_M, dft_N, CV_32FC2 );
  CvMat tmp;

  CvMat Bv=b; CvMat* B=&Bv; 
  cvGetSubRect( dft_B, &tmp, cvRect(0,0,B->cols,B->rows));
  cvCopy( B, &tmp );
  if (dft_B->cols - B->cols > 0) {
    cvGetSubRect( dft_B, &tmp, cvRect(B->cols,0,dft_B->cols - B->cols,B->rows));
    cvZero( &tmp );
  }
  cvDFT( dft_B, dft_B, CV_DXT_FORWARD, B->rows );

  cvMulSpectrums( dft_A, dft_B, dft_B, 0); // or CV_DXT_MUL_CONJ to get correlation rather than convolution
  cvDFT( dft_B, dft_B, CV_DXT_INV_SCALE); // calculate all rows
  cvGetSubRect( dft_B, &tmp, cvRect(a.cols - conv_cols, a.rows - conv_rows, conv_cols, conv_rows) );
  Mat_<CPX> d; (Mat_<CPX>(&tmp)).copyTo(d);
  cvReleaseMat(&dft_B);
  return d;
}

Mat_<CPX> pvPreConv(Mat_<CPX> a, int b_rows, int b_cols, char modo) // modo: f:full s:same v:valid
{ if (modo=='v') { return pvPreConvV(a,b_rows,b_cols); }
  if (a.rows<b_rows || a.cols<b_cols) erro("Erro preConvV: A menor que B");
  int dft_M = cvGetOptimalDFTSize( a.rows+b_rows-1 );
  int dft_N = cvGetOptimalDFTSize( a.cols+b_cols-1 );
  CvMat* dft_A = cvCreateMat( dft_M, dft_N, CV_32FC2 );
  CvMat tmp;

  CvMat Av=a; CvMat* A=&Av;
  cvGetSubRect( dft_A, &tmp, cvRect(0,0,A->cols,A->rows));
  cvCopy( A, &tmp );
  if (dft_A->cols - A->cols > 0) {
    cvGetSubRect( dft_A, &tmp, cvRect(A->cols,0,dft_A->cols - A->cols,A->rows));
    cvZero( &tmp );
  }
  cvDFT( dft_A, dft_A, CV_DXT_FORWARD, A->rows );
  Mat_<CPX> DFT_A=Mat_<CPX>(dft_A);
  return DFT_A;
}

Mat_<CPX> pvPosConv(Mat_<CPX> a, Mat_<CPX> DFT_A, Mat_<CPX> b, char modo) // modo: f:full s:same v:valid
{ if (modo=='v') { return pvPosConvV(a,DFT_A,b); }
  int conv_rows; int conv_cols;
  if      (modo=='f') { conv_rows = a.rows+b.rows-1; conv_cols = a.cols+b.cols-1; }
  else if (modo=='s') { conv_rows = a.rows; conv_cols = a.cols; }
  else erro("Erro: Modo invalido");

  int dft_M = cvGetOptimalDFTSize( a.rows+b.rows-1 );
  int dft_N = cvGetOptimalDFTSize( a.cols+b.cols-1 );
  CvMat dft_Av=DFT_A; CvMat* dft_A=&dft_Av;
  CvMat* dft_B = cvCreateMat( dft_M, dft_N, CV_32FC2 );
  CvMat tmp;

  CvMat Bv=b; CvMat* B=&Bv; 
  cvGetSubRect( dft_B, &tmp, cvRect(0,0,B->cols,B->rows));
  cvCopy( B, &tmp );
  if (dft_B->cols - B->cols > 0) {
    cvGetSubRect( dft_B, &tmp, cvRect(B->cols,0,dft_B->cols - B->cols,B->rows));
    cvZero( &tmp );
  }
  cvDFT( dft_B, dft_B, CV_DXT_FORWARD, B->rows );

  cvMulSpectrums( dft_A, dft_B, dft_B, 0); // or CV_DXT_MUL_CONJ to get correlation rather than convolution
  cvDFT( dft_B, dft_B, CV_DXT_INV_SCALE); // calculate all rows

  if      (modo=='f') cvGetSubRect( dft_B, &tmp, cvRect(0, 0, conv_cols, conv_rows) );
  else if (modo=='s') cvGetSubRect( dft_B, &tmp, cvRect(B->cols / 2, B->rows / 2, conv_cols, conv_rows) );
  else erro("Erro inesperado");
  Mat_<CPX> d; (Mat_<CPX>(&tmp)).copyTo(d);
  cvReleaseMat(&dft_B);
  return d;
}
*/

//<<<<<<<<<<<<<<<<<<<<<<<< FFT com resultado CPX <<<<<<<<<<<<<<<<<<<<<<<
Mat_<CPX> fft2(Mat_<CPX> w, int nl, int nc) {
  if (nl==0 && nc==0) { nl=w.rows; nc=w.cols; }
  if (w.rows>nl || w.cols>nc) xerro1("Erro fft2(CPX): especificacao de dimensao");
  Mat_<CPX> wt( nl, nc, CPX{0,0} );
  copia(w, wt, 0,0);
  dft(wt, wt, DFT_COMPLEX_OUTPUT, w.rows);
  return wt;
}

Mat_<CPX> ifft2(Mat_<CPX> W, int nl, int nc) {
  if (nl==0 && nc==0) { nl=W.rows; nc=W.cols; }
  if (W.rows>nl || W.cols>nc) xerro1("Erro ifft2(CPX): especificacao de dimensao");
  Mat_<CPX> Wt( nl, nc, CPX{0,0} );
  copia(W, Wt, 0,0);
  dft(Wt, Wt, DFT_COMPLEX_OUTPUT | DFT_INVERSE | DFT_SCALE, W.rows);
  return Wt;
}

Mat_<CPX> fft2(Mat_<FLT> w, int nl, int nc) {
  if (nl==0 && nc==0) { nl=w.rows; nc=w.cols; }
  if (w.rows>nl || w.cols>nc) xerro1("Erro fft2(FLT): especificacao de dimensao");
  Mat_<FLT> wt( nl, nc, 0.0 );
  copia(w, wt, 0,0);
  Mat_<CPX> W;
  dft(wt, W, DFT_COMPLEX_OUTPUT, w.rows);
  return W;
}

Mat_<CPX> ifft2(Mat_<FLT> W, int nl, int nc) {
  if (nl==0 && nc==0) { nl=W.rows; nc=W.cols; }
  if (W.rows>nl || W.cols>nc) xerro1("Erro ifft2(FLT): especificacao de dimensao");
  Mat_<FLT> Wt( nl, nc, 0.0 );
  copia(W, Wt, 0,0);
  Mat_<CPX> w;
  dft(Wt, w, DFT_COMPLEX_OUTPUT | DFT_INVERSE | DFT_SCALE, W.rows);
  return w;
}

//<<<<<<<<<<<<<<<<<<<<<<<< DFT-based convolution <<<<<<<<<<<<<<<<<<<<<<<
Mat_<FLT> conv2(Mat_<FLT> A, Mat_<FLT> B, char modo) // modo: f:full s:same v:valid. 
{ Mat_<FLT> C;
  if      (modo=='f') C.create( A.rows+B.rows-1, A.cols+B.cols-1 );
  else if (modo=='s') C.create( A.rows, A.cols );
  else if (modo=='v') C.create( A.rows-B.rows+1, A.cols-B.cols+1 );
  else erro("Erro: Modo invalido");

  Size dftSize;
  if (modo=='f' || modo=='s') {
    dftSize.height = getOptimalDFTSize(A.rows+B.rows-1);
    dftSize.width = getOptimalDFTSize(A.cols+B.cols-1);
  } else { // modo v
    dftSize.height = getOptimalDFTSize(A.rows);
    dftSize.width = getOptimalDFTSize(A.cols);
  }

  Mat_<FLT> tempA(dftSize, 0.0);
  Mat_<FLT> tempB(dftSize, 0.0);
  Mat_<FLT> roiA(tempA, Rect(0,0,A.cols,A.rows));
  A.copyTo(roiA);
  Mat_<FLT> roiB(tempB, Rect(0,0,B.cols,B.rows));
  B.copyTo(roiB);

  dft(tempA, tempA, 0, A.rows);
  dft(tempB, tempB, 0, B.rows);
  mulSpectrums(tempA, tempB, tempA, 0, false);

  if      (modo=='f') {
    dft( tempA, tempA, DFT_INVERSE + DFT_SCALE, C.rows ); // calculate only the top part
    tempA(Rect(0, 0, C.cols, C.rows)).copyTo(C);
  } else if (modo=='s') {
    dft( tempA, tempA, DFT_INVERSE + DFT_SCALE, B.rows/2+C.rows ); // calculate only the top part
    tempA(Rect(B.cols/2, B.rows/2, C.cols, C.rows)).copyTo(C);
  } else if (modo=='v') {
    dft( tempA, tempA, DFT_INVERSE + DFT_SCALE); // Compute all rows
    tempA(Rect(A.cols-C.cols, A.rows-C.rows, C.cols, C.rows)).copyTo(C);
  } else erro("Erro inesperado");
  return C;
}

Mat_<CPX> conv2(Mat_<CPX> A, Mat_<CPX> B, char modo) // modo: f:full s:same v:valid. 
{ Mat_<CPX> C;
  if      (modo=='f') C.create( A.rows+B.rows-1, A.cols+B.cols-1 );
  else if (modo=='s') C.create( A.rows, A.cols );
  else if (modo=='v') C.create( A.rows-B.rows+1, A.cols-B.cols+1 );
  else erro("Erro: Modo invalido");

  Size dftSize;
  if (modo=='f' || modo=='s') {
    dftSize.height = getOptimalDFTSize(A.rows+B.rows-1);
    dftSize.width = getOptimalDFTSize(A.cols+B.cols-1);
  } else { // modo v
    dftSize.height = getOptimalDFTSize(A.rows);
    dftSize.width = getOptimalDFTSize(A.cols);
  }

  Mat_<CPX> tempA(dftSize, CPX(0.0));
  Mat_<CPX> tempB(dftSize, CPX(0.0));
  Mat_<CPX> roiA(tempA, Rect(0,0,A.cols,A.rows));
  A.copyTo(roiA);
  Mat_<CPX> roiB(tempB, Rect(0,0,B.cols,B.rows));
  B.copyTo(roiB);

  dft(tempA, tempA, 0, A.rows);
  dft(tempB, tempB, 0, B.rows);
  mulSpectrums(tempA, tempB, tempA, 0, false);

  dft( tempA, tempA, DFT_INVERSE + DFT_SCALE); // compute all rows OK.
  if      (modo=='f') {
    tempA(Rect(0, 0, C.cols, C.rows)).copyTo(C);
  } else if (modo=='s') {
    tempA(Rect(B.cols/2, B.rows/2, C.cols, C.rows)).copyTo(C);
  } else if (modo=='v') {
    tempA(Rect(A.cols-C.cols, A.rows-C.rows, C.cols, C.rows)).copyTo(C);
  } else erro("Erro inesperado");
  return C;
}

Mat_<FLT> convV(const Mat_<FLT>& A, const Mat_<FLT>& B) {
  if (A.rows<B.rows || A.cols<B.cols) erro("Erro convolucao: A menor que B");
  Mat_<FLT> C( A.rows-B.rows+1, A.cols-B.cols+1 );
  Size dftSize;
  dftSize.height = getOptimalDFTSize(A.rows);
  dftSize.width = getOptimalDFTSize(A.cols);

  Mat_<FLT> tempA(dftSize, 0.0);
  Mat_<FLT> tempB(dftSize, 0.0);
  Mat_<FLT> roiA(tempA, Rect(0,0,A.cols,A.rows));
  A.copyTo(roiA);
  Mat_<FLT> roiB(tempB, Rect(0,0,B.cols,B.rows));
  B.copyTo(roiB);
  dft(tempA, tempA, 0, A.rows);
  dft(tempB, tempB, 0, B.rows);
  mulSpectrums(tempA, tempB, tempA, 0, false);
  dft(tempA, tempA, DFT_INVERSE+DFT_SCALE);
  tempA(Rect(A.cols-C.cols, A.rows-C.rows, C.cols, C.rows)).copyTo(C);
  return C;
}

Mat_<CPX> convV(const Mat_<CPX>& A, const Mat_<CPX>& B) {
  if (A.rows<B.rows || A.cols<B.cols) erro("Erro convolucao: A menor que B");
  Mat_<CPX> C( A.rows-B.rows+1, A.cols-B.cols+1 );
  Size dftSize;
  dftSize.height = getOptimalDFTSize(A.rows);
  dftSize.width = getOptimalDFTSize(A.cols);
  Mat_<CPX> tempA(dftSize, CPX(0,0));
  Mat_<CPX> tempB(dftSize, CPX(0,0));
  Mat_<CPX> roiA(tempA, Rect(0,0,A.cols,A.rows));
  A.copyTo(roiA);
  Mat_<CPX> roiB(tempB, Rect(0,0,B.cols,B.rows));
  B.copyTo(roiB);
  dft(tempA, tempA, 0, A.rows);
  dft(tempB, tempB, 0, B.rows);
  mulSpectrums(tempA, tempB, tempA, 0, false);
  dft(tempA, tempA, DFT_INVERSE+DFT_SCALE);
  tempA(Rect(A.cols-C.cols, A.rows-C.rows, C.cols, C.rows)).copyTo(C);
  return C;
}

// M3d<FLT> multConvV(const M3d<FLT>& A, const Mat_<FLT>& B) { // modo valid
//   if (A.ns<=0) erro("Erro multConvV: A nulo");
//   if (A.rows<B.rows || A.cols<B.cols) erro("Erro convolucao: A menor que B");

//   M3d<FLT> C( A.ns, A.rows-B.rows+1, A.cols-B.cols+1 );
//   Size dftSize;
//   dftSize.height = getOptimalDFTSize(A.rows);
//   dftSize.width = getOptimalDFTSize(A.cols);

//   Mat_<FLT> tempA(dftSize, 0.0);
//   Mat_<FLT> roiA(tempA, Rect(0,0,A.cols,A.rows));

//   Mat_<FLT> tempB(dftSize, 0.0);
//   Mat_<FLT> roiB(tempB, Rect(0,0,B.cols,B.rows));
//   B.copyTo(roiB);
//   dft(tempB, tempB, 0, B.rows);

//   for (int s=0; s<A.ns; s++) {
//     A(s).copyTo(roiA);
//     dft(tempA, tempA, 0, A.rows);
//   
//     mulSpectrums(tempA, tempB, tempA, 0);
//     dft(tempA, tempA, DFT_INVERSE+DFT_SCALE);
//     tempA(Rect(A.cols-C.cols, A.rows-C.rows, C.cols, C.rows)).copyTo(C(s));
//   }
//   return C;
// }

// M3d<CPX> multConvV(const M3d<CPX>& A, const Mat_<CPX>& B) { // modo valid
//   if (A.ns<=0) erro("Erro multConvV: A nulo");
//   if (A.rows<B.rows || A.cols<B.cols) erro("Erro convolucao: A menor que B");
//   
//   M3d<CPX> C( A.ns, A.rows-B.rows+1, A.cols-B.cols+1 );
//   Size dftSize;
//   dftSize.width = getOptimalDFTSize(A.cols);
//   dftSize.height = getOptimalDFTSize(A.rows);

//   Mat_<CPX> tempA(dftSize, CPX(0,0));
//   Mat_<CPX> roiA(tempA, Rect(0,0,A.cols,A.rows));

//   Mat_<CPX> tempB(dftSize, CPX(0,0));
//   Mat_<CPX> roiB(tempB, Rect(0,0,B.cols,B.rows));
//   B.copyTo(roiB);
//   dft(tempB, tempB, 0, B.rows);

//   for (int s=0; s<A.ns; s++) {
//     A(s).copyTo(roiA);
//     dft(tempA, tempA, 0, A.rows);

//     mulSpectrums(tempA, tempB, tempA, 0);
//     dft(tempA, tempA, DFT_INVERSE+DFT_SCALE);
//     tempA(Rect(A.cols-C.cols, A.rows-C.rows, C.cols, C.rows)).copyTo(C(s));
//   }
//   return C;
// }


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void STEPCONVFLT::inicializa(int arows, int acols, int brows, int bcols, char pmodo)
{ modo=pmodo;
  asize=Size(acols,arows);
  bsize=Size(bcols,brows);
  if (modo=='f' || modo=='s') {
    dftSize.height = getOptimalDFTSize(arows+brows-1);
    dftSize.width = getOptimalDFTSize(acols+bcols-1);
  } else if (modo=='v') { 
    dftSize.height = getOptimalDFTSize(arows);
    dftSize.width = getOptimalDFTSize(acols);
  } else erro("Erro STEPCONV::inicializa: modo invalido");
}

void STEPCONVFLT::inicializa(Mat_<FLT> a, Mat_<FLT> b, char pmodo)
{ inicializa(a.rows,a.cols,b.rows,b.cols,pmodo); }

Mat_<FLT> STEPCONVFLT::dftA(Mat_<FLT> a)
{ if (a.size()!=asize) erro("Erro STEPCONV::dftA: tamanho a invalido");
  Mat_<FLT> tempA(dftSize, 0.0);
  Mat_<FLT> roiA(tempA, Rect(0,0,a.cols,a.rows));
  a.copyTo(roiA);
  dft(tempA, tempA, 0, a.rows);
  return tempA;
}

Mat_<FLT> STEPCONVFLT::dftB(Mat_<FLT> b)
{ if (b.size()!=bsize) erro("Erro STEPCONV::dftB: tamanho b invalido");
  Mat_<FLT> tempB(dftSize, 0.0);
  Mat_<FLT> roiB(tempB, Rect(0,0,b.cols,b.rows));
  b.copyTo(roiB);
  dft(tempB, tempB, 0, b.rows);
  return tempB;
}

Mat_<FLT> STEPCONVFLT::idft(Mat_<FLT> A, Mat_<FLT> B)
{ Mat_<FLT> C,temp;
  if (A.size()!=dftSize || B.size()!=dftSize) erro("Erro STEPCONV::idft: Dimensao invalida");
  if      (modo=='f') {
    C.create( asize.height+bsize.height-1, asize.width+bsize.width-1 );
    mulSpectrums(A, B, temp, 0, false);
    dft( temp, temp, DFT_INVERSE + DFT_SCALE, C.rows ); // calculate only the top part - da erro no opencv antigo. verificar.
    temp(Rect(0, 0, C.cols, C.rows)).copyTo(C);
  } else if (modo=='s') { 
    C.create( asize.height, asize.width );
    mulSpectrums(A, B, temp, 0, false);
    dft( temp, temp, DFT_INVERSE + DFT_SCALE, bsize.height/2+C.rows ); // calculate only the top part - da erro no opencv antigo. verificar.
    temp(Rect(bsize.width/2, bsize.height/2, C.cols, C.rows)).copyTo(C);
  } else if (modo=='v') {
    C.create( asize.height-bsize.height+1, asize.width-bsize.width+1 );
    mulSpectrums(A, B, temp, 0, false);
    dft( temp, temp, DFT_INVERSE + DFT_SCALE); // Compute all rows
    temp(Rect(asize.width-C.cols, asize.height-C.rows, C.cols, C.rows)).copyTo(C);
  } else erro("Erro STEPCONV::idft: Modo invalido");
  return C;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void STEPCONVCPX::inicializa(int arows, int acols, int brows, int bcols, char pmodo)
{ modo=pmodo;
  asize=Size(acols,arows);
  bsize=Size(bcols,brows);
  if (modo=='f' || modo=='s') {
    dftSize.height = getOptimalDFTSize(arows+brows-1);
    dftSize.width = getOptimalDFTSize(acols+bcols-1);
  } else if (modo=='v') { 
    dftSize.height = getOptimalDFTSize(arows);
    dftSize.width = getOptimalDFTSize(acols);
  } else erro("Erro STEPCONV::inicializa: modo invalido");
}

void STEPCONVCPX::inicializa(Mat_<CPX> a, Mat_<CPX> b, char pmodo)
{ inicializa(a.rows,a.cols,b.rows,b.cols,pmodo); }

Mat_<CPX> STEPCONVCPX::dftA(Mat_<CPX> a)
{ if (a.size()!=asize) erro("Erro STEPCONV::dftA: tamanho a invalido");
  Mat_<CPX> tempA(dftSize, 0.0);
  Mat_<CPX> roiA(tempA, Rect(0,0,a.cols,a.rows));
  a.copyTo(roiA);
  dft(tempA, tempA, 0, a.rows);
  return tempA;
}

Mat_<CPX> STEPCONVCPX::dftB(Mat_<CPX> b)
{ if (b.size()!=bsize) erro("Erro STEPCONV::dftB: tamanho b invalido");
  Mat_<CPX> tempB(dftSize, 0.0);
  Mat_<CPX> roiB(tempB, Rect(0,0,b.cols,b.rows));
  b.copyTo(roiB);
  dft(tempB, tempB, 0, b.rows);
  return tempB;
}

Mat_<CPX> STEPCONVCPX::idft(Mat_<CPX> A, Mat_<CPX> B)
{ Mat_<CPX> C,temp;
  if (A.size()!=dftSize || B.size()!=dftSize) erro("Erro STEPCONV::idft: Dimensao invalida");
  if      (modo=='f') {
    C.create( asize.height+bsize.height-1, asize.width+bsize.width-1 );
    mulSpectrums(A, B, temp, 0, false);
    dft( temp, temp, DFT_INVERSE + DFT_SCALE); // calculate all rows
    temp(Rect(0, 0, C.cols, C.rows)).copyTo(C);
  } else if (modo=='s') { 
    C.create( asize.height, asize.width );
    mulSpectrums(A, B, temp, 0, false);
    dft( temp, temp, DFT_INVERSE + DFT_SCALE); // calculate all rows
    temp(Rect(bsize.width/2, bsize.height/2, C.cols, C.rows)).copyTo(C);
  } else if (modo=='v') {
    C.create( asize.height-bsize.height+1, asize.width-bsize.width+1 );
    mulSpectrums(A, B, temp, 0, false);
    dft( temp, temp, DFT_INVERSE + DFT_SCALE); // Compute all rows
    temp(Rect(asize.width-C.cols, asize.height-C.rows, C.cols, C.rows)).copyTo(C);
  } else erro("Erro STEPCONV::idft: Modo invalido");
  return C;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void CUTTREE::save(string st)
{ FILE* arq=fopen(st.c_str(),"wb");
  if (arq==NULL) erro("Erro na abertura de arquivo");

  int n=ee.size();
  fwrite(&n,1,sizeof(n),arq);
  fwrite(ee.data(),n,sizeof(int),arq);
  n=filt.size();
  fwrite(&n,1,sizeof(n),arq);
  fwrite(filt.data(),n,sizeof(NOFILT),arq);
  fclose(arq);
}

void CUTTREE::load(string st)
{ FILE* arq=fopen(st.c_str(),"rb");
  if (arq==NULL) erro("Erro na abertura de arquivo");

  int n;
  fread(&n,1,sizeof(n),arq);
  ee.resize(n);
  fread(ee.data(),n,sizeof(int),arq);

  fread(&n,1,sizeof(n),arq);
  filt.resize(n);
  fread(filt.data(),n,sizeof(NOFILT),arq);
  fclose(arq);
}

void CUTTREE::impFilt(void)
{ printf("****************** impfilt *********************\n");
  for (unsigned i=0; i<filt.size(); i++) {
    printf("i=%d v=%d e=%d r=%d\n",
           i,filt[i].v,filt[i].e,filt[i].r);
  }
  printf("\n");
}

/*
void impind(int l, int r)
{ int i;
  printf("****************** impind *********************\n");
  for (i=l; i<=r; i++) {
    printf("(%4d,%4d)    ",
           i, ent( ind.v[i](0)+ee(iee)(0),ind.v[i](1)+ee(iee)(1)) );
    if ((i-l)%4==3) printf("\n");
  }
}
*/

BYTE CUTTREE::valindee(int i)
// valor do feature linha ind[i], coluna indexado por iee
{ return features(ind[i],ee[iee]); }

BYTE CUTTREE::valind(int i) 
// valor de saida do indice i
{ return saidas(ind[i]); }

int CUTTREE::compara(int a, int b)
{ int va=features(a,ee[iee]);
  int vb=features(b,ee[iee]);
  if (va<vb) return -1;
  else if (va>vb) return 1;
  else return 0;
}

int CUTTREE::mediana(int l, int r)
// Devolve a primeira posicao m onde aparece o elemento mediano.
// `A esquerda da posicao devolvida m so ha elementos menores que mediano.
// `A direita da posicao devolvida m so ha elementos maiores ou iguais.
// Devolve em va a media aritmetica do mediano e o elemento que ficaria
//   na posicao m-1 se fosse ordenado.
// Devolve -1 se e' impossivel quebrar.
{ int i,j,lo,ro,min,indmin,m; int w,x;

  lo=l; ro=r; m=(l+r+1)/2;
  while (l<r) {
    x=ind[m]; i=l; j=r;
    do {
      while (compara(ind[i],x)<0) i++;
      while (compara(x,ind[j])<0) j--;
      if (i<=j) {
        w=ind[i]; ind[i]=ind[j];
        ind[j]=w; i++; j--;
      }
    } while (i<=j);
    if (j<m) l=i; 
    if (m<i) r=j;
  } // Na m-esima posicao esta o elemento mediano.

  x=ind[m]; i=lo; j=m-1;
  do {
    while (compara(ind[i],x)!=0) i++;
    while (i<=j && compara(ind[j],x)==0) j--;
    if (i<=j) {
      w=ind[i]; ind[i]=ind[j];
      ind[j]=w; i++; j--;
    }
  } while (i<=j);
  l=j+1; // l=primeira posicao onde aparece x
  if (l>lo) {
  //  m=l; l--;
  //  max=valindee(l,ent); indmax=l;
  //  for (i=l-1; i>=lo; i--) {
  //    j=valindee(i,ent);
  //    if (j>max) { max=j; indmax=i; }
  //  }
  //  va=(valindee(indmax,ent)+valindee(m,ent))/2;
  //  va=valindee(m,ent);
    return l;
  }

  i=m+1; j=ro;
  do {
    while (compara(ind[j],x)!=0) j--;
    while (i<=j && compara(ind[i],x)==0) i++;
    if (i<=j) {
      w=ind[i]; ind[i]=ind[j];
      ind[j]=w; i++; j--;
    }
  } while (i<=j);
  r=i-1;
  if (r==ro) { return -1; }
  // r=ultima posicao em que aparece x.
  // Tem que colocar elemento certo em r+1.

  r++; m=r;
  min=valindee(r); indmin=r;
  for (i=r+1; i<=ro; i++) {
    j=valindee(i);
    if (j<min) { min=j; indmin=i; }
  }
  w=ind[indmin]; ind[indmin]=ind[r];
  ind[r]=w;

  //va=(valindee(m-1,ent)+valindee(m,ent))/2; return m;
  //va=valindee(m,ent);
  return m;
}

BYTE CUTTREE::valor(int l, int r)
{ int s=0,i,j;
  static vector<int> freq(256);
  int maxfreq,maxcor,err,minerr;

  folhas++;
  
  static int contador=0;
  contador++; 
  if (contador==100000) { putc('.',stderr); contador=0; }

  if (r==l) { s=valind(l); pixelsolit++; }
  else {
    repeticoescs++; pixelsrepcs=pixelsrepcs+(r-l+1);
    if (modoconf=='m') {
      s=0;
      for (i=l; i<=r; i++) s=s+valind(i);
      j=(r-l)/2; // Para acertar arredondamentos
      s=(s+j)/(r-l+1);
    } else if (modoconf=='f') {
      for (i=0; i<256; i++) freq[i]=0;
      for (i=l; i<=r; i++) freq[valind(i)]++;
      maxfreq=0; maxcor=0;
      for (i=0; i<256; i++) {
        if (freq[i]>maxfreq) { maxfreq=freq[i]; maxcor=i; }
      }
      s=maxcor;
    } else if (modoconf=='a') {
      for (i=0; i<256; i++) freq[i]=0;
      for (i=l; i<=r; i++) freq[valind(i)]++;
      minerr=0x7fffffff; maxcor=0;
      for (i=0; i<256; i++) { // Testando cor i
        err=0;
        for (j=0; j<256; j++) err=err+abs(i-j)*freq[j];
        if (err<minerr) { minerr=err; maxcor=i; }
      } 
      s=maxcor;
    } else erro("Erro valor: modoconf invalido");
  }
  if (s<0) s=0;
  if (s>255) s=255;
  return (BYTE)s;
  // filt.tf = total de nos (folhas+internos)
  // folhas = numero de folhas
  // filt.tf-folhas = nos internos
  // nos internos + 1 = folhas
  // repeticoescs = Repeticoes com ou sem conflito
  // pixelsrepcs = numero de exemplos repetidos com ou sem conflito
  // pixelsolit = numero de exemplos nao repetidos.
  // pixelsrepcs+pixelsolit = Numero de pixels.
}

void CUTTREE::construcao(int l, int r, int pf)
{ if (r-l+1<=np) { // Base da recursao
    filt[pf].v=valor(l,r);
    filt[pf].e=FIM;
    return;
  }

  unsigned tiee=iee;
  int m;
  do {
    m=mediana(l,r);
    if (m!=-1) break;
    iee++; if (iee>=ee.size()) iee=0;
  } while (tiee!=iee);

  if (m==-1) { // Base da recursao
    filt[pf].v=valor(l,r);
    filt[pf].e=FIM;
    iee=tiee;
    return;
  } else {
    filt[pf].v=valindee(m);
    filt[pf].e=iee;
    iee=tiee;
  }

  iee++; if (iee>=ee.size()) iee=0;
  int i=insereFilt();
  construcao(l,m-1,i);
  i=insereFilt();
  filt[pf].r=i;
  construcao(m,r,i);
  if (iee==0) iee=ee.size()-1; else iee--; 
}

void CUTTREE::train(Mat_<GRY> par_features, Mat_<GRY> par_saidas, vector<int> par_ee, char par_modoconf, int par_np)
{ features=par_features; saidas=par_saidas; ee=par_ee; modoconf=par_modoconf; np=par_np; iee=0;

  assert(features.rows==saidas.rows);
  assert(saidas.cols==1);
  assert(int(par_ee.size())==features.cols);
  assert(int(par_ee.size())<=FIM-1);

  folhas=0; repeticoescs=0; pixelsrepcs=0; pixelsolit=0; 

  filt.reserve(2*teto(features.rows,np));
  ind.resize(features.rows);
  for (unsigned i=0; i<ind.size(); i++) ind[i]=i;
  int pf=insereFilt();
  construcao(0,ind.size()-1,pf);
}

BYTE CUTTREE::predict(Mat_<GRY> qu)
{ assert(qu.cols==int(ee.size()));
  assert(qu.rows==1);

//   static int contador=0;
//   contador++;
//   if (contador==100000) { putc('.',stderr); contador=0; }

  int i=0; int ruid;
  while (filt[i].e!=FIM) {
    ruid=qu( ee[filt[i].e] );   
    if (ruid<filt[i].v) i++;
    else i=filt[i].r;
  }
  return filt[i].v;
}

void CUTTREE::train(Mat_<FLT> par_features, Mat_<FLT> par_saidas, vector<int> par_ee, char par_modoconf, int par_np) {
  minMaxLoc(par_features, &minx, &maxx); alphax=255/(maxx-minx); betax=(-255*minx)/(maxx-minx);
  minMaxLoc(par_saidas,   &miny, &maxy); alphay=255/(maxy-miny); betay=(-255*miny)/(maxy-miny);
  par_features.convertTo(features, CV_8UC1, alphax, betax); 
  par_saidas.convertTo(saidas, CV_8UC1, alphay, betay); 
  train(features,saidas,par_ee,par_modoconf,par_np);
}

FLT CUTTREE::predict(Mat_<FLT> par_qu) {
  Mat_<GRY> qu;
  par_qu.convertTo(qu, CV_8UC1, alphax, betax); 
  BYTE b=predict(qu);
  return b*(maxy-miny)/255.0+miny;
}

//<<<<<<<<<<<<<<< Gaussian noise: soma ruido gaussiano
Mat_<FLT> GaussianNoise(Mat_<FLT> a, double desvio, int semente)
{ mysrand(semente);
  Mat_<FLT> b; b=a.clone();
  for (int l=0; l<b.rows; l++)
    for (int c=0; c<b.cols; c++) 
      b(l,c)=b(l,c)+desvio*mygauss();
  return b;
}

Mat_<GRY> GaussianNoise(Mat_<GRY> a, double desvio, int semente)
{ mysrand(semente);
  Mat_<GRY> b; b=a.clone();
  for (int l=0; l<b.rows; l++)
    for (int c=0; c<b.cols; c++) 
      b(l,c)=saturate_cast<GRY>(b(l,c)+desvio*mygauss());
  return b;
}

Mat_<COR> GaussianNoise(Mat_<COR> a, double desvio, int semente)
{ mysrand(semente);
  Mat_<COR> b; b=a.clone();
  for (int l=0; l<b.rows; l++)
    for (int c=0; c<b.cols; c++) {
      b(l,c)[0]=saturate_cast<GRY>(b(l,c)[0]+desvio*mygauss());
      b(l,c)[1]=saturate_cast<GRY>(b(l,c)[1]+desvio*mygauss());
      b(l,c)[2]=saturate_cast<GRY>(b(l,c)[2]+desvio*mygauss());
    }
  return b;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Mat_<GRY> rotacao(Mat_<GRY> ent, double deg) {
  Mat_<double> m=getRotationMatrix2D(Point2f(ent.cols/2,ent.rows/2), deg, 1);
  Mat_<GRY> sai;
  warpAffine(ent, sai, m, ent.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar(255));
  return sai;
}

EXPORTA Mat_<GRY> GaussianBlur(Mat_<GRY> ent, double sigma) {
  Mat_<GRY> sai;
  GaussianBlur(ent, sai, Size(0,0), sigma, sigma);
  return sai;
}

//<<<<<<<<<<<<<<<<< MNIST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Mat_<GRY> MNIST::bbox(Mat_<GRY> a) {
  int esq=a.cols, dir=0, cima=a.rows, baixo=0; // primeiro pixel diferente de 255.
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++) {
      if (a(l,c)!=255) {
        if (c<esq) esq=c;
        if (dir<c) dir=c;
        if (l<cima) cima=l;
        if (baixo<l) baixo=l;
      }
    }
  Mat_<GRY> roi(a, Rect(esq,cima,dir-esq+1,baixo-cima+1));
  Mat_<GRY> d; resize(roi,d,Size(nlado,nlado),0, 0, INTER_AREA);
  return d;
}

Mat_<FLT> MNIST::bbox(Mat_<FLT> a) {
  int esq=a.cols, dir=0, cima=a.rows, baixo=0; // primeiro pixel menor que 0.5.
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++) {
      if (a(l,c)<=0.5) {
        if (c<esq) esq=c;
        if (dir<c) dir=c;
        if (l<cima) cima=l;
        if (baixo<l) baixo=l;
      }
    }
  Mat_<FLT> roi(a, Rect(esq,cima,dir-esq+1,baixo-cima+1));
  Mat_<FLT> d; resize(roi,d,Size(nlado,nlado),0, 0, INTER_AREA);
  return d;
}

void MNIST::leX(string nomeArq, int n, vector< Mat_<GRY> >& X, Mat_<FLT>& x) {
  X.resize(n);
  for (unsigned i=0; i<X.size(); i++) X[i].create(nlado,nlado);

  FILE* arq=fopen(nomeArq.c_str(),"rb");
  BYTE b;
  Mat_<GRY> t(28,28),d;
  fseek(arq,16,SEEK_SET);
  for (unsigned i=0; i<X.size(); i++) {
    for (unsigned l=0; l<28; l++)
      for (unsigned c=0; c<28; c++) {
        fread(&b,1,1,arq);
        t(l,c)=255-b;
      }
    if (ajustaBbox) {
      d=bbox(t);
    } else{
      if (nlado!=28) resize(t,d,Size(nlado,nlado),0, 0, INTER_AREA);
      else t.copyTo(d);
    }
    if (!inverte) d=255-d;
    X[i]=d.clone();
  }
  fclose(arq);

  x.create(X.size(),X[0].total());
  for (int i=0; i<x.rows; i++) 
    for (int j=0; j<x.cols; j++)
      x(i,j)=X[i](j)/255.0;
}

void MNIST::leY(string nomeArq, int n, vector<int>& Y, Mat_<FLT>& y) {
  Y.resize(n);
  y.create(n,1);
  FILE* arq=fopen(nomeArq.c_str(),"rb");
  BYTE b;
  fseek(arq,8,SEEK_SET);
  for (unsigned i=0; i<y.total(); i++) {
    fread(&b,1,1,arq);
    Y[i]=b;
    y(i)=b;
  }
  fclose(arq);
}

void MNIST::le(string caminho, int _na, int _nq) {
  na=_na; nq=_nq;
  if (na>60000) xerro1("na>60000");
  if (nq>10000) xerro1("nq>10000");

  if (na>0) {
    leX(caminho+"/train-images.idx3-ubyte",na,AX,ax);
    leY(caminho+"/train-labels.idx1-ubyte",na,AY,ay);
  }
  if (nq>0) {
    leX(caminho+"/t10k-images.idx3-ubyte",nq,QX,qx);
    leY(caminho+"/t10k-labels.idx1-ubyte",nq,QY,qy);
    qp.create(nq,1);
  }
}

int MNIST::contaErros() {
  // conta numero de erros
  int erros=0;
  for (int l=0; l<qp.rows; l++)
    if (qp(l)!=qy(l)) erros++;
  return erros;
}

Mat_<GRY> MNIST::geraSaida(Mat_<GRY> q, int qy, int qp) {
  Mat_<GRY> d(28,38,192);
  putTxt(d,0,28,to_string(qy));
  putTxt(d,14,28,to_string(qp));
  int delta=(28-q.rows)/2;
  copia(q,d,delta,delta);
  return d;
}

Mat_<GRY> MNIST::geraSaidaErros(int maxErr) {
  // Gera imagem 23x38, colocando qy e qp a direita.
  int erros=contaErros();
  Mat_<GRY> e(28,40*min(erros,maxErr),192);
  for (int j=0, i=0; j<qp.rows; j++) {
    if (qp(j)!=qy(j)) {
      Mat_<GRY> t=geraSaida(QX[j],qy(j),qp(j));
      copia(t,e,0,40*i);
      i++;
      if (i>=min(erros,maxErr)) break;
    }
  }
  return e;
}

Mat_<GRY> MNIST::geraSaidaErros(int nl, int nc) {
  // Gera uma imagem com os primeiros nl*nc digitos classificados erradamente
  Mat_<GRY> e(28*nl,40*nc,192);
  int j=0;
  for (int l=0; l<nl; l++)
    for (int c=0; c<nc; c++) {
      //acha o proximo erro
      while (qp(j)==qy(j) && j<qp.rows) j++;
      if (j==qp.rows) goto saida;
      Mat_<GRY> t=geraSaida(QX[j],qy(j),qp(j));
      copia(t,e,28*l,40*c);
      j++;
    }
  saida: 
  return e;
}

//<<<<<<<<<<<<<<<<<<< MnistFlann <<<<<<<<<<<<<<<<<<<<<<<<<<<
void MnistFlann::train() {
  static flann::Index ind2(ax,flann::KDTreeIndexParams(4));
  ind=&ind2;
}

FLT MnistFlann::predictInterno(Mat_<FLT> query) {
  //flann::Index ind(ax,flann::KDTreeIndexParams(4));
  vector<int> indices(1);
  vector<float> dists(1);
  ind->knnSearch(query,indices,dists,1,flann::SearchParams(32));
  return ay(indices[0]);
}

FLT MnistFlann::predict(Mat_<FLT> query) {
  Mat_<FLT> t=bbox(query);
  //xprint(t.isContinuous());
  //t.reshape(1,1); xprint(t.size()); // Nao funciona por algum motivo
  //return predictInterno(t);
  Mat_<FLT> t2(1,t.total());
  for (unsigned i=0; i<t.total(); i++)
    t2(i)=t(i);
  return predictInterno(t2);
}

void MnistFlann::predict() {
  qp.create(nq,1);
  //#pragma omp parallel for
  for (int l=0; l<qp.rows; l++) {
    qp(l)=predictInterno(qx.row(l));
  }
}

void MnistFlann::save(string nomeArq) {
  ind->save(nomeArq);
}

void MnistFlann::load(string nomeArq) {
  static flann::Index ind2(ax,flann::SavedIndexParams(nomeArq));
  ind=&ind2;
}

//Cifar10
void leCifar10(const string& nomearq,
             vector< Mat_<COR> >& images, vector<BYTE>& rotulos) {
  int nl=32;
  int nc=32;
  int nbytes=3073; // nl*nc*3+1=32*32*3+1
  int nimages=10000;
  vector<BYTE> v(nbytes*nimages);

  FILE* arq=fopen(nomearq.c_str(),"rb");
  if (arq==NULL) xerro1("Erro: Abertura do arquivo "+nomearq);
  int nlidos=fread(v.data(),nbytes,nimages,arq);
  if (nlidos!=nimages) xerro1("Erro: Leitura do arquivo "+nomearq);
  fclose(arq);

  images.resize(nimages);
  rotulos.resize(nimages);
  for (unsigned i=0; i<nimages; i++) {
    rotulos[i]=v[nbytes*i];
    Mat_<COR>& m=images[i]; m.create(nl,nc);
    BYTE* pred=&(v[nbytes*i+1]);
    BYTE* pgre=pred+nl*nc;
    BYTE* pblu=pred+2*nl*nc;
    for (unsigned j=0; j<nl*nc; j++) {
      m(j)(2)=pred[j];
      m(j)(1)=pgre[j];
      m(j)(0)=pblu[j];
    }
  }
}

//<<<<<<<<<<<<<<<<<<<<<< descritores como sift <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
COR corAleat(int i)
{ COR cor;
  if      (i==0) cor=COR(0,0,255);
  else if (i==1) cor=COR(0,255,0);
  else if (i==2) cor=COR(255,0,0);
  else if (i==3) cor=COR(255,255,0);
  else if (i==4) cor=COR(255,0,255);
  else if (i==5) cor=COR(0,255,255);
  else {
    mysrand(i);
    Mat_<Vec3f> hsv(1,1);
    hsv(0,0)[0]=360*myuniform();
    hsv(0,0)[1]=2*myuniform()/3+0.5;
    hsv(0,0)[2]=2*myuniform()/3+0.5;
    Mat_<Vec3f> bgr;
    cvtColor(hsv,bgr,CV_HSV2BGR);
    Mat_<COR> m;
    bgr.convertTo(m, CV_8U, 255, 0);
    cor=m(0,0);
  }
  return cor;
}

Mat_<COR> matMyShow(Mat_<GRY> im1, Mat_<GRY> im2, 
  const vector<DMatch>& matches,
  const vector<KeyPoint>& k1,
  const vector<KeyPoint>& k2,
  char modo,
  double raioKey) {
  //modo=r/n/R/N r=rich n=normal minuscula=azul maiuscula=multicor

  Mat_<GRY> temp=grudaH(im1,im2);
  Mat_<COR> sai; converte(temp,sai);
  for (int i=0; i<int(matches.size()); i++) {
    COR vermelho(0,0,255);
    COR azul(255,0,0);
    COR cor=azul;
    if (modo=='R' || modo=='N') cor=corAleat(i);

    int l1=matches[i].queryIdx;
    if (!(0<=l1 && l1<(int)k1.size())) erro("Erro: Indice l1 fora de k1");
    KeyPoint p1=k1[l1];
    int l2=matches[i].trainIdx;
    if (!(0<=l2 && l2<(int)k2.size())) erro("Erro: Indice l2 fora de k2");
    KeyPoint p2=k2[l2];
    reta(sai,arredonda(p1.pt.y),arredonda(p1.pt.x),
             arredonda(p2.pt.y),im1.cols+arredonda(p2.pt.x),cor,1);

    if (modo=='r' || modo=='R') {
      relogioCircular(sai,arredonda(p1.pt.y),arredonda(p1.pt.x),arredonda(raioKey*p1.size),-p1.angle-90,vermelho,1);
      relogioCircular(sai,arredonda(p2.pt.y),im1.cols+arredonda(p2.pt.x),arredonda(raioKey*p2.size),-p2.angle-90,vermelho,1);
    }
  }
  return sai;
}

Mat_<COR> keyMyShow(Mat_<GRY> a, const vector<KeyPoint>& k,
  char modo,
  double raioKey) {
  //modo=r/n/R/N r=rich n=normal minuscula=azul maiuscula=multicor
  Mat_<COR> b; converte(a,b);
  for (unsigned i=0; i<k.size(); i++) {
    COR cor(0,0,255);
    if (modo=='R' || modo=='N') cor=corAleat(i);
    KeyPoint p=k[i];
    if (modo=='r' || modo=='R') 
      relogioCircular(b,arredonda(p.pt.y),arredonda(p.pt.x),arredonda(raioKey*p.size),-p.angle-90,cor,1); 
    else
      ponto(b,arredonda(p.pt.y),arredonda(p.pt.x),cor);
  }
  // Nota: O angulo em OpenCV comeca em 3 horas e caminha no sentido anti-horario.
  //       O angulo em Cekeikon comeca em 12 horas e caminha no sentido anti-horario.
  return b;
}

} // namespace cek

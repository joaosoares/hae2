#include "cekeikon.h"

namespace cek {

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void convArg(int& i, string arg)
{ if (sscanf(arg.c_str(),"%d",&i)!=1) erro("Erro: Leitura ",arg);
}

void convArg(double& i, string arg)
{ if (sscanf(arg.c_str(),"%lf",&i)!=1) erro("Erro: Leitura ",arg);
}

void convArg(float& i, string arg)
{ if (sscanf(arg.c_str(),"%f",&i)!=1) erro("Erro: Leitura ",arg);
}

void convArg(bool& b, string arg) {
  if (arg.length()==0) erro("Erro: Leitura bool");
  char ch=toupper(arg[0]);
  if (ch=='V' || ch=='T' || ch=='1') b=true;
  else if (ch=='F' || ch=='0') b=false;
  else erro("Erro: Leitura ",arg);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int fGetBit(FILE* arq)
// Devolve 0 ou 1. Quando chegar a EOF, devolve EOF == -1
{ static int i=8; static int x=0;
  if (i==8) {
    i=0;
    x=fgetc(arq);
    if (x==EOF) return EOF;
  }
  i++;
  if ((x & (0x80 >> (i-1)))==0) return 0;
  else return 1;
}

void fPutBit(int d, FILE* arq)
// Grava 0 (d==0) ou 1 (d!=0)
{ static int i=0; static unsigned char x=0;
  if (d!=0) d=1;
  x=(x<<1)+d;
  i++;
  if (i==8) {
    fputc(x,arq);
    x=0; i=0;
  }
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
namespace MostraC { // nova versao

Mat_<COR> ent,sai;
string nome;

// estatico para todas as janelas
int NumJanela=0;

// estatico para uma janela
double zoom;
int xc, yc;

void calculaRoi() {
// sai e' roi de ent
  if (zoom<1) zoom=1;
  if (zoom>ent.cols) zoom=ent.cols;
  if (zoom>ent.rows) zoom=ent.rows;
  int dx=arredonda(ent.cols/zoom); // dx>=1
  int dy=arredonda(ent.rows/zoom); // dy>=1
  
  int dxl=chao(dx-1,2); //quanto que pode andar para esquerda a partir de xc
  int dxr=teto(dx-1,2); //quanto que pode andar para direita a partir de xc
  int dyl=chao(dy-1,2);
  int dyr=teto(dy-1,2);
  
  if (xc<dxl) xc=dxl;
  if (xc>ent.cols-1-dxr) xc=ent.cols-1-dxr;
  if (yc<dyl) yc=dyl;
  if (yc>ent.rows-1-dyr) yc=ent.rows-1-dyr;
  
  int xi=xc-dxl; 
  assert(xi>=0);
  assert(xi+dx<=ent.cols); 
  
  int yi=yc-dyl; 
  assert(yi>=0);
  assert(yi+dy<=ent.rows); 

  sai=ent(Rect(xi,yi,dx,dy));
}

}

void mostra(Mat_<COR> entp, string nomep)
{ using namespace MostraC;
  if (entp.dims!=2 || entp.rows<=0 || entp.cols<=0) xerro1("Erro mostra: dimensao invalida");
  ent=entp;
  nome=nomep;
  if (nome=="") {
    ostringstream ost;
    ost << "MatCOR_" << NumJanela++;
    nome=ost.str();
  }
  zoom=1; xc=ent.cols/2; yc=ent.rows/2;

  namedWindow(nome,CV_WINDOW_NORMAL);
  calculaRoi(); imshow(nome,sai);

  char ch=0;
  while (ch!=27 && ch!='q') {
    ch=tolower(waitKey(0));
    int andax=arredonda(ent.cols/(2.0*zoom)); if (andax<1) andax=1;
    int anday=arredonda(ent.rows/(2.0*zoom)); if (anday<1) anday=1;
    if (ch==27) { break;
    } else if (ch=='+' || ch=='=') { // zoom in
      zoom*=pow(2.0,1.0/4.0);  
    } else if (ch=='-' || ch=='_') { // zoom out
      zoom/=pow(2.0,1.0/4.0);    
    } else if (ch=='0') { // reset zoom
      zoom=1.0;
    } else if (ch=='f') { // left
      xc=xc-andax;
    } else if (ch=='g') { // right
      xc=xc+andax;
    } else if (ch=='t') { // up
      yc=yc-anday;
    } else if (ch=='v') { // down
      yc=yc+anday;
    } else if (ch=='s') { // left
      xc--;
    } else if (ch=='d') { // right
      xc++;
    } else if (ch=='e') { // up
      yc--;
    } else if (ch=='x') { // down
      yc++;
    } else if (ch=='h') { // hardcopy
      imp(sai,nome+"_.png");
    } else if (ch!=27 && ch!='q') {
      printf("+-0=Zoom ESDX=SlowMv TFGV=FastMv H=hdcp ESC=ClsQuit Q=Quit\n");
    }
    calculaRoi(); imshow(nome,sai);
  }
  if (ch==27) destroyWindow(nome);
}

void mostra(Mat_<CORF> entp, string nomep, double alpha)
{ Mat_<COR> ent; 
  if (alpha!=1.0) { 
    Mat_<CORF> f=alpha*entp;
    converte(f,ent); 
  } else {
    converte(entp,ent); 
  }
  mostra(ent,nomep);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace MostraG { // precisa consertar seguindo MostraC

Mat_<GRY> ent,bc,sai;
string nome;

// trackbars
int _brightness;
int _contrast;

// estatico para todas as janelas
int NumJanela=0;

// estatico para uma janela
int zoom; // 1 ou maior
int multWin;
int xc, yc;

// calculados a partir das variaveis acima
int dx,dy,dxl,dyl,dxr,dyr,xi,yi;

void calculaRoi()
{ dx=ent.cols/zoom; 
  dy=ent.rows/zoom;
  dxl=chao(dx,2); 
  dyl=chao(dy,2);
  dxr=teto(dx,2); 
  dyr=teto(dy,2);
  xi=xc-dxl;
  yi=yc-dyl;
  if (xi<0) xi=0;
  if (yi<0) yi=0;
  if (xi+dx>ent.cols) xi=ent.cols-dx;
  if (yi+dy>ent.rows) yi=ent.rows-dy;
  xc=xi+dxl;
  yc=yi+dyl;
  sai=bc(Rect(xi,yi,dx,dy));
}

// brightness/contrast callback function 
void update_brightcont(int arg, void* data)
{ double brightness = (_brightness - 50.0)/50.0;
  double contrast = (_contrast - 50)/50.0;
  double delta,a,b;

  if (contrast>0.0) {
    delta = 0.498039215686*contrast;
    a = 1.0 / (1.0 - 2.0*delta);
    b = a * (brightness - delta);
  } else {
    delta = -0.501960784313*contrast;
    a = (1.003921568627 - 2.0*delta) / 1.0;
    b = a*brightness + delta;
  }
  bc=a*ent+255*b; // Isto cria copia de ent em bc.
  imshow(nome,sai);
}

void on_mouse(int event, int x, int y, int flags, void* param)
{ int l=yi+y;
  int c=xi+x;
  switch (event) {
    case CV_EVENT_MOUSEMOVE:
      printf("\rl=%-4d c=%-4d ori=%-3d sai=%-3d\r",l,c,ent(l,c),sai(y,x));
      break;
  }
}

}

void mostra(Mat_<GRY> entp, string nomep)
{ using namespace MostraG;
  if (entp.dims!=2 || entp.rows<=0 || entp.cols<=0) erro("Erro mostra: dimensao invalida");
  ent=entp;
  nome=nomep;
  if (nome=="") {
    ostringstream ost;
    ost << "MatGRY_" << NumJanela++;
    nome=ost.str();
  }
  zoom=1; xc=ent.cols/2; yc=ent.rows/2; 
  _brightness=50; _contrast=50;
  bc=ent.clone(); calculaRoi(); // sai e' roi de bc.

  double multRows=(2.0/3.0)*screenRows/ent.rows;
  double multCols=(2.0/3.0)*screenCols/ent.cols;
  double mult=min(multRows,multCols);
  int n=arredonda(log2(mult));
  multWin=pow2(n);

  namedWindow(nome,CV_WINDOW_NORMAL);
  cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
  createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
  createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
  cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
  update_brightcont(0,0);  // calcula bc a partir de ent
  setMouseCallback(nome, on_mouse);

  char ch=0;
  while (ch!=27 && ch!='q') {
    ch=tolower(waitKey(0));
    if (ch==27) { break;
    } else if (ch=='+' || ch=='=') { // zoom in
      zoom++;  
    } else if (ch=='-' || ch=='_') { // zoom out
      zoom--;  
      if (zoom<1) zoom=1;
    } else if (ch=='0') { // reset zoom
      zoom=1;
    } else if (ch=='m') { // adjust multWin
      multWin=1;
      destroyWindow(nome);
      namedWindow(nome,CV_WINDOW_NORMAL);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
      createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      update_brightcont(0,0);  // calcula bc a partir de ent
      setMouseCallback(nome, on_mouse);
    } else if (ch==',' || ch=='<') { // decrease multWin
      multWin/=2;
      destroyWindow(nome);
      namedWindow(nome,CV_WINDOW_NORMAL);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
      createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      update_brightcont(0,0);  // calcula bc a partir de ent
      setMouseCallback(nome, on_mouse);
    } else if (ch=='.' || ch=='>') { // increase multWin
      multWin*=2;
      destroyWindow(nome);
      namedWindow(nome,CV_WINDOW_NORMAL);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
      createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      update_brightcont(0,0);  // calcula bc a partir de ent
      setMouseCallback(nome, on_mouse);
    } else if (ch==0x00250000) { // left
      xc=xc-dxl;
    } else if (ch==0x00270000) { // right
      xc=xc+dxr;
    } else if (ch==0x00260000) { // up
      yc=yc-dyl;
    } else if (ch==0x00280000) { // down
      yc=yc+dyr;
    } else if (ch==0x00240000) { // home
      xc=dxl; yc=dyl;
    } else if (ch==0x00230000) { // end
      xc=ent.cols-dxr; yc=ent.rows-dyr;
    } else if (ch=='s') { // left
      xc--;
    } else if (ch=='d') { // right
      xc++;
    } else if (ch=='e') { // up
      yc--;
    } else if (ch=='x') { // down
      yc++;
    } else if (ch=='h') { // hardcopy
      imp(sai,"hdcp_"+nome+"_.png");
    } else if (ch!=27 && ch!='q') {
      printf("<>M=WinSz +-0=Zoom ESDX=SlowMv arrows=FastMv Home/End H=hdcp ESC=ClsQuit Q=Quit\n");
    }
    calculaRoi(); imshow(nome,sai);
  }
  // Limpa console
  printf("\r%s\r",string(70,' ').c_str());
  // Desliga callback functions
  setMouseCallback(nome, 0);
  createTrackbar("brilho", nome, &_brightness, 100, 0);
  createTrackbar("contraste", nome, &_contrast, 100, 0);
  // Destroi janela se ESC
  if (ch==27) destroyWindow(nome);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace MostraF {// precisa consertar seguindo MostraC

Mat_<FLT> ent;
Mat_<GRY> bc,sai;
string nome;
bool normaliz;

// trackbars
int _brightness;
int _contrast;

// estatico para todas as janelas
int NumJanela=0;

// estatico para uma janela
int zoom;
int multWin;
int xc, yc;

// calculados a partir das variaveis acima
int dx,dy,dxl,dyl,dxr,dyr,xi,yi;

void calculaRoi()
{ dx=ent.cols/zoom; 
  dy=ent.rows/zoom;
  dxl=chao(dx,2); 
  dyl=chao(dy,2);
  dxr=teto(dx,2); 
  dyr=teto(dy,2);
  xi=xc-dxl;
  yi=yc-dyl;
  if (xi<0) xi=0;
  if (yi<0) yi=0;
  if (xi+dx>ent.cols) xi=ent.cols-dx;
  if (yi+dy>ent.rows) yi=ent.rows-dy;
  xc=xi+dxl;
  yc=yi+dyl;
  sai=bc(Rect(xi,yi,dx,dy));
}

// brightness/contrast callback function 
void update_brightcont(int arg, void* data)
{ double brightness = (_brightness - 50.0)/50.0;
  double contrast = (_contrast - 50)/50.0;
  double delta,a,b;

  if (contrast>0.0) {
    delta = 0.498039215686*contrast;
    a = 1.0 / (1.0 - 2.0*delta);
    b = a * (brightness - delta);
  } else {
    delta = -0.501960784313*contrast;
    a = (1.003921568627 - 2.0*delta) / 1.0;
    b = a*brightness + delta;
  }
  if (normaliz) bc=255*(a*normaliza(ent)+b); // Isto cria copia de ent em bc.
  else bc=255*(a*ent+b); // Isto cria copia de ent em bc.
  imshow(nome,sai);
}

void on_mouse(int event, int x, int y, int flags, void* param)
{ int l=yi+y;
  int c=xi+x;
  switch (event) {
    case CV_EVENT_MOUSEMOVE:
      printf("\rl=%-4d c=%-4d ori=% 6.4f sai=%-3d              \r",l,c,ent(l,c),sai(y,x));
      break;
  }
}

}

void mostra(Mat_<FLT> entp, string nomep, double alpha)
{ using namespace MostraF;
  if (entp.dims!=2 || entp.rows<=0 || entp.cols<=0) erro("Erro mostra: dimensao invalida");
  ent=entp.clone();
  if (alpha!=1.0) ent=alpha*ent;
  nome=nomep;
  normaliz=false;
  if (nome=="") {
    ostringstream ost;
    ost << "MatFLT_" << NumJanela++;
    nome=ost.str();
  }
  zoom=1; xc=ent.cols/2; yc=ent.rows/2; 
  _brightness=50; _contrast=50;
  converte(ent,bc); 
  calculaRoi(); // sai e' roi de bc.

  double multRows=(2.0/3.0)*screenRows/ent.rows;
  double multCols=(2.0/3.0)*screenCols/ent.cols;
  double mult=min(multRows,multCols);
  int n=arredonda(log2(mult));
  multWin=pow2(n);

  namedWindow(nome,CV_WINDOW_NORMAL);
  cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
  createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
  createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
  cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
  update_brightcont(0,0);  // calcula bc a partir de ent
  setMouseCallback(nome, on_mouse);

  char ch=0;
  while (ch!=27 && ch!='q') {
    ch=tolower(waitKey(0));
    if (ch==27) { break;
    } else if (ch=='+' || ch=='=') { // zoom in
      zoom++;  
    } else if (ch=='-' || ch=='_') { // zoom out
      zoom--;  
      if (zoom<1) zoom=1;
    } else if (ch=='0') { // reset zoom
      zoom=1;
    } else if (ch=='m') { // adjust multWin
      multWin=1;
      destroyWindow(nome);
      namedWindow(nome,CV_WINDOW_NORMAL);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
      createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      update_brightcont(0,0);  // calcula bc a partir de ent
      setMouseCallback(nome, on_mouse);
    } else if (ch==',' || ch=='<') { // decrease multWin
      multWin/=2;
      destroyWindow(nome);
      namedWindow(nome,CV_WINDOW_NORMAL);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
      createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      update_brightcont(0,0);  // calcula bc a partir de ent
      setMouseCallback(nome, on_mouse);
    } else if (ch=='.' || ch=='>') { // increase multWin
      multWin*=2;
      destroyWindow(nome);
      namedWindow(nome,CV_WINDOW_NORMAL);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
      createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      update_brightcont(0,0);  // calcula bc a partir de ent
      setMouseCallback(nome, on_mouse);
    } else if (ch==0x00250000) { // left
      xc=xc-dxl;
    } else if (ch==0x00270000) { // right
      xc=xc+dxr;
    } else if (ch==0x00260000) { // up
      yc=yc-dyl;
    } else if (ch==0x00280000) { // down
      yc=yc+dyr;
    } else if (ch==0x00240000) { // home
      xc=dxl; yc=dyl;
    } else if (ch==0x00230000) { // end
      xc=ent.cols-dxr; yc=ent.rows-dyr;
    } else if (ch=='s') { // left
      xc--;
    } else if (ch=='d') { // right
      xc++;
    } else if (ch=='e') { // up
      yc--;
    } else if (ch=='x') { // down
      yc++;
    } else if (ch=='h') { // hardcopy
      imp(sai,"hdcp_"+nome+"_.png");
    } else if (ch=='n') { // normaliza
      normaliz=!normaliz;
      update_brightcont(0,0);
    } else if (ch!=27 && ch!='q') {
      printf("<>M=WinSz +-0=Zoom ESDX=SlowMv arrows=FastMv Home/End H=hdcp ESC=ClsQuit N=norm Q=Quit\n");
    }
    calculaRoi(); imshow(nome,sai);
  }
  // Limpa console
  printf("\r%s\r",string(70,' ').c_str());
  // Desliga callback functions
  setMouseCallback(nome, 0);
  createTrackbar("brilho", nome, &_brightness, 100, 0);
  createTrackbar("contraste", nome, &_contrast, 100, 0);
  // Destroi janela se ESC
  if (ch==27) destroyWindow(nome);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace MostraX {// precisa consertar seguindo MostraC

Mat_<CPX> ent,pol;
Mat_<FLT> polabs,polarg;
Mat_<COR> bc,sai;
string nome;

// trackbars
int _brightness;
int _contrast;

// estatico para todas as janelas
int NumJanela=0;

// estatico para uma janela
int zoom;
int multWin;
int xc, yc;

// calculados a partir das variaveis acima
int dx,dy,dxl,dyl,dxr,dyr,xi,yi;

void calculaRoi()
{ dx=ent.cols/zoom; 
  dy=ent.rows/zoom;
  dxl=chao(dx,2); 
  dyl=chao(dy,2);
  dxr=teto(dx,2); 
  dyr=teto(dy,2);
  xi=xc-dxl;
  yi=yc-dyl;
  if (xi<0) xi=0;
  if (yi<0) yi=0;
  if (xi+dx>ent.cols) xi=ent.cols-dx;
  if (yi+dy>ent.rows) yi=ent.rows-dy;
  xc=xi+dxl;
  yc=yi+dyl;
  sai=bc(Rect(xi,yi,dx,dy));
}

// brightness/contrast callback function 
void update_brightcont(int arg, void* data)
{ double brightness = (_brightness - 50.0)/50.0;
  double contrast = (_contrast - 50)/50.0;
  double delta,a,b;

  if (contrast>0.0) {
    delta = 0.498039215686*contrast;
    a = 1.0 / (1.0 - 2.0*delta);
    b = a * (brightness - delta);
  } else {
    delta = -0.501960784313*contrast;
    a = (1.003921568627 - 2.0*delta) / 1.0;
    b = a*brightness + delta;
  }

  merge(a*polabs+b,polarg,pol);
  convertePOL2COR(pol,bc); 
  imshow(nome,sai);
}

void on_mouse(int event, int x, int y, int flags, void* param)
{ int l=yi+y;
  int c=xi+x;
  switch (event) {
    case CV_EVENT_MOUSEMOVE:
      printf("\rl=%-4d c=%-4d retang=(% 6.4f, % 6.4f) polar=(%6.4f, %6.1f)\r",l,c,ent(l,c).real(),ent(l,c).imag(),abs(ent(l,c)),rad2deg(arg(ent(l,c))));
      break;
  }
}

}

void mostra(Mat_<CPX> entp, string nomep, char modo)
{ using namespace MostraX;
  if (entp.dims!=2 || entp.rows<=0 || entp.cols<=0) erro("Erro mostra: dimensao invalida");
  ent=entp;
  nome=nomep;
  if (nome=="") {
    ostringstream ost;
    ost << "MatCPX_" << NumJanela++;
    nome=ost.str();
  }
  zoom=1; xc=ent.cols/2; yc=ent.rows/2;
  _brightness=50; _contrast=50;
  pol=ret2pol(ent); split(pol,polabs,polarg);
  bc.create(ent.size()); calculaRoi(); // sai e' roi de bc.

  double multRows=(2.0/3.0)*screenRows/ent.rows;
  double multCols=(2.0/3.0)*screenCols/ent.cols;
  double mult=min(multRows,multCols);
  int n=arredonda(log2(mult));
  multWin=pow2(n);

  namedWindow(nome,CV_WINDOW_NORMAL);
  cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
  createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
  createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
  cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
  update_brightcont(0,0);  // calcula bc a partir de ent
  setMouseCallback(nome, on_mouse);

  char ch=0;
  while (ch!=27 && ch!='q') {
    ch=tolower(waitKey(0));
    if (ch==27) { break;
    } else if (ch=='+' || ch=='=') { // zoom in
      zoom++;  
    } else if (ch=='-' || ch=='_') { // zoom out
      zoom--;  
      if (zoom<1) zoom=1;
    } else if (ch=='0') { // reset zoom
      zoom=1;
    } else if (ch=='m') { // adjust multWin
      multWin=1;
      destroyWindow(nome);
      namedWindow(nome,CV_WINDOW_NORMAL);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
      createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      update_brightcont(0,0);  // calcula bc a partir de ent
      setMouseCallback(nome, on_mouse);
    } else if (ch==',' || ch=='<') { // decrease multWin
      multWin/=2;
      destroyWindow(nome);
      namedWindow(nome,CV_WINDOW_NORMAL);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
      createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      update_brightcont(0,0);  // calcula bc a partir de ent
      setMouseCallback(nome, on_mouse);
    } else if (ch=='.' || ch=='>') { // increase multWin
      multWin*=2;
      destroyWindow(nome);
      namedWindow(nome,CV_WINDOW_NORMAL);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      createTrackbar("brilho", nome, &_brightness, 100, update_brightcont);
      createTrackbar("contraste", nome, &_contrast, 100, update_brightcont);
      cvResizeWindow(nome.c_str(),ent.cols*multWin,ent.rows*multWin);
      update_brightcont(0,0);  // calcula bc a partir de ent
      setMouseCallback(nome, on_mouse);
    } else if (ch==0x00250000) { // left
      xc=xc-dxl;
    } else if (ch==0x00270000) { // right
      xc=xc+dxr;
    } else if (ch==0x00260000) { // up
      yc=yc-dyl;
    } else if (ch==0x00280000) { // down
      yc=yc+dyr;
    } else if (ch==0x00240000) { // home
      xc=dxl; yc=dyl;
    } else if (ch==0x00230000) { // end
      xc=ent.cols-dxr; yc=ent.rows-dyr;
    } else if (ch=='s') { // left
      xc--;
    } else if (ch=='d') { // right
      xc++;
    } else if (ch=='e') { // up
      yc--;
    } else if (ch=='x') { // down
      yc++;
    } else if (ch=='h') { // hardcopy
      imp(sai,"hdcp_"+nome+"_.png");
    } else if (ch!=27 && ch!='q') {
      printf("<>M=WinSz +-0=Zoom ESDX=SlowMv arrows=FastMv Home/End H=hdcp ESC=ClsQuit Q=Quit\n");
    }
    calculaRoi(); imshow(nome,sai);
  }
  // Limpa console
  printf("\r%s\r",string(70,' ').c_str());
  // Desliga callback functions
  setMouseCallback(nome, 0);
  createTrackbar("brilho", nome, &_brightness, 100, 0);
  createTrackbar("contraste", nome, &_contrast, 100, 0);
  // Destroi janela se ESC
  if (ch==27) destroyWindow(nome);
}

void mostra(Mat_<SHT> entp, string nomep)
{ Mat_<GRY> ent; converte(entp,ent); mostra(ent); }

void mostra(Mat_<DBL> entp, string nomep)
{ Mat_<FLT> ent; converte(entp,ent); mostra(ent); }

void mostra(Mat ap, string nomep)
{ if (ap.type()==CV_8UC1) { //gray
    Mat_<GRY> a=ap; mostra(a,nomep);
  } else if (ap.type()==CV_8UC3) { //color
    Mat_<COR> a=ap; mostra(a,nomep);
  } else if (ap.type()==CV_32FC3) { //CORF
    Mat_<CORF> a=ap; mostra(a,nomep);
  } else if (ap.type()==CV_32FC1) { //float
    Mat_<FLT> a=ap; mostra(a,nomep);
  } else if (ap.type()==CV_32FC2) { //CPX
    Mat_<CPX> a=ap; mostra(a,nomep);
  } else erro("Erro mostra: tipo desconhecido");
}

//<<<<<<<<<<<<<<<<<<<<< funcoes io gerais <<<<<<<<<<<<<<<<<
void sufixoImg(string nome, string& raiz, string& suf, int& quali)
// Ex: iMg.jPg20
// retorna raiz=iMg.jPg
//         suf=jpg
//         quali=20
// Se nao ha quali, retorna -1.
// supoe-se que suf seja 3 letras
{ quali=-1; // quali default
  raiz=nome;

  // Arquivo sem extensao
  int ponto=(int)nome.find_last_of('.');
  if (ponto==-1) { suf=""; return; }

  suf=minuscula(nome.substr(ponto+1));
  // Arquivo com suf e qualidade
  if (suf.length()>3) {
    string qua=suf.substr(3);
    if (sscanf(qua.c_str(),"%d",&quali)!=1) erro("Erro suf do arquivo: numero apos suf");
    suf=suf.substr(0,3);
    raiz=nome.substr(0,ponto+4);
  }
}

int tipoImg(string nome)
// Le cabecalho do arquivo para descobrir o tipo de imagem
// return 1: TGA Gray 8 bit uncompressed sem palette
// return 2: TGA 8 bit uncompressed com palette
// return 3: TGA COR 24 bits uncompressed sem palette
// removido - return 4: BMP binario nao-compactado - removido
// return 5: Arquivo TXT
// return 11: IMGSHT*
// return 13: IMGFLT*
// return 14: I3DFLT*
// return 15: IMGCPX*
// return 16: I3DSHT*
// return 17: IMGDBL*
// return 18: I3DCPX*
// return 21: JPEG/JFIF
// return 51: AVI 8 bits uncompressed com palette
// return 52: AVI 24 bits uncompressed sem palette
// 61: PBM P1 text
// 62: PGM P2 text
// 63: PPM P3 text
// 64: PBM P4 bin
// 65: PGM P5 bin
// 66: PPM P6 bin
{ FILE* arq=fopen(nome.c_str(),"rb");
  if (arq==NULL) erro("Erro tipoImg - Abertura ",nome);
  BYTE v[192];
  fread(v,1,192,arq);
  fclose(arq);

  HEADER::HeaderTga* h = (HEADER::HeaderTga*)v;

  if (h->c1==0x00030000 && h->c2==0x00000000 &&
      h->c3==0x00000000 && h->c4==0x08)
    return 1; // TGA Gray 8 bit uncompressed sem palette

  if (h->c1==0x00010100 && v[4]==0x00 && v[7]==0x18 &&
      h->c3==0x00000000 && h->c4==0x08)
    return 2; // TGA 8 bit uncompressed com palette

  if (h->c1==0x00020000 && h->c2==0x00000000 &&
      h->c3==0x00000000 && h->c4==0x18)
    return 3; // TGA COR 24 bits uncompressed sem palette

  /*
  WORD* ImageFileType = (WORD*)v;
  //HEADER::WIN3XHEAD* head = (HEADER::WIN3XHEAD*)(&v[2]);
  HEADER::WIN3XINFOHEAD* infohead = (HEADER::WIN3XINFOHEAD*)(&v[14]);
  bool correto=true;
  if (*ImageFileType!=0x4d42) correto=false;
  if (infohead->BitsPerPixel!=1) correto=false;
  if (infohead->CompressionMethod!=0) correto=false;
  if (infohead->NumColorsUsed!=2 && infohead->NumColorsUsed!=0) correto=false;
  if (correto) return 4; // BMP binario nao-compactado
  */
  
  if (v[0]==0xff && v[1]==0xd8)
  // && v[2]==0xff && v[3]==0xe0 &&
  //    v[6]==0x4a && v[7]==0x46 && v[8]==0x49 && v[9]==0x46)
    return 21; // Arquivo JPEG/JFIF

  char* ch; ch=(char *)v;
  DWORD* dw; dw=(DWORD *)v;
  if (strncmp(&(ch[0]),"RIFF",4)==0 && strncmp(&(ch[8]),"AVI ",4)==0) {
    if (dw[0xb8/4]==0x00080001 && dw[0xbc/4]==0) return 51; // AVI 8 bits
    if (dw[0xb8/4]==0x00180001 && dw[0xbc/4]==0) return 52; // AVI 24 bits
    erro("Erro tipoImg - rmato deve ser JPG ou um dos nao-compactados: "
         "BMP-1bit ou TGA-8bits ou TGA-24bits ou .TXT (MAT) ou .IMG ou .AVI");
  }

  bool correto=true;
  arq=fopen(nome.c_str(),"rt");
  if (arq==NULL) erro("Erro tipoImg - Abertura ",nome);
  string st; int l,c;
  st=leStr(arq); if (sscanf(st.c_str(),"%d",&l)!=1) correto=false;
  st=leStr(arq); if (sscanf(st.c_str(),"%d",&c)!=1) correto=false;
  fclose(arq);

  if (correto) return 5; // Arquivo TXT

  char* st2; st2=(char*)v; st2[7]=0; st=st2;
  if (st=="IMGSHT*") return 11;
  if (st=="IMGFLT*") return 13;
  if (st=="I3DFLT*") return 14;
  if (st=="IMGCPX*") return 15;
  if (st=="I3DSHT*") return 16;
  if (st=="IMGDBL*") return 17;

  st2[2]=0; st=st2;
  if (st=="P1") return 61;
  if (st=="P2") return 62;
  if (st=="P3") return 63;
  if (st=="P4") return 64;
  if (st=="P5") return 65;
  if (st=="P6") return 66;

  erro("Erro tipoImg - Formato deve ser JPG ou um dos nao-compactados:\n"
       "BMP-1bit ou TGA-8bits ou TGA-24bits ou .TXT (MAT) ou .IMG ou .AVI\n"
       "ou PBM ou PGM ou PPM");
  return 0;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Mat_<GRY> <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void leTga(Mat_<GRY>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rb");
  if (arq==NULL) erro("Erro leTga - Abertura de ",nome);
  HEADER::HeaderTga h; fread(&h,18,1,arq); // sizeof(h)!=18
  bool correto=true;
  if (h.c1!=0x00030000) correto=false;
  if (h.c2!=0x00000000) correto=false;
  if (h.c3!=0x00000000) correto=false;
  if (h.c4!=0x08) correto=false;
  if (!correto)
    erro("Erro IMGGRY::LeTga - Formato TGA deve ser 8bits grayscale "
         "sem-palette nao-compactado");

  int nll=h.ImageHeight;
  int ncl=h.ImageWidth;

  d.create(nll,ncl);
  if (d.isContinuous()==false) erro("Erro leTga !isContinuous");
  size_t lidos=fread(d.data,1,nll*ncl,arq);
  if (lidos!=size_t(nll*ncl)) erro("Erro IMGGRY::LeTga - Fim inesperado");
  fclose(arq);

  if ((h.ordem & 0x30)==0)
    for (int l=0; l<nll/2; ++l)
      for (int c=0; c<ncl; ++c)
        swap( d(l,c), d(nll-l-1,c) );
}

void leTgaP(Mat_<GRY>& d, string nome)
{ // Le TGA com palette (aprox para cinza mais px).
  FILE* arq=fopen(nome.c_str(),"rb");
  if (arq==NULL) erro("Erro IMGGRY::LeTgaP - Abertura de ",nome);
  HEADER::HeaderTga h; fread(&h,18,1,arq); // sizeof(h)!=18
  bool correto=true;
  if (h.c1!=0x00010100) correto=false;
  if (h.c3!=0x00000000) correto=false;
  if (h.c4!=0x08) correto=false;
  BYTE* x=(BYTE*)(&h);
  if (x[4]!=0x00 || x[7]!=0x18) correto=false;
  if (!correto)
    erro("Erro leTgaP - Formato TGA deve ser 8bits "
         "com-palette nao-compactado");

  int nll=h.ImageHeight;
  int ncl=h.ImageWidth;
  WORD* y=(WORD*)(&x[5]);
  int cml=y[0];

  vector<COR> pal(cml); fread(&pal.front(),sizeof(COR),cml,arq);
  d.create(nll,ncl);
  if (d.isContinuous()==false) erro("Erro leTgaP !isContinuous");
  size_t lidos=fread(d.data,1,nll*ncl,arq);
  if (lidos!=size_t(nll*ncl)) erro("Erro IMGGRY::LeTgaP - Fim inesperado");
  fclose(arq);

  vector<BYTE> gray(cml);
  for (int l=0; l<cml; ++l) gray[l]=C2G(pal[l]);

  if ((h.ordem & 0x30)==0)
    for (int l=0; l<nll/2; ++l)
      for (int c=0; c<ncl; ++c)
        swap( d(l,c), d(nll-l-1,c) );

  for (int l=0; l<nll; ++l)
    for (int c=0; c<ncl; ++c)
      d(l,c)=gray[ d(l,c) ];
}

void leTxt(Mat_<GRY>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rt");
  if (arq==NULL) erro("Erro leTxt - Abertura ",nome);

  int nll,ncl;
  leNum(arq,nll); leNum(arq,ncl);

  d.create(nll,ncl);
  BYTE b;
  for (int l=0; l<nll; ++l)
    for (int c=0; c<ncl; ++c) {
      leNum(arq,b); d(l,c)=b;
    }

  int temp;
  leNumIgnEOF(arq,temp);
  if (temp!=minint) {
    //(*this).lc()=temp;
    leNumIgnEOF(arq,temp);
    //if (temp!=minint) (*this).cc()=temp;
  }
  fclose(arq);
}

void impTga(Mat_<GRY> d, string nome)
{ FILE* arq=fopen(nome.c_str(),"wb");
  if (arq==NULL) erro("Erro impTga - Abertura de ",nome);

  HEADER::HeaderTga h;
  h.c1=0x00030000;
  h.c2=0x00000000;
  h.c3=0x00000000;
  h.c4=0x08;
  if (d.cols>0xffff || d.rows>0xffff)
    erro("Erro: Imagem muito grande para TGA");
  h.ImageWidth=d.cols;
  h.ImageHeight=d.rows;
  h.ordem=0x20;
  fwrite(&h,18,1,arq); // sizeof(h)!=18
  if (d.isContinuous()) 
    fwrite(d.data,1,d.rows*d.cols,arq);
  else { 
    for (int l=0; l<d.rows; l++) 
      fwrite(d.ptr(l),1,d.cols,arq);
  }
  fclose(arq);
}

void impTxt(Mat_<GRY> d, string nome)
{ ofstream sai(nome.c_str());
  if (!sai) erro("Erro impTxt - Abertura ",nome);

  sai << d.rows << ' ' << d.cols << endl;
  for (int l=0; l<d.rows; ++l) {
    for (int c=0; c<d.cols; ++c) {
      sai.width(3);
      sai << int(d(l,c)) << ' ';
    }
    sai << endl;
  }
  sai.close();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Mat_<COR> <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void leTga(Mat_<COR>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rb");
  if (arq==NULL) erro("Erro leTga - Abertura ",nome);
  HEADER::HeaderTga h; fread(&h,18,1,arq); // sizeof(h)!=18
  bool correto=true;
  if (h.c1!=0x00020000) correto=false;
  if (h.c2!=0x00000000) correto=false;
  if (h.c3!=0x00000000) correto=false;
  if (h.c4!=0x18) correto=false;
  if (!correto)
    erro("Erro IMGCOR::LeTga - Formato TGA deve ser 24bits "
         "sem-palette nao-compactado");

  int nll=h.ImageHeight;
  int ncl=h.ImageWidth;

  d.create(nll,ncl);
  if (d.isContinuous()==false) erro("Erro leTga !isContinuous");
  size_t lidos=fread(d.data,sizeof(COR),nll*ncl,arq);
  if (lidos!=size_t(nll*ncl)) erro("Erro IMGCOR::LeTga - Fim inesperado");
  fclose(arq);

  if ((h.ordem & 0x30)==0)
    for (int l=0; l<nll/2; ++l)
      for (int c=0; c<ncl; ++c)
        swap( d(l,c), d(nll-l-1,c) );
}

void leTgaP(Mat_<COR>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rb");
  if (arq==NULL) erro("Erro leTgaP - Abertura ",nome);
  HEADER::HeaderTga h; fread(&h,18,1,arq); // sizeof(h)!=18
  bool correto=true;
  if (h.c1!=0x00010100) correto=false;
  if (h.c3!=0x00000000) correto=false;
  if (h.c4!=0x08) correto=false;
  BYTE* x=(BYTE*)(&h.c1);
  if (x[4]!=0x00 || x[7]!=0x18) correto=false;
  if (!correto)
    erro("Erro leTgaP - Formato TGA deve ser 8bits "
         "com-palette nao-compactado");

  int nll=h.ImageHeight;
  int ncl=h.ImageWidth;
  WORD* y=(WORD*)(&x[5]);
  int cml=y[0];

  vector<COR> pal(cml);
  fread(&pal.front(),sizeof(COR),cml,arq);
  //for (int l=0; l<cml; ++l) vira( pal(l) );

  vector<BYTE> a(nll*ncl);
  size_t lidos=fread(&a.front(),1,nll*ncl,arq);
  if (lidos!=size_t(nll*ncl)) erro("Erro IMGCOR::LeTgaP - Fim inesperado");
  fclose(arq);

  d.create(nll,ncl);
  if (d.isContinuous()==false) erro("Erro leTgaP !isContinuous");
  for (int l=0; l<nll; ++l)
    for (int c=0; c<ncl; ++c)
      d(l,c)=pal[ a[l*ncl+c] ];

  if ((h.ordem & 0x30)==0)
    for (int l=0; l<nll/2; ++l)
      for (int c=0; c<ncl; ++c)
        swap( d(l,c), d(nll-l-1,c) );
}

void leTxt(Mat_<COR>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rt");
  if (arq==NULL) erro("Erro leTxt - Abertura ",nome);

  int nll,ncl;
  leNum(arq,nll); leNum(arq,ncl);

  d.create(nll,ncl);
  BYTE b;
  for (int l=0; l<nll; ++l)
    for (int c=0; c<ncl; ++c) {
      COR& cor=d(l,c);
      leNum(arq,b); cor[2]=b;
      leNum(arq,b); cor[1]=b;
      leNum(arq,b); cor[0]=b;
    }

  int temp;
  leNumIgnEOF(arq,temp);
  if (temp!=minint) {
    //(*this).lc()=temp;
    leNumIgnEOF(arq,temp);
    //if (temp!=minint) (*this).cc()=temp;
  }
  fclose(arq);
}

void impTga(Mat_<COR> d, string nome)
{ FILE* arq=fopen(nome.c_str(),"wb");
  if (arq==NULL) erro("Erro impTga - Abertura ",nome);

  HEADER::HeaderTga h;
  h.c1=0x00020000;
  h.c2=0x00000000;
  h.c3=0x00000000;
  h.c4=0x18;
  if (d.cols>0xffff || d.rows>0xffff)
    erro("Erro: Imagem muito grande para TGA");
  h.ImageWidth=d.cols;
  h.ImageHeight=d.rows;
  h.ordem=0x20;
  fwrite(&h,18,1,arq); // sizeof(h)!=18
  if (d.isContinuous()) 
    fwrite(d.data,sizeof(COR),d.rows*d.cols,arq);
  else {
    for (int l=0; l<d.rows; l++) 
      fwrite(d.ptr(l),sizeof(COR),d.cols,arq);
  }
  fclose(arq);
}

void impTxt(Mat_<COR> d, string nome)
{ ofstream sai(nome.c_str());
  if (!sai) erro("Erro impTxt - Abertura ",nome);

  sai << d.rows << ' ' << d.cols << endl;
  for (int l=0; l<d.rows; ++l) {
    for (int c=0; c<d.cols; ++c) {
      sai.width(3); sai << int(d(l,c)[2]) << ' ';
      sai.width(3); sai << int(d(l,c)[1]) << ' ';
      sai.width(3); sai << int(d(l,c)[0]) << "    ";
    }
    sai << endl;
  }
  sai.close();
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Mat_<FLT> <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void leTxt(Mat_<FLT>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rt");
  if (arq==NULL) erro("Erro leTxt - Abertura ",nome);

  int nll,ncl;
  leNum(arq,nll); leNum(arq,ncl);

  d.create(nll,ncl);
  FLT f;
  for (int l=0; l<nll; ++l)
    for (int c=0; c<ncl; ++c) {
      leNum(arq,f); d(l,c)=f;
    }

  int temp;
  leNumIgnEOF(arq,temp);
  if (temp!=minint) {
    //(*this).lc()=temp;
    leNumIgnEOF(arq,temp);
    //if (temp!=minint) (*this).cc()=temp;
  }
  fclose(arq);
}

void leImg(Mat_<FLT>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rb");
  if (arq==NULL) erro("Erro leImg - Abertura de ",nome);

  bool correto=true;
  char st[9]; fread(st,1,8,arq); st[7]=0;
  if (string(st)!="IMGFLT*") correto=false;

  int tam; fread(&tam,4,1,arq);
  if (tam!=sizeof(FLT)) correto=false;

  if (!correto) erro("Erro leImg - Formato incorreta");

  int nl,nc,lc,cc;
  fread(&nl,4,1,arq);
  fread(&nc,4,1,arq);
  fread(&lc,4,1,arq);
  fread(&cc,4,1,arq);
  d.create(nl,nc);

  size_t lidos=fread(d.data,tam,nl*nc,arq);
  if (lidos!=size_t(nl*nc)) erro("Erro leImg - Fim inesperado");

  fclose(arq);
}

void impTxt(Mat_<FLT> d, string nome)
{ ofstream sai(nome.c_str());
  if (!sai) erro("Erro impTxt - Abertura ",nome);

  sai << d.rows << ' ' << d.cols << endl;
  for (int l=0; l<d.rows; ++l) {
    for (int c=0; c<d.cols; ++c) {
      //sai.width(10);
      sai << float(d(l,c)) << ' ';
    }
    sai << endl;
  }
  sai.close();
}

void impImg(Mat_<FLT> a, string nome)
{ FILE* arq=fopen(nome.c_str(),"wb");
  if (arq==NULL) erro("Erro impImg - Abertura de ",nome);

  int tam=sizeof(FLT);
  char st[]="IMGFLT*\x1a";
  fwrite(st,1,8,arq);
  fwrite(&tam,4,1,arq);
  fwrite(&a.rows,4,1,arq);
  fwrite(&a.cols,4,1,arq);
  int temp=0;
  fwrite(&temp,4,1,arq);
  fwrite(&temp,4,1,arq);

  if (a.isContinuous()) 
    fwrite(a.data,tam,a.rows*a.cols,arq);
  else { 
    for (int l=0; l<a.rows; l++) 
      fwrite(a.ptr(l),tam,a.cols,arq);
  }
  fclose(arq);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Mat_<CPX> <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void leTxt(Mat_<CPX>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rt");
  if (arq==NULL) erro("Erro leTxt - Abertura ",nome);

  int nll,ncl;
  leNum(arq,nll); leNum(arq,ncl);

  d.create(nll,ncl);
  FLT b1,b2;
  for (int l=0; l<nll; ++l)
    for (int c=0; c<ncl; ++c) {
      leNum(arq,b1); leNum(arq,b2);
      d(l,c)=CPX(b1,b2);
    }

  int temp;
  leNumIgnEOF(arq,temp);
  if (temp!=minint) {
    //(*this).lc()=temp;
    leNumIgnEOF(arq,temp);
    //if (temp!=minint) (*this).cc()=temp;
  }
  fclose(arq);
}

void leImg(Mat_<CPX>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rb");
  if (arq==NULL) erro("Erro leImg - Abertura de ",nome);
  
  bool correto=true;
  char st[9]; fread(st,1,8,arq); st[7]=0;
  if (string(st)!="IMGCPX*") correto=false;

  int tam; fread(&tam,4,1,arq);
  if (tam!=sizeof(CPX)) correto=false;

  if (!correto) erro("Erro leImg - Formato incorreta");

  int nl,nc,lc,cc;
  fread(&nl,4,1,arq);
  fread(&nc,4,1,arq);
  fread(&lc,4,1,arq);
  fread(&cc,4,1,arq);
  d.create(nl,nc);

  size_t lidos=fread(d.data,tam,nl*nc,arq);
  if (lidos!=size_t(nl*nc)) erro("Erro leImg - Fim inesperado");

  fclose(arq);
}

void impTxt(Mat_<CPX> d, string nome)
{ ofstream sai(nome.c_str());
  if (!sai) erro("Erro impTxt - Abertura ",nome);

  sai << d.rows << ' ' << d.cols << endl;
  for (int l=0; l<d.rows; ++l) {
    for (int c=0; c<d.cols; ++c) {
      sai << d(l,c) << ' ';
    }
    sai << endl;
  }
  sai.close();
}

void impImg(Mat_<CPX> a, string nome)
{ FILE* arq=fopen(nome.c_str(),"wb");
  if (arq==NULL) erro("Erro impImg - Abertura de ",nome);

  int tam=sizeof(CPX);
  char st[]="IMGCPX*\x1a";
  fwrite(st,1,8,arq);
  fwrite(&tam,4,1,arq);
  fwrite(&a.rows,4,1,arq);
  fwrite(&a.cols,4,1,arq);
  int temp=0;
  fwrite(&temp,4,1,arq);
  fwrite(&temp,4,1,arq);

  if (a.isContinuous()) 
    fwrite(a.data,tam,a.rows*a.cols,arq);
  else { 
    for (int l=0; l<a.rows; l++) 
      fwrite(a.ptr(l),tam,a.cols,arq);
  }
  fclose(arq);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<< Mat_<SHT> <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void leTxt(Mat_<SHT>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rt");
  if (arq==NULL) erro("Erro leTxt - Abertura ",nome);

  int nll,ncl;
  leNum(arq,nll); leNum(arq,ncl);

  d.create(nll,ncl);
  SHT b;
  for (int l=0; l<nll; ++l)
    for (int c=0; c<ncl; ++c) {
      leNum(arq,b); d(l,c)=b;
    }

  int temp;
  leNumIgnEOF(arq,temp);
  if (temp!=minint) {
    //(*this).lc()=temp;
    leNumIgnEOF(arq,temp);
    //if (temp!=minint) (*this).cc()=temp;
  }
  fclose(arq);
}

void impTxt(Mat_<SHT>& d, string nome)
{ ofstream sai(nome.c_str());
  if (!sai) erro("Erro impTxt - Abertura ",nome);

  sai << d.rows << ' ' << d.cols << endl;
  sai << endl;
  for (int l=0; l<d.rows; ++l) {
    for (int c=0; c<d.cols; ++c) {
      sai.width(6);
      sai << d(l,c) << ' ';
    }
    sai << endl;
  }
  sai << endl;
  sai.close();
}
void leImg(Mat_<SHT>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rb");
  if (arq==NULL) erro("Erro LeImgS - Abertura de ",nome);

  bool correto=true;
  char st[9]; fread(st,1,8,arq); st[7]=0;
  if (string(st)!="IMGSHT*") correto=false;

  int tam; fread(&tam,4,1,arq);
  if (tam!=sizeof(SHT)) correto=false;

  if (!correto) erro("Erro IMGSHT::LeImg - Formato incorreta");

  int nl,nc,lc,cc;
  fread(&nl,4,1,arq);
  fread(&nc,4,1,arq);
  fread(&lc,4,1,arq);
  fread(&cc,4,1,arq);
  d.create(nl,nc);

  size_t lidos=fread(d.data,tam,nl*nc,arq);
  if (lidos!=size_t(nl*nc)) erro("Erro leImg - Fim inesperado");

  fclose(arq);
}

void impImg(Mat_<SHT> a, string nome)
{ FILE* arq=fopen(nome.c_str(),"wb");
  if (arq==NULL) erro("Erro IMGSHT::ImpImg - Abertura de ",nome);

  int tam=sizeof(SHT);
  char st[]="IMGSHT*\x1a";
  fwrite(st,1,8,arq);
  fwrite(&tam,4,1,arq);
  fwrite(&a.rows,4,1,arq);
  fwrite(&a.cols,4,1,arq);
  int temp=0;
  fwrite(&temp,4,1,arq);
  fwrite(&temp,4,1,arq);

  if (a.isContinuous()) 
    fwrite(a.data,tam,a.rows*a.cols,arq);
  else { 
    for (int l=0; l<a.rows; l++) 
      fwrite(a.ptr(l),tam,a.cols,arq);
  }
  fclose(arq);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Mat_<DBL> <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void leTxt(Mat_<DBL>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rt");
  if (arq==NULL) erro("Erro leTxt - Abertura ",nome);

  int nll,ncl;
  leNum(arq,nll); leNum(arq,ncl);

  d.create(nll,ncl);
  DBL f;
  for (int l=0; l<nll; ++l)
    for (int c=0; c<ncl; ++c) {
      leNum(arq,f); d(l,c)=f;
    }

  int temp;
  leNumIgnEOF(arq,temp);
  if (temp!=minint) {
    //(*this).lc()=temp;
    leNumIgnEOF(arq,temp);
    //if (temp!=minint) (*this).cc()=temp;
  }
  fclose(arq);
}

void leImg(Mat_<DBL>& d, string nome)
{ FILE* arq=fopen(nome.c_str(),"rb");
  if (arq==NULL) erro("Erro leImg - Abertura de ",nome);

  bool correto=true;
  char st[9]; fread(st,1,8,arq); st[7]=0;
  if (string(st)!="IMGDBL*") correto=false;

  int tam; fread(&tam,4,1,arq);
  if (tam!=sizeof(DBL)) correto=false;

  if (!correto) erro("Erro leImg - Formato incorreta");

  int nl,nc,lc,cc;
  fread(&nl,4,1,arq);
  fread(&nc,4,1,arq);
  fread(&lc,4,1,arq);
  fread(&cc,4,1,arq);
  d.create(nl,nc);

  size_t lidos=fread(d.data,tam,nl*nc,arq);
  if (lidos!=size_t(nl*nc)) erro("Erro leImg - Fim inesperado");

  fclose(arq);
}

void impTxt(Mat_<DBL> d, string nome)
{ ofstream sai(nome.c_str());
  if (!sai) erro("Erro impTxt - Abertura ",nome);

  sai << d.rows << ' ' << d.cols << endl;
  for (int l=0; l<d.rows; ++l) {
    for (int c=0; c<d.cols; ++c) {
      sai.width(12);
      sai << float(d(l,c)) << ' ';
    }
    sai << endl;
  }
}

void impImg(Mat_<DBL> a, string nome)
{ FILE* arq=fopen(nome.c_str(),"wb");
  if (arq==NULL) erro("Erro impImg - Abertura de ",nome);

  int tam=sizeof(DBL);
  char st[]="IMGDBL*\x1a";
  fwrite(st,1,8,arq);
  fwrite(&tam,4,1,arq);
  fwrite(&a.rows,4,1,arq);
  fwrite(&a.cols,4,1,arq);
  int temp=0;
  fwrite(&temp,4,1,arq);
  fwrite(&temp,4,1,arq);

  if (a.isContinuous()) 
    fwrite(a.data,tam,a.rows*a.cols,arq);
  else { 
    for (int l=0; l<a.rows; l++) 
      fwrite(a.ptr(l),tam,a.cols,arq);
  }
  fclose(arq);
}

//<<<<<<<<<<<<<<<<<<<< le <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<,
void le(Mat_<GRY>& d, string nome) 
{ if (!existeArq(nome)) erro("Erro: Arquivo inexistente ",nome);
  string suf=sufixo(nome);  
  if (suf=="bmp" || suf=="dib" || suf=="jpeg" || suf=="jpg" || suf=="jpe" || suf=="jp2" || suf=="png" ||
      suf=="pbm" || suf=="pgm" || suf=="ppm" || suf=="sr" || suf=="ras" || suf=="tiff" || suf=="tif") {
    d=imread(nome,0);
    if (d.data!=NULL) return;
  }
  int tipo=tipoImg(nome);
  if      (tipo==1) leTga(d,nome);
  else if (tipo==2) leTgaP(d,nome);
  else if (tipo==3) { Mat_<COR> a; leTga(a,nome); converte(a,d); }
  else if (tipo==5) leTxt(d,nome);
  else if (tipo==13) { Mat_<FLT> a; leImg(a,nome); converte(a,d); }
  else erro("Tipo de imagem invalido ",nome);
}

void le(Mat_<COR>& d, string nome)
{ if (!existeArq(nome)) erro("Erro: Arquivo inexistente ",nome);
  string suf=sufixo(nome);  
  if (suf=="bmp" || suf=="dib" || suf=="jpeg" || suf=="jpg" || suf=="jpe" || suf=="jp2" || suf=="png" ||
      suf=="pbm" || suf=="pgm" || suf=="ppm" || suf=="sr" || suf=="ras" || suf=="tiff" || suf=="tif") {
    d=imread(nome,1);
    if (d.data!=NULL) return;
  }
  int tipo=tipoImg(nome);
  if (tipo==1) { Mat_<GRY> a; leTga(a,nome); converte(a,d); }
  else if (tipo==2) leTgaP(d,nome);
  else if (tipo==3) leTga(d,nome);
  else if (tipo==5) leTxt(d,nome);
  else if (tipo==13) { Mat_<FLT> a; leImg(a,nome); converte(a,d); }
  else erro("Tipo de imagem invalido ",nome);
}

void le(Mat_<FLT>& d, string nome)
{ if (!existeArq(nome)) erro("Erro: Arquivo inexistente ",nome);

  string suf=sufixo(nome);  
  if (suf=="bmp" || suf=="dib" || suf=="jpeg" || suf=="jpg" || suf=="jpe" || suf=="jp2" || suf=="png" ||
      suf=="pbm" || suf=="pgm" || suf=="ppm" || suf=="sr" || suf=="ras" || suf=="tiff" || suf=="tif") {
    Mat_<GRY> a=imread(nome,0);
    if (a.data==NULL) erro("Erro leitura 1");
    converte(a,d);
    return;
  } else if (suf=="tga") {
    Mat_<GRY> g; le(g,nome); converte(g,d); return;
  }

  int tipo=tipoImg(nome);
  if (tipo==13) leImg(d,nome);
  else if (tipo==5) leTxt(d,nome);
  else erro("Erro leitura");
}

void le(Mat_<CPX>& d, string nome)
{ if (!existeArq(nome)) erro("Erro: Arquivo inexistente ",nome);

  string suf=sufixo(nome);  
  if (suf=="bmp" || suf=="dib" || suf=="jpeg" || suf=="jpg" || suf=="jpe" || suf=="jp2" || suf=="png" ||
      suf=="pbm" || suf=="pgm" || suf=="ppm" || suf=="sr" || suf=="ras" || suf=="tiff" || suf=="tif") {
    Mat_<GRY> a=imread(nome,0);
    if (a.data==NULL) erro("Erro leitura 1");
    converte(a,d);
    return;
  } else if (suf=="tga") {
    Mat_<GRY> g; le(g,nome); converte(g,d); return;
  }

  int tipo=tipoImg(nome);
  if (tipo==15) leImg(d,nome);
  else if (tipo==5) leTxt(d,nome);
  else erro("Erro leitura");
}

void le(Mat_<SHT>& d, string nome)
{ if (!existeArq(nome)) erro("Erro: Arquivo inexistente ",nome);

  string suf=sufixo(nome);  
  if (suf=="bmp" || suf=="dib" || suf=="jpeg" || suf=="jpg" || suf=="jpe" || suf=="jp2" || suf=="png" ||
      suf=="pbm" || suf=="pgm" || suf=="ppm" || suf=="sr" || suf=="ras" || suf=="tiff" || suf=="tif") {
    Mat_<GRY> a=imread(nome,0);
    if (a.data==NULL) erro("Erro leitura 1");
    converte(a,d);
    return;
  } else if (suf=="tga") {
    Mat_<GRY> g; le(g,nome); converte(g,d); return;
  }

  int tipo=tipoImg(nome);
  if (tipo==11) leImg(d,nome);
  else if (tipo==5) leTxt(d,nome);
  else erro("Erro leitura");
}

void le(Mat_<DBL>& d, string nome)
{ if (!existeArq(nome)) erro("Erro: Arquivo inexistente ",nome);

  string suf=sufixo(nome);  
  if (suf=="bmp" || suf=="dib" || suf=="jpeg" || suf=="jpg" || suf=="jpe" || suf=="jp2" || suf=="png" ||
      suf=="pbm" || suf=="pgm" || suf=="ppm" || suf=="sr" || suf=="ras" || suf=="tiff" || suf=="tif") {
    Mat_<GRY> a=imread(nome,0);
    if (a.data==NULL) erro("Erro leitura 1");
    converte(a,d);
    return;
  } else if (suf=="tga") {
    Mat_<GRY> g; le(g,nome); converte(g,d); return;
  }

  int tipo=tipoImg(nome);
  if (tipo==17) leImg(d,nome);
  else if (tipo==5) leTxt(d,nome);
  else erro("Erro leitura 2");
}

void le(Mat& a, string nome, int type)
{ if (!existeArq(nome)) erro("Erro: Arquivo inexistente ",nome);
  //printf("le(MAT): tipo=%d\n",type);
  if (type==CV_8UC1) { //gray
    Mat_<GRY> ap=a;
    le(ap,nome);
  } else if (type==CV_8UC3) { //color
    Mat_<COR> ap=a;
    le(ap,nome);
  } else if (type==CV_32FC1) { //FLT
    Mat_<FLT> ap=a;
    le(ap,nome);
  } else if (type==CV_32FC2) { //CPX
    Mat_<CPX> ap=a;
    le(ap,nome);
  } else if (type==CV_16SC1) { //SHT
    Mat_<SHT> ap=a;
    le(ap,nome);
  } else if (type==CV_64FC1) { //FLT
    Mat_<DBL> ap=a;
    le(ap,nome);
  } else erro("Erro le(Mat): tipo desconhecido");
}

//<<<<<<<<<<<<<<<<<<<< imp <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<,
void imp(Mat_<GRY> d, string nome)
{ if (d.dims!=2 || d.rows<=0 || d.cols<=0) erro("Erro imp: dimensao invalida");
  bool ok=true;
  int quali; string suf,raiz;
  sufixoImg(nome,raiz,suf,quali);
  //cout << "raiz=" << raiz << " suf=" << suf << " quali=" << quali << endl;
  //nome=minuscula(nome);
  if (nome=="tela" || nome=="win" || nome=="win:") 
    mostra(d);
  else if (nome=="con" || nome=="con:")
    impTxt(d,nome);
  else if (suf=="tga") // suf=="img"
    impTga(d,raiz);
  else if (suf=="txt" || suf=="mat") 
    impTxt(d,raiz);
  else if (suf=="jpg") {
    if (quali==-1) ok=imwrite(raiz,d);
    else {
      int v[]={CV_IMWRITE_JPEG_QUALITY,quali};
      ok=imwrite(raiz,d,vector<int>(v,v+2));
    }
  } else if (suf=="png") {
    if (quali==-1) ok=imwrite(raiz,d);
    else {
      int v[]={CV_IMWRITE_PNG_COMPRESSION,quali};
      ok=imwrite(raiz,d,vector<int>(v,v+2));
    }
  } else if (suf=="pgm") {
    if (quali==-1) ok=imwrite(raiz,d);
    else {
      int v[]={CV_IMWRITE_PXM_BINARY,quali};
      ok=imwrite(raiz,d,vector<int>(v,v+2));
    }
  } else {
    ok=imwrite(raiz,d);
  }
  if (ok==false) erro("Erro: ImpMatG ",nome);
}

void imp(Mat_<COR> d, string nome)
{ if (d.dims!=2 || d.rows<=0 || d.cols<=0) erro("Erro imp: dimensao invalida");
  bool ok=true;
  int quali; string suf,raiz;
  sufixoImg(nome,raiz,suf,quali);
  //cout << "raiz=" << raiz << " suf=" << suf << " quali=" << quali << endl;
  if (nome=="tela" || nome=="win" || nome=="win:") 
    mostra(d);
  else if (nome=="con" || nome=="con:")
    impTxt(d,nome);
  else if (suf=="tga") // suf=="img" )
    impTga(d,raiz);
  else if (suf=="txt" || suf=="mat") 
    impTxt(d,raiz);
  else if (suf=="jpg") {
    if (quali==-1) ok=imwrite(raiz,d);
    else {
      int v[]={CV_IMWRITE_JPEG_QUALITY,quali};
      ok=imwrite(raiz,d,vector<int>(v,v+2));
    }
  } else if (suf=="png") {
    if (quali==-1) ok=imwrite(raiz,d);
    else {
      int v[]={CV_IMWRITE_PNG_COMPRESSION,quali};
      ok=imwrite(raiz,d,vector<int>(v,v+2));
    }
  } else if (suf=="ppm") {
    if (quali==-1) ok=imwrite(raiz,d);
    else {
      int v[]={CV_IMWRITE_PXM_BINARY,quali};
      ok=imwrite(raiz,d,vector<int>(v,v+2));
    }
  } else {
    ok=imwrite(raiz,d);
  }
  if (ok==false) erro("Erro: ImpMatC ",nome);
}

void imp(Mat_<CORF> d, string nome)
{ Mat_<COR> e; converte(d,e); imp(e,nome); }

void imp(Mat_<FLT> d, string nome)
{ if (d.dims!=2 || d.rows<=0 || d.cols<=0) erro("Erro imp: dimensao invalida");
  int quali; string suf,raiz;
  sufixoImg(nome,raiz,suf,quali);

  if (nome=="tela" || nome=="win" || nome=="win:") 
    mostra(d);
  else if (nome=="con" || nome=="con:") {
    impTxt(d,nome);
  } else if (suf=="txt" || suf=="mat") 
    impTxt(d,raiz);
  else if (suf=="img") 
    impImg(d,raiz);
  else {
    Mat_<GRY> a; 
    converte(d,a); 
    imp(a,nome);
  }
}

void imp(Mat_<CPX> d, string nome)
{ if (d.dims!=2 || d.rows<=0 || d.cols<=0) erro("Erro imp: dimensao invalida");
  int quali; string suf,raiz;
  sufixoImg(nome,raiz,suf,quali);

  if (nome=="tela" || nome=="win" || nome=="win:") 
    mostra(d);
  else if (nome=="con" || nome=="con:")
    impTxt(d,nome);
  else if (suf=="txt" || suf=="mat") 
    impTxt(d,raiz);
  else if (suf=="img") 
    impImg(d,raiz);
  else {
    Mat_<COR> a; converte(d,a); imp(a,nome);
  }
}

void imp(Mat_<SHT> d, string nome)
{ if (d.dims!=2 || d.rows<=0 || d.cols<=0) erro("Erro imp: dimensao invalida");
  int quali; string suf,raiz;
  sufixoImg(nome,raiz,suf,quali);

  if (nome=="tela" || nome=="win" || nome=="win:") { 
    Mat_<FLT> f; converte(d,f); mostra(f);
  } else if (nome=="con" || nome=="con:") {
    impTxt(d,nome);
  } else if (suf=="txt" || suf=="mat") 
    impTxt(d,raiz);
  else if (suf=="img") 
    impImg(d,raiz);
  else {
    Mat_<GRY> a; converte(d,a); imp(a,nome);
  }
}

void imp(Mat_<DBL> d, string nome)
{ if (d.dims!=2 || d.rows<=0 || d.cols<=0) erro("Erro imp: dimensao invalida");
  int quali; string suf,raiz;
  sufixoImg(nome,raiz,suf,quali);

  if (nome=="tela" || nome=="win" || nome=="win:") {
    Mat_<FLT> f; converte(d,f); mostra(f);
  } else if (nome=="con" || nome=="con:") {
    impTxt(d,nome);
  } else if (suf=="txt" || suf=="mat") 
    impTxt(d,raiz);
  else if (suf=="img") 
    impImg(d,raiz);
  else {
    Mat_<GRY> a; converte(d,a); imp(a,nome);
  }
}

void imp(Mat d, string nome)
{ if (d.type()==CV_8UC1) { //gray
    Mat_<GRY> ap=d; imp(ap,nome);
  } else if (d.type()==CV_8UC3) { //color
    Mat_<COR> ap=d; imp(ap,nome);
  } else if (d.type()==CV_32FC1) { //FLT
    Mat_<FLT> ap=d; imp(ap,nome);
  } else if (d.type()==CV_32FC2) { //CPX
    Mat_<CPX> ap=d; imp(ap,nome);
  } else if (d.type()==CV_16SC1) { //SHT
    Mat_<SHT> ap=d; imp(ap,nome);
  } else if (d.type()==CV_64FC1) { //DBL
    Mat_<DBL> ap=d; imp(ap,nome);
  } else erro("Erro imp: tipo desconhecido");
}

} // namespace cek

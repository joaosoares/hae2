#include <cekeikon.h>
int _CRT_glob = 0;   // Para impedir expansao de wildcard

// <<<<<<<<<<<<<<<<<<<< funcoes <<<<<<<<<<<<<<<<<<<<<<<<<<<<
void version(int argc, char** argv);
void arg(int argc, char** argv);
void renomeia(int argc, char** argv);
void delpref(int argc, char** argv);
void minusc(int argc, char** argv);
void enumera(int argc, char** argv);

void mconvert(int argc, char** argv);

void getquad(int argc, char** argv);
void sobrmmc(int argc, char** argv);
void sobrepoe(int argc, char** argv);
void alinha(int argc, char** argv);
void smoothc(int argc, char** argv);
void colafund(int argc, char** argv);
void quebrac(int argc, char** argv);
void binariza(int argc, char** argv);
void minimoc(int argc, char** argv);
void cropc(int argc, char** argv);
void canvasc(int argc, char** argv);
void zoomc(int argc, char** argv);
void projcor(int argc, char** argv);

void normal01(int argc, char** argv);
void zoomg(int argc, char** argv);
void ruidospg(int argc, char** argv);
void brilcong(int argc, char** argv);
void histeqg(int argc, char** argv);
void otsug(int argc, char** argv);
void threshg(int argc, char** argv);
void gradieng(int argc, char** argv);
void houghgr(int argc, char** argv);
void distg(int argc, char** argv);
void mserg(int argc, char** argv);

void houghb(int argc, char** argv);
void houcirb(int argc, char** argv);

void pedestre(int argc, char** argv);
void gerahog(int argc, char** argv);
void showhog(int argc, char** argv);
void classify(int argc, char** argv);

void boopred(int argc, char** argv);
void bootrain(int argc, char** argv);
void dtpred(int argc, char** argv);
void dttrain(int argc, char** argv);
void rndtrain(int argc, char** argv);
void rndpred(int argc, char** argv);
void svmpred(int argc, char** argv);
void svmtrain(int argc, char** argv);
void segmenc(int argc, char** argv);
void pixelmap(int argc, char** argv);
void pixmappo(int argc, char** argv);

void mostrac(int argc, char** argv);
void mostrag(int argc, char** argv);
void mostraf(int argc, char** argv);
//void mostra1d(int argc, char** argv);
void mostrad(int argc, char** argv);
void mostrax(int argc, char** argv);
void campox(int argc, char** argv);

//void mostrav(int argc, char** argv);
void copyvid(int argc, char** argv);
void img2vid(int argc, char** argv);
void cam2vid(int argc, char** argv);
// void captura(int argc, char** argv);
void camtest(int argc, char** argv);
void cam2img(int argc, char** argv);
void webcam(int argc, char** argv);
void reduzv(int argc, char** argv);
void vid2imc(int argc, char** argv);

void difframe(int argc, char** argv);
// void findbk2(int argc, char** argv);
// void allbksub(int argc, char** argv);
// void blocos(int argc, char** argv);
// void allblobk(int argc, char** argv);

void featureg(int argc, char** argv);
void lkflow(int argc, char** argv);
void lkout(int argc, char** argv);
void vidlkout(int argc, char** argv);

void tmatchg(int argc, char** argv);
void tmatchc(int argc, char** argv);

void dogextr(int argc, char** argv);
void copybk(int argc, char** argv);

void shp2imb(int argc, char** argv);

void glcm(int argc, char** argv);

//<<<<<<<<<<<<<<<<<<< helpst <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
string helpst[]={
"ARQ","Version ","Imprime a versao de OpenCV",
"ARQ","Arg     ","Imprime os argumentos do programa",
"ARQ","Renomeia","Renomeia um conjunto de arquivos",
"ARQ","DelPref ","Apaga n letras iniciais dos nomes dos arquivos",
"ARQ","Minusc  ","Renomeia arquivos para minuscula",
"ARQ","Enumera ","Renomeia arquivos usando numeros sequenciais",

"BGC","MConvert","Converte multiplas imagens",

"COR","GetQuad ","Extrai regiao quadrilatera e faz warping",
"COR","SobrMMc ","Sobrepoe multiplas mascaras",
"COR","Sobrepoe","Sobrepoe imagens como se fossem transparentes",
"COR","Alinha  ","Translada A para ficar alinhada com REF",
"COR","SmoothC ","Filtra MatCOR com media-movel, mediana ou gaussiana",
"COR","ColaFund","Cola duas imagens com fundo transparente",
"COR","QuebraC ","Quebra imagem colorida em subimagens",
"COR","Binariza","Binariza imagem colorida com pesos em RGB",
"COR","MinimoC ","Calcula minimo elementwise de n Mat_<COR>",
"COR","CropC   ","Apaga bordas de imagem colorida",
"COR","CanvasC ","Insere bordas de imagem colorida",
"COR","ZoomC   ","Faz ampliacao ou reducao de multiplas MatCOR",
"COR","ProjCor ","Projeta as cores da Mat_<COR> nos planos rg, rb e gb",

"GRY","Normal01","Normaliza imagem para seguir gaussiana",
"GRY","ZoomG   ","Faz ampliacao ou reducao de multiplas MatGRY",
"GRY","RuidoSPG","Acrescenta ruido SP (aleatorio) em MatGRY",
"GRY","BrilConG","Ajusta brilho/contraste de Mat_<GRY>",
"GRY","HistEqG ","Equaliza histograma de Mat_<GRY>",
"GRY","OtsuG   ","Binariza imagem usando limiar de Otsu global",
"GRY","ThreshG ","Binariza imagem usando limiar global",
"GRY","GradienG","Calcula gradiente de Mat_<GRY> e salva como Mat_<CPX>",
"GRY","HoughGr ","Calcula Hough-retas de gradiente, sem detectar arestas",
"GRY","DistG   ","Calcula diferenca entre duas Mat_<GRY>",
"GRY","MserG   ","MSER (maximally stable extremal region) de Mat_<GRY>",

"BIN","HoughB  ","Transf. Hough de im. binarias para detectar retas",
"BIN","HouCirB ","Transf. Hough de im. binarias para detectar circulos",

"HOG","Pedestre","HOG de imagens 64x128 espelhada e grava como .IMG",
"HOG","GeraHog ","Gera HOG de imagens arbitraria e grava como .IMG",
"HOG","ShowHOG ","Mostra HOG de imagem 64x128",
"HOG","Classify","Classifica imagem 64x128 em pedestre/carro",

"MLE","BooPred ","AdaBoost predict",
"MLE","BooTrain","AdaBoost train",
"MLE","DtPred  ","Decision tree predict",
"MLE","DtTrain ","Decision tree train",
"MLE","RndPred ","Random tree predict",
"MLE","RndTrain","Random tree train",
"MLE","SvmPred ","Support vector machine predict",
"MLE","SvmTrain","Support vector machine train",
"MLE","SegmenC ","Segmenta Mat_<COR> pela cor",
"MLE","PixelMap","Segmenta Mat_<COR> pela cor, usando ex-pos e ex-neg",
"MLE","PixMapPo","Segmenta Mat_<COR> pela cor, usando so ex-pos",

"SHW","MostraC ","Mostra multiplas MatCOR",
"SHW","MostraG ","Mostra multiplas MatGRY com aj. brilho/contraste",
"SHW","MostraF ","Mostra multiplas MatFLT com aj. brilho/contraste",
//"SHW","Mostra1D","Mostra 1 MatDBL com varios ajustes",
"SHW","MostraD ","Mostra multiplas MatDBL com aj. brilho/contraste",
"SHW","MostraX ","Mostra multiplas MatCPX com aj. brilho/contraste",
"SHW","CampoX  ","Converte MatCPX como campo vetorial com flechas",

//"VID","MostraV ","Mostra multiplos videos",
"VID","CopyVid ","Copia video sem audio. Converte videos para avi-xvid",
"VID","Img2vid ","Converte seq de img em vid",
"VID","Cam2vid ","Grava webcam em video, especificando FOURCC",
// "VID","Captura ","Grava webcam em video, com cortes periodicas",
"VID","CamTest ","Testa webcam, diferentes nlxnc e fps.",
"VID","Cam2img ","Captura quadros da webcam como imagem jpg",
"VID","Webcam  ","Mostra a captura de webcam",
"VID","ReduzV  ","Pega quadros dividiveis por n de video",
"VID","Vid2IMC ","Pega um quadro de video",

"BCK","DifFrame","Calcula diferenca entre quadros consecutivos",
// "BCK","FindBk2 ","Gera video de background, considerando primeiro quadro",
// "BCK","AllBkSub","Mostra original+difframe+bkgd+subbkgd",
// "BCK","Blocos  ","Detecta blocos que mudaram em relacao ao 1o quadro",
// "BCK","AllBloBk","Mostra original+difframe+bkgd+blocos",

"LK ","FeatureG","Good features to track grayscale",
"LK ","LKFlow  ","Fluxo otico LK entre duas imagens",
"LK ","LKOut   ","Fluxo otico LK entre duas imagens sem outliers",
"LK ","VidLkOut","Fluxo otico LK entre quadros consecutivos sem outliers",

"OCV","TMatchG ","Template matching grayscale",
"OCV","TMatchC ","Template matching color",

"FOR","DogExtr ","Extremo de diferenca de gaussiana",
"FOR","CopyBk  ","Copia blocos aleatoriamente para testar oclusao parcial",

"SHP","shp2imb ","Shape para imgbin",

"TEX","glcm    ","Calcula graylevel co-occurrence matrix",

"","",""
};

//<<<<<<<<<<<<<<<<<<<<<< helpst 2 help <<<<<<<<<<<<<<<<<<<<<<<<<<<<

MATRIZ<string> help;

void helpst2help()
{ int nl=0; 
  while (helpst[3*nl]!="") nl++;

  help.resize(nl,3);
  for (int l=0; l<nl; l++) {
    help(l,0)=helpst[3*l+0];
    help(l,1)=helpst[3*l+1];
    help(l,2)=helpst[3*l+2];
  }
}

string about=
"< Recipiente KCEK.EXE. Cekeikon5+OpenCV2410. >\n"
"_______________________________________________________________________________\n";

string categorias=
"KCEK nome  - Programas de KCEK em ordem de nome\n"
"KCEK categ - Programas de KCEK em ordem de categoria\n"
"KCEK ARQ   - Manipulacao de arquivos\n"
"KCEK BGC   - Processamento de imagens grayscale e colorida\n"
"KCEK COR   - Processamento de imagens coloridas\n"
"KCEK GRY   - Processamento de imagens grayscale\n"
"KCEK BIN   - Processamento de imagens binarias\n"
"KCEK HOG   - Histogram of gradient\n"
"KCEK MLE   - Machine learning\n"
"KCEK SHW   - Mostra imagens na tela\n"
"KCEK VID   - Processamento de video\n"
"KCEK BCK   - Deteccao e subtracao de background\n"
"KCEK LK    - Tracking LK de objetos\n"
"KCEK OCV   - programas que chamam rotinas de opencv +- diretamente\n"
"KCEK FOR   - Forapro, Ciratefi e SIFT\n"
"KCEK SHP   - SHAPE\n"
"KCEK TEX   - Texture\n"
"Nota: Se nao couber na tela, use 'KCEK ARGUMENTOS | MORE'\n";

void swapl(MATRIZ<string>& a, int l1, int l2)
{ for (unsigned c=0; c<a.nc(); c++)
    swap(a(l1,c),a(l2,c));
}

int compara(MATRIZ<string>& a, int l, vector<string>& x)
{ for (unsigned c=0; c<a.nc(); c++)
    if (maiuscula(a(l,c))<maiuscula(x[c])) return -1;
    else if (maiuscula(a(l,c))>maiuscula(x[c])) return 1;
  return 0;
}

void copial(vector<string>& x, MATRIZ<string>& a, int l)
{ if (x.size()!=a.nc()) erro("Erro inesperado 3");
  for (unsigned c=0; c<x.size(); c++) x[c]=a(l,c);
}

// Ordena matriz, linha a linha, da linha l a r.
void quicksortl(MATRIZ<string>& a, int l, int r)
{ if (!(l<=r)) erro("Erro: deveria ter l<=r");
  vector<string> x(a.nc());
  int i=l; int j=r;
  copial(x,a,(l+r)/2);
  do {
    while (compara(a,i,x)<0) i++;
    while (compara(a,j,x)>0) j--;
    if (i<=j) { swapl(a,i,j); i++; j--; }
  } while (i<=j);
  if (l<j) quicksortl(a,l,j);
  if (i<r) quicksortl(a,i,r);
}

void imprimehelp(int ordena, string categ)
// ordena=-1 nao ordena
// ordena=0 categoria/nome
// ordena=1 nome/categoria
// categ="" imprime todos
// categ="GEN" imprime so programas da categoria GEN
{ if (ordena==0) quicksortl(help,0,help.nl()-1);
  else if (ordena==1) { 
    for (unsigned l=0; l<help.nl(); l++) swap(help(l,0),help(l,1));
    quicksortl(help,0,help.nl()-1);
    for (unsigned l=0; l<help.nl(); l++) swap(help(l,0),help(l,1));
  } else if (ordena==-1);
  else erro("Erro inesperado");

  cout << about;
  for (unsigned l=0; l<help.nl(); l++) {
    if (categ=="" || categ==help(l,0)) {
      printf("KCEK %-8s <%-3s> %-59s\n",help(l,1).c_str(),help(l,0).c_str(),help(l,2).c_str());
    }
  }
}

int main(int argc, char** argv)
{ int c1=centseg(); 
  if (argc<=1) {
    cout << about;
    cout << categorias;
    erro("Erro KCEK.EXE: Numero de argumentos invalido");
  } else {
    helpst2help();
    //for (int i=0; i<argc; i++) printf("%s ",argv[i]);
    //printf("\n");

    string comando=minuscula(argv[1]);
    if      (comando=="nome") imprimehelp(1,"");
    else if (comando=="categ") imprimehelp(0,"");
    else if (comando=="arq") imprimehelp(0,"ARQ");
    else if (comando=="bgc") imprimehelp(0,"BGC");
    else if (comando=="cor") imprimehelp(0,"COR");
    else if (comando=="gry") imprimehelp(0,"GRY");
    else if (comando=="bin") imprimehelp(0,"BIN");
    else if (comando=="hog") imprimehelp(0,"HOG");
    else if (comando=="mle") imprimehelp(0,"MLE");
    else if (comando=="shw") imprimehelp(0,"SHW");
    else if (comando=="vid") imprimehelp(0,"VID");
    else if (comando=="bck") imprimehelp(0,"BCK");
    else if (comando=="lk")  imprimehelp(0,"LK ");
    else if (comando=="ocv") imprimehelp(0,"OCV");
    else if (comando=="for") imprimehelp(0,"FOR");
    else if (comando=="shp") imprimehelp(0,"SHP");
    else if (comando=="tex") imprimehelp(0,"TEX");

    else if (comando=="version")  version(argc-1,&argv[1]);
    else if (comando=="arg")  arg(argc-1,&argv[1]);
    else if (comando=="renomeia") renomeia(argc-1,&argv[1]);
    else if (comando=="delpref") delpref(argc-1,&argv[1]);
    else if (comando=="minusc") minusc(argc-1,&argv[1]);
    else if (comando=="enumera") enumera(argc-1,&argv[1]);

    else if (comando=="mconvert") mconvert(argc-1,&argv[1]);

    else if (comando=="getquad")  getquad(argc-1,&argv[1]);
    else if (comando=="sobrmmc")  sobrmmc(argc-1,&argv[1]);
    else if (comando=="sobrepoe") sobrepoe(argc-1,&argv[1]);
    else if (comando=="alinha")   alinha(argc-1,&argv[1]);
    else if (comando=="smoothc")  smoothc(argc-1,&argv[1]);
    else if (comando=="colafund") colafund(argc-1,&argv[1]);
    else if (comando=="quebrac")  quebrac(argc-1,&argv[1]);
    else if (comando=="binariza") binariza(argc-1,&argv[1]);
    else if (comando=="minimoc")  minimoc(argc-1,&argv[1]);
    else if (comando=="cropc")    cropc(argc-1,&argv[1]);
    else if (comando=="canvasc")  canvasc(argc-1,&argv[1]);
    else if (comando=="zoomc")    zoomc(argc-1,&argv[1]);
    else if (comando=="projcor")  projcor(argc-1,&argv[1]);

    else if (comando=="normal01") normal01(argc-1,&argv[1]);
    else if (comando=="zoomg")    zoomg(argc-1,&argv[1]);
    else if (comando=="ruidospg") ruidospg(argc-1,&argv[1]);
    else if (comando=="brilcong") brilcong(argc-1,&argv[1]);
    else if (comando=="histeqg")  histeqg(argc-1,&argv[1]);
    else if (comando=="otsug")    otsug(argc-1,&argv[1]);
    else if (comando=="threshg")  threshg(argc-1,&argv[1]);
    else if (comando=="gradieng") gradieng(argc-1,&argv[1]);
    else if (comando=="houghgr")  houghgr(argc-1,&argv[1]);
    else if (comando=="distg")    distg(argc-1,&argv[1]);
    else if (comando=="mserg")    mserg(argc-1,&argv[1]);

    else if (comando=="houghb")   houghb(argc-1,&argv[1]);
    else if (comando=="houcirb")  houcirb(argc-1,&argv[1]);

    else if (comando=="pedestre") pedestre(argc-1,&argv[1]);
    else if (comando=="gerahog")  gerahog(argc-1,&argv[1]);
    else if (comando=="showhog")  showhog(argc-1,&argv[1]);
//     else if (comando=="classify") classify(argc-1,&argv[1]);

//     else if (comando=="boopred")  boopred(argc-1,&argv[1]);
//     else if (comando=="bootrain") bootrain(argc-1,&argv[1]);
//     else if (comando=="dtpred")   dtpred(argc-1,&argv[1]);
//     else if (comando=="dttrain")  dttrain(argc-1,&argv[1]);
//     else if (comando=="rndpred")  rndpred(argc-1,&argv[1]);
//     else if (comando=="rndtrain") rndtrain(argc-1,&argv[1]);
//     else if (comando=="svmpred")  svmpred(argc-1,&argv[1]);
//     else if (comando=="svmtrain") svmtrain(argc-1,&argv[1]);
    else if (comando=="segmenc")  segmenc(argc-1,&argv[1]);
    else if (comando=="pixelmap") pixelmap(argc-1,&argv[1]);
    else if (comando=="pixmappo") pixmappo(argc-1,&argv[1]);

    else if (comando=="mostrac")  mostrac(argc-1,&argv[1]);
    else if (comando=="mostrag")  mostrag(argc-1,&argv[1]);
    else if (comando=="mostraf")  mostraf(argc-1,&argv[1]);
    //else if (comando=="mostra1d") mostra1d(argc-1,&argv[1]);
    else if (comando=="mostrad")  mostrad(argc-1,&argv[1]);
    else if (comando=="mostrax")  mostrax(argc-1,&argv[1]);
    else if (comando=="campox")   campox(argc-1,&argv[1]);

    //else if (comando=="mostrav")  mostrav(argc-1,&argv[1]);
    else if (comando=="copyvid")  copyvid(argc-1,&argv[1]);
    else if (comando=="img2vid")  img2vid(argc-1,&argv[1]);
    else if (comando=="cam2vid")  cam2vid(argc-1,&argv[1]);
//     else if (comando=="captura")  captura(argc-1,&argv[1]);
    else if (comando=="camtest")  camtest(argc-1,&argv[1]);
    else if (comando=="cam2img")  cam2img(argc-1,&argv[1]);
    else if (comando=="webcam")   webcam(argc-1,&argv[1]);
    else if (comando=="reduzv")   reduzv(argc-1,&argv[1]);
    else if (comando=="vid2imc")  vid2imc(argc-1,&argv[1]);

    else if (comando=="difframe") difframe(argc-1,&argv[1]);
//     else if (comando=="findbk2")  findbk2(argc-1,&argv[1]);
//     else if (comando=="allbksub") allbksub(argc-1,&argv[1]);
//     else if (comando=="blocos")   blocos(argc-1,&argv[1]);
//     else if (comando=="allblobk") allblobk(argc-1,&argv[1]);

    else if (comando=="featureg") featureg(argc-1,&argv[1]);
    else if (comando=="lkflow")   lkflow(argc-1,&argv[1]);
    else if (comando=="lkout")    lkout(argc-1,&argv[1]);
//     else if (comando=="vidlkout") vidlkout(argc-1,&argv[1]);

    else if (comando=="tmatchg")  tmatchg(argc-1,&argv[1]);
    else if (comando=="tmatchc")  tmatchc(argc-1,&argv[1]);

    else if (comando=="dogextr")  dogextr(argc-1,&argv[1]);
    else if (comando=="copybk")   copybk(argc-1,&argv[1]);

    else if (comando=="shp2imb")  shp2imb(argc-1,&argv[1]);

    else if (comando=="glcm")     glcm(argc-1,&argv[1]);

    else erro("Erro KCEK.EXE: Programa inexistente ",comando.c_str());
  }
  int c=centseg()-c1;
  printf("Tempo gasto: %6.2f segundos\n\n",c/100.0);
}













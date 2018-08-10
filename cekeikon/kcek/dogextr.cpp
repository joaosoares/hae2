#include <cekeikon.h>

void dogextr(int argc, char** argv)
{ if (argc!=6 && argc!=7) {
    printf("DoGExtr: Difference of Gaussians extrema\n");
    printf("DoGExtr ent.pgm sai.pgm NEsc EscInic escOitava [limiar=0]\n");
    printf("  NEsc=#escalas(>=4) EscInic=escala inicial escOitava=#escalas por oitava\n");
    printf("  So picos acima de limiar e vales abaixo de -limiar sao mostrados\n");
    printf("  Ex: DoGExtr ent.pgm sai.ppm 9 1.0 3 0.1\n");
    erro("Erro: Numero de argumentos invalido");
  }

  int ns;
  if (sscanf(argv[3],"%d",&ns)!=1) erro("Erro: Leitura NEsc");
  if (ns<4) erro("Erro: NEsc<4");

  double scale;
  if (sscanf(argv[4],"%lf",&scale)!=1) erro("Erro: Leitura EscInic");
  if (scale<0.3) erro("Erro: EscInic<0.3");

  double escOitava;
  if (sscanf(argv[5],"%lf",&escOitava)!=1) erro("Erro: Leitura escOitava");
  if (escOitava<=0.0) erro("Erro: escOitava<=0.0");

  double limiar=0;
  if (argc==7) convArg(limiar,argv[6]);

  Mat_<GRY> g; le(g,argv[1]);
  Mat_<FLT> a; converte(g,a);
  int tam1[]={ns,a.rows,a.cols}; M3d_<FLT> f(3,tam1);
  vector<double> sca(ns);

  // double passo=exp(log(2.0)/escOitava); 
  double passo=pow(2.0,1.0/escOitava);

  Mat_<FLT> b;
  for (int s=0; s<ns; s++) {
    sca[s]=scale;
    GaussianBlur(a, b, Size(0,0), scale); 
    b.copyTo(fatia(f,s));  
    scale=scale*passo;
  }
//   cout << sca << endl;
//   impAvi(f,"espaco.avi");

  int tam2[]={ns-1,a.rows,a.cols}; M3d_<FLT> dog(3,tam2);
  for (int s=0; s<dog.size[0]; s++) {
    b = FLT(escOitava)*(fatia(f,s+1)-fatia(f,s));
    b.copyTo(fatia(dog,s));
  }
//   impAvi(dog,"dog.avi");

  Mat_<COR> sai; converte(g,sai);
  for (int s=1; s<dog.size[0]-1; s++)
    for (int l=1; l<dog.size[1]-1; l++)
      for (int c=1; c<dog.size[2]-1; c++) {
        double scale=sca[s];
        FLT valor=dog(s,l,c);

        bool omaior=true;
        for (int s2=-1; s2<=1; s2++)
          for (int l2=-1; l2<=1; l2++)
            for (int c2=-1; c2<=1; c2++)
              if (valor<dog(s+s2,l+l2,c+c2)) { omaior=false; goto sai1; }
        sai1:

        if (omaior==true && valor>limiar) {
          sai(l,c)=COR(0,0,255);
          circulo(sai,l,c,arredonda(scale*2),COR(0,0,255));
        } else {
          bool omenor=true;
          for (int s2=-1; s2<=1; s2++)
            for (int l2=-1; l2<=1; l2++)
              for (int c2=-1; c2<=1; c2++)
                if (valor>dog(s+s2,l+l2,c+c2)) { omenor=false; goto sai2; }
          sai2:
          if (omenor==true && valor<-limiar) {
            sai(l,c)=COR(0,255,0);
            circulo(sai,l,c,arredonda(scale*2),COR(0,255,0));
          }
        }
      }
  imp(sai,argv[2]);
}

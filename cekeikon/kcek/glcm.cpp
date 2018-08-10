#include <cekeikon.h>

Mat_<int> calculaGLCM(Mat_<GRY> ent, bool ignoraPreto, int dl, int dc)
{ Mat_<int> MC(256,256,0);
  IMG_<GRY> ente(ent,0,0);
  Vec2i delta(dl,dc);
  if (ignoraPreto==false) {
    for (int l=0; l<ent.rows-1; l++)
      for (int c=0; c<ent.cols-1; c++)
        MC(ente.atx(l,c),ente.atx(l+delta[0],c+delta[1]))++;
  } else {
    for (int l=0; l<ent.rows-1; l++)
      for (int c=0; c<ent.cols-1; c++)
        if (ente.atx(l,c)!=0 && ente.atx(l+delta[0],c+delta[1])!=0)
          MC(ente.atx(l,c),ente.atx(l+delta[0],c+delta[1]))++;
  }
  return MC;
}

Mat_<int> calculaGLCM4(Mat_<GRY> ori, bool ignoraPreto, int dl, int dc)
{ Mat_<GRY> ent=ori/4;

  Mat_<int> MC(256/4,256/4,0);
  IMG_<GRY> ente(ent,0,0);
  Vec2i delta(dl,dc);
  if (ignoraPreto==false) {
    for (int l=0; l<ent.rows-1; l++)
      for (int c=0; c<ent.cols-1; c++)
        MC(ente.atx(l,c),ente.atx(l+delta[0],c+delta[1]))++;
  } else {
    for (int l=0; l<ent.rows-1; l++)
      for (int c=0; c<ent.cols-1; c++)
        if (ente.atx(l,c)!=0 && ente.atx(l+delta[0],c+delta[1])!=0)
          MC(ente.atx(l,c),ente.atx(l+delta[0],c+delta[1]))++;
  }
  return MC;
}

Mat_<FLT> normalizaGLCM(Mat_<int> MC)
{ Mat_<FLT> mc(256,256,0.0);
  double soma=0.0;
  for (unsigned i=0; i<MC.total(); i++)
    soma += MC(i);
  for (unsigned i=0; i<MC.total(); i++)
    mc(i) = MC(i) / soma;
  return mc;
}

Mat_<FLT> normalizaGLCM4(Mat_<int> MC)
{ Mat_<FLT> mc(256/4,256/4,0.0);
  double soma=0.0;
  for (unsigned i=0; i<MC.total(); i++)
    soma += MC(i);
  for (unsigned i=0; i<MC.total(); i++)
    mc(i) = MC(i) / soma;
  return mc;
}

double fener(Mat_<FLT> mc)
{ double f=0.0;
  for (int l=0; l<mc.rows; l++)
    for (int c=0; c<mc.cols; c++)
      f += elev2(mc(l,c));
  return f;
}

double fent(Mat_<FLT> mc)
{ double f=0.0;
  for (int l=0; l<mc.rows; l++)
    for (int c=0; c<mc.cols; c++)
      if (mc(l,c)>0.0)
        f += mc(l,c) * log(mc(l,c));
  return -f;
}

double fcon(Mat_<FLT> mc)
{ double f=0.0;
  for (int l=0; l<mc.rows; l++)
    for (int c=0; c<mc.cols; c++)
      f += mc(l,c) * elev2(l-c);
  return f;
}

double mi_l(Mat_<FLT> mc)
{ double mi=0.0;
  for (int l=0; l<mc.rows; l++)
    for (int c=0; c<mc.cols; c++)
      mi += l * mc(l,c);
  return mi;
}

double mi_c(Mat_<FLT> mc)
{ double mi=0.0;
  for (int l=0; l<mc.rows; l++)
    for (int c=0; c<mc.cols; c++)
      mi += c * mc(l,c);
  return mi;
}

double var_l(Mat_<FLT> mc)
{ double mi=mi_l(mc);

  double f=0.0;  
  for (int l=0; l<mc.rows; l++)
    for (int c=0; c<mc.cols; c++)
      f += elev2(l-mi) * mc(l,c);
  return f;
}

double var_c(Mat_<FLT> mc)
{ double mi=mi_c(mc);

  double f=0.0;  
  for (int l=0; l<mc.rows; l++)
    for (int c=0; c<mc.cols; c++)
      f += elev2(c-mi) * mc(l,c);
  return f;
}

double fvar(Mat_<FLT> mc)
{ return var_l(mc); }

// Esta e' a definicao de [Ito]
// double fcorr(Mat_<FLT> mc)
// { double mil=mi_l(mc);
//   double mic=mi_c(mc);
//   double dl=sqrt(var_l(mc));
//   double dc=sqrt(var_c(mc));
//   double f=0.0;
//   for (int l=0; l<mc.rows; l++)
//     for (int c=0; c<mc.cols; c++)
//       f += ((l*c)*mc(l,c) - mil*mic)/(dl*dc);
//   return f;
// }

// Esta e' a definicao de [Barrera]
double fcorr(Mat_<FLT> mc)
{ double mil=mi_l(mc);
  double mic=mi_c(mc);
  double dl=sqrt(var_l(mc));
  double dc=sqrt(var_c(mc));
  double f=0.0;
  for (int l=0; l<mc.rows; l++)
    for (int c=0; c<mc.cols; c++)
      f += (mc(l,c)*(l-mil)*(c-mic))/(dl*dc);
  return f;
}

double fhom(Mat_<FLT> mc)
{ double f=0.0;
  for (int l=0; l<mc.rows; l++)
    for (int c=0; c<mc.cols; c++)
      f += mc(l,c) / (1 + elev2(l-c));
  return f;
}

void glcm(int argc, char** argv)
{ if (argc!=2 && argc!=3 && argc!=5) {
    printf("GLCM: Calcula graylevel co-occurrence matrix\n");
    printf("GLCM ent*.pgm [ignoraPreto] [dl dc]\n");
    printf("  ignoraPreto=T ou F. Default=F.\n");
    erro("Erro: Numero de argumentos invalido");
  }

  vector<string> vs;
  vsWildCard(argv[1],vs);

  bool ignoraPreto=false;
  if (argc>=3) {
    char ch=tolower(argv[2][0]);
    if (ch=='1' || ch=='t' || ch=='i') ignoraPreto=true;
    else if (ch=='0' || ch=='f' || ch=='n') ignoraPreto=false;
    else erro("Erro ignoraPreto");
  }

  int dl=1, dc=1;
  if (argc>=5) {
    convArg(dl,argv[3]);
    convArg(dc,argv[4]);
  }

  printf("%11s%11s%11s%11s%11s%11s%s\n","fener","fent","fcon","fvar","fcorr","fhom"," nomearq");
  for (unsigned i=0; i<vs.size(); i++) {
    Mat_<GRY> ent; le(ent,vs[i]);
    Mat_<int> MC=calculaGLCM(ent,ignoraPreto,dl,dc);
    Mat_<FLT> mc=normalizaGLCM(MC);
  
    Mat_<FLT> f(1,6);
    f(0)=fener(mc);
    f(1)=fent(mc);
    f(2)=fcon(mc);
    f(3)=fvar(mc);
    f(4)=fcorr(mc);
    f(5)=fhom(mc);
    for (int i=0; i<f.cols; i++)
      printf("% 11.2e",f(i));
    printf(" %s",vs[i].c_str());
    printf("\n");
  }
}

  
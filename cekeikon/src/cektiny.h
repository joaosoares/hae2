//cektiny.h
#include <cekeikon.h>
#include <tiny_dnn/tiny_dnn.h>
using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace tiny_dnn::layers;

void converte(const vec_t& v, Mat_<FLT>& m, int nl, int nc) {
  if (int(v.size())!=nl*nc) xerro1("Erro converte: Dimensoes nl nc invalidas");
  m.create(nl,nc);
  for (unsigned i=0; i<m.total(); i++) 
    m(i)=v[i];
}
  
void converte(const Mat_<FLT>& m, vec_t& v) {
  v.resize(m.total());
  for (unsigned i=0; i<m.total(); i++) {
    v[i]=m(i);
  }
}

void converte(const vec_t& v, Mat_<GRY>& m, int nl, int nc) {
  if (int(v.size())!=nl*nc) xerro1("Erro converte: Dimensoes nl nc invalidas");
  m.create(nl,nc);
  for (unsigned i=0; i<m.total(); i++) 
    m(i)=F2G(v[i]);
}
  
void converte(const Mat_<GRY>& m, vec_t& v) {
  v.resize(m.total());
  for (unsigned i=0; i<m.total(); i++) {
    v[i]=G2F(m(i));
  }
}

void converte(const vec_t& v, Mat_<COR>& m, int nl, int nc) {
  if (int(v.size())!=3*nl*nc) xerro1("Erro converte: Dimensoes nl nc invalidas");
  m.create(nl,nc);
  int j=0;
  for (int p=0; p<3; p++)
    for (unsigned i=0; i<m.total(); i++) 
      m(i)[2-p]=F2G(v[j++]);
}

void converte(const Mat_<COR>& m, vec_t& v) {
  v.resize(3*m.total());
  int j=0;
  for (int p=0; p<3; p++)
    for (unsigned i=0; i<m.total(); i++) 
      v[j++]=G2F(m(i)[2-p]);
}

void converte(const vec_t& v, Mat_<CORF>& m, int nl, int nc) {
  if (int(v.size())!=3*nl*nc) xerro1("Erro converte: Dimensoes nl nc invalidas");
  m.create(nl,nc);
  int j=0;
  for (int p=0; p<3; p++)
    for (unsigned i=0; i<m.total(); i++) 
      m(i)[2-p]=v[j++];
}

void converte(const Mat_<CORF>& m, vec_t& v) {
  v.resize(3*m.total());
  int j=0;
  for (int p=0; p<3; p++)
    for (unsigned i=0; i<m.total(); i++) 
      v[j++]=m(i)[2-p];
}

vec_t deslocaEsquerda(const vec_t& v, int nl, int nc, int ns) {
  //ns = numero de slices ou numero de espectros ou numero de cores
  //Neste momento, ns==1 ou ns==3
  if (v.size()!=unsigned(nl*nc*ns)) xerro1("Erro: Dimensao invalida");
  if (ns==3) {
    Mat_<CORF> f; converte(v,f,nl,nc);
    for (int c=0; c<f.cols-1; c++)
      for (int l=0; l<f.rows; l++)
        f(l,c)=f(l,c+1);
    vec_t w; converte(f,w);
    return w;
  } else if (ns==1) {
    Mat_<FLT> f; converte(v,f,nl,nc);
    for (int c=0; c<f.cols-1; c++)
      for (int l=0; l<f.rows; l++)
        f(l,c)=f(l,c+1);
    vec_t w; converte(f,w);
    return w;
  } else xerro1("Erro deslocaEsquerda: deve ter ns==1 ou ns==3");
}

vec_t deslocaDireita(const vec_t& v, int nl, int nc, int ns) {
  //ns = numero de slices ou numero de espectros ou numero de cores
  //Neste momento, ns==1 ou ns==3
  if (v.size()!=unsigned(nl*nc*ns)) xerro1("Erro: Dimensao invalida");
  if (ns==3) {
    Mat_<CORF> f; converte(v,f,nl,nc);
    for (int c=f.cols-1; c>0; c--)
      for (int l=0; l<f.rows; l++)
        f(l,c)=f(l,c-1);
    vec_t w; converte(f,w);
    return w;
  } else if (ns==1) {
    Mat_<FLT> f; converte(v,f,nl,nc);
    for (int c=f.cols-1; c>0; c--)
      for (int l=0; l<f.rows; l++)
        f(l,c)=f(l,c-1);
    vec_t w; converte(f,w);
    return w;
  } else xerro1("Erro deslocaDireita: deve ter ns==1 ou ns==3");
}

vec_t deslocaCima(const vec_t& v, int nl, int nc, int ns) {
  //ns = numero de slices ou numero de espectros ou numero de cores
  //Neste momento, ns==1 ou ns==3
  if (v.size()!=unsigned(nl*nc*ns)) xerro1("Erro: Dimensao invalida");
  if (ns==3) {
    Mat_<CORF> f; converte(v,f,nl,nc);
    for (int l=0; l<f.rows-1; l++)
      for (int c=0; c<f.cols; c++)
        f(l,c)=f(l+1,c);
    vec_t w; converte(f,w);
    return w;
  } else if (ns==1) {
    Mat_<FLT> f; converte(v,f,nl,nc);
    for (int l=0; l<f.rows-1; l++)
      for (int c=0; c<f.cols; c++)
        f(l,c)=f(l+1,c);
    vec_t w; converte(f,w);
    return w;
  } else xerro1("Erro deslocaCima: deve ter ns==1 ou ns==3");
}

vec_t deslocaBaixo(const vec_t& v, int nl, int nc, int ns) {
  //ns = numero de slices ou numero de espectros ou numero de cores
  //Neste momento, ns==1 ou ns==3
  if (v.size()!=unsigned(nl*nc*ns)) xerro1("Erro: Dimensao invalida");
  if (ns==3) {
    Mat_<CORF> f; converte(v,f,nl,nc);
    for (int l=f.rows-1; l>0; l--)
      for (int c=0; c<f.cols; c++)
        f(l,c)=f(l-1,c);
    vec_t w; converte(f,w);
    return w;
  } else if (ns==1) {
    Mat_<FLT> f; converte(v,f,nl,nc);
    for (int l=f.rows-1; l>0; l--)
      for (int c=0; c<f.cols; c++)
        f(l,c)=f(l-1,c);
    vec_t w; converte(f,w);
    return w;
  } else xerro1("Erro deslocaBaixo: deve ter ns==1 ou ns==3");
}

vec_t espelha(const vec_t& v, int nl, int nc, int ns) {
  //ns = numero de slices ou numero de espectros ou numero de cores
  //Neste momento, ns==1 ou ns==3
  if (v.size()!=unsigned(nl*nc*ns)) xerro1("Erro: Dimensao invalida");
  if (ns==3) {
    Mat_<CORF> f; converte(v,f,nl,nc);
    flip(f,f,1);
    vec_t w; converte(f,w);
    return w;
  } else if (ns==1) {
    Mat_<FLT> f; converte(v,f,nl,nc);
    flip(f,f,1);
    vec_t w; converte(f,w);
    return w;
  } else xerro1("Erro espelha: deve ter ns==1 ou ns==3");
}

void aumentaTreino(vector<vec_t>& timg, vector<label_t>& tlab, int nl, int nc, int ns, 
  bool bespelha=false, bool diagonais=false) {
  if (timg.size()!=tlab.size()) xerro1("Erro: Dimensoes diferentes timg e tlab");
  if (ns!=1 && ns!=3) xerro1("Erro aumentaTreino: deve ter ns==1 ou ns==3");

  if (bespelha) {
    unsigned tamanho=timg.size();
    for (unsigned i=0; i<tamanho; i++) {
      timg.push_back( espelha( timg[i],nl,nc,ns ) ); tlab.push_back( tlab[i] );
    }
  }

  unsigned tamanho=timg.size();
  for (unsigned i=0; i<tamanho; i++) {
    timg.push_back( deslocaEsquerda( timg[i],nl,nc,ns ) ); tlab.push_back( tlab[i] );
    timg.push_back( deslocaDireita(  timg[i],nl,nc,ns ) ); tlab.push_back( tlab[i] );
    timg.push_back( deslocaCima( timg[i],nl,nc,ns ) );     tlab.push_back( tlab[i] );
    timg.push_back( deslocaBaixo(  timg[i],nl,nc,ns ) );   tlab.push_back( tlab[i] );
  }

  if (diagonais) {
    unsigned tamanho=timg.size();
    for (unsigned i=0; i<tamanho; i++) {
      timg.push_back( deslocaCima( deslocaEsquerda( timg[i],nl,nc,ns ), nl,nc,ns) ); 
      tlab.push_back( tlab[i] );
      timg.push_back( deslocaCima( deslocaDireita(  timg[i],nl,nc,ns ), nl,nc,ns) ); 
      tlab.push_back( tlab[i] );
      timg.push_back( deslocaBaixo( deslocaEsquerda( timg[i],nl,nc,ns ), nl,nc,ns) ); 
      tlab.push_back( tlab[i] );
      timg.push_back( deslocaBaixo( deslocaDireita(  timg[i],nl,nc,ns ), nl,nc,ns) ); 
      tlab.push_back( tlab[i] );
    }
  }
}
  

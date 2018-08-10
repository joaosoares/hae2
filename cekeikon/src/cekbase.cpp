#include "cekeikon.h"

namespace cek {

//<<<<<<<<<<<<<< Funcoes de string e char[] <<<<<<<<<<<<<<<<<<<<<<<<
string minuscula(string st)
{ for (unsigned i=0; i<st.length(); i++)
    st[i]=tolower(st[i]);
  return st;
}

string maiuscula(string st)
{ for (unsigned i=0; i<st.length(); i++)
    st[i]=toupper(st[i]);
  return st;
}

//<<<<<<<<<<<<<< Funcoes matematicas simples <<<<<<<<<<<<<<<<<<<<<<<
CPX ret2pol(CPX a) { return CPX(abs(a),arg(a)); }
CPX pol2ret(CPX a) { return polar(real(a),imag(a)); }
CPXD ret2pol(CPXD a) { return CPXD(abs(a),arg(a)); } 
CPXD pol2ret(CPXD a) { return polar(real(a),imag(a)); }

//<<<<< Funcoes relacionadas com normal/gaussiana <<<<<<<<<<
double normal(double r, double desvio) // Funcao gaussiana 1D
{ double r2=r*r;
  double v=desvio*desvio;
  const double sqrt2pi=sqrt(2*M_PI);
  return (1/(sqrt2pi*desvio)) * exp(-r2/(2*v));
}

double dxnormal(double r, double desvio) // Primeira derivada da normal 1D
{ const double sqrt2pi=sqrt(2*M_PI);
  double v=desvio*desvio;
  return -r/(desvio*v*sqrt2pi) * exp(-r*r/(2*v));
}

double dxxnormal(double r, double desvio) // Segunda derivada da normal 1D
{ const double sqrt2pi=sqrt(2*M_PI);
  double v=desvio*desvio;
  return (r*r - v) / (v*v*desvio*sqrt2pi) * exp(-r*r/(2*v));
}

double binormal(double r, double desvio) // Funcao gaussiana 2D
{ double r2=r*r;
  double v=desvio*desvio;
  return (1/(2*M_PI*v)) * exp(-r2/(2*v));
}

double grxbinormal(double x, double y, double desvio) // Gradiente x da gaussiana 2D
{ double v=desvio*desvio;
  double r2=x*x+y*y;
  double cx=(-x)/(2*M_PI*v*v) * exp(-r2/(2*v));
  return cx;
}

double grybinormal(double x, double y, double desvio) // Gradiente y da gaussiana 2D
{ double v=desvio*desvio;
  double r2=x*x+y*y;
  double cy=(-y)/(2*M_PI*v*v) * exp(-r2/(2*v));
  return cy;
}

double lapnormal(double r, double desvio) // Laplace da gaussiana 2D
{ double r2=r*r;
  double v=desvio*desvio;
  return ( r2/(2*M_PI*v*v*v) - 1/(M_PI*v*v) ) * exp(-r2/(2*v));
}

double normalsqr(double r2, double desvio) // Funcao gaussiana 1D com parametro r^2
{ double v=desvio*desvio;
  const double sqrt2pi=sqrt(2*M_PI);
  return (1/(sqrt2pi*desvio)) * exp(-r2/(2*v));
}

double binormalsqr(double r2, double desvio) // Funcao gaussiana 2D com parametro r^2
{ double v=desvio*desvio;
  return (1/(2*M_PI*v)) * exp(-r2/(2*v));
}

double lapbinormalsqr(double r2, double desvio) // Laplace da gaussiana 2D com parametro r^2
{ double v=desvio*desvio;
  return ( r2/(2*M_PI*v*v*v) - 1/(M_PI*v*v) ) * exp(-r2/(2*v));
}

//<<<<<<<<<<<<<<<<<<<< Leitura de arquivo <<<<<<<<<<<<<<<<<<<<<<<<<<<
// Nota: Sempre devolvia caracteres minuscula. Mudei para devolver
// maiusculas e minusculas

int leChar(FILE* arq)
{ int c=fgetc(arq);
  if (c==26) c=EOF;
  //if (c!=EOF) c=tolower(c);
  return c;
}

bool separador(int c)
{ if (c==',' || c==';' || c==' ' || c=='\t' || c=='\n' || c=='\r' || 
      c=='(' || c==')' || c=='=')
    return true;
  else
    return false;
}

bool ident(int c)
{ if ( ('a'<=c && c<='z') || ('A'<=c && c<='Z') || ('0'<=c && c<='9')
       || c=='+' || c=='-' || c=='.' || c=='_') return true;
  else return false;
}

// Comentarios podem vir:
// (1) Com //
// (2) Com /* */
// (3) Com #
string leStr(FILE* arq)
{ string st; int c;

  c=leChar(arq);
  LAB1:
    if (c==EOF) { st="eof"; goto FIM; }
    else if (separador(c)) { c=leChar(arq); goto LAB1; }
    else if (ident(c)) { st=c; c=leChar(arq); goto LAB2; }
    else if (c=='/') { c=leChar(arq); goto LAB3; }
    else if (c=='#') { c=leChar(arq); goto LAB4; }
    else { st="erro"; goto FIM; }
  LAB2:
    if (c==EOF || separador(c)) { goto FIM; }
    else if (ident(c)) { st+=c; c=leChar(arq); goto LAB2; }
    else { st="erro"; goto FIM; }
  LAB3:
    if (c=='/') { c=leChar(arq); goto LAB4; }
    else if (c=='*') { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB4:
    if (c=='\n') { c=leChar(arq); goto LAB1; }
    else if (c==EOF) { st="eof"; goto FIM; }
    else { c=leChar(arq); goto LAB4; }
  LAB5:
    if (c=='*') { c=leChar(arq); goto LAB6; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB6:
    if (c=='/') { c=leChar(arq); goto LAB1; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  FIM:
    return st;
}

bool separadorFileName(int c)
{ if (c==' ' || c=='\t' || c=='\n' || c=='\r' || c==',' || c==';')
    return true;
  else
    return false;
}

bool identFileName(int c)
{ if ( ('a'<=c && c<='z') || ('A'<=c && c<='Z') || ('0'<=c && c<='9')
       || c=='_' || c=='-' || c=='.' || c==':' || c=='\\' || c=='/' || c=='@' || c=='+') 
    return true;
  else return false;
}

// Comentarios podem vir:
// (1) Com //
// (2) Com /* */
// (3) Com #
string leFileName(FILE* arq)
{ string st; int c;

  c=leChar(arq);
  LAB1:
    if (c==EOF) { st="eof"; goto FIM; }
    else if (separadorFileName(c)) { c=leChar(arq); goto LAB1; }
    else if (identFileName(c)) { st=c; c=leChar(arq); goto LAB2; }
    else if (c=='/') { c=leChar(arq); goto LAB3; }
    else if (c=='#') { c=leChar(arq); goto LAB4; }
    else { st="erro"; goto FIM; }
  LAB2:
    if (c==EOF || separadorFileName(c)) { goto FIM; }
    else if (identFileName(c)) { st+=c; c=leChar(arq); goto LAB2; }
    else { st="erro"; goto FIM; }
  LAB3:
    if (c=='/') { c=leChar(arq); goto LAB4; }
    else if (c=='*') { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB4:
    if (c=='\n') { c=leChar(arq); goto LAB1; }
    else if (c==EOF) { st="eof"; goto FIM; }
    else { c=leChar(arq); goto LAB4; }
  LAB5:
    if (c=='*') { c=leChar(arq); goto LAB6; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB6:
    if (c=='/') { c=leChar(arq); goto LAB1; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  FIM:
    return st;
}

void leNum(FILE* arq, BYTE& b)
{ string st=leStr(arq);
  int i;
  if (sscanf(st.c_str(),"%d",&i)!=1) erro("leNum(BYTE)");
  if (i<0) b=0;
  else if (i>255) b=255;
  else b=i;
}

void leNumIgnEOF(FILE* arq, int& i)
{ string st=leStr(arq);
  if (st=="eof") { i=minint; return; }
  if (sscanf(st.c_str(),"%d",&i)!=1) erro("leNum(int)");
}

void leNum(FILE* arq, int& i)
{ string st=leStr(arq);
  if (sscanf(st.c_str(),"%d",&i)!=1) erro("leNum(int)");
}

void leNum(FILE* arq, SHT& s)
{ string st=leStr(arq);
  if (st=="max" || st=="m" || st=="+max" || st=="maxsht" || st=="+m") {
    s=maxsht; return;
  }
  if (st=="-max" || st=="-m" || st=="min" || st=="minsht" || st==".") {
    s=minsht; return;
  }
  int i;
  if (sscanf(st.c_str(),"%d",&i)!=1) erro("leNum(SHT)");
  s=i;
}

void leNum(FILE* arq, FLT& f)
{ string st=leStr(arq);
  if (st=="max" || st=="m" || st=="+max" || st=="infinito" || st=="+m") {
    f=infinito; return;
  }
  if (st=="-max" || st=="-m" || st=="min" || st=="-infinito" || st==".") {
    f=-infinito; return;
  }
  double d;
  if (sscanf(st.c_str(),"%lf",&d)!=1) erro("leNum(FLT)");
  f=d;
}

void leNum(FILE* arq, DBL& d)
{ string st=leStr(arq);
  if (st=="max" || st=="m" || st=="+max" || st=="infinito" || st=="+m") {
    d=infinito; return;
  }
  if (st=="-max" || st=="-m" || st=="min" || st=="-infinito" || st==".") {
    d=-infinito; return;
  }
  if (sscanf(st.c_str(),"%lf",&d)!=1) erro("leNum(double)");
}

void leNum(FILE* arq, bool& b)
{ string st=leStr(arq);
  if (st=="true" || st=="1" || st=="t" || st=="v" || st=="x") b=true;
  else if (st=="false" || st=="0" || st=="f" || st==".") b=false;
  else erro("leNum(bool)");
}

string leStrBool(FILE* arq)
{ string st; int c;

  c=leChar(arq);
  LAB1:
    if (c==EOF) { st="eof"; goto FIM; }
    else if (separador(c)) { c=leChar(arq); goto LAB1; }
    else if (ident(c)) { st=c; goto FIM; }
    else if (c=='/') { c=leChar(arq); goto LAB3; }
    else if (c=='#') { c=leChar(arq); goto LAB4; }
    else { st="erro"; goto FIM; }
  LAB3:
    if (c=='/') { c=leChar(arq); goto LAB4; }
    else if (c=='*') { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB4:
    if (c=='\n') { c=leChar(arq); goto LAB1; }
    else if (c==EOF) { st="eof"; goto FIM; }
    else { c=leChar(arq); goto LAB4; }
  LAB5:
    if (c=='*') { c=leChar(arq); goto LAB6; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB6:
    if (c=='/') { c=leChar(arq); goto LAB1; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  FIM:
    return st;
}

void leBool(FILE* arq, bool& b)
{ string st=leStrBool(arq);
  if (st=="1" || st=="t" || st=="v" || st=="x") b=true;
  else if (st=="0" || st=="f" || st==".") b=false;
  else erro("Erro: leBool ",st.c_str());
}

//<<<<<<<<<<<<<<<<<<<< Leitura de ISTR <<<<<<<<<<<<<<<<<<<<<<<<<<<
// Nota: Sempre devolve caracteres minuscula

void ISTR::arg2str(int argc, char** argv)
{ if (argc<=0) { st=""; return; }
  st=argv[0];
  for (int i=1; i<argc; i++) st=st+" "+argv[i];
  pos=0;
}

ISTR::ISTR(int argc, char** argv) // converte todos os argv para st. Ex: ISTR(argc-1,argv[1]).
{ pos=0; arg2str(argc,argv); } 

ISTR::ISTR(char* argv) // Converte um argv para st. Ex: ISTR(argv[3]); 
{ pos=0; st=argv; } 

ISTR::ISTR(string argv) 
{ pos=0; st=argv; } 

int leChar(ISTR& arq)
{ int c;
  if (int(arq.st.size())<=arq.pos) c=EOF;
  //else c=tolower(arq.st[arq.pos++]);
  else c=arq.st[arq.pos++];
  return c;
}

// Comentarios podem vir:
// (1) Com //
// (2) Com /* */
// (3) Com #
string leStr(ISTR& arq)
{ string st; int c;

  c=leChar(arq);
  LAB1:
    if (c==EOF) { st="eof"; goto FIM; }
    else if (separador(c)) { c=leChar(arq); goto LAB1; }
    else if (ident(c)) { st=c; c=leChar(arq); goto LAB2; }
    else if (c=='/') { c=leChar(arq); goto LAB3; }
    else if (c=='#') { c=leChar(arq); goto LAB4; }
    else { st="erro"; goto FIM; }
  LAB2:
    if (c==EOF || separador(c)) { goto FIM; }
    else if (ident(c)) { st+=c; c=leChar(arq); goto LAB2; }
    else { st="erro"; goto FIM; }
  LAB3:
    if (c=='/') { c=leChar(arq); goto LAB4; }
    else if (c=='*') { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB4:
    if (c=='\n') { c=leChar(arq); goto LAB1; }
    else if (c==EOF) { st="eof"; goto FIM; }
    else { c=leChar(arq); goto LAB4; }
  LAB5:
    if (c=='*') { c=leChar(arq); goto LAB6; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB6:
    if (c=='/') { c=leChar(arq); goto LAB1; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  FIM:
    return st;
}

// Comentarios podem vir:
// (1) Com //
// (2) Com /* */
// (3) Com #
string leFileName(ISTR& arq)
{ string st; int c;

  c=leChar(arq);
  LAB1:
    if (c==EOF) { st="eof"; goto FIM; }
    else if (separadorFileName(c)) { c=leChar(arq); goto LAB1; }
    else if (identFileName(c)) { st=c; c=leChar(arq); goto LAB2; }
    else if (c=='/') { c=leChar(arq); goto LAB3; }
    else if (c=='#') { c=leChar(arq); goto LAB4; }
    else { st="erro"; goto FIM; }
  LAB2:
    if (c==EOF || separadorFileName(c)) { goto FIM; }
    else if (identFileName(c)) { st+=c; c=leChar(arq); goto LAB2; }
    else { st="erro"; goto FIM; }
  LAB3:
    if (c=='/') { c=leChar(arq); goto LAB4; }
    else if (c=='*') { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB4:
    if (c=='\n') { c=leChar(arq); goto LAB1; }
    else if (c==EOF) { st="eof"; goto FIM; }
    else { c=leChar(arq); goto LAB4; }
  LAB5:
    if (c=='*') { c=leChar(arq); goto LAB6; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB6:
    if (c=='/') { c=leChar(arq); goto LAB1; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  FIM:
    return st;
}

void leNum(ISTR& arq, BYTE& b)
{ string st=leStr(arq);
  int i;
  if (sscanf(st.c_str(),"%d",&i)!=1) erro("leNum(BYTE)");
  if (i<0) b=0;
  else if (i>255) b=255;
  else b=i;
}

void leNumIgnEOF(ISTR& arq, int& i)
{ string st=leStr(arq);
  if (st=="eof") { i=minint; return; }
  if (sscanf(st.c_str(),"%d",&i)!=1) erro("leNum(int)");
}

void leNum(ISTR& arq, int& i)
{ string st=leStr(arq);
  if (sscanf(st.c_str(),"%d",&i)!=1) erro("leNum(int)");
}

void leNum(ISTR& arq, SHT& s)
{ string st=leStr(arq);
  if (st=="max" || st=="m" || st=="+max" || st=="maxsht" || st=="+m") {
    s=maxsht; return;
  }
  if (st=="-max" || st=="-m" || st=="min" || st=="minsht" || st==".") {
    s=minsht; return;
  }
  int i;
  if (sscanf(st.c_str(),"%d",&i)!=1) erro("leNum(SHT)");
  s=i;
}

void leNum(ISTR& arq, FLT& f)
{ string st=leStr(arq);
  if (st=="max" || st=="m" || st=="+max" || st=="infinito" || st=="+m") {
    f=infinito; return;
  }
  if (st=="-max" || st=="-m" || st=="min" || st=="-infinito" || st==".") {
    f=-infinito; return;
  }
  double d;
  if (sscanf(st.c_str(),"%lf",&d)!=1) erro("leNum(FLT)");
  f=d;
}

void leNum(ISTR& arq, DBL& d)
{ string st=leStr(arq);
  if (st=="max" || st=="m" || st=="+max" || st=="infinito" || st=="+m") {
    d=infinito; return;
  }
  if (st=="-max" || st=="-m" || st=="min" || st=="-infinito" || st==".") {
    d=-infinito; return;
  }
  if (sscanf(st.c_str(),"%lf",&d)!=1) erro("leNum(double)");
}

void leNum(ISTR& arq, bool& b)
{ string st=leStr(arq);
  if (st=="true" || st=="1" || st=="t" || st=="v" || st=="x") b=true;
  else if (st=="false" || st=="0" || st=="f" || st==".") b=false;
  else erro("leNum(bool)");
}

string leStrBool(ISTR& arq)
{ string st; int c;

  c=leChar(arq);
  LAB1:
    if (c==EOF) { st="eof"; goto FIM; }
    else if (separador(c)) { c=leChar(arq); goto LAB1; }
    else if (ident(c)) { st=c; goto FIM; }
    else if (c=='/') { c=leChar(arq); goto LAB3; }
    else if (c=='#') { c=leChar(arq); goto LAB4; }
    else { st="erro"; goto FIM; }
  LAB3:
    if (c=='/') { c=leChar(arq); goto LAB4; }
    else if (c=='*') { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB4:
    if (c=='\n') { c=leChar(arq); goto LAB1; }
    else if (c==EOF) { st="eof"; goto FIM; }
    else { c=leChar(arq); goto LAB4; }
  LAB5:
    if (c=='*') { c=leChar(arq); goto LAB6; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  LAB6:
    if (c=='/') { c=leChar(arq); goto LAB1; }
    else if (c!=EOF) { c=leChar(arq); goto LAB5; }
    else { st="erro"; goto FIM; }
  FIM:
    return st;
}

void leBool(ISTR& arq, bool& b)
{ string st=leStrBool(arq);
  if (st=="1" || st=="t" || st=="v" || st=="x") b=true;
  else if (st=="0" || st=="f" || st==".") b=false;
  else erro("Erro: leBool ",st.c_str());
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
bool seekArg(ISTR& arq, string nome)
{ int inicio=0; arq.pos=0;
  string st=leStr(arq);
  while (st!="eof" && st!=nome) { inicio=arq.pos; st=leStr(arq); }
  if (st=="eof") return false; // Nao achou nome
  arq.st.erase(inicio,arq.pos-inicio); // apaga "nome"
  return true;
}

bool seekArg(ISTR& arq, string nome, BYTE& b)
{ int inicio=0; arq.pos=0;
  string st=leStr(arq);
  while (st!="eof" && st!=nome) { inicio=arq.pos; st=leStr(arq); }
  if (st=="eof") return false; // Nao achou nome
  leNum(arq,b);
  arq.st.erase(inicio,arq.pos-inicio); // apaga "nome=b"
  return true;
}

bool seekArg(ISTR& arq, string nome, int& i)
{ int inicio=0; arq.pos=0;
  string st=leStr(arq);
  while (st!="eof" && st!=nome) { inicio=arq.pos; st=leStr(arq); }
  if (st=="eof") return false; // Nao achou nome
  leNum(arq,i);
  arq.st.erase(inicio,arq.pos-inicio); // apaga "nome=b"
  return true;
}

bool seekArg(ISTR& arq, string nome, SHT& s)
{ int inicio=0; arq.pos=0;
  string st=leStr(arq);
  while (st!="eof" && st!=nome) { inicio=arq.pos; st=leStr(arq); }
  if (st=="eof") return false; // Nao achou nome
  leNum(arq,s);
  arq.st.erase(inicio,arq.pos-inicio); // apaga "nome=b"
  return true;
}

bool seekArg(ISTR& arq, string nome, FLT& f)
{ int inicio=0; arq.pos=0;
  string st=leStr(arq);
  while (st!="eof" && st!=nome) { inicio=arq.pos; st=leStr(arq); }
  if (st=="eof") return false; // Nao achou nome
  leNum(arq,f);
  arq.st.erase(inicio,arq.pos-inicio); // apaga "nome=b"
  return true;
}

bool seekArg(ISTR& arq, string nome, DBL& d)
{ int inicio=0; arq.pos=0;
  string st=leStr(arq);
  while (st!="eof" && st!=nome) { inicio=arq.pos; st=leStr(arq); }
  if (st=="eof") return false; // Nao achou nome
  leNum(arq,d);
  arq.st.erase(inicio,arq.pos-inicio); // apaga "nome=b"
  return true;
}

bool seekArg(ISTR& arq, string nome, bool& b)
{ int inicio=0; arq.pos=0;
  string st=leStr(arq);
  while (st!="eof" && st!=nome) { inicio=arq.pos; st=leStr(arq); }
  if (st=="eof") return false; // Nao achou nome
  leNum(arq,b);
  arq.st.erase(inicio,arq.pos-inicio); // apaga "nome=b"
  return true;
}

bool seekArg(ISTR& arq, string nome, string& st2)
{ int inicio=0; arq.pos=0;
  string st=leStr(arq);
  while (st!="eof" && st!=nome) { inicio=arq.pos; st=leStr(arq); }
  if (st=="eof") return false; // Nao achou nome
  st2=leStr(arq);
  arq.st.erase(inicio,arq.pos-inicio); // apaga "nome=b"
  return true;
}

bool seekFileName(ISTR& arq, string nome, string& st2)
{ int inicio=0; arq.pos=0;
  string st=leStr(arq);
  while (st!="eof" && st!=nome) { inicio=arq.pos; st=leStr(arq); }
  if (st=="eof") return false; // Nao achou nome
  st2=leFileName(arq);
  arq.st.erase(inicio,arq.pos-inicio); // apaga "nome=b"
  return true;
}

bool seekFim(ISTR& arq)
{ arq.pos=0;
  string st=leStr(arq);
  if (st=="eof") return true;
  return false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<< ArgVS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void ArgVS::arg2vs(int argc, char** argv) {
  for (int i=0; i<argc; i++) {
    string st=argv[i];
    vs.push_back(st);
  } 
  if (expandeRun) {
    for (int i=1; i<argc; i++) {
      string run;
      if ( vs[i].find("-run=")==0 ) run=vs[i].substr(5);
      if ( vs[i][0]=='`') {
        if (vs[i][ vs[i].length()-1 ]!='`') 
          erro("Error: Enclose argument \"`...`\"");
        run=vs[i].substr(1, vs[i].length()-2);
      }
      if (run!="") { 
        //cout << "run=" << run << endl;
        run += " > _util_edvar.txt";
        system(run.c_str());
        string st = leArq("_util_edvar.txt");
        vs[i]=st;
      }
    }
  }
}

void ArgVS::imp() {
  for (unsigned i=0; i<vs.size(); i++) {
    cout << i << " " << vs[i] << endl;
  }
  cout << endl;
}

//<<<<<<<<<<<<<<<<<<<< Leitura de ArgStr <<<<<<<<<<<<<<<<<<<<<<<<<<<
void ArgComando::converteSt(string& st) {
  for (unsigned i=0; i<st.length(); i++) {
    char& ch=st[i];
    if (exclamacao2porcentagem && ch=='!') ch='%';
    if (apostrofe2aspas && ch=='\'') ch='"';
  }
}

Comando ArgComando::separaComando(const string& st) {
  Comando comando{"","",false};
  if (st!="") {
    if (st.find_first_of(indicadorComando)==0) { // aparece '-' na posicao zero
      size_t i=st.find_first_of(separador);
      if (i==string::npos) { // nao ha separador
        comando.first=st;
      } else { // separador na posicao i
        comando.first=st.substr(0,i);
        comando.second=st.substr(i+1);
      }
    } else { // nao aparece '-' na posicao zero. Usa 2 numeros: 00, 01, etc
      char vet[8];
      sprintf(vet,"%02d",nameless++);
      comando.first=string(vet);
      comando.second=st;
    }
  }
  return comando;
}

void ArgComando::arg2comando(int argc, char** argv) {
  if (expandeRun) {
    ArgVS vs(argc,argv,true);
    vs2comando(vs);
  } else {
    for (int i=1; i<argc; i++) {
      string st=argv[i];
      converteSt(st);
      Comando comando=separaComando(st);
      vs.push_back(comando);
    } 
  }
}

void ArgComando::vs2comando(const ArgVS& arg) {
  for (int i=1; i<int(arg.vs.size()); i++) {
    string st=arg.vs[i];
    converteSt(st);
    Comando comando=separaComando(st);
    vs.push_back(comando);
  } 
}

void ArgComando::imp() {
  for (unsigned i=0; i<vs.size(); i++) {
    cout << vs[i].first << " = " << vs[i].second << endl;
  }
  cout << endl;
}

int ArgComando::procura(const string& nome1, const string& nome2) {
  int i;
  for (i=0; i<int(vs.size()); i++) 
    if (vs[i].first==nome1 || vs[i].first==nome2) {
      break;  
    }
  if (i==int(vs.size())) i=-1;
  else vs[i].chequei=true;
  return i;
}

bool ArgComando::getBool(const string& nome1, const string& nome2, bool def) { 
  int pos=procura(nome1,nome2);
  if (pos<0) return def;

  bool b=true;
  string st=maiuscula(vs[pos].second);
  //if (st=="FALSE") b=false;
  //else if (st=="TRUE") b=true;
  //else b=true;
  if (st=="FALSE") b=false;
  else if (st=="TRUE") b=true;
  else if (st=="") b=true;
  else erro("Erro: Booleano "+vs[pos].first+" deve ser true ou false");
  return b;
}

int ArgComando::getInt(const string& nome1, const string& nome2, int def) {
  int pos=procura(nome1,nome2);
  if (pos<0) return def;
  int sai;
  if (sscanf(vs[pos].second.c_str(),"%d",&sai)!=1) 
    erro("Error: Integer conversion "+vs[pos].first);
  return sai;
}

double ArgComando::getDouble(const string& nome1, const string& nome2, double def) {
  int pos=procura(nome1,nome2);
  if (pos<0) return def;
  double sai;
  if (sscanf(vs[pos].second.c_str(),"%lf",&sai)!=1) 
    erro("Error: Double conversion "+vs[pos].first);
  return sai;
}

string ArgComando::getString(const string& nome1, const string& nome2, string def) {
  int pos=procura(nome1,nome2);
  if (pos<0) return def;
  return vs[pos].second;
}

string ArgComando::getCommand(int indice) {
  char cstr[16];
  sprintf(cstr,"%02d",indice);
  int pos=procura(string(cstr));
  if (pos<0) erro("Error: There is no command #"+string(cstr));
  return vs[pos].second;
}

void ArgComando::leuTodos() {
  for (int i=0; i<int(vs.size()); i++) {
    if (vs[i].chequei==false) 
      erro("Error: Invalid extra command "+vs[i].first+" "+vs[i].second);
  }
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<< DATAHORA <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
bool bissexto(int y)
{ return (y%4 == 0 && y%100 != 0) || (y%400 == 0); }

int diasDoMes(DATAHORA h)
// Retorna quantos dias tem um mes, dados mes/ano.
{
  static int diasdomesbissexto[]={0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  static int diasdomesnormal[]  ={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (h.mes<1 || 12<h.mes) erro("Erro: Mes inexistente");

  if (bissexto(h.ano)) return diasdomesbissexto[h.mes];
  else return diasdomesnormal[h.mes];
}

bool existeDataHora(DATAHORA h)
// Testa se data/hora e' valido
{ bool existe=true; int dm;
  if (h.ano<1900 || 3000<h.ano) { existe=false; goto fim; }
  if (h.mes<1 || 12<h.mes) { existe=false; goto fim; }
  dm=diasDoMes(h);
  if (h.dia<1 || dm<h.dia) { existe=false; goto fim; }
  if (h.hor<0 || 23<h.hor) { existe=false; goto fim; }
  if (h.min<0 || 59<h.min) { existe=false; goto fim; }
  if (h.seg<0 || 59<h.seg) { existe=false; goto fim; }
  fim: return existe;
}

void imp(DATAHORA h)
{ printf("%04d-%02d-%02d %02d:%02d:%02d\n",h.ano,h.mes,h.dia,h.hor,h.min,h.seg);
}

DATAHORA somaUmDia(DATAHORA h)
// Soma um dia a h
{ DATAHORA d=h;
  d.dia++;
  if (d.dia>diasDoMes(h)) {
    d.dia=1; d.mes++;
    if (d.mes>12) {
      d.mes=1; d.ano++;
    }
  }
  return d;
}

DATAHORA somaSeg(DATAHORA h, int s)
// Soma s segundos a h
{ h.seg=h.seg+s;
  int vai;
  vai=quociente(h.seg,60); h.seg=modulo(h.seg,60); h.min=h.min+vai;
  vai=quociente(h.min,60); h.min=modulo(h.min,60); h.hor=h.hor+vai;
  vai=quociente(h.hor,24); h.hor=modulo(h.hor,24);

  for (int i=0; i<vai; i++) h=somaUmDia(h);
  return h;
}

void hmscs(int k, int& h, int& m, int& s, int& cs)
// Converte centesimos de segundos em hh:mm:ss:cc
{ cs=modulo(k,100); k=quociente(k,100);
  s=modulo(k,60); k=quociente(k,60);
  m=modulo(k,60); k=quociente(k,60);
  h=k;
}

string leArq(string nome) {
  ifstream ent(nome);
  string linha, arquivo;
  while (!ent.eof()) {
    getline(ent,linha);
    arquivo = arquivo + " " + linha;
  }
  return arquivo;
}

} // namespace cek



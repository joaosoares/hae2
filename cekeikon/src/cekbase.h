#ifndef __CEKBASE__
#define __CEKBASE__

#include <complex>
#include <cctype>
#include <cstring>
#include <vector>
#include <set>

#include "cekessen.h"

#ifndef M_PI
  #define M_PI 3.1415926535897932384626433832795
#endif

#ifndef M_PI_2
  #define M_PI_2 1.57079632679489661923
#endif

#ifndef M_LN2
  #define M_LN2 0.69314718055994530941723212145818
#endif

//Outra opcao para VC:
//#define _USE_MATH_DEFINES
//#include <cmath>

#define M_2PI 6.283185307179586476925286766559

namespace cek {
using namespace std;
using namespace cv;

//<<<<<<<<<<<<<<<<<<<< Definicao dos tipos <<<<<<<<<<<<<<<<<<<<<<<<<<
typedef complex<FLT> CPX;
typedef complex<DBL> CPXD;

//<<<<<<<<<<<<<< Funcoes de string e c_string <<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA string minuscula(string st);
EXPORTA string maiuscula(string st);

//<<<<<<<<<<<<<< Funcoes matematicas simples <<<<<<<<<<<<<<<<<<<<<<<
// Por algum motivo, nao funciona!
//template<class T>
//T elev2(T x) { return x*x; }

inline double elev2(double x) { return x*x; }
inline int elev2(int x) { return x*x; }
inline double elev3(double x) { return x*x*x; }
inline int elev3(int x) { return x*x*x; }

#ifdef _MSC_VER
  inline double log2(double x) { return log(x)/M_LN2; } // Nao precisa no GCC
#endif 

inline double pow2(double x) { return pow(2.0,x); }
#ifdef _MSC_VER
  inline int pow2(int x) { return cvRound(pow(2.0,x)); } // VC: Isto deve ser melhorado
#else
  inline int pow2(int x) { return pow(2,x); } // GCC
#endif

inline int sign(double x)
{ if (x==0.0) return 0;
  else if (x>0.0) return 1;
  else return -1;
}

inline int sign(int x) // OK. Positivo retorna 1. Negativo retorna -1. Zero retorna 0.
{ if (x==0) return 0;
  else if (x>0) return 1;
  else return -1;
}

inline int chao(int a, int b) // OK. Calcula a/b, truncando o resultado em direcao a -infinito.
{ div_t d=div(a,b);
  if (b>0 && d.rem<0) return d.quot-1;
  if (b<0 && d.rem>0) return d.quot-1;
  return d.quot;
}

inline int arredonda(int a, int b) // OK. Calcula divisao de a por b, arredondando o resultado. arredonda(1,2)=1 arredonda(-1,2)=-1.
{ if (sign(a)==sign(b)) return (a+b/2)/b;
  else return (a-b/2)/b;
}

inline int teto(int a, int b) // OK. Calcula divisao de a por b, truncando o resultado em direcao a +infinito.
{ div_t d=div(a,b);
  if (b>0 && d.rem>0) return d.quot+1;
  if (b<0 && d.rem<0) return d.quot+1;
  return d.quot;
}

inline int modulo(int a, int b) // OK. Sempre retorna numero nao-negativo entre [0,b-1]
{ if (b<0) { a=-a; b=-b; }
  int d=a%b;
  if (d<0) d=d+b;
  return d;
}

inline int quociente(int a, int b) // OK. Quociente para funcionar junto com a funcao modulo acima. Modulo e' sempre positivo.
{ if (b<0) { a=-a; b=-b; }
  div_t d=div(a,b);
  if (d.rem<0) return d.quot-1;
  else return d.quot;
}

inline int chao(double x) // floor finds the largest integer not > x.
{ return int(floor(x)); }
/* Nota: diferenca entre int() e chao():
int( 0.9)= 0 chao( 0.9)= 0
int( 1.1)= 1 chao( 1.1)= 1
int(-0.9)= 0 chao(-0.9)=-1
int(-1.1)=-1 chao(-1.1)=-2
*/

inline int arredonda(double x) // arredonda(0.5)=1 arredonda(-0.5)=-1.
{ return cvRound(x); } // round nao e' padrao de C++
//{ return int(round(x)); } // round nao e' padrao de C++

inline int teto(double x) // ceil finds the smallest integer not < x.
{ return int(ceil(x)); }

// fmod(-1.7,2.0)=-1.7  modulo(-1.7,2.0)=0.3
// fmod(-2.1,2.0)=-0.1  modulo(-2.1,2.0)=1.9
inline double modulo(double x, double b)
// Sempre retorna numero nao-negativo entre [0,b[
{ double d;
  d=fmod(x,b);
  if (d<0) d=d+b;
  return d;
}

inline int roundImpar(double d) // Arredonda para impar mais proximo
{ return 2*cvRound((d-1.0)/2.0)+1; }

inline int ceilImpar(double d) // Arredonda para impar >= d
{ return 2*cvRound(ceil((d-1.0)/2.0))+1; }


inline double deg2rad(double x)
{ return (x/180.0)*(M_PI); }

inline double rad2deg(double x)
{ return 180.0*x/M_PI; }

// Diferenca entre dois angulos em radianos - entre 0 e M_PI
inline double difAngRad(double a, double b)
{ double d=modulo(a-b,M_2PI);
  return min(d,M_2PI-d);
}

// Diferenca entre dois angulos em graus
inline double difAngDeg(double a, double b)
{ double d=modulo(a-b,360.0);
  return min(d,360.0-d);
}

inline int nextExp2(int n)
// Dado n, retorna m>=n tq m=2^i para i inteiro
{ return arredonda(pow(2.0,ceil(log2(n)-1e-40))); }

inline int min3(int a, int b, int c)
{ return min(min(a,b),c); }

inline int max3(int a, int b, int c)
{ return max(max(a,b),c); }

inline double min3(double a, double b, double c)
{ return min(min(a,b),c); }

inline double max3(double a, double b, double c)
{ return max(max(a,b),c); }

inline int min4(int a, int b, int c, int d)
{ return min(min(a,b),min(c,d)); }

inline int max4(int a, int b, int c, int d)
{ return max(max(a,b),max(c,d)); }

inline double min4(double a, double b, double c, double d)
{ return min(min(a,b),min(c,d)); }

inline double max4(double a, double b, double c, double d)
{ return max(max(a,b),max(c,d)); }

EXPORTA CPX ret2pol(CPX a); // -pi < arg <=pi
EXPORTA CPX pol2ret(CPX a);
inline CPX operator* (double t, CPX a) { return CPX(t*real(a),t*imag(a)); }

EXPORTA CPXD ret2pol(CPXD a); // -pi < arg <=pi
EXPORTA CPXD pol2ret(CPXD a);
inline CPXD operator* (double t, CPXD a) { return CPXD(t*real(a),t*imag(a)); }

//<<<<< Funcoes relacionadas com normal/gaussiana <<<<<<<<<<
EXPORTA double normal(double r, double desvio); // Funcao gaussiana 1D
EXPORTA double dxNormal(double r, double desvio); // Primeira derivada da normal 1D
EXPORTA double dxxNormal(double r, double desvio); // Segunda derivada da normal 1D

EXPORTA double binormal(double r, double desvio); // Funcao gaussiana 2D
EXPORTA double grxBinormal(double x, double y, double desvio); // Gradiente x da gaussiana 2D
EXPORTA double gryBinormal(double x, double y, double desvio); // Gradiente y da gaussiana 2D
EXPORTA double lapBinormal(double r, double desvio); // Laplace da gaussiana 2D

EXPORTA double normalSqr(double r2, double desvio); // Funcao gaussiana 1D com parametro r^2
EXPORTA double binormalSqr(double r2, double desvio); // Funcao gaussiana 2D com parametro r^2
EXPORTA double lapBinormalSqr(double r2, double desvio); // Laplace da gaussiana 2D com parametro r^2

//<<<<<<<<<<<<<<<<<<<<<<<<<<< Leitura de arquivo com comentarios estilo C <<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA string leStr(FILE* arq);
// Nota: Sempre devolvia caracteres minusculos. 
// Mudei para devolver minusculos e maiusculos
// separador: (c==',' || c==';' || c==' ' || c=='\t' || c=='\n' || c=='\r' || c=='(' || c==')' || c=='=')
// ident: ( ('a'<=c && c<='z') || ('0'<=c && c<='9') || c=='+' || c=='-' || c=='.' || c=='_')
// Comentarios podem vir:
// (1) Com //
// (2) Com /* */
// (3) Com #
//retorna "eof" se tenta ler apos fim
EXPORTA string leFileName(FILE* arq);
//retorna "eof" se tenta ler apos fim
EXPORTA void leNum(FILE* arq, BYTE& b);
EXPORTA void leNumIgnEOF(FILE* arq, int& i); // retorna minint quando chega a eof
EXPORTA void leNum(FILE* arq, int& i);
EXPORTA void leNum(FILE* arq, SHT& s);
EXPORTA void leNum(FILE* arq, FLT& f);
EXPORTA void leNum(FILE* arq, DBL& d);
EXPORTA void leNum(FILE* arq, bool& b); // os bits 0/1 tem que estar separados por separadores
EXPORTA void leBool(FILE* arq, bool& b); // os bits 0/1 nao precisam estar separados

//<<<<<<<<<<<<<<<<<<<< Leitura de ISTR <<<<<<<<<<<<<<<<<<<<<<<<<<<
// Nota: Sempre devolvia caracteres minusculos. Mudei
class EXPORTA ISTR {
 public:
  int pos;
  string st;
  void arg2str(int argc, char** argv); // converte todos os argv para st. Ex: arg2str(argc-1,&argv[1]).
  ISTR() { pos=0; }
  ISTR(int argc, char** argv); // converte todos os argv para st. Ex: ISTR(argc-1,&argv[1]).
  ISTR(char* argv); // Converte um argv para st. Ex: ISTR(argv[3]); 
  ISTR(string argv); 
};

EXPORTA int leChar(ISTR& arq);
EXPORTA string leStr(ISTR& arq);
EXPORTA string leFileName(ISTR& arq);
EXPORTA void leNum(ISTR& arq, BYTE& b);
EXPORTA void leNumIgnEOF(ISTR& arq, int& i);
EXPORTA void leNum(ISTR& arq, int& i);
EXPORTA void leNum(ISTR& arq, SHT& s);
EXPORTA void leNum(ISTR& arq, FLT& f);
EXPORTA void leNum(ISTR& arq, DBL& d);
EXPORTA void leNum(ISTR& arq, bool& b);  // os bits 0/1 tem que estar separados por separadores
EXPORTA void leBool(ISTR& arq, bool& b); // os bits 0/1 nao precisam estar separados

EXPORTA bool seekArg(ISTR& arq, string nome);
EXPORTA bool seekArg(ISTR& arq, string nome, BYTE& b);
EXPORTA bool seekArg(ISTR& arq, string nome, int& i);
EXPORTA bool seekArg(ISTR& arq, string nome, SHT& s);
EXPORTA bool seekArg(ISTR& arq, string nome, FLT& f);
EXPORTA bool seekArg(ISTR& arq, string nome, DBL& d);
EXPORTA bool seekArg(ISTR& arq, string nome, bool& b); 
EXPORTA bool seekArg(ISTR& arq, string nome, string& st2); 
EXPORTA bool seekFileName(ISTR& arq, string nome, string& st2); 
EXPORTA bool seekFim(ISTR& arq); 

//<<<<<<<<<<<<<<<<<<<<<<<<<<< ArgVS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class ArgVS { // argv[0] e' armazenado
 public:
  vector<string> vs;
  bool expandeRun=true;
  void arg2vs(int argc, char** argv); // converte todos os argv para vs. 
  ArgVS() {}
  ArgVS(int argc, char** argv, bool _expandeRun=true) { expandeRun=_expandeRun; arg2vs(argc,argv); } 
  void imp(); 
};

//<<<<<<<<<<<<<<<<<<<< Leitura de ArgStr <<<<<<<<<<<<<<<<<<<<<<<<<<<
// Nota: Devolve minuscula e maiuscula, sem fazer conversao de caso
class Comando { public: string first; string second; bool chequei; }; 

class ArgComando { // argv[0] nao e' armazenado
 public:
  bool exclamacao2porcentagem=true; // Converte ! para %
  bool apostrofe2aspas=true; // Converte ' para "
  bool expandeRun=true;

  ArgComando() {}
  ~ArgComando() { leuTodos(); }
  void arg2comando(int argc, char** argv); // converte todos os argv para vs. 
  ArgComando(int argc, char** argv, bool _expandeRun=true) { expandeRun=_expandeRun; arg2comando(argc,argv); } 
  // converte todos os argv para vs. Ex: ArgStr(argc-1,&argv[1]).
  void vs2comando(const ArgVS& arg);  
  ArgComando(const ArgVS& arg, bool _expandeRun=true) { expandeRun=_expandeRun; vs2comando(arg); }
  void imp();

  bool getBool(const string& nome1, const string& nome2="", bool def=false); 
  // Sem argumento ou seguido de true/false. So presenca indica true.
  int getInt(const string& nome1, const string& nome2="", int def=INT_MIN);
  double getDouble(const string& nome1, const string& nome2="", double def=-DBL_MAX);
  string getString(const string& nome1, const string& nome2="", string def="");
  string getCommand(int indice); 
  // Indice comeca do zero. Devolve comando sem -nome
  void leuTodos();
  // Gera erro se algum comando nao tiver sido checado. Deve chamar apos todos os gets

  int nameless=0; //numero de comandos sem "-"
 private:
  const string separador="="; 
  const string indicadorComando="-";  
  vector< Comando > vs; //nome do comando + argumentos. Ex: -f=2.4 => -f 2.4;  nome.cpp => -0 nome.cpp
  void converteSt(string& st);
  Comando separaComando(const string& st);
  int procura(const string& nome1, const string& nome2=""); // devolve -1 se nao acha
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<< DATAHORA <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
struct EXPORTA DATAHORA {
  int ano,mes,dia,hor,min,seg;
};
EXPORTA bool bissexto(int y);
EXPORTA int diasDoMes(DATAHORA h); // Retorna quantos dias tem um mes, dados mes/ano.
EXPORTA bool existeDataHora(DATAHORA h); // Testa se data/hora e' valido
EXPORTA void imp(DATAHORA h);
EXPORTA DATAHORA somaUmDia(DATAHORA h);  // Soma um dia a h
EXPORTA DATAHORA somaDeg(DATAHORA h, int s); // Soma s segundos a h
EXPORTA void hmscs(int k, int& h, int& m, int& s, int& cs); // Converte centesimos de segundos em hh:mm:ss:cc

//<<<<<<<<<<<<<<<<<<<< Scalar
inline uchar scalar2g(Scalar a)
{ return saturate_cast<uchar>(a[0]); }

inline COR scalar2c(Scalar a)
{ COR cor; 
  cor[0]=saturate_cast<uchar>(a[0]);
  cor[1]=saturate_cast<uchar>(a[1]);
  cor[2]=saturate_cast<uchar>(a[2]);
  return cor;
}

inline Scalar toScalar(GRY a)
{ return Scalar(a,a,a,a); }

inline Scalar toScalar(COR a)
{ return Scalar(a[0],a[1],a[2],0); }

inline Scalar toScalar(FLT a)
{ return Scalar(a,a,a,a); }

inline double distancia(COR a, COR b)
{ return sqrt(elev2(a[0]-b[0])+elev2(a[1]-b[1])+elev2(a[2]-b[2]));
}

string leArq(string nome);

} //namespace cek

#endif

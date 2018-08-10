#ifndef __CEKARQ__
#define __CEKARQ__

#include "cekbase.h"
#include <iostream>
#include <sys/stat.h>

#ifdef _WIN64
  #include <dos.h>
  #include <direct.h>
  #include <sys/utime.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace cek {
using namespace std;
using namespace cv;

EXPORTA string getEnv(const string& name);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA bool isDirec(string nome);
EXPORTA bool isFile(string nome);

EXPORTA int64_t tamArq(string nome);

//<<<<<<<<<<<<<< Funcoes de arquivo. <<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA string sufixo(string st); // Devolve sufixo "c:\ab\cd.ext => ext"
EXPORTA string semSufixo(string st); // Devolve o nome do arquivo sem sufixo (e sem .) "c:\ab\cd.ext => c:\ab\cd"
EXPORTA string semDiret(string st); // retorna o string depois do ultimo \ ou / ou : "c:\ab\cd.ext => cd.ext"
EXPORTA string diretorio(string st); // retorna o string antes do ultimo \ ou / ou : "c:\ab\cd.ext => c:\ab"
inline string semDiretSufixo(string st) { return semSufixo(semDiret(st)); }
EXPORTA string addPrefix(string pref, string nome); 
// acrescenta prefixo ao nome do arquivo. pref="pref" nome="c:\ab\cd.ext" => "c:\ab\prefcd.ext"
// acrescenta prefixo ao nome do arquivo. pref="pref" nome="cd.ext" => "prefcd.ext"
// Caractere ! indica apagar um caracter. pref="t!" nome="c:\ab\cd.ext" => "c:\ab\td.ext"
//                                        pref="t!!" nome="c:\ab\cd.ext" => "c:\ab\t.ext"

EXPORTA vector<string> paths(string va="PATH", bool insereDefault=false); // Devolve um diretorio do path em cada string. O primeiro e' "." se insereDefault==true
EXPORTA string procuraNoPath(string nomeArq); // Procura nomeArq no path. Se achar, devolve nome com diretorio. Se nao achar, devolve ""

EXPORTA bool existeArq(string nome);

EXPORTA string getced(string argv0);
// get current executable directory
// Recebe argv[0]
// Devolve o diretorio onde se encontra o executavel. Ex: c:\lixo
// Se encontra no diretorio default, retorna ponto "."
// EXPORTA string wildCard(string nomearq, char separador=' ');
// Expande wildcard num string separado por separador
// Ex: wildCard("*.jpg",'#'); Saída st="N1.jpg#N2.jpg#N3.jpg#N4.jpg#N5.jpg#"

EXPORTA void vsWildCard(string nomearq, vector<string>& vs, bool addNotFound=false);
// Expande wildcard num vetor de string
// Ex: wildCard("*.jpg",vs); Saída vs={"N1.jpg","N2.jpg","N3.jpg","N4.jpg","N5.jpg"}
// Acrescenta novos arquivos no final do vs.
// addNotFound==false: Se *.jpg nao ocorre, nada acrescenta no vs
// addNotFound==true:  Se *.jpg nao ocorre, acrescenta *.jpg no vs
EXPORTA vector<string> vsWildCard(int argc, char** argv, bool addNotFound=true);
// Ex: Expande todos os argumentos. Ex: st=vsWildCard(argc-1,&argv[1]).
// Ex: string args=vsWildCard(argc,argv): trabalha em args como se fosse argv
// Se algum argv[i] nao aparece, acrescenta o proprio argv[i]. 
// EX: programa teste *.jpg => vs={"programa","teste","img1.jpg","img2.jpg"}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
EXPORTA string maiorArq(string nome);
// Devolve o arquivo com o maior nome (em ordem lexicografica)
// Ex: maiorArq("c:\\lixo\\v*.jpg") devolve o arquivo v*.jpg com o maior nome em c:\lixo, com o nome do path
// Ex: maiorArq("*.*") ou maiorarq("*") devolve o arquivo com o maior nome no diretorio default
// Se nao existe nenhum arquivo especificado, devolve ""
EXPORTA int maiorArq(string nome, int tamSuf);
// Devolve o numero do arquivo com o maior nome (em ordem lexicografica)
// O numero e composto por tamSuf ultimos caracteres.
// Ex: v000.jpg, v001.jpg, v002.jpg => maiorArq("v???.jpg",3) = 2
// Devolve -1 se nao houver arquivo
#ifdef _WIN64
EXPORTA void subDir(string nomedir);
EXPORTA void diret(string nomedir);
EXPORTA void delDir(string nomedir);
EXPORTA void copiaArq(string source, string target);
EXPORTA void copiaDir(string SourceDir, string TargetDir);

// modo='l': list only
// modo='p': perform operations only
// modo='a': list and perform
EXPORTA void syncTarget(string SourceDir, string TargetDir, char modo);
// Copy different and new files

EXPORTA void pruneTarget(string SourceDir, string TargetDir, char modo);
// Prune orphan directories and files from target directory

EXPORTA void updateTarget(string SourceDir, string TargetDir, char modo);
// Copy newer and non-existing files

EXPORTA void maior(string nomedir, unsigned tamanho);
// Imprime arquivos maiores que tamanho
  
#endif //#ifdef _WIN64

} //namespace cek

#endif

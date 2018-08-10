#ifndef __CEKMAC__
#define __CEKMAC__

#include <cekeikon.h>
//#include <conio.h>
#include "macadapt.h"

//<<<<<<<<<<<<<<<< myrandom class <<<<<<<<<<<<<<<<<<<<<
class EXPORTA CRIP : RANDOM
{
public:
  CRIP(int semente=7);

  vector<int> vetpermut(int n);
  vector<int> vetipermut(int n);
  DWORD permut(DWORD d);
  DWORD ipermut(DWORD d);
  DWORD encrypt(DWORD d);
  DWORD decrypt(DWORD d);
  void encrypt(vector<DWORD>& d);
  void decrypt(vector<DWORD>& d);
  BYTE permut(BYTE d);
  BYTE ipermut(BYTE d);
  BYTE encrypt(BYTE d);
  BYTE decrypt(BYTE d);
  void encrypt(vector<BYTE>& d);
  void decrypt(vector<BYTE>& d);
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.


EXPORTA int senhaprojeto(string projeto);
EXPORTA vector<BYTE> string2vector(string st);
EXPORTA vector<BYTE> encript(string projeto, string mac);
EXPORTA vector<BYTE> decript(string projeto, string maccriptografado);
EXPORTA bool valida(string projeto, string maccriptografado);

#endif
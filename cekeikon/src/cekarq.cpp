#include "cekeikon.h"

namespace cek {

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

string getEnv(const string& name) {
// Get env var value
  const char* val = getenv( name.c_str() );
  return val == 0 ? "" : val;
}

//#define _A_NORMAL       0x00    /* Normal file - No read/write restrictions */
//#define _A_RDONLY       0x01    /* Read only file */
//#define _A_HIDDEN       0x02    /* Hidden file */
//#define _A_SYSTEM       0x04    /* System file */
//#define _A_SUBDIR       0x10    /* subDirectory */
//#define _A_ARCH         0x20    /* Archive file */

bool isDirec(string nome) {
// retorna true se nomedir for um diretorio
  struct stat buffer;
  if (stat(nome.c_str(), &buffer) != 0)
    return 0;
  return S_ISDIR(buffer.st_mode);
}

bool isFile(string nome) {
  struct stat buffer;
  if (stat(nome.c_str(), &buffer) != 0)
    return 0;
  return S_ISREG(buffer.st_mode);
}

#ifdef _WIN64
bool pegaAttribArq(string st, struct _finddata_t& f)
{ intptr_t handle;
  handle = _findfirst(st.c_str(), &f);

  bool existe=true;
  if (handle==-1) existe=false;
  _findclose(handle);
  return existe;
}
#endif

int64_t tamArq(string nome) {
  struct stat buffer;
  int rc = stat(nome.c_str(), &buffer);
  return rc == 0 ? buffer.st_size : -1;
}

//<<<<<<<<<<<<<< Funcoes de arquivo. <<<<<<<<<<<<<<<<<<<<<<<<<<<<
string sufixo(string st) 
// Devolve sufixo "c:\ab\cd.ext => ext"
{ size_t comp=st.length();
  if (comp<=0 || comp>255) erro("Erro sufixo: nome arquivo invalido",st.c_str());

  size_t ponto=st.find_last_of('.');

  string suf;
  if (ponto==size_t(-1)) suf=""; // Arquivo sem extensao
  else suf=st.substr(ponto+1);

  return suf;
}

string semSufixo(string st) 
// Devolve o nome do arquivo sem sufixo (e sem .) "c:\ab\cd.ext => c:\ab\cd"
{ size_t comp=st.length();
  if (comp<=0 || comp>255) erro("Erro semSufixo: nome arquivo invalido",st.c_str());
  size_t ponto=st.find_last_of('.');
  string sem;
  if (ponto==size_t(-1)) sem=st; // Arquivo sem extensao
  else sem=st.substr(0,ponto);
  return sem;
}

string semDiret(string st) 
// retorna o string depois do ultimo \ ou / ou : "c:\ab\cd.ext => cd.ext"
{ int i1=(int)st.rfind('\\');
  int i2=(int)st.rfind('/');
  int i3=(int)st.rfind(':');
  int i=max3(i1,i2,i3)+1;
  return st.substr(i,st.length()-i);
}

string diretorio(string st) 
// retorna o string antes do ultimo \ ou / ou : "c:\ab\cd.ext => c:\ab"
{ int i1=(int)st.rfind('\\');
  int i2=(int)st.rfind('/');
  int i3=(int)st.rfind(':');
  int i=max3(i1,i2,i3);
  if (i>=0) return st.substr(0,i);
  else return "";
}

// string addPrefix(string pref, string nome) 
// // acrescenta prefixo ao nome do arquivo. pref="pref" nome="c:\ab\cd.ext" => "c:\ab\prefcd.ext"
// // acrescenta prefixo ao nome do arquivo. pref="pref" nome="cd.ext" => "prefcd.ext"
// { string d=diretorio(nome);
//   string n=semDiret(nome);
//   if (d=="") return pref+n;
//   else       return d+"\\"+pref+n;
// }

string contaRemoveExclama(string ent, int& conta)
{ size_t found=ent.find_last_not_of("!");
  conta=ent.size()-found-1;
  string sai=ent;
  sai.erase(found+1);
  return sai;
}

string addPrefix(string pref, string nome) 
// acrescenta prefixo ao nome do arquivo. pref="pref" nome="c:\ab\cd.ext" => "c:\ab\prefcd.ext"
// acrescenta prefixo ao nome do arquivo. pref="pref" nome="cd.ext" => "prefcd.ext"
// Caractere ! indica apagar um caracter. pref="t!" nome="c:\ab\cd.ext" => "c:\ab\td.ext"
//                                        pref="t!!" nome="c:\ab\cd.ext" => "c:\ab\t.ext"
{ 
  #ifdef _WIN64
    char separador='\\';
  #else
    char separador='/';
  #endif
  string d=diretorio(nome);

  int contaExclama;
  string semExclama=contaRemoveExclama(pref,contaExclama);
  string n=semDiret(nome);
  if (contaExclama<=int(n.size())) n=n.substr(contaExclama);
  else n="";

  if (d=="") return semExclama+n;
  else       return d+separador+semExclama+n;
}

vector<string> paths(string va, bool insereDefault) {
// Devolve um diretorio do path em cada string
// O primeiro e' "." se insereDefault==true
  #ifdef _WIN64
    char separador=';';
  #else
    char separador=':';
  #endif

  char* pt=getenv(va.c_str());
  vector<string> d;
  if (pt==NULL) return d;
  string st=pt;

  if (insereDefault) d.push_back(".");
  int iant=0; int i=0;
  while (i<int(st.length())) {
    if (st[i]!=separador) i++;
    else {
      string st2=st.substr(iant,i-iant); // iant ate i-1
      char ultimo=*(st2.end()-1);
      if (ultimo=='\\' || ultimo=='/') { st2.erase(st2.end()-1); } // apaga \ ou / final      
      if (st2!="") d.push_back(st2);
      i++; iant=i;
    }
  }
  string st2=st.substr(iant,i-iant); // iant ate i-1
  char ultimo=*(st2.end()-1);
  if (ultimo=='\\' || ultimo=='/') { st2.erase(st2.end()-1); } // apaga \ ou / final      
  if (st2!="") d.push_back(st2);
  return d;
}

string procuraNoPath(string nomeArq) {
  #ifdef _WIN64
    bool insereDefault=true;
    char separador='\\';
  #else
    bool insereDefault=false;
    char separador='/';
  #endif

  string nomeComDir;
  vector<string> d=paths("PATH",insereDefault);
  bool existe=false;
  for (int i=0; i<int(d.size()); i++) {
    nomeComDir=d[i]+separador+nomeArq;
    if (existeArq(nomeComDir)) { existe=true; break; }
  }
  if (!existe) return "";
  else return nomeComDir;
}

bool existeArq(string nome) {
  struct stat buffer;   
  return (stat (nome.c_str(), &buffer) == 0); 
}

string getced(string argv0) {
// get current executable directory
// Recebe argv[0]
// Devolve o diretorio onde se encontra o executavel. Ex: c:\lixo
// Se encontra no diretorio default, retorna ponto "."
  #ifdef _WIN64
    const int MAXPATH=_MAX_PATH; //260
  #else
    const int MAXPATH=PATH_MAX; //4096
  #endif

  if (diretorio(argv0)!="") { // Diretorio esta especificado
    char buf[MAXPATH];
    #ifdef _WIN64
      _fullpath(buf, argv0.c_str(), MAXPATH);
    #else
      realpath(argv0.c_str(), buf);
    #endif
    return diretorio(buf);
  } else { // sem especificadao do diretorio - arquivo pode estar no path
    #ifdef _WIN64
      argv0=semSufixo(argv0)+".exe";
    #endif
    string nomearq;
    #ifdef _WIN64
      vector<string> d=paths("PATH",true);
      char separador='\\';
    #else
      vector<string> d=paths("PATH",false);
      char separador='/';
    #endif
    bool existe=false;
    unsigned i;
    for (i=0; i<d.size(); i++) {
      nomearq=d[i]+separador+argv0;
      //printf("Procurando %s\n",nomearq.c_str());
      if (existeArq(nomearq)) { existe=true; break; }
    }
    if (!existe) erro("Erro getced: Nao achei arquivo executavel no path: ",argv0);
    return d[i];
  }
}

#ifdef _WIN64
  void vsWildCard(string nome, vector<string>& vs, bool addNotFound) {
  // Expande wildcard num vetor de string
  // Ex: wildCard("*.jpg",vs); Saída vs={"N1.jpg","N2.jpg","N3.jpg","N4.jpg","N5.jpg"}
  // Acrescenta novos arquivos no final do vs.
  // addNotFound==false: Se *.jpg nao ocorre, nada acrescenta no vs
  // addNotFound==true:  Se *.jpg nao ocorre, acrescenta *.jpg no vs
    struct _finddata_t f;
    string nomearq=semDiret(nome);
    string nomedir=diretorio(nome);
    intptr_t handle, done;
    handle = done = _findfirst(nome.c_str(), &f);
    int inseridos=0;
    while (done!=-1) {
      if ((f.attrib & (~_A_ARCH)) == _A_NORMAL) {
        // Nao pode ser hidden, rdonly, subdir e system.
        // Pode ser arch
        if (nomedir!="") vs.push_back(nomedir+'\\'+f.name);
        else vs.push_back(f.name);
        inseridos++;
      }
      done = _findnext(handle, &f);
    }
    _findclose(handle);
    if (inseridos==0 && addNotFound) vs.push_back(nome);
  }
#else
  #include <glob.h>
  void vsWildCard(string nome, vector<string>& vs, bool addNotFound) {
    glob_t glob_result;
    glob(nome.c_str(), GLOB_TILDE,NULL, &glob_result);
    if (glob_result.gl_pathc==0 && addNotFound) vs.push_back(nome);
    for (unsigned i=0; i<glob_result.gl_pathc; i++) {
      vs.push_back( string(glob_result.gl_pathv[i]) );
    }
    globfree(&glob_result);
  }
#endif

vector<string> vsWildCard(int argc, char** argv, bool addNotFound)
// Ex: Expande todos os argumentos. Ex: st=vsWildCard(argc-1,&argv[1]).
{ vector<string> vs;
  for (int i=0; i<argc; i++)
    vsWildCard(argv[i],vs,addNotFound);
  return vs;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
string maiorArq(string nome) {
// Devolve o arquivo com o maior nome (em ordem lexicografica)
// Ex: maiorArq("c:\\lixo\\v*.jpg") devolve o arquivo v*.jpg com o maior nome em c:\lixo, com o nome do path
// Ex: maiorArq("*.*") ou maiorarq("*") devolve o arquivo com o maior nome no diretorio default
// Se nao existe nenhum arquivo especificado, devolve ""
  vector<string> vs;
  vsWildCard(nome,vs);
  if (vs.size()>0) {
    auto maior=max_element(vs.begin(),vs.end());
    return *maior;
  } else {
    return "";
  }
}

int maiorArq(string nome, int tamSuf)
// Devolve o numero do arquivo com o maior nome (em ordem lexicografica)
// O numero eh composto por tamSuf ultimos caracteres.
// Ex: v000.jpg, v001.jpg, v002.jpg => maiorArq("v???.jpg",3) = 2
// Devolve -1 se nao houver arquivo
{ string maior=maiorArq(nome);
  int r;
  if (maior!="") {
    string st=semSufixo(maior); st=st.substr(st.length()-tamSuf);
    r=atoi(st.c_str());
  } else r=-1;
  return r;
}

#ifdef _WIN64
void subDir(string nomedir)
{ char buf[_MAX_PATH];
  _fullpath(buf, nomedir.c_str(), _MAX_PATH);
  nomedir=string(buf);

  printf("Directory listing of %s\n",nomedir.c_str());
  if (!isDirec(nomedir)) erro("Erro: Deve especificar o nome de um diretorio");

  struct _finddata_t f;
  intptr_t handle, done;
  string st=nomedir+"\\*";
  handle = done = _findfirst(st.c_str(), &f);
  while (done!=-1) {
    if (!(f.attrib & _A_SUBDIR)) {
      printf("  ");
      if (f.attrib & _A_ARCH)   printf("A"); else printf(".");
      if (f.attrib & _A_SYSTEM) printf("S"); else printf(".");
      if (f.attrib & _A_HIDDEN) printf("H"); else printf(".");
      if (f.attrib & _A_RDONLY) printf("R"); else printf(".");
      //if (f.attrib & _A_VOLID)  printf("V"); else printf(".");
      printf(" %s\n", f.name);
    }
    done = _findnext(handle, &f);
  }
  _findclose(handle);

  handle = done = _findfirst(st.c_str(), &f);
  while (done!=-1) {
    if (f.attrib & _A_SUBDIR) {
      string st2=f.name;
      if (st2!="." && st2!="..") subDir(nomedir+"\\"+st2);
    }
    done = _findnext(handle, &f);
  }
  _findclose(handle);
}

void diret(string nomedir)
{ char buf[_MAX_PATH];
  _fullpath(buf, nomedir.c_str(), _MAX_PATH);
  nomedir=string(buf);

  printf("Directory listing of %s\n",nomedir.c_str());
  if (!isDirec(nomedir)) erro("Erro: Deve especificar o nome de um diretorio");

  struct _finddata_t f;
  intptr_t handle, done;
  string st=nomedir+"\\*";
  handle = done = _findfirst(st.c_str(), &f);
  while (done!=-1) {
    printf("  ");
    if (f.attrib & _A_ARCH)   printf("A"); else printf(".");
    if (f.attrib & _A_SYSTEM) printf("S"); else printf(".");
    if (f.attrib & _A_HIDDEN) printf("H"); else printf(".");
    if (f.attrib & _A_RDONLY) printf("R"); else printf(".");
    if (f.attrib & _A_SUBDIR) printf("D"); else printf(".");

    if (f.size<1048576) printf(" %8lu Bytes",f.size);
    else if (f.size<1073741824) printf(" %8luKBytes",f.size/1024);
    else printf(" %8luMBytes",f.size/1048576);

    printf(" %s\n", f.name);
    done = _findnext(handle, &f);
  }
  _findclose(handle);
}

void delDir(string nomedir)
{ char buf[_MAX_PATH];
  _fullpath(buf, nomedir.c_str(), _MAX_PATH);
  nomedir=string(buf);
  //printf("delDir %s\n",nomedir.c_str());
  if (!isDirec(nomedir)) erro("Erro: Deve especificar o nome de um diretorio");

  struct _finddata_t f;

  intptr_t handle, done;
  string st=nomedir+"\\*";
  handle = done = _findfirst(st.c_str(), &f);
  while (done!=-1) {
    if (!(f.attrib & _A_SUBDIR)) {
      st=nomedir+"\\"+f.name;
      if (_unlink(st.c_str())==-1) printf("  %s (CUIDADO - NAO APAGUEI ARQUIVO)\n",st.c_str());
    }
    done = _findnext(handle,&f);
  }
  _findclose(handle);

  string st2;
  st=nomedir+"\\*";
  handle = done = _findfirst(st.c_str(), &f);
  while (done!=-1) {
    if (f.attrib & _A_SUBDIR) {
      st2=f.name;
      if (st2!="." && st2!="..") {
        st=nomedir+"\\"+st2;
        delDir(st);
        //printf("Vou chamar %s\n",st.c_str());
      }
    }
    done = _findnext(handle,&f);
  }
  _findclose(handle);

  if (_rmdir(nomedir.c_str())) printf("  %s (CUIDADO - NAO APAGUEI DIRETORIO)\n",nomedir.c_str());
}

void copiaArq(string source, string target)
{ FILE* ent=fopen(source.c_str(),"rb");
  if (ent==NULL) erro("Erro: Abertura de ",source);
  FILE* sai=fopen(target.c_str(),"wb");
  if (sai==NULL) erro("Erro: Abertura de ",target);
  BYTE buf[maxbuf]; size_t lidos;
  do {
    lidos=fread(buf,1,maxbuf,ent);
    fwrite(buf,1,lidos,sai);
  } while (lidos==maxbuf);
  fclose(ent); fclose(sai);

  struct _stat src_stat;
  if (_stat(source.c_str(),&src_stat) != 0)
    erro("Unable to get status of source file");
  struct _utimbuf times;
  times.modtime = times.actime = src_stat.st_mtime;
  if (_utime(target.c_str(),&times) != 0)
    erro("Unable to set time of destination file");
}

void copiaDir(string SourceDir, string TargetDir)
{ //printf("copiaDir %s %s\n",SourceDir.c_str(),TargetDir.c_str());
  if (!isDirec(SourceDir)) erro("Erro: SourceDir nao e' diretorio");
  if (existeArq(TargetDir)) erro("Erro: TargetDir ja existe");

  //printf("  mkdir %s\n",TargetDir.c_str());
  if (_mkdir(TargetDir.c_str())==-1) erro("Erro: _mkdir ",TargetDir);

  struct _finddata_t f;
  intptr_t handle, done;
  string st=SourceDir+"\\*";
  handle = done = _findfirst(st.c_str(), &f);
  string TargetFile, SourceFile;
  while (done!=-1) {
    if (!((f.attrib & _A_SYSTEM) || (f.attrib & _A_HIDDEN) || (f.attrib & _A_RDONLY) || (f.attrib & _A_SUBDIR))) {
      TargetFile=TargetDir+"\\"+f.name;
      SourceFile=SourceDir+"\\"+f.name;
      //printf("  copiaArq %s %s\n",SourceFile.c_str(),TargetFile.c_str());
      copiaArq(SourceFile,TargetFile);
    }
    done = _findnext(handle, &f);
  }
  _findclose(handle);

  handle = done = _findfirst(st.c_str(), &f);
  while (done!=-1) {
    if (f.attrib & _A_SUBDIR) {
      string st2=f.name;
      if (st2!="." && st2!="..") {
        TargetFile=TargetDir+"\\"+f.name;
        SourceFile=SourceDir+"\\"+f.name;
        copiaDir(SourceFile,TargetFile);
      }
    }
    done = _findnext(handle, &f);
  }
  _findclose(handle);
}

void syncTarget(string SourceDir, string TargetDir, char modo)
// Copy new and different files to target directory
// modo='l': list only
// modo='p': perform only
// modo='a': list and update
// Copy different and new files
{ if (!isDirec(SourceDir)) erro("Erro: SourceDir nao e' diretorio");
  if (!isDirec(TargetDir)) erro("Erro: TargetDir nao e' diretorio");
  if (modo!='l' && modo!='p' && modo!='a') erro("Erro: modo invalido");

  //if (modo=='l' || modo=='a') printf("syncTarget %s %s\n",SourceDir.c_str(),TargetDir.c_str());
  struct _finddata_t SourceBk,TargetBk;
  intptr_t handle, done;
  string st=SourceDir+"\\*";
  handle = done = _findfirst(st.c_str(), &SourceBk);
  string TargetFile, SourceFile;
  while (done!=-1) {
    if (!((SourceBk.attrib & _A_SYSTEM) || (SourceBk.attrib & _A_HIDDEN) || (SourceBk.attrib & _A_RDONLY) || (SourceBk.attrib & _A_SUBDIR))) {
      TargetFile=TargetDir+"\\"+SourceBk.name;
      //SourceFile=SourceDir+"\\"+SourceBk.name;

      bool existe=pegaAttribArq(TargetFile,TargetBk);
      bool igual=false;
      if (existe) {
        igual = (SourceBk.time_write==TargetBk.time_write) &&
                (SourceBk.size==TargetBk.size);
      }
      if (!existe || !igual) {
        SourceFile=SourceDir+"\\"+SourceBk.name;
        if (modo=='l' || modo=='a') printf("  copiaArq %s\n",SourceFile.c_str());
        if (modo=='p' || modo=='a') copiaArq(SourceFile,TargetFile);
      }
    }
    done = _findnext(handle, &SourceBk);
  }
  _findclose(handle);

  handle = done = _findfirst(st.c_str(), &SourceBk);
  while (done!=-1) {
    if (SourceBk.attrib & _A_SUBDIR) {
      string st2=SourceBk.name;
      if (st2!="." && st2!="..") {
        TargetFile=TargetDir+"\\"+SourceBk.name;
        SourceFile=SourceDir+"\\"+SourceBk.name;
        bool existe=isDirec(TargetFile);
        if (!existe) {
          if (modo=='l' || modo=='a') printf("  copiaDir %s\n",SourceFile.c_str());
          if (modo=='p' || modo=='a') copiaDir(SourceFile,TargetFile);
        } else {
          syncTarget(SourceFile,TargetFile,modo);
        }
      }
    }
    done = _findnext(handle, &SourceBk);
  }
  _findclose(handle);
}

void pruneTarget(string SourceDir, string TargetDir, char modo)
// Prune orphan directories and files from target directory
// modo='l': list only
// modo='p': perform only
// modo='a': list and update
{ if (!isDirec(SourceDir)) erro("Erro: SourceDir nao e' diretorio");
  if (!isDirec(TargetDir)) erro("Erro: TargetDir nao e' diretorio");
  if (modo!='l' && modo!='p' && modo!='a') erro("Erro: modo invalido");

  //if (modo=='l' || modo=='a') printf("syncTarget %s %s\n",SourceDir.c_str(),TargetDir.c_str());
  struct _finddata_t SourceBk,TargetBk;
  intptr_t handle, done;
  string TargetWild=TargetDir+"\\*";
  handle = done = _findfirst(TargetWild.c_str(), &TargetBk);
  string TargetFile, SourceFile;
  while (done!=-1) {
    if (!((TargetBk.attrib & _A_SYSTEM) || (TargetBk.attrib & _A_HIDDEN) || (TargetBk.attrib & _A_RDONLY) || (TargetBk.attrib & _A_SUBDIR))) {
      SourceFile=SourceDir+"\\"+TargetBk.name;
      bool existe=pegaAttribArq(SourceFile,SourceBk);
      if (!existe) {
        TargetFile=TargetDir+"\\"+TargetBk.name;
        if (modo=='l' || modo=='a') printf("  Remove %s\n",TargetFile.c_str());
        if (modo=='p' || modo=='a') if (_unlink(TargetFile.c_str())) printf("  %s (CUIDADO - NAO APAGUEI ARQUIVO)\n",TargetFile.c_str());
      }
    }
    done = _findnext(handle, &TargetBk);
  }
  _findclose(handle);

  handle = done = _findfirst(TargetWild.c_str(), &TargetBk);
  while (done!=-1) {
    if (TargetBk.attrib & _A_SUBDIR) {
      string st2=TargetBk.name;
      if (st2!="." && st2!="..") {
        SourceFile=SourceDir+"\\"+TargetBk.name;
        bool existe=isDirec(SourceFile);
        TargetFile=TargetDir+"\\"+TargetBk.name;
        if (!existe) {
          if (modo=='l' || modo=='a') printf("  delDir %s\n",TargetFile.c_str());
          if (modo=='p' || modo=='a') delDir(TargetFile);
        } else {
          pruneTarget(SourceFile,TargetFile,modo);
        }
      }
    }
    done = _findnext(handle, &TargetBk);
  }
  _findclose(handle);
}

void updateTarget(string SourceDir, string TargetDir, char modo)
// Copy newer and non-existing files
// modo='l': list only
// modo='p': perform only
// modo='a': list and update
{ if (!isDirec(SourceDir)) erro("Erro: SourceDir nao e' diretorio");
  if (!isDirec(TargetDir)) erro("Erro: TargetDir nao e' diretorio");

  if (modo!='l' && modo!='p' && modo!='a') erro("Erro: modo invalido");

  //if (modo=='l' || modo=='a') printf("syncTarget %s %s\n",SourceDir.c_str(),TargetDir.c_str());
  struct _finddata_t SourceBk,TargetBk;
  intptr_t handle, done;
  string SourceWild=SourceDir+"\\*";
  handle = done = _findfirst(SourceWild.c_str(), &SourceBk);
  string TargetFile, SourceFile;
  while (done!=-1) {
    if (!((SourceBk.attrib & _A_SYSTEM) || (SourceBk.attrib & _A_HIDDEN) || (SourceBk.attrib & _A_RDONLY) || (SourceBk.attrib & _A_SUBDIR))) {
      TargetFile=TargetDir+"\\"+SourceBk.name;
      bool existe=pegaAttribArq(TargetFile,TargetBk);
      bool newer=false;
      if (existe) {
        newer = (SourceBk.time_write>TargetBk.time_write);
      }
      if (!existe || newer) {
        SourceFile=SourceDir+"\\"+SourceBk.name;
        if (modo=='l' || modo=='a') printf("  copiaArq %s\n",SourceFile.c_str());
        if (modo=='p' || modo=='a') copiaArq(SourceFile,TargetFile);
      }
    }
    done = _findnext(handle, &SourceBk);
  }
  _findclose(handle);

  handle = done = _findfirst(SourceWild.c_str(), &SourceBk);
  while (done!=-1) {
    if (SourceBk.attrib & _A_SUBDIR) {
      string st2=SourceBk.name;
      if (st2!="." && st2!="..") {
        TargetFile=TargetDir+"\\"+SourceBk.name;
        SourceFile=SourceDir+"\\"+SourceBk.name;
        bool existe=isDirec(TargetFile);
        if (!existe) {
          if (modo=='l' || modo=='a') printf("  copiaDir %s\n",SourceFile.c_str());
          if (modo=='p' || modo=='a') copiaDir(SourceFile,TargetFile);
        } else {
          updateTarget(SourceFile,TargetFile,modo);
        }
      }
    }
    done = _findnext(handle, &SourceBk);
  }
  _findclose(handle);
}

void maior(string nomedir, unsigned tamanho)
{ char buf[_MAX_PATH];
  _fullpath(buf, nomedir.c_str(), _MAX_PATH);
  printf("Files of %s larger than %u bytes:\n",buf,tamanho);
  if (!isDirec(nomedir)) erro("Erro: Deve especificar o nome de um diretorio");

  struct _finddata_t f;
  intptr_t handle, done;
  string st=nomedir+"\\*";
  handle = done = _findfirst(st.c_str(), &f);
  while (done!=-1) {
    if (f.size>=tamanho) {
      if (f.attrib & _A_ARCH)   printf("A"); else printf(".");
      if (f.attrib & _A_SYSTEM) printf("S"); else printf(".");
      if (f.attrib & _A_HIDDEN) printf("H"); else printf(".");
      if (f.attrib & _A_RDONLY) printf("R"); else printf(".");
      if (f.attrib & _A_SUBDIR) printf("D"); else printf(".");
  
      if (f.size<1048576) printf(" %8lu Bytes",f.size);
      else if (f.size<1073741824) printf(" %8luKBytes",f.size/1024);
      else printf(" %8luMBytes",f.size/1048576);
  
      printf(" %s\\%s\n",nomedir.c_str(),f.name);
    }
    done = _findnext(handle, &f);
  }
  _findclose(handle);

  handle = done = _findfirst(st.c_str(), &f);
  while (done!=-1) {
    if (f.attrib & _A_SUBDIR) {
      string st2=f.name;
      if (st2!="." && st2!="..") maior(nomedir+"\\"+st2,tamanho);
    }
    done = _findnext(handle, &f);
  }
  _findclose(handle);
}
  
#endif //#ifdef _WIN64

} // namespace cek


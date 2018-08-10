#include <cekeikon.h>

void enumera(int argc, char** argv) { 
  if (argc<3) {
    printf("Enumera: Renomeia nomes dos arquivos com numeracao sequencial\n");
    printf("Enumera prefixo NOME1*.* NOME1*.* ...\n");
    printf("  Ex: Enumera p x.ext y.ext z.ext => vira p0.ext p1.ext p2.ext\n");
    printf("Use com muito cuidado. Pode apagar arquivos.\n");
    erro("Erro: Numero de argumentos invalido");
  }
  int n=argc-2;
  int digitos=int( log10(n) ) + 1;
  vector<string> ent(n), sai(n);
  string prefixo=argv[1];
  
  for (int i=2; i<argc; i++) 
    ent[i-2] = argv[i];
  
  for (unsigned i=0; i<ent.size(); i++) {
    string nome;
    if (digitos==1)      nome=format("%01d",i);
    else if (digitos==2) nome=format("%02d",i);
    else if (digitos==3) nome=format("%03d",i);
    else if (digitos==4) nome=format("%04d",i);
    else if (digitos==5) nome=format("%05d",i);
    
    string st;
    if (diretorio(ent[i])!="") st=diretorio(ent[i])+"/";
    st = st + prefixo + nome;
    if (sufixo(ent[i])!="") st = st + "." + sufixo(ent[i]);
    sai[i]=st;
  }
  
  for (unsigned i=0; i<ent.size(); i++) 
    cout << "Vou renomear " << ent[i] << " para " << sai[i] << endl;
  
  cout << "Continua? (s/n) ";
  int ch=getchar();
  if (ch!='s' && ch!='S') {
    cout << "Nao alterei nenhum nome.\n";
    exit(0);
  }

  for (unsigned i=0; i<ent.size(); i++) {
    int result = rename( ent[i].c_str(), sai[i].c_str() );
    if (result==0)
      cout << "Renomeei " << ent[i] << " para " << sai[i] << endl;
    else 
      xerro1("Nao consegui renomear " + ent[i] + " para " + sai[i]);
  }
}

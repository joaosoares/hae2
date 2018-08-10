// MSERG.CPP - 2016
// Compile com opencv2.4.10 (-v2)
#include <cekeikon.h>

void mserg(int argc, char** argv) {
  const char* keys =
    " curto | longo    |default| explicacao\n"
    "  -d   | -delta   |     5 | compara tams cd delta graylevels\n"
    "  -min | -minarea |    60 | area minima em pixels\n"
    "  -max | -maxarea | 14400 | area maxima em pixels\n"
    "  -var | -maxvar  |  0.25 | poda filho com area similar\n"
    "  -div | -mindiv  |  0.20 | cut off diversity<mindiv\n"
    "  -vis | -visinter| false | visualiza imagens intermediarias\n";

  if (argc<3) {
    printf("MserG: Maximally stable extremal region\n");
    printf("MserG ent.pgm sai.ppm [opcoes]\n");
    printf("%s",keys);
    erro("Erro: Numero de argumentos invalido");
  }

  ArgComando cmd(argc,argv);
  string nomeent=cmd.getCommand(0);
  if (nomeent=="") erro("Erro: Nao especificou ent.pgm");
  string nomesai=cmd.getCommand(1);
  if (nomesai=="") erro("Erro: Nao especificou sai.ppm");
 
  int delta=cmd.getInt("-d","-delta",5);
  int minArea=cmd.getInt("-min","-minarea",60);
  int maxArea=cmd.getInt("-max","-maxarea",14400);
  double maxVar=cmd.getDouble("-var","-maxvar",0.25);
  double minDiv=cmd.getDouble("-div","-mindiv",0.20);
  bool visInter=cmd.getBool("-vis","-visinter",false);
  cmd.leuTodos();

  Mat_<GRY> g; le(g,argv[1]);

  //xprint(delta);
  //xprint(minArea);
  //xprint(maxArea);
  //xprint(maxVar);
  //xprint(minDiv);
  
  MSER mser(delta,minArea,maxArea,maxVar,minDiv);
  vector< vector<Point> > v;
  mser(g,v);

  Mat_<COR> a;
  converte(g,a);

  srand(7);
  for (int r=v.size()-1; r>=0; r--) {
    COR cor=COR(rand()%160,128+rand()%128,128+rand()%128);
    cor=converteCor(cor,CV_HLS2BGR);
    for (unsigned p=0; p<v[r].size(); p++) {
      Point q=v[r][p];
      assert(0<=q.x && q.x<a.cols && 0<=q.y && q.y<a.rows);
      a(v[r][p])=cor;
    }
  }
  cout << "#regioes=" << v.size() << endl;
  imp(a,argv[2]);

  if (visInter) {
    for (int r=v.size()-1; r>=0; r--) {
      Mat_<COR> a;
      converte(g,a);
      for (unsigned p=0; p<v[r].size(); p++) 
        a(v[r][p])=COR(0,0,255);
      putTxt(a,v[r][0].y,v[r][0].x,to_string(v[r].size()),COR(255,255,0));
      mostra(a);
      waitKey(300);
    }
  }
}

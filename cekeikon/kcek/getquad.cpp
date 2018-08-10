#include <cekeikon.h>

void quadrilateral(Mat_<COR>& a, Point2f* src)
{ line(a,src[0],src[1],Scalar(0,0,255));
  line(a,src[1],src[3],Scalar(0,0,255));
  line(a,src[3],src[2],Scalar(0,0,255));
  line(a,src[2],src[0],Scalar(0,0,255));
}

void getquad(int argc, char** argv)
{ if (argc!=4) {
    printf("GetQuad: Extrai uma regiao quadrilatera e faz warping para 128x128\n");
    printf("GetQuad ent.ppm sai.ppm \"quad=x1 y1 x2 y2 x3 y3 x4 y4\"\n");
    printf("  Pontos em ordem raster (ul ur dl dr)\n");
    erro("Erro: Numero de argumentos invalido");
  }

  Mat_<COR> ent; le(ent,argv[1]);
  const int tam=128;

  Point2f src[4];
  ISTR arq(argv[3]);
  string st=leStr(arq);
  while (st!="eof") {
    if (st=="quad") { 
      leNum(arq,src[0].x); 
      leNum(arq,src[0].y); 
      leNum(arq,src[1].x); 
      leNum(arq,src[1].y); 
      leNum(arq,src[2].x); 
      leNum(arq,src[2].y); 
      leNum(arq,src[3].x); 
      leNum(arq,src[3].y); 
    } else {
      erro("Erro: Palavra desconhecida ",st);
    }
    st=leStr(arq);
  }

  Point2f dst[4];
  dst[0]=Point2f(0,0);
  dst[1]=Point2f(tam-1,0);
  dst[2]=Point2f(0,tam-1);
  dst[3]=Point2f(tam-1,tam-1);

  Mat T=getPerspectiveTransform(src,dst);

  Mat_<COR> sai;
  warpPerspective(ent,sai,T,Size(tam,tam),INTER_LINEAR,BORDER_REPLICATE);
  //mostra(sai);
  //quadrilateral(ent,src);
  //mostra(ent);
  imp(sai,argv[2]);
}

#include <cekeikon.h>

void campox(int argc, char** argv)
{ if (argc!=5) {
    printf("CampoX: Visualiza IMGCPX/MatCpx como campo vetorial\n");
    printf("CampoX ent.img sai.png fator espaco\n");
    printf("  fator: Multiplica os numeros complexos\n");
    printf("  espaco: Distancia em pixels entre dois numeros complexos\n");
    erro("Erro: Numero de argumentos invalido");
  }

  Mat_<CPX> a; le(a,argv[1]);
  double fator; convArg(fator,argv[3]);
  int espaco; convArg(espaco,argv[4]);
  Mat_<COR> b=campox(a,fator,espaco);
  imp(b,argv[2]);
}

//void campox(int argc, char** argv)
//{ if (argc!=4) {
    //printf("CampoX: Visualiza IMGCPX/MatCpx como campo vetorial\n");
    //printf("CampoX ent.img fator espaco\n");
    //printf("  fator: Multiplica os numeros complexos\n");
    //printf("  espaco: Distancia em pixels entre dois numeros complexos\n");
    //erro("Erro: Numero de argumentos invalido");
  //}

  //Mat_<CPX> a; le(a,argv[1]);
  //double fator; convArg(fator,argv[2]);
  //int espaco; convArg(espaco,argv[3]);
  //Mat_<COR> b=campox(a,fator,espaco);
  //mostra(b);
//}

// void campox(int argc, char** argv)
// { if (argc!=4) {
//     printf("CampoX: Visualiza IMGCPX/MatCpx como campo vetorial\n");
//     printf("CampoX ent.img fator espaco\n");
//     printf("  fator: Multiplica os numeros complexos\n");
//     printf("  espaco: Distancia em pixels entre dois numeros complexos\n");
//     erro("Erro: Numero de argumentos invalido");
//   }

//   double fator; convArg(fator,argv[2]);

//   int espaco; convArg(espaco,argv[3]);
//   int espaco2=espaco/2;

//   Mat_<CPX> a; le(a,argv[1]);
//   Mat_<COR> b(espaco*a.rows,espaco*a.cols,COR(255,255,255));

//   for (int l=0; l<a.rows; l++)
//     for (int c=0; c<a.cols; c++) {
//       flecha(b, l*espaco+espaco2, c*espaco+espaco2, 
//                 (l*espaco+espaco2)-cvRound(fator*imag(a.at<CPX>(l,c))), (c*espaco+espaco2)+cvRound(fator*real(a.at<CPX>(l,c))) );
//       b(l*espaco+espaco2, c*espaco+espaco2)=COR(0,0,255);
//     }
//   mostra(b);
// }

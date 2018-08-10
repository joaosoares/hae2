#include "cekeikon.h"

namespace cek {

//<<<<<<<<<<<<<<<<<<<< Manipulacao basica <<<<<<<<<<<<<<<<<<<<<<<<<<<
// void vira(DWORD& d)
// { BYTE* b = (BYTE*)(&d);
//   swap( b[0], b[3] ); swap( b[1], b[2] );
// }

// void vira(int& d)
// { BYTE* b = (BYTE*)(&d);
//   swap( b[0], b[3] ); swap( b[1], b[2] );
// }

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Mat??? - GRY COR SHT FLT DBL CPX

//<<< toMatGRY
/*
Mat_<GRY> toMatGRY(Mat_<COR> ent)
{ Mat_<GRY> sai; cvtColor(ent, sai, CV_BGR2GRAY); return sai; }

Mat_<GRY> toMatGRY(Mat_<SHT> ent)
{ Mat_<GRY> sai; ent.convertTo(sai,CV_8U); return sai; }

Mat_<GRY> toMatGRY(Mat_<FLT> ent, double alpha, double beta)
{ Mat_<GRY> sai; ent.convertTo(sai,CV_8U,alpha,beta); return sai; }

Mat_<GRY> toMatGRY(Mat_<DBL> ent, double alpha, double beta)
{ Mat_<GRY> sai; ent.convertTo(sai,CV_8U,alpha,beta); return sai; }

//<<< toMatCOR
Mat_<COR> toMatCOR(Mat_<GRY> ent)
{ Mat_<COR> sai; cvtColor(ent, sai, CV_GRAY2BGR); return sai; }

Mat_<COR> toMatCOR(Mat_<SHT> ent)
{ Mat_<COR> sai;
  Mat_<GRY> temp; 
  ent.convertTo(temp, CV_8U);
  cvtColor(temp, sai, CV_GRAY2BGR); 
  return sai;
}

Mat_<COR> toMatCOR(Mat_<FLT> ent)
{ Mat_<COR> sai;
  Mat_<GRY> temp; 
  ent.convertTo(temp, CV_8U, 255.0, 0.0);
  cvtColor(temp, sai, CV_GRAY2BGR); 
  return sai;
}

Mat_<COR> toMatCOR(Mat_<DBL> ent)
{ Mat_<COR> sai;
  Mat_<GRY> temp; 
  ent.convertTo(temp, CV_8U, 255.0, 0.0);
  cvtColor(temp, sai, CV_GRAY2BGR); 
  return sai;
}

Mat_<COR> toMatCOR(Mat_<CPX> ent, char modo)
// modo=='h': converte MATCPX ent para MATCOR d usando HSV
// modo=='r': converte MATCPX ent para MATCOR d usando RB
{ Mat_<COR> sai(ent.size()); 
  COR cor;
  if (modo=='h') {
    for (int l=0; l<sai.rows; l++) {
      for (int c=0; c<sai.cols; c++) {
        CPX e=ent(l,c);
        if (e!=CPX(0.0,0.0)) {
          double ang=modulo(arg(e),M_2PI)/M_2PI; // ang entre 0 e 1
          cor[0]=saturate_cast<uchar>(180.0*ang); // H de 0 a 180
          cor[1]=255; // S
          cor[2]=saturate_cast<uchar>(255.0*abs(e)); // V
        } else {
          cor=COR(0,0,0);
        }
        sai(l,c)=cor;
      }
    }
    cvtColor(sai,sai,CV_HSV2BGR);
  } else if (modo=='r') {
    for (int l=0; l<sai.rows; l++) {
      for (int c=0; c<sai.cols; c++) {
        CPX e=ent(l,c);
        cor[2]=saturate_cast<uchar>(127.0*e.real()+128.0); // R
        cor[1]=0;
        cor[0]=saturate_cast<uchar>(127.0*e.imag()+128.0); // B
        sai(l,c)=cor;
      }
    }
  } else erro("Erro converte: modo invalido");
  return sai;
}

//<<< toMatSHT
Mat_<SHT> toMatSHT(Mat_<GRY> ent)
{ Mat_<SHT> sai; ent.convertTo(sai,CV_16S); return sai; }

Mat_<SHT> toMatSHT(Mat_<COR> ent)
{ Mat_<GRY> temp; cvtColor(ent, temp, CV_BGR2GRAY); Mat_<SHT> sai; temp.convertTo(sai,CV_16S); return sai; }

Mat_<SHT> toMatSHT(Mat_<FLT> ent, double alpha, double beta)
{ Mat_<SHT> sai; ent.convertTo(sai,CV_16S,alpha,beta); return sai; }

Mat_<SHT> toMatSHT(Mat_<DBL> ent, double alpha, double beta)
{ Mat_<SHT> sai; ent.convertTo(sai,CV_16S,alpha,beta); return sai; }

//<<< toMatFLT
Mat_<FLT> toMatFLT(Mat_<GRY> ent, double alpha, double beta)
{ Mat_<FLT> sai; ent.convertTo(sai,CV_32F,alpha,beta); return sai; }

Mat_<FLT> toMatFLT(Mat_<COR> ent)
{ Mat_<GRY> temp; cvtColor(ent, temp, CV_BGR2GRAY); Mat_<FLT> sai; temp.convertTo(sai,CV_32F,1.0/255.0,0.0); return sai; }

Mat_<FLT> toMatFLT(Mat_<SHT> ent, double alpha, double beta)
{ Mat_<FLT> sai; ent.convertTo(sai,CV_32F,alpha,beta); return sai; }

Mat_<FLT> toMatFLT(Mat_<DBL> ent)
{ Mat_<FLT> sai; ent.convertTo(sai,CV_32F); return sai; }

//<<< toMatDBL
Mat_<DBL> toMatDBL(Mat_<GRY> ent, double alpha, double beta)
{ Mat_<DBL> sai; ent.convertTo(sai,CV_64F,alpha,beta); return sai; }

Mat_<DBL> toMatDBL(Mat_<COR> ent)
{ Mat_<GRY> temp; cvtColor(ent, temp, CV_BGR2GRAY); Mat_<DBL> sai; temp.convertTo(sai,CV_64F,1.0/255.0,0.0); return sai; }

Mat_<DBL> toMatDBL(Mat_<SHT> ent, double alpha, double beta)
{ Mat_<DBL> sai; ent.convertTo(sai,CV_64F,alpha,beta); return sai; }

Mat_<DBL> toMatDBL(Mat_<FLT> ent)
{ Mat_<DBL> sai; ent.convertTo(sai,CV_64F); return sai; }
*/

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< converte
COR converteCor(COR a, int code) {
  //CV_BGR2HLS, CV_RGB2HLS, CV_HLS2BGR, CV_HLS2RGB
  Mat_<COR> ai(1,1,a);
  Mat_<COR> bi;
  cvtColor(ai,bi,code);
  return bi(0);
} 

void converte(Mat_<GRY> ent, Mat_<COR>& sai)
{ cvtColor(ent, sai, CV_GRAY2BGR); }

void converte(Mat_<COR> ent, Mat_<GRY>& sai)
{ cvtColor(ent, sai, CV_BGR2GRAY); }

void converte(Mat_<GRY> ent, Mat_<FLT>& sai, double alpha, double beta)
{ ent.convertTo(sai, CV_32F, alpha, beta); }

void converte(Mat_<FLT> ent, Mat_<GRY>& sai, double alpha, double beta)
{ ent.convertTo(sai, CV_8U, alpha, beta); }

void converte(Mat_<FLT> ent, Mat_<COR>& sai)
{ Mat_<GRY> temp; ent.convertTo(temp, CV_8U, 255.0, 0.0);
  cvtColor(temp, sai, CV_GRAY2BGR); 
}

void converte(Mat_<COR> ent, Mat_<FLT>& sai)
{ Mat_<GRY> temp; cvtColor(ent, temp, CV_BGR2GRAY); 
  temp.convertTo(sai, CV_32F, 1.0/255.0, 0.0); 
}

void converte(Mat_<GRY> ent, Mat_<CPX>& sai)
{ sai.create(ent.size()); //sai=CPX(0,0);
  for (int l=0; l<ent.rows; l++)
    for (int c=0; c<ent.cols; c++)
      //sai(l,c).real()=ent(l,c)/255.0;
      sai(l,c)=CPX(ent(l,c)/255.0,0.0);
}

void converte(Mat_<CPX> ent, Mat_<COR>& sai, char modo)
// modo=='h': converte MATCPX ent para MATCOR d usando HSV
// modo=='r': converte MATCPX ent para MATCOR d usando RB
{ 
  sai.create(ent.size()); 
  COR cor;
  if (modo=='h') {
    for (int l=0; l<sai.rows; l++) {
      for (int c=0; c<sai.cols; c++) {
        CPX e=ent(l,c);
        if (e!=CPX(0.0,0.0)) {
          double ang=modulo(arg(e),M_2PI)/M_2PI; // ang entre 0 e 1
          cor[0]=saturate_cast<uchar>(180.0*ang); // H de 0 a 180
          cor[1]=255; // S
          cor[2]=saturate_cast<uchar>(255.0*abs(e)); // V
        } else {
          cor=COR(0,0,0);
        }
        sai(l,c)=cor;
      }
    }
    cvtColor(sai,sai,CV_HSV2BGR);
  } else if (modo=='r') {
    for (int l=0; l<sai.rows; l++) {
      for (int c=0; c<sai.cols; c++) {
        CPX e=ent(l,c);
        cor[2]=saturate_cast<uchar>(127.0*e.real()+128.0); // R
        cor[1]=0;
        cor[0]=saturate_cast<uchar>(127.0*e.imag()+128.0); // B
        sai(l,c)=cor;
      }
    }
  } else erro("Erro converte: modo invalido");
}

void convertePOL2COR(Mat_<CPX> ent, Mat_<COR>& sai)
// converte MatCPX no modo polar para saida em HSV
{ sai.create(ent.size()); 
  COR cor;
  for (int l=0; l<sai.rows; l++) {
    for (int c=0; c<sai.cols; c++) {
      CPX e=ent(l,c);
      if (e!=CPX(0.0,0.0)) {
        double ang=modulo(e.imag(),M_2PI)/M_2PI; // 0<=ang<1
        cor[0]=saturate_cast<uchar>(180.0*ang); // 0<=H<180
        cor[1]=255; // S
        cor[2]=saturate_cast<uchar>(255.0*e.real()); // V
      } else {
        cor=COR(0,0,0);
      }
      sai(l,c)=cor;
    }
  }
  cvtColor(sai,sai,CV_HSV2BGR);
}

void converte(Mat_<GRY> ent, Mat_<SHT>& sai, double alpha, double beta)
{ ent.convertTo(sai,CV_16S,alpha,beta); }

void converte(Mat_<SHT> ent, Mat_<GRY>& sai, double alpha, double beta)
{ ent.convertTo(sai,CV_8U,alpha,beta); }

void converte(Mat_<SHT> ent, Mat_<FLT>& sai, double alpha, double beta)
{ ent.convertTo(sai,CV_32F,alpha,beta); }

void converte(Mat_<FLT> ent, Mat_<SHT>& sai, double alpha, double beta)
{ ent.convertTo(sai,CV_16S,alpha,beta); }

void converte(Mat_<GRY> ent, Mat_<DBL>& sai, double alpha, double beta)
{ ent.convertTo(sai, CV_64F, alpha, beta); }

void converte(Mat_<DBL> ent, Mat_<GRY>& sai, double alpha, double beta)
{ ent.convertTo(sai, CV_8U, alpha, beta); }

void converte(Mat_<DBL> ent, Mat_<COR>& sai)
{ Mat_<GRY> temp; ent.convertTo(temp, CV_8U, 255.0, 0.0);
  cvtColor(temp, sai, CV_GRAY2BGR); 
}

void converte(Mat_<COR> ent, Mat_<DBL>& sai)
{ Mat_<GRY> temp; cvtColor(ent, temp, CV_BGR2GRAY); 
  temp.convertTo(sai, CV_64F, 1.0/255.0, 0.0); 
}

void converte(Mat_<FLT> ent, Mat_<DBL>& sai)
{ ent.convertTo(sai, CV_64F); }

void converte(Mat_<DBL> ent, Mat_<FLT>& sai)
{ ent.convertTo(sai, CV_32F); }

void converte(Mat_<COR> ent, Mat_<CORF>& sai, double alpha, double beta)
{ ent.convertTo(sai, CV_32F, alpha, beta); }

void converte(Mat_<CORF> ent, Mat_<COR>& sai, double alpha, double beta)
{ ent.convertTo(sai, CV_8U, alpha, beta); }

void converte(COR ent, CORF& sai)
{ sai = ent/255.0; }

void converte(CORF ent, COR& sai)
{ sai[0] = saturate_cast<BYTE>(255*ent[0]); 
  sai[1] = saturate_cast<BYTE>(255*ent[1]); 
  sai[2] = saturate_cast<BYTE>(255*ent[2]); 
}

void converte(Mat_<FLT> ent, Mat_<CPX>& sai) {
  sai.create(ent.size());
  for (unsigned i=0; i<ent.total(); i++)
    sai(i) = CPX{ ent(i), 0.0 };
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< split-merge
void split(Mat_<COR> ent, Mat_<GRY>& b, Mat_<GRY>& g, Mat_<GRY>& r)
{ vector< Mat > gray(3);
  split(ent,gray);
  b=gray[0];
  g=gray[1];
  r=gray[2];
}

void merge(Mat_<GRY> b, Mat_<GRY> g, Mat_<GRY> r, Mat_<COR>& sai)
{ vector< Mat > gray(3);
  gray[0]=b;
  gray[1]=g;
  gray[2]=r;
  merge(gray,sai);
}

void split(Mat_<CPX> ent, Mat_<FLT>& re, Mat_<FLT>& im)
{ vector< Mat > flt(2);
  split(ent,flt);
  re=flt[0];
  im=flt[1];
}

void merge(Mat_<FLT> re, Mat_<FLT> im, Mat_<CPX>& sai)
{ vector< Mat > flt(2);
  flt[0]=re;
  flt[1]=im;
  merge(flt,sai);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< campox <<<<<<<<<<<<<<<<<<<<<
Mat_<COR> campox(Mat_<CPX> a, double fator, int espaco)
//Converte Mat_<CPX> para campo vetorial com flechas
{ int espaco2=espaco/2;
  Mat_<COR> b(espaco*a.rows,espaco*a.cols,COR(255,255,255));
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++) {
      flecha(b, l*espaco+espaco2, c*espaco+espaco2, 
                (l*espaco+espaco2)-cvRound(fator*imag(a(l,c))), 
                (c*espaco+espaco2)+cvRound(fator*real(a(l,c))) );
      b(l*espaco+espaco2, c*espaco+espaco2)=COR(0,0,255);
    }
  return b;
}

//<<<<<<<<<<<<<<<<<<< OpenCV/OpenGL 
Mat_<COR> cv2gl(Mat_<COR> ent)
{ Mat_<COR> sai=ent.clone();
  flip(sai,sai,0);
  cvtColor(sai,sai,CV_BGR2RGB);
  return sai;
}

} // namespace cek

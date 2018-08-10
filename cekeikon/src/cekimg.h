#ifndef __CEKIMG__
#define __CEKIMG__

#include "cekvet.h"

namespace cek {
using namespace std;
using namespace cv;

//<<<<<<<<<<<<<<<<<<<< Manipulacao basica <<<<<<<<<<<<<<<<<<<<<<<<<<<
// EXPORTA void vira(DWORD& d);
// EXPORTA void vira(int& d);

//<<<<<<<<<<<<<<<<<<<<<<<<<<< namespace HEADER <<<<<<<<<<<<<<<<<<<<<<
namespace HEADER {

/*
struct EXPORTA WIN3XHEAD
{ //WORD  ImageFileType; // Tirei para permitir alinhamento
  DWORD FileSize;
  WORD  Reserved1;
  WORD  Reserved2;
  DWORD ImageDataOffset;
};

struct EXPORTA WIN3XINFOHEAD
{ DWORD HeaderSize;
  DWORD ImageWidth;
  DWORD ImageHeight;
  WORD  NumberOfImagePlanes;
  WORD  BitsPerPixel;
  DWORD CompressionMethod;
  DWORD SizeOfBitmap;
  DWORD HorzResolution;
  DWORD VertResolution;
  DWORD NumColorsUsed;
  DWORD NumSignificantColors;
};

struct EXPORTA RGBQUAD
{ BYTE Blue;
  BYTE Green;
  BYTE Red;
  BYTE Reserved;
};
*/

/*
1) Arquivo TGA 256 grayscale (tgaG)
[0000] 00 00 03 00 00 00 00 00 [] 00 00 00 00 05 00 05 00
                  |  ^     ^                 ^  x  ^  y  ^
            c1         CML             c3     12 13 14 15
[0010] 08 20/CF CF CF CF CF CF [] CF CF CF CF CF CF CF CF
       c4 ^ ^acaba header
          |- 0 indica linhas de baixo para cima (gerada pelo alchemy/PSP)
             0x20 indica linhas de cima para baixo (gerada pelo winjpeg)

2) Arquivo TGA 256 com palette (tgaP)
[0000] 00 01 01 00 00 00 01 18 [] 00 00 00 00 03 00 04 00
                  |  ^5CML6^                 ^  x  ^  y  ^
            c1          c2            c3      12 13 14 15
[0010] 08 20 00 00 00 33 00 00 [] 66 00 00 80 00 00 CC 00
       c4 ^ ^acaba header
          |- 0 indica linhas de baixo para cima (gerada pelo alchemy/PSP)
             0x20 indica linhas de cima para baixo (gerada pelo winjpeg)?

3) Arquivo TGA colorido
[0000] 00 00 02 00 00 00 00 00 [] 00 00 00 00 05 00 05 00
                  |  ^     ^    |            ^  x  ^  y  ^
            c1         cml            c3      12 13 14 15
[0010] 18 20/00 00 FF/00 FF 00/[] FF 00 00/B2 00 00/B2 00
       c4 ^ ^acaba header         b  g  r  b  g  r
          |- 0 indica linhas de baixo para cima (gerada pelo alchemy/PSP)
             0x20 indica linhas de cima para baixo (gerada pelo winjpeg)
*/
struct EXPORTA HeaderTga {
  DWORD c1,c2,c3;
  WORD ImageWidth;
  WORD ImageHeight;
  BYTE c4;
  BYTE ordem;
};

};

//<<<<<<<<<<<<<<<<<<< Funcoes de conversao <<<<<<<<<<<<<<<<<<<<<<<<<<<
//............ 2G ..................
inline GRY C2G(COR cor) 
{ return saturate_cast<GRY>( 0.299*cor[2] + 0.587*cor[1] + 0.114*cor[0]); }

inline GRY int2G(int i) 
{ return saturate_cast<GRY>(i); }

inline GRY double2G(double d) 
{ return saturate_cast<GRY>(d); }

inline GRY F2G(FLT d) 
{ return saturate_cast<GRY>(255.0*d); }

//.......... 2C ................
inline COR G2C(GRY b) 
{ return COR(b,b,b); }

inline COR F2C(FLT b) 
{ GRY c=F2G(b);
  return COR(c,c,c);
}

inline COR CORF2COR(CORF corf) 
{ return COR(
    saturate_cast<BYTE>(255*corf[0]),
    saturate_cast<BYTE>(255*corf[1]), 
    saturate_cast<BYTE>(255*corf[2]) );
}

//.......... 2FLT ..............
inline FLT G2F(GRY b) //OK
{ return b/255.0; }

inline FLT C2F(COR cor) //OK
{ return (0.299*cor[2] + 0.587*cor[1] + 0.114*cor[0])/255.0; }

//.......... 2CPX ..............
inline CPX G2X(GRY b) //OK
{ return CPX( G2F(b), 0.0); }

inline CPX C2X(COR cor)
{ return CPX( C2F(cor), 0.0); }

inline CPX F2X(FLT b)
{ return CPX(b, 0.0); }

//.......... 2CORF .............
inline CORF COR2CORF(COR cor) 
{ return cor/255.0; }

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Mat??? - GRY COR SHT FLT DBL CPX
// EXPORTA Mat_<GRY> toMatGRY(Mat_<COR> ent);
// EXPORTA Mat_<GRY> toMatGRY(Mat_<SHT> ent);
// EXPORTA Mat_<GRY> toMatGRY(Mat_<FLT> ent, double alpha=255, double beta=0);
// EXPORTA Mat_<GRY> toMatGRY(Mat_<DBL> ent, double alpha=255, double beta=0);

// EXPORTA Mat_<COR> toMatCOR(Mat_<GRY> ent);
// EXPORTA Mat_<COR> toMatCOR(Mat_<SHT> ent);
// EXPORTA Mat_<COR> toMatCOR(Mat_<FLT> ent);
// EXPORTA Mat_<COR> toMatCOR(Mat_<DBL> ent);
// EXPORTA Mat_<COR> toMatCOR(Mat_<CPX> ent, char modo='h');

// EXPORTA Mat_<SHT> toMatSHT(Mat_<GRY> ent);
// EXPORTA Mat_<SHT> toMatSHT(Mat_<COR> ent);
// EXPORTA Mat_<SHT> toMatSHT(Mat_<FLT> ent, double alpha=255, double beta=0);
// EXPORTA Mat_<SHT> toMatSHT(Mat_<DBL> ent, double alpha=255, double beta=0);

// EXPORTA Mat_<FLT> toMatFLT(Mat_<GRY> ent, double alpha=1.0/255.0, double beta=0);
// EXPORTA Mat_<FLT> toMatFLT(Mat_<COR> ent);
// EXPORTA Mat_<FLT> toMatFLT(Mat_<SHT> ent, double alpha=1.0/255.0, double beta=0);
// EXPORTA Mat_<FLT> toMatFLT(Mat_<DBL> ent);

// EXPORTA Mat_<DBL> toMatDBL(Mat_<GRY> ent, double alpha=1.0/255.0, double beta=0);
// EXPORTA Mat_<DBL> toMatDBL(Mat_<COR> ent);
// EXPORTA Mat_<DBL> toMatDBL(Mat_<SHT> ent, double alpha=1.0/255.0, double beta=0);
// EXPORTA Mat_<DBL> toMatDBL(Mat_<FLT> ent);

/*
EXPORTA void converte(Mat_<GRY> ent, Mat_<CPX>& sai);
// modo=='h': converte MATCPX ent para MATCOR d usando HSV
// modo=='r': converte MATCPX ent para MATCOR d usando RB
EXPORTA void convertePOL2COR(Mat_<CPX> ent, Mat_<COR>& sai);
// converte MatCPX no modo polar para saida em HSV
*/

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< converte
EXPORTA COR converteCor(COR a, int code);

EXPORTA void converte(Mat_<GRY> ent, Mat_<COR>& sai);
EXPORTA void converte(Mat_<COR> ent, Mat_<GRY>& sai);

EXPORTA void converte(Mat_<GRY> ent, Mat_<FLT>& sai, double alpha=1.0/255.0, double beta=0);
EXPORTA void converte(Mat_<FLT> ent, Mat_<GRY>& sai, double alpha=255, double beta=0);
EXPORTA void converte(Mat_<FLT> ent, Mat_<COR>& sai);
EXPORTA void converte(Mat_<COR> ent, Mat_<FLT>& sai);

EXPORTA void converte(Mat_<GRY> ent, Mat_<CPX>& sai);
EXPORTA void converte(Mat_<CPX> ent, Mat_<COR>& sai, char modo='h');
// modo=='h': converte MATCPX ent para MATCOR d usando HSV
// modo=='r': converte MATCPX ent para MATCOR d usando RB
EXPORTA void convertePOL2COR(Mat_<CPX> ent, Mat_<COR>& sai);
// converte MatCPX no modo polar para saida em HSV

EXPORTA void converte(Mat_<GRY> ent, Mat_<SHT>& sai, double alpha=1, double beta=0);
EXPORTA void converte(Mat_<SHT> ent, Mat_<GRY>& sai, double alpha=1, double beta=0);
EXPORTA void converte(Mat_<SHT> ent, Mat_<FLT>& sai, double alpha=1.0/255.0, double beta=0);
EXPORTA void converte(Mat_<FLT> ent, Mat_<SHT>& sai, double alpha=255, double beta=0);

EXPORTA void converte(Mat_<GRY> ent, Mat_<DBL>& sai, double alpha=1.0/255.0, double beta=0);
EXPORTA void converte(Mat_<DBL> ent, Mat_<GRY>& sai, double alpha=255, double beta=0);
EXPORTA void converte(Mat_<DBL> ent, Mat_<COR>& sai);
EXPORTA void converte(Mat_<COR> ent, Mat_<DBL>& sai);
EXPORTA void converte(Mat_<FLT> ent, Mat_<DBL>& sai);
EXPORTA void converte(Mat_<DBL> ent, Mat_<FLT>& sai);
EXPORTA void converte(Mat_<COR> ent, Mat_<CORF>& sai, double alpha=1.0/255.0, double beta=0);
EXPORTA void converte(Mat_<CORF> ent, Mat_<COR>& sai, double alpha=255, double beta=0);
EXPORTA void converte(COR ent, CORF& sai);
EXPORTA void converte(CORF ent, COR& sai);

EXPORTA void converte(Mat_<FLT> ent, Mat_<CPX>& sai);
// para converter Mat_<CPX> para Mat_<FLT>, use modulo, real ou imag

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< split-merge
EXPORTA void split(Mat_<COR> ent, Mat_<GRY>& b, Mat_<GRY>& g, Mat_<GRY>& r);
EXPORTA void merge(Mat_<GRY> b, Mat_<GRY> g, Mat_<GRY> r, Mat_<COR>& sai);
EXPORTA void split(Mat_<CPX> ent, Mat_<FLT>& re, Mat_<FLT>& im);
EXPORTA void merge(Mat_<FLT> re, Mat_<FLT> im, Mat_<CPX>& sai);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< campox <<<<<<<<<<<<<<<<<<<<<
EXPORTA Mat_<COR> campox(Mat_<CPX> a, double fator, int espaco);
//Converte Mat_<CPX> para campo vetorial com flechas

//<<<<<<<<<<<<<<<<<<< OpenCV/OpenGL 
EXPORTA Mat_<COR> cv2gl(Mat_<COR> ent);
inline Mat_<COR> gl2cv(Mat_<COR> ent) { return cv2gl(ent); }

} //namespace cek

#endif

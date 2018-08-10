#ifdef _MSC_VER
  #ifdef _WINDLL
     #define EXPORTA __declspec(dllexport)
  #else 
     #define EXPORTA __declspec(dllimport)
  #endif
#endif

#ifdef __GNUC__
  #define EXPORTA 
#endif

extern "C" // Forca nao fazer name mangling - estilo C
EXPORTA void GetMACaddress(unsigned char MACData[16][6], int* n);


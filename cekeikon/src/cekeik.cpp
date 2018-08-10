#include "cekeikon.h"

namespace cek {

string depth2str(int t)
{ if (t==CV_8U) return "CV_8U";
  if (t==CV_8S) return "CV_8S";
  if (t==CV_16U) return "CV_16U";
  if (t==CV_16S) return "CV_16S";
  if (t==CV_32S) return "CV_32S";
  if (t==CV_32F) return "CV_32F";
  if (t==CV_64F) return "CV_64F";
  return "Tipo desconhecido";
}

string tipo(Mat a) // devolve depth e channel de um Mat. Ex:  CV_16SC3
{ string st=depth2str(a.depth()); // Ex: CV_16S

  ostringstream ost;
  ost << a.channels();

  st = st + ost.str();
  return st;
}

} // namespace cek

#include <cekeikon.h>

void version(int argc, char** argv) {
  cout << "OpenCV versao: " << CV_MAJOR_VERSION << '.' 
                            << CV_MINOR_VERSION << '.' 
                            << CV_SUBMINOR_VERSION << endl;
}

//cekdlib.h
#include <dlib/dnn.h>
#include <dlib/opencv.h>
#include <cekeikon.h>
using namespace dlib;

void converte(Mat_<GRY> a, matrix<uchar>& d) {
  cv_image<uchar> temp(a);
  assign_image(d,temp);
}

void converte(matrix<uchar> a, Mat_<GRY>& d) {
  Mat_<GRY> b=toMat(a);
  b.copyTo(d);
}

void converte(Mat_<COR> a, matrix<bgr_pixel>& d) {
  cv_image<bgr_pixel> temp(a);
  assign_image(d,temp);
}

void converte(matrix<bgr_pixel> a, Mat_<COR>& d) {
  Mat_<COR> b=toMat(a);
  b.copyTo(d);
}

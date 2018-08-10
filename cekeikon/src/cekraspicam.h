#ifndef __CEKRASPICAM__
#define __CEKRASPICAM__
//Se incluir isto, deve compilar com:
//compila programa -c -r

#include <raspicam/raspicam_cv.h>

using namespace raspicam;
class CEKRASPICAM {
public:
  RaspiCam_Cv cam;
  CEKRASPICAM(int nl=480, int nc=640, bool colorido=true) {
    if (colorido) cam.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    else cam.set(CV_CAP_PROP_FORMAT, CV_8UC1);
    cam.set(CV_CAP_PROP_FRAME_HEIGHT, nl);
    cam.set(CV_CAP_PROP_FRAME_WIDTH,  nc);
    if (!cam.open()) erro("Error opening the camera");
  }
  CEKRASPICAM& operator>>(Mat_<COR>& image) {
    cam.grab();
    cam.retrieve(image);
    //cvtColor(image,image,CV_RGB2BGR);
    return *this;
  }
  CEKRASPICAM& operator>>(Mat_<GRY>& image) {
    cam.grab();
    cam.retrieve(image);
    return *this;
  }
  void set(int propId, double value) {
    cam.set(propId,value);
  }
  ~CEKRASPICAM() { cam.release(); }
};

/*
#include <raspicam/raspicam.h>

class CEKRASPICAM {
public:
  int nl,nc;
  raspicam::RaspiCam cam;
  CEKRASPICAM(int _nl=480, int _nc=640) {
    nl=_nl; nc=_nc;
    cam.setHeight(nl);
    cam.setWidth(nc);
    cam.setAWB(raspicam::RASPICAM_AWB_SUNLIGHT);
    //Atribua aqui outras propriedades da camera ("set")
    if (!cam.open()) erro("Error opening the camera");
  }
  CEKRASPICAM& operator>>(Mat_<COR>& image) {
    image.create(nl,nc);
    cam.grab();
    cam.retrieve(image.data, raspicam::RASPICAM_FORMAT_IGNORE);
    cvtColor(image,image,CV_RGB2BGR);
    return *this;
  }
};
*/

#endif

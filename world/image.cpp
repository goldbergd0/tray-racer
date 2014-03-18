// Dan Goldberg and Vic McGowen
//Image class

#include "image.h"

Image::Image(){
  height_ = 1024;
  width_ = 768;
  im_ = new Colour[width_*height_];
  factor_ = 256;
  //for(unsigned int i = 0; i < width_; ++i)
  //  im_[i] = new double[height_];
  // im_(new double(768,1024))
}

Image::Image(unsigned int w, unsigned int h){
  height_=h;
  width_=w;
  im_ = new Colour[width_*height_];
  factor_ = 256;
  //for(unsigned int i = 0; i < width_; ++i)
  //  im_[i] = new double[height_];
}

Image::Image(const Image& im){
  height_ = im.getHeight();
  width_ = im.getWidth();
  im_ = im.getData();
  factor_ = im.getFactor();
}

Image::~Image(){
 /* Old code: 
    for (unsigned int i = 0; i < width_; ++i){
        delete[] im_[i];
  }
  delete[] im_;*/

  delete[] im_;
}

void Image::toneReproduction() {
  double max = .01;
  double scale = 1;
  for (unsigned int i = 0; i<height_*width_;++i){
    if (im_[i].getR()>max)
      max = im_[i].getR();
    if (im_[i].getG()>max)
      max = im_[i].getG();
    if (im_[i].getB()>max)
      max = im_[i].getB();
  }

  if (max>.01){
    scale = 1/max;
  }
  for (unsigned int i = 0; i<height_*width_;++i){
    im_[i] = im_[i]*scale;
  }

}

void Image::toPPM(const std::string fname) const{
  std::ofstream file;
//  std::string::size_type sz;
  std::ostringstream ss;
  //ss << Number;
  //ss.str();
  ss << width_;
  std::string strWidth(ss.str());
  ss.str(std::string());
  ss << height_;
  std::string strHeight(ss.str());
  ss.str(std::string());
 
  file.open(fname.c_str());
  // Color Image file in ascii
  file << "P3\n";
  // width space height
  file << strWidth << " " << strHeight << "\n";
  // Max Value
  file <<(unsigned int)(factor_)<< "\n";
  
  Colour c;
  
  for (unsigned int j = 0; j<height_;++j){
    for (unsigned int i = 0; i<width_;++i){
      c = this->getPixel(i,j);
      
      ss << (unsigned int) (c.getR()*factor_);
      file << ss.str() << " ";
      ss.str(std::string());

      ss << (unsigned int) (c.getG()*factor_);
      file << ss.str() << " ";
      ss.str(std::string());

      ss << (unsigned int) (c.getB()*factor_);
      file << ss.str() << " ";
      ss.str(std::string());


    }
    file << "\n";
  }

  file.close();
}

Image& Image::operator=(const Image &im){
  height_ = im.getHeight();
  width_ = im.getWidth();
  im_ = im.getData();
  factor_ = im.getFactor();

  return *this;
}

/*
 50 
 51   unsigned int pixW_ = 3;
 52   unsigned int pixH_ = 4;
 53   double num(0);
 54   Colour c;
 55   Image im(pixW_,pixH_);
 56   for (unsigned int i=0;i<pixW_;++i){
 57     for (unsigned int j=0;j<pixH_;++j){
 58       c.setRGB(num);
 59       im.setPixel(i,j,c);
 60       num++;
 61     }
 62   }
 63 
 64   im.toPPM("small.ppm");
*/

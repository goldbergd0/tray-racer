#include <iostream>
#include <Eigen/Dense>
#include "aux/light.h"
#include "aux/colour.h"
#include "world/world.h"
#include "world/object.h"
#include "world/sphere.h"
#include "world/triangle.h"
#include "world/camera.h"
#include "lighting/illuminationmodel.h"
#include "lighting/phong.h"
#include "lighting/phongblinn.h"
#include "texture/checkerboard.h"
#include "texture/texture.h"

int main() {
   // Colour bgColour(0,0.7,0.7);
  Colour bgColour(0);
  World w;
  w.setBgColour(bgColour);
  Phong* p(new Phong);
  //PhongBlinn* p(new PhongBlinn);
  p->setKd(.7);
  p->setKs(.3);
  p->setKe(10);
  w.setModel(p);
  
  // White Light
  Light* l = new Light(Point(0,100,0),Colour(1000));
  // White Light2
  Light* l2 = new Light(Point(100,0,0),Colour(1000));
  Light* l3 = new Light(Point(0,100,-100),Colour(1000));
  Light* l4 = new Light(Point(-100,100,0),Colour(1000));
  //w.add(l);
  w.add(l2);
  w.add(l3);
  w.add(l4);

  // larger sphere
  Object* o1 = new Sphere(2, Point(-0.75, 1, 11));
  o1->setColour(Colour(1.,0.,0.));
  o1->setSpecular(Colour(1,1,1));
  // smaller sphere
  Object* o2 = new Sphere(2, Point(2.75, 0, 17));
  o2->setColour(Colour(0.,1.,0.));
  
  o2->setSpecular(Colour(1,1,1));
  
  // plane coordinates
//   Point topLeft(-5, 2, 30);//6., -2., 0.);
//   Point topRight(7,2, 30);//6., 2., 0.);
//   Point botLeft(-15,-20, 1);//,4., 2., 0.);
//   Point botRight(25,-20, 1);// -10);//,4., 2., 0.);

   Point topLeft(-10,-5, 50);//6., -2., 0.);
   Point topRight(10,-5, 50);//6., 2., 0.);
   Point botLeft(-10,-5, -30);//,4., 2., 0.);
   Point botRight(10,-5, -30);// -10);//,4., 2., 0.);


  // triangle objects to make plane
  Triangle* t1 = new Triangle(topLeft, topRight, botLeft);
  Triangle* t2 = new Triangle(topRight, botRight, botLeft);
  Checkerboard* ch1 = new Checkerboard();
  Checkerboard* ch2 = new Checkerboard();
//  Texture* tex1 = new Checkerboard();
//  Texture* tex2 = new Checkerboard();
 
  ch1->setV0(Point(0,0,20),t1->getv0());
  ch1->setV1(Point(5,0,20),t1->getv1());
  ch1->setV2(Point(0,0,0),t1->getv2());

  ch2->setV0(Point(5,0,20),t2->getv0());
  ch2->setV1(Point(5,0,0),t2->getv1());
  ch2->setV2(Point(0,0,0),t2->getv2());

  Texture* tex1 = ch1;
  Texture* tex2 = ch2;

  t1->setTexture(tex1);
  t2->setTexture(tex2);
  
  t1->setColour(Colour(0.,0.,1.));
  t2->setColour(Colour(0.,0.,1.));
  t1->setSpecular(Colour(1,1,1));
  t2->setSpecular(Colour(1,1,1));
  
  Object* o3 = t1;
  Object* o4 = t2;
  w.add(o3);
  w.add(o4);
  w.add(o1);
  w.add(o2);

  // Front view camera
  Point camPos(0, 5, -10);
  Point look(0, 0, 5);
  Vector up(0,1,0);
  Camera cam(camPos,look,up, 5);
  cam.setPixDim(720,540);
//  cam.setPixDim(1600,1200);
  cam.setDim(4,3);
  
//  w.printObjects();
//  w.printLights();
//  std::cout<<"\n";
  Eigen::Matrix4d viewMatrix(cam.getViewMatrix());
  Image im(cam.render(w,viewMatrix));
  im.toneReproduction();
  im.toPPM("test.ppm");
  //Image im;
  //im = cam.render(w,viewMatrix);

/*  int N=1;
  for (int i=0;i<N;i++){
    viewMatrix = cam.getViewMatrix();
    im = cam.render(w,viewMatrix);
    im.toneReproduction();
    im.toPPM("test.ppm");
 
  }*/
//  w.printObjects();
//  w.printLights();
  
//  im.setFactor(10000);
  
  return 0;
}


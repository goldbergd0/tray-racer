// Vic McGowen and Dan Goldberg Ray Tracer

#include "illuminationmodel.h"

IlluminationModel::IlluminationModel(){}// empty constructor
/*	:intersect_(IntersectData()){}

IlluminationModel::IlluminationModel(const IntersectData& intersect)
	: intersect_(intersect){}
*/
IlluminationModel::~IlluminationModel(){}// deconstrucor

//abstract illuminate method

Colour IlluminationModel::illuminate(const Object* o,const IntersectData& intersect){
  Light l(intersect.getLight());
  Colour c(o->getColour());
  return l.getColour()*c;
}

//------------------------------------------------------------------------------
// ORGANIZATION : Kyneprox srl
// PROJECT      : Motor Control
// PURPOSE      : Defines the data structure of the project
// AUTHOR       : Simone Andreini
//------------------------------------------------------------------------------

#ifndef DATA_TYPES_H
#define DATA_TYPES_H

struct T_Motors{
  float   X_Power_Output;
  float   Y_Power_Output;
  float   Z_Power_Output;

};

struct T_Position{
   float   z_axis;
   float   inclination;
   float   rotation;
};


#endif

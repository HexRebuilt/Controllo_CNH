//------------------------------------------------------------------------------
// ORGANIZATION : Kyneprox srl
// PROJECT      : Motor Control
// PURPOSE      : Defines the data structure of the project
// AUTHOR       : Simone Andreini
//------------------------------------------------------------------------------

#ifndef DATA_TYPES_H
#define DATA_TYPES_H

struct T_Motors{
  int   X_Power_Output;
  int   Y_Power_Output;
  int   Z_Power_Output;

};

struct T_Position{
   int   z_axis;
   int   inclination;
   int   rotation;
};


#endif

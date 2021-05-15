
#pragma once

namespace fly{

double map(double x, double r1, double r2, double a1, double a2){

  double p = (r2 - r1) / (x - r1);
  double y = ((a2 - a1) / p) + a1;
  return y;
}

}


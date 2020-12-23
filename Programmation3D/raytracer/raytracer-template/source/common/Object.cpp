//////////////////////////////////////////////////////////////////////////////
//
//  --- Object.cpp ---
//  Created by Brian Summa
//
//////////////////////////////////////////////////////////////////////////////


#include "common.h"

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Sphere::intersect(vec4 p0, vec4 V){
  IntersectionValues result;
  double t = raySphereIntersection(p0, V);
  result.t = t;

  if(result.t == std::numeric_limits< double >::infinity() || result.t < 0){
    result.ID_ = -1;
  }
  else{
    result.ID_ = 1;
    result.P = p0 + (result.t * normalize(V));
    result.N = result.P - this->center;
  }
  return result;
}

/* -------------------------------------------------------------------------- */
/* ------ Ray = p0 + t*V  sphere at origin center and radius radius    : Find t ------- */
double Sphere::raySphereIntersection(vec4 p0, vec4 V){
  double t   = std::numeric_limits< double >::infinity();
  //d = v
 // t*t * d*d + 2*t * d * (p0 * V) + (p0 - V) * (p0 - V) - r*r 
  double b = 2 * dot(V , (p0 - center));
  double a = dot(V,V);
  double c = dot((p0 - center),(p0 - center)) - radius * radius;
  int tMax = 0;
  int tMin = 0;
  double discr = pow(b,2) - (4* a * c);
  if(discr == 0) t = -b/2*a; 
  else if(discr > 0){
    tMin = (-b - sqrt(discr))/2*a;
    tMax = (-b + sqrt(discr))/2*a;
    if(tMin < tMax) t = tMin;
    else t = tMax;
  }
  
  return t;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Square::intersect(vec4 p0, vec4 V) {
    IntersectionValues result;
    double t = raySquareIntersection(p0, V);

    /*
    4 cas :
      - t infini => rayon parralèle et distinct du plan
      - t non-défini => rayon confondu avec le plan
      - t < 0 => intersection derrière la caméra
      - t > 0 => intersection devant la caméra
    */

    if (t == std::numeric_limits< double >::infinity() || t < 0) {
        result.ID_ = -1;
    }
    else {
        vec4 p1 = this->mesh.vertices[2];
        vec4 p2 = this->mesh.vertices[1];
        vec4 p3 = this->mesh.vertices[0];
        vec4 a = p3 - p2;
        vec4 b = p1 - p2;
        vec4 normal = cross(a, b);

        result.t = t;
        result.ID_ = 2;
        result.P = p0 +  normalize(V) * t;
        result.N = normalize(normal);
    }

    return result;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
double Square::raySquareIntersection(vec4 p0, vec4 V) {
    double t = std::numeric_limits< double >::infinity();


    vec4 o = p0; 
    vec4 d = V;

    vec4 a = this->point;
    vec4 n = vec4(this->normal.x, this->normal.y, this->normal.z, 0.);

    float D = dot(a, n);
    
    t = (D - dot(o, n)) / (dot(d, n));
    //New point
    if (t != std::numeric_limits< double >::infinity() || t >= 0) {
        vec4 pI = p0 + normalize(V) * t; 

        vec4 A = this->mesh.vertices[0];
        vec4 B = this->mesh.vertices[5];
        vec4 C = this->mesh.vertices[2];
        vec4 D = this->mesh.vertices[1];

        if (dot(D - C, pI - C) < 0) return -1; //Error
        if (dot(B - D, pI - D) < 0) return -1; //Error
        if (dot(A - B, pI - B) < 0) return -1; //Error
        if (dot(C - A, pI - A) < 0) return -1; //Error
    }

    return t;
}
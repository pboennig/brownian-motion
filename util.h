#ifndef UTIL_H
#define UTIL_H
#include <math.h>
#include "molecule.h"
using namespace std;
/**
 * function: calcElectroStatic
 * ---------------------------
 * calculate the electroStatic forces of each molecule
 */
map<int, Vec> calcElectroStatic(QList<Molecule*> molecules, double coulombFactor);
/**
 * function: magnitude
 * -------------------
 * finds the Euclidean 2-norm of a vector
 */
double magnitude(Vec& v);
/**
 * function: distVector
 * -------------------
 * finds the vector between two points a and b
 */
Vec distVector(QPointF a, QPointF b);
/**
 * function: getRandPos
 * --------------------
 * gets a random position
 */
QPointF getRandPos();
#endif // UTIL_H

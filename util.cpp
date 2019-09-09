#include "util.h"
#include <iostream>
double magnitude(Vec& v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

Vec distVector(QPointF a, QPointF b) {
    Vec r = { (double)(a.x() - b.x()), (double)(a.y() - b.y())};
    return r;
}

static Vec coloumb(Molecule* mol1, Molecule* mol2, double coloumbFactor) {
    Vec f;
    Vec r = distVector(mol2->pos(),mol1->pos());
    double factor = (coloumbFactor * (double)(mol1->charge * mol2->charge)) / (pow(magnitude(r),2));
    f.x = factor * (r.x / magnitude(r));
    if (abs(f.x) < 1e-10) f.x = 0;
    f.y = factor * (r.y / magnitude(r));
    if (abs(f.y) < 1e-10) f.y = 0;
    return f;
}

map<int, Vec> calcElectroStatic(QList<Molecule*> molecules, double coloumbFactor) {
    map<int, Vec> forces;
    for (size_t i = 0; i< (size_t)molecules.size(); i++) {
        for (size_t j = 0; j<i; j++) {
            Vec force = coloumb(molecules[(int)i], molecules[(int)j], coloumbFactor);
            forces[molecules[(int)i]->id] = forces[molecules[(int)i]->id] + force;
            forces[molecules[(int)i]->id] = forces[molecules[(int)j]->id] - force; //equal and opposite force on other particle (Newton's third law)
        }
    }
    return forces;
}

QPointF getRandPos() {
    QPointF p;
    p.setX(qrand() % 400);
    p.setY(qrand() % 400);
    return p;
}


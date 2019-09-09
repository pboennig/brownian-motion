#include "molecule.h"
#include <stdio.h>
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <qmath.h>
#include <iostream>
#include "util.h"

Molecule::Molecule(Ion name, int id) : id(id), name(name)
{
    switch (name) {
        case Na:
            mass = 23;
            rad = 12;
            color = Qt::red;
            charge = 1;
            speed = getSpeed();
            break;
        case H :
            mass = 1;
            rad = 5;
            color = Qt::blue;
            charge = 1;
            speed = getSpeed();
            break;
        case OH :
            mass = 17;
            rad = 15;
            color = Qt::green;
            charge = -1;
            speed = getSpeed();
            break;
        case Cl :
            mass = 17;
            rad = 20;
            color = Qt::yellow;
            charge = -1;
            speed = getSpeed();
            break;
        }
    acc = {0, 0};
}

Vec Molecule::getSpeed() {
    int xfactor = (qrand() % 2 == 1) ? -1 : 1;
    int yfactor = (qrand() % 2 == 1) ? -1 : 1;
    Vec v = {(double)(xfactor * qrand() % 30), (double)(yfactor * qrand() % 30)};
    return v;
}


QRectF Molecule::boundingRect() const
{
    return QRectF(-rad - .1, rad + .1, 2* rad + .2, 2 * rad + .2);
}

QPainterPath Molecule::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Molecule::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //Molecule
    painter->setBrush(color);
    painter->drawEllipse(-(int)rad, (int)rad, int(rad)*2, int(rad)*2);
    //text
    painter->setBrush(Qt::black);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, this->toString());
}

QString Molecule::toString() {
    switch (name) {
        case (Na): return "Na+";
        case (OH): return "OH-";
        case (H): return "H+";
        case (Cl): return "Cl-";
    }
}

void Molecule::wallCollide(bool vert, int dir) {
    if (vert && -speed.x*dir > 0) {
        if (dir == 1) setPos(11, pos().y());
        else setPos(489, pos().y());
        speed.x = -speed.x;
    }
    else {
        if (dir == 1) setPos(pos().x(), 11);
        else setPos(pos().x(), 489);
        speed.y = -speed.y;
    }
}

void Molecule::advance(int phase)
{
    if (!phase) return;
    speed = {speed.x + acc.x * .1, speed.y + acc.y *.1};
    setPos(mapToParent(speed.x*.1 + .5 * (acc.x) * pow(.1,2), speed.y*.1 + .5 * (acc.y) * pow(.1,2)));
    if (pos().x() <= 10) wallCollide(true, 1);
    else if (pos().x() >= 490) wallCollide(true, -1);
    if (pos().y() <= 10) wallCollide(false, 1);
    else if (pos().y() >= 490) wallCollide(false, -1);
}

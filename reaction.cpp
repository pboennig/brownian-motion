#include "reaction.h"
#include <iostream>
Reaction::Reaction(QGraphicsScene *scene): scene(scene)
{
    QList<QGraphicsItem*> items = scene->items();
    for ( QGraphicsItem* mol: items) {
        Molecule* m = dynamic_cast<Molecule*>(mol);
        molecules.append(m);
    }
    coulombFactor = 1e4;
    forces = calcElectroStatic(molecules, coulombFactor);

}

void Reaction::collideParticles() {
    map<int, set<int>> alreadyCollided;
    for (QGraphicsItem*& mol_i: scene->items()) {
        for (QGraphicsItem* mol_j: scene->collidingItems(mol_i)) {
            Molecule* i = dynamic_cast<Molecule*>(mol_i);
            Molecule* j = dynamic_cast<Molecule*>(mol_j);
            if (alreadyCollided[i->id].find(j->id) == alreadyCollided[i->id].end()) {
                QPointF dpos = j->pos() - i->pos();
                Vec dr = {dpos.x(), dpos.y()};
                Vec dv = i->speed - j->speed;
                Vec n_hat = dr * (1 / magnitude(dr));
                i->speed = i->speed - n_hat * (((2 * j->mass) / (i->mass + j->mass)) * (n_hat.x * dv.x + n_hat.y * dv.y));
                j->speed = j->speed + n_hat * (((2 * i->mass) / (i->mass + j->mass)) * (n_hat.x * dv.x + n_hat.y * dv.y));
                alreadyCollided[i->id].insert(j->id);
                alreadyCollided[j->id].insert(i->id);
            }
        }
    }
}

void Reaction::setColoumb(int force) {
    coulombFactor = (double)force;
}


void Reaction::updateForces() {
    for (Molecule* mol: molecules) {
        Vec f = forces[mol->id];
        mol->acc = {f.x / mol->mass, f.y / mol->mass};
    }
    forces.clear();
    forces = calcElectroStatic(molecules, coulombFactor);
}



QRectF Reaction::boundingRect() const
{
    return QRectF(0, 0, 520, 520);
}

void Reaction::paint(QPainter * , const QStyleOptionGraphicsItem *,
           QWidget *) {
    return;
}
QPainterPath Reaction::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}


void Reaction::move() {
    collideParticles();
    updateForces();
}

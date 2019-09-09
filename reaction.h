#ifndef REACTION_H
#define REACTION_H
#include "molecule.h"
#include "util.h"
#include <QGraphicsScene>
#include <QPainter>
#include <map>
#include <set>
/**
 * The Reaction class manages the electrostatic interactions and elastic collisions of the particles
 */
class Reaction : public QGraphicsObject
{
    Q_OBJECT
public:
    /**
     * function: Reaction
     * ------------------
     * initializes a new reaction class by going through the objects of the given scene
     */
    Reaction(QGraphicsScene* scene);
    /**
     * function: updateForces
     * ----------------------
     * updates the forces of molecules via Coloumb's law
     */
    void updateForces();
    /**
     * function: boundingRect
     * ----------------------
     * Returns the rectangle surrounding rectangle
     */
    QRectF boundingRect() const override;
    /**
     * function: shape
     * ---------------
     * traces a circular path around the molecule
     */
    QPainterPath shape() const override;
    /**
     * function: paint
     * ---------------
     * returns, because we don't want to draw anything for this container class
     */
    void paint(QPainter *, const QStyleOptionGraphicsItem *,
               QWidget *) override;
    /**
     * function: collideParticles
     * --------------------------
     * Runs through the elastic collisions of all aprticles in the rxn
     */
    void collideParticles();
public slots:
    /**
     * function: move
     * -------------
     * moves the rxn forward by colliding particles and updating forces
     */
    void move();
    /**
     * function: setColoumb
     * --------------------
     * sets the coloumb factor in the calc of electrostatic forces
     */
    void setColoumb(int force);
private:
    QGraphicsScene* scene;
    /**
     * QList: molecules
     * -------------------
     * a list of the molecules contained in a scene
     */
    QList<Molecule*> molecules;
    /**
     * map: forces
     * ----------------
     * a map of the current forces of each molecule, updated each updateForces()
     */
    std::map<int, Vec> forces;
    double coulombFactor;
};

#endif // REACTION_H

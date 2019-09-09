#ifndef MOLECULE_H
#define MOLECULE_H


#include <QGraphicsItem>
enum Ion {Na, H, OH, Cl};
struct Vec {
    double x;
    double y;
    Vec operator +(const Vec& v) {
        Vec r;
        r.x = this->x + v.x;
        r.y = this->y + v.y;
        return r;
    }
    Vec operator -(const Vec& v) {
        Vec r;
        r.x = this->x - v.x;
        r.y = this->y - v.y;
        return r;
    }
    Vec operator *(const double& d) {
        Vec r;
        r.x = d * this->x;
        r.y = d * this->y;
        return r;
    }
};
/**
 * The Molecule Class: Implements both the visualization and data of each molecule by extending the QGraphicsItem class
 */


class Molecule : public QGraphicsItem
{
public:
    bool operator <(const Molecule& mol) {
        return (this->name < mol.name);
    }
    /**
     * Molecule constructor
     * -------------------
     * Constructs a new molecule with the given name and id
     */
    Molecule(Ion name, int id);

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
     * paints the molecule
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    int charge;
    double mass;
    int id;
    Vec acc;
    Vec speed;
    Ion name;
    double rad; //radius
protected:
    /**
     * function: advance
     * -----------------
     * slot function that advances the molecule by doing collisions with
     * walls and advancing particles
     */
    void advance(int phase) override;

private:
    QColor color;
    /**
     * function: toString
     * ------------------
     * returns the string name and charge of the molecule
     */
    QString toString();
    /**
     * function: wallCollide
     * ---------------------
     * changes the velocity of particles after colliding with a particularly oriented form
     */
    void wallCollide(bool vert, int dir);
    /**
     * function: getSpeed
     * ------------------
     * returns a random speed
     */
    Vec getSpeed();
};

#endif

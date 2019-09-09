#include <QtWidgets>
#include <math.h>
#include "util.h"
#include "molecule.h"
#include "reaction.h"
#include <iostream>
#include <QSlider>
int numOH = 5;
int numCl = 5;
int numNa = 5;
int numH = 5;

/**
 * function: drawMolecules
 * -----------------------
 * places molecules randomly on scene
 */
void drawMolecules(QGraphicsScene& scene, int numOH, int numCl, int numNa, int numH) {
    int i = 0;
    while (i < numOH) {
         Molecule *oh = new Molecule(OH, i);
         oh->setPos(getRandPos());
         while (oh->collidingItems().size() != 0) oh->setPos(getRandPos()); //keep replacing until mol is not placed on top of another
         scene.addItem(oh);
         i++;
     }
     for (int i = 0; i < numCl; i++) {
         Molecule *cl = new Molecule(Cl, i + numOH);
         cl->setPos(getRandPos());
         while (cl->collidingItems().size() != 0) cl->setPos(getRandPos());
         scene.addItem(cl);
     }
     for (int i = 0; i < numH; i++) {
         Molecule *h = new Molecule(H, i + numOH + numCl);
         h->setPos(getRandPos());
         while (h->collidingItems().size() != 0) h->setPos(getRandPos());
         scene.addItem(h);
     }
     for (int i = 0; i < numNa; i++) {
         Molecule *na = new Molecule(Na, i + numOH + numCl + numH);
         na->setPos(getRandPos());
         while (na->collidingItems().size() != 0) na->setPos(getRandPos());
         scene.addItem(na);
     }
}

/**
 * function: setView
 * -----------------
 * sets the parameters of the QGraphicsView
 */
void setView(QGraphicsView& view) {
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Brownian Motion Simulation"));
    view.resize(800, 800);
}
/**
 * function: setScene
 * ------------------
 * sets parameters for the QGraphicsScene
 */
void setScene(QGraphicsScene& scene) {
    scene.setSceneRect(0, 0, 500, 500);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    drawMolecules(scene, numOH, numCl, numNa, numH);
}

/**
 * function: main
 * --------------
 * main loop of the program
 */
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWidget* widg = new QWidget();
    //opening info window
    QGridLayout* setup = new QGridLayout;
    QLabel * welcome = new QLabel("<b>Welcome to a simulation of Brownian motion!</b> <br>The environment will be populated with ions of various charges and masses <br> "
                                  "You can change the speed of the reaction and the <br> strength of the electromagnetic force inside the reaction window </p>");
    QPushButton *button = new QPushButton("Start");
    setup->addWidget(welcome);
    setup->addWidget(button);
    widg->setLayout(setup);
    widg->show();


    //set up scene
    QWidget* widget = new QWidget();
    QGraphicsScene scene;
    setScene(scene);
    //set view
    QGraphicsView view(&scene);
    setView(view);
    //sliders
    QGridLayout* sliders = new QGridLayout();
    QSlider* speed = new QSlider(Qt::Horizontal);
    speed->setRange(1, 499);
    speed->setSliderPosition(250);
    speed->setInvertedAppearance(true);
    QLabel* sLabel = new QLabel("Speed", speed);
    QSlider* coulomb = new QSlider(Qt::Horizontal);
    coulomb->setRange(1e3, 1e4);
    coulomb->setSliderPosition(5e3);
    QLabel* cLabel = new QLabel("Coulomb force strength", coulomb);
    sliders->addWidget(sLabel, 0, 0);
    sliders->addWidget(speed, 0, 1);
    sliders->addWidget(coulomb, 1, 1);
    sliders->addWidget(cLabel, 1, 0);

    QGridLayout* grid = new QGridLayout;
    grid->addWidget(&view, 0, 0);
    grid->addLayout(sliders, 0, 1);
    widget->setLayout(grid);

    //init reaction
    Reaction* rxn = new Reaction(&scene);
    QTimer timer;
    timer.setInterval(250); //default setting

    //link signals and events
    QObject::connect(button, SIGNAL(clicked()), widget, SLOT(show())); //display rxn
    QObject::connect(button, SIGNAL(clicked()), &timer, SLOT(start())); //start sim
    QObject::connect(button, SIGNAL(clicked()), widg, SLOT(close())); //close intro window
    QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance())); //each timeout, advance sim
    QObject::connect(&timer, SIGNAL(timeout()), rxn, SLOT(move())); //each timeout, update rxn
    QObject::connect(speed, SIGNAL(sliderMoved(int)), &timer, SLOT(start(int))); //each time slider changed, change timer
    QObject::connect(coulomb, SIGNAL(sliderMoved(int)), rxn, SLOT(setColoumb(int))); //each time slider changed, change coloumb factor
    return app.exec();
}

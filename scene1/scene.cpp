#include "scene.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

Scene::Scene(QObject *parent)
  : QGraphicsScene(parent),
    state(nullptr),
    line(nullptr){
}


void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsScene::mousePressEvent(event);

  if (event->button() == Qt::RightButton) {

      start = event->scenePos();

      state = new QGraphicsEllipseItem(-10, -10, 30, 30);
      static_cast<QGraphicsEllipseItem*>(state)->setBrush(Qt::blue);

      addItem(state);
      state->setPos(start);
      state->setFlag(QGraphicsItem::ItemIsMovable);
      state->setAcceptHoverEvents(true);
      state->setEnabled(true);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);

    if (event->button() == Qt::RightButton) {

        end = event->scenePos();

        line = new QGraphicsLineItem(start.x(), start.y(), end.x(), end.y());

        //static_cast<QGraphicsLineItem*>(state)->setBrush(Qt::blue);

        addItem(line);
        line->setFlag(QGraphicsItem::ItemIsMovable);
        line->setAcceptHoverEvents(true);
        line->setEnabled(true);
      }
}

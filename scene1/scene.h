#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>

class Scene : public QGraphicsScene {
  Q_OBJECT

public:
  explicit Scene(QObject *parent = nullptr);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
  QGraphicsItem* state;
  QGraphicsItem* line;
  QPointF start;
  QPointF end;
  QPen pen;
  QBrush brush;

};

#endif // SCENE_H

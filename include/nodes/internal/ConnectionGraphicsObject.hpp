#pragma once

#include <utility>

#include <QtCore/QUuid>
#include <QtWidgets/QGraphicsObject>

#include "Definitions.hpp"
#include "ConnectionState.hpp"

class QGraphicsSceneMouseEvent;

namespace QtNodes
{

class GraphicsScene;
class Connection;
class ConnectionGeometry;

/// Graphic Object for connection. Adds itself to scene
class ConnectionGraphicsObject
  : public QGraphicsObject
{
  Q_OBJECT

public:

  /// Defines whether we construct a new connection
  /// or it is already binding two nodes.
  enum State
  {
    Pending   = 0,
    Connected = 1
  };

public:

  using ConnectionId = std::pair<NodeId, NodeId>;

  ConnectionGraphicsObject(GraphicsScene & scene,
                           ConnectionId    connectionId);

  virtual ~ConnectionGraphicsObject();

  enum { Type = UserType + 2 };
  int type() const override { return Type; }

public:

  ConnectionId connectionId();

  QRectF boundingRect() const override;

  QPainterPath shape() const override;

  QPointF const & getEndPoint(PortType portType) const;

  void setEndPoint(PortType portType, QPointF const & point);

  void moveEndPointBy(PortType portType, QPointF const & offset);


  void setGeometryChanged();

  /// Updates the position of both ends
  void move();

  void lock(bool locked);

  ConnectionState const & connectionState() const;
  ConnectionState & connectionState();

  std::array<QPointF, 2> inOut() const { return _inOut; }

protected:

  void paint(QPainter * painter,
             QStyleOptionGraphicsItem const * option,
             QWidget *  widget = 0) override;

  void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

  void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;

  void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

  void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;

  void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;

private:

  void addGraphicsEffect();

  std::pair<QPointF, QPointF> pointsC1C2() const;

private:

  GraphicsScene & _scene;

  ConnectionState _connectionState;

  ConnectionId _connectionId;

  State _state;

  std::array<QPointF, 2> _inOut;

  bool _hovered;

};
}

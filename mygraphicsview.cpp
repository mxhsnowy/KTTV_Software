#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent):QGraphicsView(parent)
{
    setDragMode(RubberBandDrag);
    setInteractive(true);
    setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
}
void MyGraphicsView::wheelEvent(QWheelEvent *event){
//    if(zoomEnabled){
//        if(event->orientation() == Qt::Vertical){
//            double angleDeltaY=event->angleDelta().y();
//            double zoomFactor= qPow(1.0015,angleDeltaY);
//            scale(zoomFactor,zoomFactor);
//            if(angleDeltaY>0){
//                this->centerOn(scenePos);
//                scenePos=this->mapToScene(event->pos());
//            }
//            this->viewport()->update();
//            event->accept();
//        }
//        else {
//            event->ignore();
//        }
//    }
//    else {
//        QGraphicsView::wheelEvent(event);
//    }
//    QGraphicsView::wheelEvent(event);
}
void MyGraphicsView::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Plus:
        scale(1.1, 1.1);
        break;
    case Qt::Key_Minus:
        scale(1/1.1, 1/1.1);
        break;
    }
}
void MyGraphicsView::resizeEvent(QResizeEvent *event){

}
void MyGraphicsView::mousePressEvent(QMouseEvent *event){
    startPoint = event->pos();
    if(zoomEnabled){
//        if(!rubberBandRect){
//           rubberBandRect =
//        }
        rubberBandRect.setTopLeft(this->mapToScene(startPoint));
        rubberBand->setGeometry(QRect(startPoint, QSize()));
        rubberBand->show();
    }
}
void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
    if(zoomEnabled){
        rubberBand->setGeometry(QRect(startPoint, event->pos()).normalized());
    }
    QGraphicsView::mouseMoveEvent(event);

}
void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event){
    if(zoomEnabled){
        rubberBand->hide();
        rubberBandRect.setBottomRight(this->mapToScene(event->pos()));
        this->fitInView(rubberBandRect, Qt::KeepAspectRatio);
    }
}





// m_bSelectiveZoomOn is a variable to turn on / off the zooming operation
// I had a situation wher i needed to zoom using rubberband if that operation was selected.
// If it was not, the behaviour was the default one.

//void MyGraphicsView::mousePressEvent ( QMouseEvent * event )
//{
//	QPoint globalCursorPos;
//	globalCursorPos = QCursor::pos();

//	if(zoomEnabled)
//	{
//		startPoint = globalCursorPos;	// store the start pos for selective zoom

//		// start rubberbanding
//		if (!band)
//			band = new QRubberBand(QRubberBand::Rectangle,this);

//		// set the rubberband shape
//		band->setGeometry(QRect(mapFromGlobal(startPoint), QSize()));
//		band->show();	// show the rubberband
//		isRubber = true;	// now we are rubberbanding !!
//	}
//	else	// if selective zoom off
//	{	// pass the event to base class
//		QGraphicsView::mousePressEvent(event);
//	}

//}


//void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
//{
//	QPoint globalCursorPos;
//	globalCursorPos = QCursor::pos();

//	// if zoom is being performed, update the zoom rectangle
//	if(zoomEnabled && isRubber)
//	{
//		band->setGeometry(QRect(mapFromGlobal(startPoint), mapFromGlobal(globalCursorPos)).normalized());
//	}
//	else
//	{
//		QGraphicsView::mouseMoveEvent(event);
//	}

//}
//void MyGraphicsView::mouseReleaseEvent(QMouseEvent * event)
//{
//	QPoint globalCursorPos;
//	globalCursorPos = QCursor::pos();
//	QRectF zoomRect;

//	endPoint = globalCursorPos;	// get the position of end point


//	if(zoomEnabled)
//	{
//		band->hide();
//		isRubber = false;

//		// find the rectangle to be zoomed
//		zoomRect = QRect(mapToScene( mapFromGlobal(startPoint)).toPoint() ,mapToScene(mapFromGlobal(endPoint)).toPoint());

//		// zoom the rectangle
//		if((startPoint-endPoint).manhattanLength() >= // some minimum distance for zooming)
//		{
//			// if the rect lies in scene
//			if(isPointInSceneRect(startPoint) && isPointInSceneRect(endPoint))
//			{
//				// fiv the rect
//				// fit in view the rect - zoomRect.toRect()
//			}
//		}
//	}
//	else
//	{	// pass the event to base class
//		QGraphicsView::mouseReleaseEvent(event);
//	}

//}
//void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
//    scenePos = mapToScene(event->pos());
//    QGraphicsView::mouseMoveEvent(event);
//}

#include "arrayviewer.h"

arrayviewer::arrayviewer(QWidget *parent) : QWidget(parent)
{
    colorA = Qt::darkBlue;
    colorB = Qt::darkRed;
}
void arrayviewer::setModel(const arraymodel *newModel)
{
    model = newModel;
}
void arrayviewer::paintEvent(QPaintEvent *event)
{
    event->accept();
    QPainter p(this);
    QRect bounds = this->rect().adjusted(0,0,-1,-1);
    QBrush br(Qt::black);
    QPen pen(br,1);

    p.setPen(pen);
    p.setBrush(br);
    p.drawRect(bounds);

    int i = 0;
    int size = model->size();
    double width = static_cast<double>( bounds.width() ) / static_cast<double> ( size );
    double heightScale = static_cast<double> ( bounds.height() ) / static_cast<double> ( model->max() );
    double bottom = bounds.height();
    double base = width/2;

    pen.setWidthF(width);

#ifdef DEBUG
    qDebug() << base << bottom << heightScale << bounds;
#endif

    while( i < size )
    {
        if(i == model->A())
        {
            pen.setColor(colorA);
        }
        else if (i == model->B() )
        {
            pen.setColor(colorB);
        }
        else
        {
            pen.setColor(Qt::white);
        }

        p.setPen(pen);
        p.drawLine( QLineF ( base, bottom, base, bottom - (model->element(i) * heightScale ) ) );

        ++i;
        base += width;
    }
}

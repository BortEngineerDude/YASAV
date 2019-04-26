#include "arrayviewer.h"

arrayviewer::arrayviewer(QWidget *parent) : QWidget(parent)
{
    colorA = QColor(0x3f,0x51,0xb5);
    colorB = QColor(0xfb,0x8c,0);
    colorDone = QColor(0x4c, 0x8c, 0x4a);
    colorUnknown = Qt::lightGray;
    colorBackground = QColor(0x26,0x32, 0x38);
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
    QBrush br(colorBackground);
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
    //qDebug() << base << bottom << heightScale << bounds;
#endif

    while( i < size )
    {
        if( i == model->A() )
        {
            pen.setColor(colorA);
        }
        else if ( i == model->B() )
        {
            pen.setColor(colorB);
        }
        else if( i >= model->m_top )
        {
            pen.setColor(colorDone);
        }
        else
        {
            pen.setColor(colorUnknown);
        }

        p.setPen(pen);
        p.drawLine( QLineF ( base, bottom, base, bottom - (model->m_vect.at(i) * heightScale ) ) );

        ++i;
        base += width;
    }
}

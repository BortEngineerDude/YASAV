#include "arrayviewer.h"

arrayviewer::arrayviewer(QWidget *parent) : QWidget(parent)
{
    //set default colors defined in headers
    colorA = QColor(COLOR_A);
    colorB = QColor(COLOR_B);
    colorDone = QColor(COLOR_DONE);
    colorUnknown = QColor(COLOR_UNKNOWN);
    colorBackground = QColor(COLOR_BACKGR);
}
void arrayviewer::setModel(const arraymodel *newModel)
{
    model = newModel;
}
void arrayviewer::paintEvent(QPaintEvent *event)
{
    //this is the endpoint for the paint event
    event->accept();

    QPainter p(this);

    //defines bounds of our drawing space
    QRect bounds = this->rect();
    //adjust rect so it won't interfere with viewer frame borders
    bounds.adjust(0, 0, -1, -1);

    //draw solid background inside frame
    QBrush br(colorBackground);
    QPen pen(br, 1);
    p.setPen(pen);
    p.setBrush(br);
    p.drawRect(bounds);

    int i = 0;
    int size = model->size();

    //width of a single line representing one element
    double width = static_cast<double>( bounds.width() ) /
            static_cast<double> ( size );

    //point (0,0) is at top left corner, using bottom variable we can:
    //-draw from actual frame bottom
    //-save on bottom() member function calls
    double bottom = bounds.bottom();

    //height multipler for each bar -- to make sure everything fits in frame
    double heightScale = static_cast<double> ( bounds.height() * 0.95 ) /
            static_cast<double> ( model->max() );

    //base is X position for line; as line is drawn from the middle, we put it
    //in the middle
    double base = width/2;

    pen.setWidthF(width);

#ifdef DEBUG
    //qDebug() << heightScale << bounds;
#endif

    //drawing all the lines
    while( i < size )
    {
        //determine color for the current line
        if( i == model->A() )
        {
            pen.setColor(colorA);
        }
        else if ( i == model->B() )
        {
            pen.setColor(colorB);
        }
        else if( model->m_complete.inRange(i) )
        {
            pen.setColor(colorDone);
        }
        else
        {
            pen.setColor(colorUnknown);
        }

        p.setPen(pen);

        //draw line for one element
        p.drawLine(
                    QLineF ( base,
                             bottom,
                             base,
                             bottom -
                             ( static_cast<double>( model->m_vect.at(i) )
                               * heightScale )
                             ) );

        ++i;

        //shift the X for the next line
        base += width;
    }

    //draw stats
    if( model->A() != -1 && model->B() != -1)
    {
        QFont def;
        const int sizeFactor = bounds.height() / 10;
        const int xOffset = bounds.width() / 25;
        def.setPixelSize(sizeFactor);

        QString stat;
        QTextStream statStream(&stat);

        statStream << "A [ " << model->m_idxA << " ] = " << model->elementA();
        pen.setColor(colorA.lighter());
        p.setPen(pen);
        p.setFont(def);
        p.drawText(xOffset, sizeFactor, stat);

        stat.clear();
        statStream << "B [ " << model->m_idxB << " ] = " << model->elementB();
        pen.setColor(colorB.lighter());
        p.setPen(pen);
        p.drawText(xOffset, sizeFactor*2, stat);
    }
}

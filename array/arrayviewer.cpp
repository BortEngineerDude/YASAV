#include "arrayviewer.h"

const QColor& arrayviewer::determineColor(int val)
{
    if( val == model->A() )
    {
        return colorA;
    }
    if ( val == model->B() )
    {
        return colorB;
    }
    if( model->m_complete.inRange( val ) )
    {
        return colorDone;
    }
    return colorUnknown;
}
void arrayviewer::drawBoxes()
{
    QPainter p( this );
    //defines bounds of our drawing space AND
    //adjust rect so it won't interfere with viewer frame borders
    const QRect bounds = this->rect().adjusted( 0, 0, -1, -1 );

    //draw solid background inside frame
    QBrush br( colorBackground );
    QPen pen( br, 1 );
    p.setPen( pen );
    p.setBrush( br );
    p.drawRect( bounds );

    int i = 0;
    const int size = model->size();

    //dimension of a single cube representing one element
    const double width = static_cast<double>( bounds.width() ) /
            static_cast<double> ( size );
    const double middle = bounds.center().y() - width / 2;

    const double spacingMultiplier = 0.05;

    QFont font;
    font.setPixelSize( static_cast<int>( ( width * ( 1. - spacingMultiplier * 4. ) ) ) );
    p.setFont( font );

    //first box is placed at ( spacingMultuplier / 2 )
    QRectF box( width * spacingMultiplier / 2, middle, width * 0.9, width * 0.9 );

    while( i < size )
    {
        const QColor current( determineColor( i ) );
        pen.setColor( current );
        br.setColor( current );

        p.setPen( pen );
        p.setBrush( br );
        p.drawRoundedRect( box, 20, 20, Qt::RelativeSize );

        pen.setColor( colorBackground );
        p.setPen( pen );
        QString value;
        QPointF valuePos = box.bottomLeft();
        valuePos.rx() += width * spacingMultiplier / 2;
        valuePos.ry() -= width * spacingMultiplier * 2;
        value.setNum( model->m_vect.at(i) );
        p.drawText( valuePos, value );

        ++i;
        box.moveTo( i * width + width * spacingMultiplier, middle );
    }
}
void arrayviewer::drawBars()
{
    QPainter p( this );
    //defines bounds of our drawing space AND
    //adjust rect so it won't interfere with viewer frame borders
    const QRect bounds = this->rect().adjusted( 0, 0, -1, -1 );;

    //draw solid background inside frame
    QBrush br( colorBackground );
    QPen pen( br, 1 );
    p.setPen( pen );
    p.setBrush( br );
    p.drawRect( bounds );

    int i = 0;
    const int size = model->size();

    //width of a single line representing one element
    const double width = static_cast<double>( bounds.width() ) /
            static_cast<double> ( size );

    //point (0,0) is at top left corner, using bottom variable we can:
    //-draw from actual frame bottom
    //-save on bottom() member function calls
    const double bottom = bounds.bottom();

    //height multipler for each bar -- to make sure everything fits in frame
    const double heightScale = static_cast<double> ( bounds.height() * 0.95 ) /
            static_cast<double> ( model->max() );

    //base is X position for line; as line is drawn from the middle, we put it
    //in the middle
    double base = width / 2;

    pen.setWidthF(width);

    //drawing all the lines
    while( i < size )
    {
        pen.setColor( determineColor( i ) );
        p.setPen( pen );

        //draw line for one element
        p.drawLine(
                    QLineF ( base,
                             bottom,
                             base,
                             bottom -
                             ( static_cast<double>( model->m_vect.at( i ) )
                               * heightScale )
                             ) );

        ++i;

        //shift the X for the next line
        base += width;
    }
}
arrayviewer::arrayviewer( QWidget *parent ) : QWidget( parent ), colorA( COLOR_A ),
    colorB (COLOR_B ), colorDone( COLOR_DONE ), colorUnknown( COLOR_UNKNOWN ),
    colorBackground( COLOR_BACKGR ), style( VIEW_STYLE::BARS )
{}
void arrayviewer::setModel(const arraymodel *newModel)
{
    model = newModel;
}
void arrayviewer::setViewStyle(VIEW_STYLE newViewStyle)
{
    if(newViewStyle != style)
    {
        style = newViewStyle;
    }
}
void arrayviewer::paintEvent(QPaintEvent *event)
{
    //this is the endpoint for the paint event
    event->accept();

    if( style == VIEW_STYLE::BARS )
    {
        drawBars();
    }
    else
    {
        drawBoxes();
    }
}

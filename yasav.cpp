#include "yasav.h"
#include "ui_yasav.h"

yasav::yasav(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yasav),
    s(new bubble)
{
    ui->setupUi(this);

    QPalette labels(ui->labelA->palette());

    labels.setColor(QPalette::WindowText, QColor(COLOR_A).darker());
    ui->labelA->setPalette(labels);

    labels.setColor(QPalette::WindowText, QColor(COLOR_B).darker());
    ui->labelB->setPalette(labels);

    ui->comboBoxArrayInit->addItem(
                QObject::tr("Linear fill"),
                QVariant(static_cast<int>(FILL_TYPE::LINEAR)));
    ui->comboBoxArrayInit->addItem(
                QObject::tr("Cubic fill"),
                QVariant(static_cast<int>(FILL_TYPE::CUBIC)));
    ui->comboBoxArrayInit->addItem(
                QObject::tr("'One odd' fill"),
                QVariant(static_cast<int>(FILL_TYPE::ONE_ODD)));
    ui->comboBoxArrayInit->addItem(
                QObject::tr("Inverse linear fill"),
                QVariant(static_cast<int>(FILL_TYPE::LINEAR_INVERSE)));

    ui->comboBoxSortingAlgorithm->addItem(
                QObject::tr("Bubble sort"),
                QVariant(static_cast<int>(SORT_TYPE::BUBBLE)));
    ui->comboBoxSortingAlgorithm->addItem(
                QObject::tr("Selection sort"),
                QVariant(static_cast<int>(SORT_TYPE::SELECTION)));
    ui->comboBoxSortingAlgorithm->addItem(
                QObject::tr("Insertion sort"),
                QVariant(static_cast<int>(SORT_TYPE::INSERTION)));

    ticker.setInterval(ui->spinBoxTiming->value());

    m.setFillType(static_cast<FILL_TYPE>(
                      ui->comboBoxArrayInit->itemData(0).toInt()) );

    m.setSize( ui->horizontalSliderArraySize->value());

    ui->viewer->setModel(&m);
    s->setModel(&m);

    connect(ui->pushButtonShuffle, SIGNAL(released()), &m, SLOT(shuffle()));
    connect(ui->horizontalSliderArraySize, SIGNAL(valueChanged(int)), &m, SLOT(setSize(int)));
    connect(&m, SIGNAL(changed()), ui->viewer, SLOT(repaint()));

    connectSorter();
}

yasav::~yasav()
{
    delete ui;
    delete s;
}
void yasav::connectSorter()
{
    connect(ui->pushButtonShuffle, SIGNAL(released()), s, SLOT(resetState()));
    connect(ui->horizontalSliderArraySize, SIGNAL(valueChanged(int)), s, SLOT(resetState()));
    connect(ui->comboBoxArrayInit, SIGNAL(currentIndexChanged(int)), s, SLOT(resetState()));
    connect(ui->pushButtonStep, SIGNAL(released()), s, SLOT(advance()));
    connect(&ticker, SIGNAL(timeout()), s, SLOT(advance()));
    connect(s, SIGNAL(finished()), this, SLOT(stop()));
    connect(s, SIGNAL(stepDone()), this, SLOT(repaint()));
    connect(s, SIGNAL(stepDone()), this, SLOT(updateStats()));
}
void yasav::updateArraySizeLabel(int newSize)
{
    QString newText( QObject::tr("Array size: ")+=QString::number(newSize) );
    ui->labelArraySize->setText(newText);
}
void yasav::updateArrayFill(int newIndex)
{
    //super lame stuff
    m.setFillType(
                static_cast<FILL_TYPE>(
                    ui->comboBoxArrayInit->itemData(newIndex).toInt()) );
}
void yasav::updateSorter(int newIndex)
{
    SORT_TYPE newSort = static_cast<SORT_TYPE>(newIndex);
    if( s->sortType() != newSort )
    {
        //s->resetState();
        delete s;
        switch(newSort)
        {
        case SORT_TYPE::BUBBLE:
            s = new bubble();
            break;
        case SORT_TYPE::SELECTION:
            s = new selection();
            break;
        case SORT_TYPE::INSERTION:
            s = new insertion();
            break;
        }
        s->setModel(&m);
        connectSorter();
    }
}
void yasav::updateTicker(int newMs)
{
    ticker.setInterval(newMs);
}
void yasav::updateStats()
{
    QString label;
    QTextStream labelStream(&label);

    labelStream << "A = " << m.A() << ", ARR[A] = " << m.element(m.A());
    ui->labelA->setText( label );
    label.clear();

    labelStream << "B = " << m.B() << ", ARR[B] = " << m.element(m.B());
    ui->labelB->setText( label );

    ui->labelNextStep->setText( s->getState() );
}
void yasav::updateViewStyle()
{
    if(ui->radioButtonBarsView->isChecked())
    {
        ui->horizontalSliderArraySize->setRange(10,200);
        ui->horizontalSliderArraySize->setTickInterval(20);
        ui->viewer->setViewStyle(VIEW_STYLE::BARS);
    }
    else
    {
        ui->horizontalSliderArraySize->setRange(5,20);
        ui->horizontalSliderArraySize->setTickInterval(1);
        ui->viewer->setViewStyle(VIEW_STYLE::BOXES);
    }
    ui->viewer->repaint();
}
void yasav::toggleIteration()
{
    if(ticker.isActive())
    {
        stop();
    }
    else
    {
        ui->pushButtonGoStop->setText( QObject::tr("Stop") );
        ui->pushButtonGoStop->setChecked( true );
        connect(s, SIGNAL( iterationDone() ), this, SLOT( stop() ));
        ticker.start();
    }
}
void yasav::toggleGoStop()
{
    if(ticker.isActive())
    {
        stop();
    }
    else
    {
        ui->pushButtonGoStop->setText( QObject::tr("Stop") );
        ui->pushButtonIteration->setEnabled( false );
        ticker.start();
    }
}
void yasav::stop()
{
    ui->pushButtonGoStop->setText( QObject::tr("Go") );
    ui->pushButtonIteration->setChecked( false );
    ui->pushButtonIteration->setEnabled( true );
    ui->pushButtonGoStop->setChecked( false );
    disconnect(s, SIGNAL( iterationDone() ), this, SLOT( stop() ));
    ticker.stop();
}

#include "yasav.h"
#include "ui_yasav.h"

yasav::yasav(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yasav),
    s(new bubble)
{
    ui->setupUi(this);

    ui->comboBoxArrayInit->addItem(QObject::tr("Linear fill"), QVariant(static_cast<int>(FILL_TYPE::LINEAR)));
    ui->comboBoxArrayInit->addItem(QObject::tr("Cubic fill"), QVariant(static_cast<int>(FILL_TYPE::CUBIC)));

    ui->comboBoxSortingAlgorithm->addItem(QObject::tr("Bubble sort"), QVariant(static_cast<int>(SORT_TYPE::BUBBLE)));
    ui->comboBoxSortingAlgorithm->addItem(QObject::tr("Selection sort"), QVariant(static_cast<int>(SORT_TYPE::SELECTION)));

    ticker.setInterval(ui->spinBoxTiming->value());

    m.setSize( ui->horizontalSliderArraySize->value());
    m.setFillType( static_cast<FILL_TYPE>( ui->comboBoxArrayInit->itemData(0).toInt()) );
    ui->viewer->setModel(&m);
    s->setModel(&m);

    connect(ui->pushButtonShuffle, SIGNAL(released()), &m, SLOT(shuffle()));
    connect(ui->pushButtonShuffle, SIGNAL(released()), this, SLOT(stop()));

    connect(ui->horizontalSliderArraySize, SIGNAL(valueChanged(int)), &m, SLOT(setSize(int)));
    connect(ui->horizontalSliderArraySize, SIGNAL(valueChanged(int)), this, SLOT(stop()));

    connect(&m, SIGNAL(changed()), ui->viewer, SLOT(repaint()));

    connect(ui->comboBoxArrayInit, SIGNAL(currentIndexChanged(int)), this, SLOT(updateArrayFill(int)));

    connect(ui->comboBoxSortingAlgorithm, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSorter(int)));
    connect(ui->comboBoxSortingAlgorithm, SIGNAL(currentIndexChanged(int)), this, SLOT(stop()));

    connect(ui->pushButtonStep, SIGNAL(released()), this, SLOT(repaint()));
    connect(ui->pushButtonStep, SIGNAL(released()), this, SLOT(stop()));
    connect(ui->pushButtonGoStop, SIGNAL(pressed()), this, SLOT(toggleGoStop()));

    connect(&ticker, SIGNAL(timeout()), this, SLOT(repaint()));
    connect(ui->spinBoxTiming, SIGNAL(valueChanged(int)), this, SLOT(updateTicker(int)));

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
    connect(s, SIGNAL(finished()), this, SLOT(repaint()));
}
void yasav::updateArraySizeLabel(int newSize)
{
    QString newText( QObject::tr("Array size: ")+=QString::number(newSize) );
    ui->labelArraySize->setText(newText);
}
void yasav::updateArrayFill(int newIndex)
{
    m.setFillType( static_cast<FILL_TYPE>( ui->comboBoxArrayInit->itemData(newIndex).toInt()) ); //this is LAME
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
        }
        s->setModel(&m);
        connectSorter();
    }
}
void yasav::updateTicker(int newMs)
{
    ticker.setInterval(newMs);
}
void yasav::toggleGoStop()
{
    if(ui->pushButtonGoStop->isChecked())
    {
        stop();
    }
    else
    {
        ui->pushButtonGoStop->setText( QObject::tr("Stop") );
        ticker.start();
    }
}
void yasav::stop()
{
    ui->pushButtonGoStop->setText( QObject::tr("Go") );
    ui->pushButtonGoStop->setChecked(false);
    ticker.stop();
}

#include "yasav.h"
#include "ui_yasav.h"

yasav::yasav(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yasav)
{
    ui->setupUi(this);

    ui->comboBoxArrayInit->addItem(QObject::tr("Unique"), QVariant(static_cast<int>(FILL_TYPE::UNIQUE)));
    ui->comboBoxArrayInit->addItem(QObject::tr("Cubic"), QVariant(static_cast<int>(FILL_TYPE::CUBIC)));

    autoticker.setInterval(ui->spinBoxTiming->value());
    m.setSize( ui->horizontalSliderArraySize->value());
    m.setFillType( static_cast<FILL_TYPE>( ui->comboBoxArrayInit->itemData(0).toInt()) );
    ui->viewer->setModel(&m);
    b.setModel(&m);

    connect(ui->pushButtonShuffle, SIGNAL(released()), &m, SLOT(shuffle()));
    connect(ui->pushButtonShuffle, SIGNAL(released()), &b, SLOT(reset()));

    connect(ui->horizontalSliderArraySize, SIGNAL(valueChanged(int)), &m, SLOT(setSize(int)));
    connect(ui->horizontalSliderArraySize, SIGNAL(valueChanged(int)), &b, SLOT(updateModel()));

    connect(&m, SIGNAL(changed()), ui->viewer, SLOT(repaint()));
    connect(ui->comboBoxArrayInit, SIGNAL(currentIndexChanged(int)), this, SLOT(updateArrayFill(int)));
    connect(ui->comboBoxArrayInit, SIGNAL(currentIndexChanged(int)), &b, SLOT(reset()));

    connect(ui->pushButtonStep, SIGNAL(released()), &b, SLOT(advance()));
    connect(ui->pushButtonStep, SIGNAL(released()), this, SLOT(repaint()));
    connect(ui->pushButtonStep, SIGNAL(released()), this, SLOT(stop()));
    connect(ui->pushButtonGoStop, SIGNAL(pressed()), this, SLOT(toggleGoStop()));
    connect(&autoticker, SIGNAL(timeout()), &b, SLOT(advance()));
    connect(&autoticker, SIGNAL(timeout()), this, SLOT(repaint()));
    connect(ui->spinBoxTiming, SIGNAL(valueChanged(int)), this, SLOT(updateAutoTicker(int)));
    connect(&b,SIGNAL(finished()),this,SLOT(stop()));
}

yasav::~yasav()
{
    delete ui;
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

void yasav::updateAutoTicker(int newMs)
{
    autoticker.setInterval(newMs);
}
void yasav::toggleGoStop()
{
    if(ui->pushButtonGoStop->isChecked())
    {
        ui->pushButtonGoStop->setText( QObject::tr("Go") );
        autoticker.stop();
    }
    else
    {
        ui->pushButtonGoStop->setText( QObject::tr("Stop") );
        autoticker.start();
    }
}
void yasav::stop()
{
    ui->pushButtonGoStop->setText( QObject::tr("Go") );
    ui->pushButtonGoStop->setChecked(false);
    autoticker.stop();
}

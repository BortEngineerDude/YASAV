#include "yasav.h"
#include "ui_yasav.h"

yasav::yasav(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yasav)
{
    ui->setupUi(this);
    ui->viewer->setModel(&m);

    ui->comboBoxArrayInit->addItem(QObject::tr("Unique"), QVariant(static_cast<int>(FILL_TYPE::UNIQUE)));
    ui->comboBoxArrayInit->addItem(QObject::tr("Cubic"), QVariant(static_cast<int>(FILL_TYPE::CUBIC)));

    connect(ui->pushButtonShuffle,SIGNAL(released()),&m,SLOT(shuffle()));
    connect(ui->horizontalSliderArraySize,SIGNAL(valueChanged(int)),&m,SLOT(setSize(int)));
    connect(&m,SIGNAL(changed()),ui->viewer,SLOT(repaint()));
    connect(ui->comboBoxArrayInit, SIGNAL(currentIndexChanged(int)), this, SLOT(updateArrayFill(int)));
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

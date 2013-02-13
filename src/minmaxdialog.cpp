#include "minmaxdialog.h"
#include <QLineEdit>
#include <QIntValidator>

/// Constructor
MinMax::MinMax( QWidget *parent):
    QDialog(parent)
{
    this->setFixedSize(400,200);
    this->setWindowTitle("Choose price ...");

    QIntValidator *validator = new QIntValidator(0, 9999999, this);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);
    buttonBox->setGeometry(0,150,330,35);

    priceMinLineEdit = new QLineEdit(this);
    priceMaxLineEdit = new QLineEdit(this);
    priceMinLineEdit->setValidator(validator);
    priceMaxLineEdit->setValidator(validator);
    priceMinLineEdit->setGeometry(80,70,100,35);
    priceMaxLineEdit->setGeometry(230,70,100,35);

    minLabel = new QLabel("Price Min",this);
    maxLabel = new QLabel("Price Max",this);

    minLabel->setGeometry(100,20,100,35);
    maxLabel->setGeometry(250,20,100,35);

    QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
}


/// get min price
int MinMax::getPriceMin() const
{
    return priceMin;
}

/// Get max price
int MinMax::getPriceMax() const
{
    return priceMax;
}

/// Buttons click callback
void MinMax::onButtonClicked(QAbstractButton* button)
{
    if(buttonBox->buttonRole(button) == QDialogButtonBox::AcceptRole){
        if(!priceMaxLineEdit->text().isEmpty() &&  !priceMinLineEdit->text().isEmpty() && priceMaxLineEdit->text().toInt()>=priceMinLineEdit->text().toInt()){
            priceMax = priceMaxLineEdit->text().toInt();
            priceMin = priceMinLineEdit->text().toInt();
            this->accept();
        }
    }else if(buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole){
        this->reject();
    }
}

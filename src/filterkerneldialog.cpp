#include "filterkerneldialog.h"
#include "ui_filterkerneldialog.h"
#include <QLineEdit>

FilterKernelDialog::FilterKernelDialog(QWidget *parent) :
    QDialog(parent),  ui(new Ui::FilterKernelDialog)
{
    ui->setupUi(this);
    QIntValidator *validator = new QIntValidator(-999, 999, this);

    for(int j=0;j<ui->tableWidget->columnCount();j++){
        for(int i=0;i<ui->tableWidget->rowCount();i++){
            QLineEdit *lineEdit = new QLineEdit(this);
            lineEdit->setValidator(validator);
            ui->tableWidget->setCellWidget(i,j, lineEdit);
        }
    }

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onButtonClicked()));
}

FilterKernelDialog::~FilterKernelDialog()
{
    delete ui;
}

void FilterKernelDialog::onButtonClicked()
{
    for(int j=0;j<3;j++){
        for(int i=0;i<3;i++){
            QLineEdit *lineEdit = static_cast<QLineEdit*> (ui->tableWidget->cellWidget(i,j));
            kernelMat[i][j] = lineEdit->text().toInt();
        }
    }
}

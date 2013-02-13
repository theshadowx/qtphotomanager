#ifndef FILTERKERNELDIALOG_H
#define FILTERKERNELDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>

namespace Ui{
    class FilterKernelDialog;
}

class FilterKernelDialog : public QDialog
{
    Q_OBJECT

public:
    FilterKernelDialog(QWidget *parent = 0);
    virtual ~FilterKernelDialog();

    double kernelMat[3][3];

private:
    Ui::FilterKernelDialog *ui;

private slots:
    void onButtonClicked();
};

#endif // FILTERKERNELDIALOG_H

#ifndef MINMAXDIALOG_H
#define MINMAXDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLineEdit>


class MinMax: public QDialog
{
    Q_OBJECT
public:
    MinMax(QWidget *parent = 0);

    int getPriceMin() const;
    int getPriceMax() const;

    int priceMax;
    int priceMin;

private:
    QLabel *minLabel;
    QLabel *maxLabel;

    QLineEdit *priceMinLineEdit;
    QLineEdit *priceMaxLineEdit;

    QDialogButtonBox *buttonBox;


private slots:
    void onButtonClicked(QAbstractButton *button);
signals:
    void  buttonClicked(int,int);
};

#endif // MINMAXDIALOG_H

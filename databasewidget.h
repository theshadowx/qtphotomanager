#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include "database.h"
#include "comboboxdelegate.h"

class DatabaseWidget : public QWidget
{
    Q_OBJECT
public:

    explicit DatabaseWidget(DataBase *database, QWidget *parent = 0);
    virtual ~DatabaseWidget();

protected:
    void resizeEvent(QResizeEvent* );
    void paintEvent(QPaintEvent *);

private:
    DataBase *database;

    QTableView *userTableView;
    QTableView *imageTableView;
    QStandardItemModel *userModel;
    QStandardItemModel *imageModel;
    ComboBoxDelegate *userDelegate;
    ComboBoxDelegate *imageSizeDelegate;
    ComboBoxDelegate *imageCfdyDelegate;

    QFrame *frame;
    QHBoxLayout *layout;
    QPushButton *cancelButton;
    QPushButton *saveButton;
    QSpacerItem *leftSpacer;
    QSpacerItem *rightSpacer;

    bool imageDbModified;
    bool userDbModified;

signals:
    void cancelButtonClicked();
    void saveButtonClicked();
    void imageDbChanged(DataBase *);
    void userDbChanged(DataBase *);

public slots:
    void onCancelButtonClicked();
    void onSaveButtonClicked();
    void onUserDbChanged();
    void onImageDbChanged();
    void showUserDb();
    void showImageDb();
    
};

#endif // DATABASEWIDGET_H

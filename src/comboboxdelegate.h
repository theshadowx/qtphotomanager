#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <QComboBox>



class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxDelegate(QString enumString, QObject *parent = 0);
    virtual ~ComboBoxDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QVector<QString> items;
    QString type;
signals:
    
public slots:
    
};

#endif // COMBOBOXDELEGATE_H

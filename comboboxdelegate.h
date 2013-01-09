#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <QWidget>
#include <QtGui>
#include <QtCore>


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
  std::vector<std::string> items;

signals:
    
public slots:
    
};

#endif // COMBOBOXDELEGATE_H

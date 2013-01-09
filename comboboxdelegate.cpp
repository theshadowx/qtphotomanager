#include "comboboxdelegate.h"

/// Constructor of ComboBoxDelegate
ComboBoxDelegate::ComboBoxDelegate(QString enumString,QObject *parent)
:QItemDelegate(parent)
{

    if(enumString == "Permission"){
            items.push_back("LEVEL_1");
            items.push_back("LEVEL_2");
            items.push_back("LEVEL_3");
    }else if(enumString == "Size"){
            items.push_back("SMALL");
            items.push_back("MEDIUM");
            items.push_back("LARGE");
    }else if(enumString == "Confidentiality"){
            items.push_back("F");
            items.push_back("R");
    }

}

/// Destructor of ComboBoxDelegate
ComboBoxDelegate::~ComboBoxDelegate()
{
}

/// Create editor
QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
  QComboBox* editor = new QComboBox(parent);
  for(unsigned int i = 0; i < items.size(); ++i){
    editor->addItem(items[i].c_str());
  }
  return editor;
}

/// Set data to editor
void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  int value = index.model()->data(index, Qt::EditRole).toInt();
  comboBox->setCurrentIndex(value);
}

/// Set data to the model
void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  model->setData(index, comboBox->currentIndex(), Qt::EditRole);
}

/// Update geometry of the editor
void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}

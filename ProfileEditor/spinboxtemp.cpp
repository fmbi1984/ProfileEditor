#include "spinboxtemp.h"


SpinBoxTemp::SpinBoxTemp(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


SpinBoxTemp::~SpinBoxTemp()
{
}


QWidget *SpinBoxTemp::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{  
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setDecimals(1);
    editor->setMinimum(0.0);
    editor->setMaximum(80);

    return editor;
}


void SpinBoxTemp::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index,Qt::EditRole).toDouble();

    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->setValue(value);
}


void SpinBoxTemp::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->interpretText();
    double value = spinBox->value();

    model->setData(index,value,Qt::EditRole);
}

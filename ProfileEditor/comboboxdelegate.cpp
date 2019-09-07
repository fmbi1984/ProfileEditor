#include "comboboxdelegate.h"


ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


ComboBoxDelegate::~ComboBoxDelegate()
{
}


QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Create the combobox and populate it
    QComboBox *cb = new QComboBox(parent);
    const int row = index.row();
    cb->addItem(QString("Pausa").arg(row));
    cb->addItem(QString("Carga").arg(row));
    //cb->addItem(QString("three in row %1").arg(row));
    return cb;
}


void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    // get the index of the text in the combobox that matches the current value of the item
    const QString currentText = index.data(Qt::EditRole).toString();
    const int cbIndex = cb->findText(currentText);

    // if it is valid, adjust the combobox
    if (cbIndex >= 0)
      cb->setCurrentIndex(cbIndex);

    qDebug()<<"currentText";
    qDebug()<<currentText;
    qDebug()<<"setEditor";
}


void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    model->setData(index, cb->currentText(), Qt::EditRole);
}

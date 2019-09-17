#include "comboboxtime.h"


ComboBoxTime::ComboBoxTime(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


ComboBoxTime::~ComboBoxTime()
{
}


QWidget *ComboBoxTime::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Create the combobox and populate it
    QComboBox *cbt = new QComboBox(parent);
    const int row = index.row();
    cbt->addItem(QString("AH").arg(row));
    cbt->addItem(QString("T").arg(row));

    return cbt;
}


void ComboBoxTime::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cbt = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cbt);
    // get the index of the text in the combobox that matches the current value of the item
    const QString currentText = index.data(Qt::EditRole).toString();
    const int cbIndex = cbt->findText(currentText);

    // if it is valid, adjust the combobox
    if (cbIndex >= 0)
      cbt->setCurrentIndex(cbIndex);

    //qDebug()<<"currentText";
    //qDebug()<<currentText;
    //qDebug()<<"setEditor";
}


void ComboBoxTime::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cbt = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cbt);
    model->setData(index, cbt->currentText(), Qt::EditRole);
}

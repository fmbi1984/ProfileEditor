#include "timedelegate.h"


TimeDelegate::TimeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}


TimeDelegate::~TimeDelegate()
{
}


QWidget *TimeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{  
     QTimeEdit *timeEdit = new QTimeEdit(parent);
     timeEdit->setDisplayFormat("mm:ss");
     connect(timeEdit, SIGNAL(editingFinished()),
     this, SLOT(commitAndCloseEditor()));

     return timeEdit;
}


void TimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int secs = index.model()->data(index, Qt::DisplayRole).toInt();
    QTimeEdit *timeEdit = qobject_cast<QTimeEdit *>(editor);
    timeEdit->setTime(QTime(0, secs / 60, secs % 60));
}


void TimeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QTimeEdit *timeEdit = qobject_cast<QTimeEdit *>(editor);
    QTime time = timeEdit->time();
    int secs = (time.minute() * 60) + time.second();
    model->setData(index, secs);
}

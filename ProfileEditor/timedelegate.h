#ifndef TIMEDELEGATE_H
#define TIMEDELEGATE_H

#include <QTimeEdit>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QDebug>

class TimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TimeDelegate(QObject *parent = nullptr);
    ~TimeDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // COMBOBOXITEMDELEGATE_H


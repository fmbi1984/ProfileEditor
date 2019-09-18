#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QDebug>

class SpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SpinBoxDelegate(QObject *parent = nullptr);
    ~SpinBoxDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif


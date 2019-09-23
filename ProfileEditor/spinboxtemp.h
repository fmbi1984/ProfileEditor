#ifndef SPINBOXTEMP_H
#define SPINBOXTEMP_H

#include <QDoubleSpinBox>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QDebug>

class SpinBoxTemp : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SpinBoxTemp(QObject *parent = nullptr);
    ~SpinBoxTemp();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif


#ifndef COMBOBOXTIME_H
#define COMBOBOXTIME_H

#include <QComboBox>
#include <QStyledItemDelegate>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QDebug>

class ComboBoxTime : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ComboBoxTime(QObject *parent = nullptr);
    ~ComboBoxTime();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // COMBOBOXITEMDELEGATE_H


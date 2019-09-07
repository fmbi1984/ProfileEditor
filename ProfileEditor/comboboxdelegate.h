#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QComboBox>
#include <QStyledItemDelegate>
#include <QDebug>

class ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ComboBoxDelegate(QObject *parent = nullptr);
    ~ComboBoxDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // COMBOBOXITEMDELEGATE_H


#include "tabledelegate.h"

#include <QPainter>
#include "tablemodel.h"

TableDelegate::TableDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    if (index.column() == TableModel::Value)
    {
        QSlider *editor = new QSlider(Qt::Horizontal, parent);
        editor->setRange(0, 100);
        editor->setAutoFillBackground(true);
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == TableModel::Value)
    {
        QSlider *slider = qobject_cast<QSlider *>(editor);
        if (slider)
        {
            const int value = index.model()->data(index).toInt();
            slider->setValue(value);
        }
    }
    else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void TableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == TableModel::Value)
    {
        QSlider *slider = qobject_cast<QSlider *>(editor);
        if (editor)
        {
            model->setData(index, slider->value());
        }
    }
    else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void TableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == TableModel::Value)
    {
        painter->save();
        const int value = index.model()->data(index).toInt();
        QRect rect(option.rect);
        const int width = (value * rect.width()) / 100;
        rect.setWidth(width);
        QColor c;
        if (value <= 20)
        {
            c = Qt::red;
        }
        else if (value <= 50)
        {
            c = QColor(240, 96, 0);
        }
        else
        {
            c = Qt::green;
        }

        painter->fillRect(rect, c);
        QTextOption o;
        o.setAlignment(Qt::AlignCenter);
        painter->drawText(option.rect, QString("%1 %").arg(value), o);

        painter->restore();
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

void TableDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

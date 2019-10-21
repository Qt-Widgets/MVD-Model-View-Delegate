#include "tablemodel.h"


TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (index.column() == Element)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    else if (index.column() == Value)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }

    return QAbstractTableModel::flags(index);
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mElements.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : Count;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= mElements.count())
    {
        return QVariant();
    }

    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        if (index.column() == Element)
        {
            return mElements[index.row()].first;
        }
        else if (index.column() == Value)
        {
            return mElements[index.row()].second;
        }
        break;
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case Element:
            return "Element";
        case Value:
            return "Value";
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() < 0 || index.row() >= mElements.count())
    {
        return false;
    }

    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
        if (index.column() == Element)
        {
            mElements[index.row()].first = value.toString();
        }
        else if (index.column() == Value)
        {
            mElements[index.row()].second = value.toInt();
        }
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

void TableModel::addElement(const QString &element, int value)
{
    const int count = mElements.count();
    if (value < 0)
    {
        value = 0;
    }
    else if (value > 100)
    {
        value = 100;
    }
    beginInsertRows(QModelIndex(), count, count);
    mElements << qMakePair(element, value);
    endInsertRows();
}

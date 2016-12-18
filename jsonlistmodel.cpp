#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "jsonlistmodel.h"

JsonListModel::JsonListModel(QObject *parent) : QAbstractListModel(parent)
{
}

//

QString JsonListModel::json() const
{
    return m_json;
}

void JsonListModel::setJson(const QString &json)
{
    m_json = json;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(m_json.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArray = jsonObj[m_query].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QHash<int, QVariant> jsonData;
        beginInsertRows(QModelIndex(), m_jsonList.size(), m_jsonList.size());
        for ( int i = 0; i < m_roles.size(); i++ ) {
            jsonData.insert(i, obj[m_roles[i]].toVariant());
        }
        m_jsonList.append(jsonData);
        endInsertRows();
    }
}

QString JsonListModel::query() const
{
    return m_query;
}

void JsonListModel::setQuery(const QString &query)
{
    m_query = query;
}

QStringList JsonListModel::roles() const
{
    return m_roles;
}

void JsonListModel::setRoles(const QStringList &roles)
{
    m_roles = roles;
}

//

int JsonListModel::rowCount(const QModelIndex &) const
{
    return m_jsonList.size();
}

QHash<int, QByteArray> JsonListModel::roleNames() const
{
    QHash<int, QByteArray> ret;
    for ( int i = 0; i < m_roles.size(); i++ ) {
        ret.insert(i, m_roles[i].toUtf8());
    }
    return ret;
}

QVariant JsonListModel::data(const QModelIndex &index, int role) const
{
    return m_jsonList[index.row()][role];
}

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "jsonlistmodel.h"

JsonListModel::JsonListModel(QObject *parent) : QAbstractListModel(parent)
{
}

//

QString JsonListModel::jsonText() const
{
    return m_jsonText;
}

void JsonListModel::setJsonText(const QString &jsonText)
{
    m_jsonText = jsonText;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(m_jsonText.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArray = jsonObj[m_role].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QHash<int, QVariant> jsonData;
        beginInsertRows(QModelIndex(), m_jsonList.size(), m_jsonList.size());
        for ( int i = 0; i < m_jrole.size(); i++ ) {
            jsonData.insert(i, obj[m_jrole[i]].toVariant());
        }
        m_jsonList.append(jsonData);
        endInsertRows();
    }
}

QString JsonListModel::role() const
{
    return m_role;
}

void JsonListModel::setRole(const QString &role)
{
    m_role = role;
}

QStringList JsonListModel::jrole() const
{
    return m_jrole;
}

void JsonListModel::setJrole(const QStringList &jrole)
{
    m_jrole = jrole;
}

//

int JsonListModel::rowCount(const QModelIndex &) const
{
    return m_jsonList.size();
}

QHash<int, QByteArray> JsonListModel::roleNames() const
{
    QHash<int, QByteArray> ret;
    for ( int i = 0; i < m_jrole.size(); i++ ) {
        ret.insert(i, m_jrole[i].toUtf8());
    }
    return ret;
}

QVariant JsonListModel::data(const QModelIndex &index, int role) const
{
    return m_jsonList[index.row()][role];
}

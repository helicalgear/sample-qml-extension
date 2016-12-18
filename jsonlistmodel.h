#ifndef JSONLISTMODEL_H
#define JSONLISTMODEL_H

#include <QAbstractListModel>

class JsonListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString jsonText READ jsonText WRITE setJsonText)
    Q_PROPERTY(QString query READ query WRITE setQuery)
    Q_PROPERTY(QStringList jrole READ jrole WRITE setJrole)

public:
    //
    int rowCount(const QModelIndex &parent) const;
    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;
    //
    QString jsonText() const;
    void setJsonText(const QString &jsonText);
    QString query() const;
    void setQuery(const QString &query);
    QStringList jrole() const;
    void setJrole(const QStringList &jrole);
    //
    explicit JsonListModel(QObject *parent = 0);

private:
    QString m_jsonText;
    QString m_query;
    QStringList m_jrole;
    QList<QHash<int, QVariant>> m_jsonList;
};

#endif // JSONLISTMODEL_H

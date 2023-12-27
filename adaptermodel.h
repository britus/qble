#ifndef ADAPTERMODEL_H
#define ADAPTERMODEL_H

#include <QAbstractListModel>
#include <QDBusPendingReply>

#include <QtDBus>

class AdapterModel : public QAbstractListModel
{
    Q_OBJECT

public:
    typedef QMap<QString, QVariantMap> InterfaceList;
    typedef QMap<QDBusObjectPath, InterfaceList> ManagedObjectList;

    AdapterModel(QObject *parent = nullptr);
    enum Roles { AdapterPath = Qt::UserRole + 1, AdapterName, ItemText };

    QHash<int, QByteArray> roleNames() const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QDBusInterface *m_objectManager = nullptr;
    QStringList m_devices;
    QStringList m_deviceNames;
    QHash<int, QByteArray> m_roleNames;

private:
    inline bool getManagedObjects(QDBusPendingReply<ManagedObjectList> &reply);
};

Q_DECLARE_METATYPE(AdapterModel::InterfaceList)
Q_DECLARE_METATYPE(AdapterModel::ManagedObjectList)

#endif // ADAPTERMODEL_H

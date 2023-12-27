#include "adaptermodel.h"
#include <QDebug>

AdapterModel::AdapterModel(QObject *parent)
    : QAbstractListModel(parent)
{
    qDBusRegisterMetaType<InterfaceList>();
    qDBusRegisterMetaType<ManagedObjectList>();

    m_roleNames[AdapterPath] = "path";
    m_roleNames[AdapterName] = "name";
    m_roleNames[ItemText] = "itemText";

    m_objectManager = new QDBusInterface( //
        "org.bluez", "/", "org.freedesktop.DBus.ObjectManager", QDBusConnection::systemBus());

    QDBusPendingReply<ManagedObjectList> reply;
    if (!getManagedObjects(reply)) {
        qCritical() << "[AdapterModel]: Unable to run DBUS::GetManagedObjects";
        return;
    }

    const QList<QDBusObjectPath> keys = static_cast< //
        const QList<QDBusObjectPath>>(reply.value().keys());
    for (const QDBusObjectPath &path: keys) {
        const InterfaceList ifaceList = reply.value().value(path);
        const QList<QString> ikeys = static_cast< //
            const QList<QString>>(ifaceList.keys());
        for (const QString &iface: ikeys) {
            if (iface == QStringLiteral("org.bluez.Adapter1")) {
                m_devices << path.path();
                m_deviceNames << ifaceList.value(iface).value(QStringLiteral("Name")).toString();
            }
        }
    }
}

inline bool AdapterModel::getManagedObjects(QDBusPendingReply<ManagedObjectList> &reply)
{
    reply = m_objectManager->call("GetManagedObjects");
    reply.waitForFinished();
    if (reply.isError()) {
        qCritical() << "[AdapterModel]: Unable to run DBUS::GetManagedObjects";
        return false;
    }
    return true;
}

int AdapterModel::columnCount(const QModelIndex &) const
{
    return m_roleNames.count();
}

QVariant AdapterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("path");
            case 1:
                return tr("name");
            case 2:
                return tr("itemText");
        }
    }
    return QVariant();
}

int AdapterModel::rowCount(const QModelIndex &) const
{
    return m_devices.count();
}

QVariant AdapterModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0: {
                return data(index, AdapterPath);
            }
            case 1: {
                return data(index, AdapterName);
            }
            case 2: {
                return data(index, ItemText);
            }
        }
        return QVariant();
    }

    if (index.row() >= 0 && index.row() < m_devices.length()) {
        if (role == AdapterPath || role == ItemText) {
            return m_devices.at(index.row());
        } else if (role == AdapterName) {
            return m_deviceNames.at(index.row());
        }
    }

    return QVariant();
}

QHash<int, QByteArray> AdapterModel::roleNames() const
{
    return m_roleNames;
}

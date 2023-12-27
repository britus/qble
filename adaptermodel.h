#ifndef ADAPTERMODEL_H
#define ADAPTERMODEL_H

#include <QAbstractListModel>
#include <QtDBus>

class AdapterModel : public QAbstractListModel
{
    Q_OBJECT

public:
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
};

#endif // ADAPTERMODEL_H

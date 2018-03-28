#pragma once
#include<QObject>
#include <hueplusplus/Hue.h>
#include <QDebug>
#include <hueplusplus/LinHttpHandler.h>
#include <hueplusplus/UPnP.h>
#include <QVariantList>
#include <QAbstractListModel>

// A single light
class Light {
public:
    Light(const QString &name) : name(name) {}
    QString name{};
};


// A list of lights
class LightModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LightModel(QObject *parent = 0) {}
    virtual ~LightModel() {}

    enum LightRoles {
        NameRole = Qt::UserRole + 1
    };

    QHash<int, QByteArray> roleNames() const override{
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        return roles;
    }

    QVariant data(const QModelIndex &index, int role) const override
    {
        if (index.row() < 0 || index.row() >= m_lights.size())
        {
            return QVariant();
        }

        if (role == NameRole)
        {
            return QVariant::fromValue(m_lights.at(index.row()).name);
        }
        return QVariant();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return m_lights.length();
    }

    void add(const QString name) {
        Light new_light{name};
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_lights << new_light;
        endInsertRows();
    }

private:
    QList<Light> m_lights{};
};

class HueAPI : public QObject {
    Q_OBJECT
    Q_PROPERTY(LightModel* model MEMBER model NOTIFY modelChanged)
public:
    explicit HueAPI();
    virtual ~HueAPI();
    Q_INVOKABLE void sync();
    LightModel *model;
private:
    std::shared_ptr<LinHttpHandler> m_handler;
    Hue* m_bridge;
    Q_SIGNAL void modelChanged();
    const std::string ip = "PUT_IP_HERE";
    const std::string username = "PUT_USERNAME_HERE";
};

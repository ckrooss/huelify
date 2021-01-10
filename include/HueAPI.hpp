#pragma once
#include<QObject>
#include <hueplusplus/Hue.h>
#include <QDebug>
#include <hueplusplus/LinHttpHandler.h>
#include <hueplusplus/UPnP.h>
#include <QVariantList>
#include <QAbstractListModel>
#include <atomic>

// A single light
class Light {
public:
    Light(const QString name, const unsigned int brightness, const bool isOn) : name(name), brightness(brightness), isOn(isOn) {}
    QString name{};
    unsigned int brightness;
    bool isOn;
};


// A list of lights
class LightModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LightModel(QObject *parent = 0) : QAbstractListModel(parent) {}
    virtual ~LightModel() {}

    enum LightRoles {
        NameRole = Qt::UserRole + 1,
        BrightnessRole,
        OnRole
    };

    QHash<int, QByteArray> roleNames() const override{
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[BrightnessRole] = "brightness";
        roles[OnRole] = "isOn";
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
        else if (role == BrightnessRole)
        {
            return QVariant::fromValue(m_lights.at(index.row()).brightness);
        }
        else if (role == OnRole)
        {
            return QVariant::fromValue(m_lights.at(index.row()).isOn);
        }

        return QVariant();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return m_lights.length();
    }

    void add(const Light &light) {
        for (int idx=0; idx < m_lights.length(); idx++) {
            if (m_lights[idx].name == light.name) {
                beginInsertRows(QModelIndex(), idx, idx);
                m_lights[idx] = light;
                endInsertRows();
                return;
            }
        }

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_lights << light;
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
    Q_INVOKABLE void setBrightness(int id, int bri);
    LightModel *model;
private:
    std::shared_ptr<LinHttpHandler> m_handler;
    Hue* m_bridge;
    Q_SIGNAL void modelChanged();
    const std::string ip = "192.168.178.35";
    const std::string username = "1Bg4rqVIkCxRzSfPURfI5SrfEpZMOAktzzMTNXhL";
    std::atomic<bool> m_locked{false};
};

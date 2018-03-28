#include <HueAPI.hpp>

HueAPI::HueAPI() : m_handler(std::make_shared<LinHttpHandler>()) {
    qWarning() << "instantiated";
    m_bridge = new Hue{ip, username, m_handler};
    model = new LightModel();
}

HueAPI::~HueAPI() {
    qDebug() << "Destroyed";
}

void HueAPI::sync() {
    for (int light_id = 0; light_id < 100;light_id++) {
        if (!m_bridge->lightExists(light_id)) continue;
        try {
            auto light = m_bridge->getLight(light_id);
            model->add(QString::fromStdString(light.getName()));
        }
        catch(const std::runtime_error &e) {
            qWarning() << e.what();
        }
    }
    emit modelChanged();
}

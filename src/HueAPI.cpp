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
    auto lights = m_bridge->getAllLights();

    for (HueLight &hue_light: lights) {
        Light light{QString::fromStdString(hue_light.getName()), hue_light.getBrightness(), hue_light.isOn()};
        model->add(light);
    }
    emit modelChanged();
}

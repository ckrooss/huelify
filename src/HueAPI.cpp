#include <HueAPI.hpp>
#include <QtConcurrent>

HueAPI::HueAPI() : m_handler(std::make_shared<LinHttpHandler>()) {
    qWarning() << "instantiated";
    m_bridge = new Hue{ip, username, m_handler};
    model = new LightModel();
}

HueAPI::~HueAPI() {
    qDebug() << "Destroyed";
}

void HueAPI::sync() {
    QtConcurrent::run([this](){
        auto lights = m_bridge->getAllLights();
        for (HueLight &hue_light: lights) {
            Light light{QString::fromStdString(hue_light.getName()), hue_light.getBrightness(), hue_light.isOn()};
            model->add(light);
        }
        emit modelChanged();
    });
}

void HueAPI::setBrightness(int id, int bri) {
    auto was_locked = m_locked.exchange(true);
    if(was_locked) {
        std::cout << "bailing out" << std::endl;
        return;
    }

    if(bri < 0 || bri > 254) {
        std::cout << "nonsense value " << bri << std::endl;
        return;
    }

    QtConcurrent::run([this, id, bri](){
        auto light = m_bridge->getLight(id);
        light.setBrightness(bri, 1);
        std::cout << bri << std::endl;
        m_locked.store(false);
    });
}

#include <viam/sdk/components/sensor/sensor.hpp>
#include <viam/sdk/module/service.hpp>

#include "wifi.hpp"

using namespace viam::sdk;

class WifiSensor : public Sensor {
   public:
    WifiSensor(Dependencies deps, ResourceConfig cfg) : Sensor(cfg.name()) {}
    AttributeMap do_command(const AttributeMap& command) { return {}; }
    std::vector<GeometryConfig> get_geometries(const AttributeMap& extra) { return std::vector<GeometryConfig>(); }
    AttributeMap get_readings(const AttributeMap& extra) { return read_wireless(); }
};

int main(int argc, char **argv) {
    std::shared_ptr<ModelRegistration> mr = std::make_shared<ModelRegistration>(
        Sensor::static_api(), Model("viam", "wifi", "cpp"),
        [](Dependencies deps, ResourceConfig cfg) { return std::make_shared<WifiSensor>(deps, cfg); }
    );

    // The `ModuleService` must outlive the Server, so the declaration order here matters.
    auto service = std::make_shared<ModuleService>(argc, argv, std::vector{mr});
    service->serve();
    return 0;
}

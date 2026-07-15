#include "model/Sample.h"

namespace monitor::model {

Sample Sample::fromJson(const json::JsonValue& value) {
    Sample sample;
    sample.id = value.at("id").asString();
    sample.name = value.at("name").asString();
    sample.avgProcessTimeMin = value.at("avgProcessTimeMin").asNumber();
    sample.yieldRate = value.at("yieldRate").asNumber();
    sample.stock = static_cast<int>(value.at("stock").asNumber());
    return sample;
}

}  // namespace monitor::model

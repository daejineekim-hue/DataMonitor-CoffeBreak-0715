#pragma once

#include <string>

#include "json/JsonValue.h"

namespace monitor::model {

struct Sample {
    std::string id;
    std::string name;
    double avgProcessTimeMin = 0.0;
    double yieldRate = 0.0;
    int stock = 0;

    static Sample fromJson(const json::JsonValue& value);
};

}  // namespace monitor::model

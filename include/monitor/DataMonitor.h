#pragma once

#include <string>
#include <vector>

#include "model/Sample.h"

namespace monitor {

// Reads a JSON-backed sample store on a fixed interval and re-renders a
// console dashboard, so an operator can watch the current data state
// without restarting the tool. Press 'q' at any time to stop.
class DataMonitor {
public:
    DataMonitor(std::string filePath, int refreshIntervalSec);

    void run();

private:
    std::string filePath_;
    int refreshIntervalSec_;

    std::vector<model::Sample> loadSamples() const;
    void render(const std::vector<model::Sample>& samples) const;
};

}  // namespace monitor

#include "monitor/DataMonitor.h"

int main() {
    monitor::DataMonitor dataMonitor("data/samples.json", 2);
    dataMonitor.run();
    return 0;
}

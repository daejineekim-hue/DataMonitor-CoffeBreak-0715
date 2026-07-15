#include "monitor/DataMonitor.h"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <thread>

#ifdef _WIN32
#include <conio.h>
#endif

namespace monitor {

using json::JsonValue;
using model::Sample;

DataMonitor::DataMonitor(std::string filePath, int refreshIntervalSec)
    : filePath_(std::move(filePath)), refreshIntervalSec_(refreshIntervalSec) {}

std::vector<Sample> DataMonitor::loadSamples() const {
    std::vector<Sample> samples;
    std::ifstream in(filePath_);
    if (!in.is_open()) return samples;

    std::ostringstream buffer;
    buffer << in.rdbuf();
    std::string text = buffer.str();
    if (text.empty()) return samples;

    JsonValue root = JsonValue::parse(text);
    for (const auto& item : root.items()) {
        samples.push_back(Sample::fromJson(item));
    }
    return samples;
}

namespace {

std::string statusOf(const Sample& sample) {
    if (sample.stock <= 0) return "고갈";
    if (sample.stock < 50) return "부족";
    return "여유";
}

std::string currentTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm localTm{};
#ifdef _WIN32
    localtime_s(&localTm, &now);
#else
    localtime_r(&now, &localTm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&localTm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\x1B[2J\x1B[H";
#endif
}

}  // namespace

void DataMonitor::render(const std::vector<Sample>& samples) const {
    clearScreen();
    std::cout << "==================================================\n";
    std::cout << " 데이터 모니터링 도구  (" << currentTimestamp() << ")\n";
    std::cout << " 대상 파일: " << filePath_ << "\n";
    std::cout << "==================================================\n";

    int totalStock = std::accumulate(samples.begin(), samples.end(), 0,
                                      [](int sum, const Sample& s) { return sum + s.stock; });
    std::cout << "등록 시료 수: " << samples.size() << "종   총 재고: " << totalStock << " ea\n\n";

    if (samples.empty()) {
        std::cout << "표시할 데이터가 없습니다.\n";
    } else {
        std::cout << std::left << std::setw(10) << "ID" << std::setw(20) << "시료명"
                   << std::setw(10) << "재고" << "상태\n";
        for (const auto& s : samples) {
            std::cout << std::left << std::setw(10) << s.id << std::setw(20) << s.name
                       << std::setw(10) << s.stock << statusOf(s) << "\n";
        }
    }

    std::cout << "\n" << refreshIntervalSec_ << "초마다 자동 갱신됩니다. 'q'를 누르면 종료합니다.\n";
}

void DataMonitor::run() {
    while (true) {
        render(loadSamples());

        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(refreshIntervalSec_);
        while (std::chrono::steady_clock::now() < deadline) {
#ifdef _WIN32
            if (_kbhit()) {
                int ch = _getch();
                if (ch == 'q' || ch == 'Q') return;
            }
#endif
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

}  // namespace monitor

//
// Created by czy on 23-7-1.
//

#ifndef GROUND_SURFACE_ESTIMATION_TIMER_H
#define GROUND_SURFACE_ESTIMATION_TIMER_H
#include <string>
#include <chrono>
#include <map>
#include <vector>

class Timer {
 public:
  struct TimerRecord {
    TimerRecord() = default;
    TimerRecord(const std::string& name, double time_usage) {
      func_name_ = name;
      time_usage_in_ms_.emplace_back(time_usage);
    }
    std::string func_name_;
    std::vector<double> time_usage_in_ms_;
  };

  template <class F>
  static void Evaluate(F&& func, const std::string& func_name) {
    auto t1 = std::chrono::steady_clock::now();
    std::forward<F>(func)();
    auto t2 = std::chrono::steady_clock::now();
    auto time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count() * 1000;

    if (records_.find(func_name) != records_.end()) {
      records_[func_name].time_usage_in_ms_.emplace_back(time_used);
    } else {
      records_.insert({func_name, TimerRecord(func_name, time_used)});
    }
  }

  static void PrintAll();

  static void DumpIntoFile(const std::string& file_name);

  static double GetMeanTime(const std::string& func_name);

  static void Clear() { records_.clear(); }

 private:
  static std::map<std::string, TimerRecord> records_;
};

#endif  // GROUND_SURFACE_ESTIMATION_TIMER_H

#include "Utils.hpp"
#include <map>
#include <numeric>
#include <string_view>
#include <iostream>

template<typename InputType_ = int, typename DepthType_ = int, typename HorizontalType_ = int, typename AimType_ = int>
struct Command {
  using InputType = InputType_;
  using DepthType = DepthType_;
  using HorizontalType = HorizontalType_;
  using AimType = AimType_;
  using PositionType = std::tuple<DepthType, HorizontalType, AimType>;

  virtual ~Command() = default;
  virtual PositionType calculateDifference(const InputType &input) const = 0;
};

struct UpCommand : Command<> {
  PositionType calculateDifference(const InputType &input) const final {
    return {0, 0, -input};
  }
};

struct DownCommand : Command<> {
  PositionType calculateDifference(const InputType &input) const final {
    return {0, 0, input};
  }
};

struct ForwardCommand : Command<> {
  PositionType calculateDifference(const InputType &input) const final {
    return {0, input, 0};
  }
};

void partTwo(const auto &inputData) {
  const std::map<std::string_view, std::shared_ptr<Command<>>> commands{
          {"up", std::make_unique<UpCommand>()},
          {"down", std::make_unique<DownCommand>()},
          {"forward", std::make_unique<ForwardCommand>()},
  };

  const auto [result_y, result_x, result_aim] = std::accumulate(inputData.cbegin(), inputData.cend(), Command<>::PositionType{}, [&commands](const Command<>::PositionType& position, const auto& input) {
    const auto& [value, command] = input;
    const auto& [current_y, current_x, current_aim] = position;
    const auto [delta_y, delta_x, delta_aim] = commands.at(command)->calculateDifference(value);
    return Command<>::PositionType{current_y + delta_x * (current_aim + delta_aim), current_x + delta_x, current_aim + delta_aim};
  });

  std::cout << "Depth is: " << result_y << ", horizontal is: " << result_x << ", multiplying it gives: " << result_y * result_x << std::endl;
}

int main() {
  static constexpr auto inputFile = R"(C:\Code\aoc_2021\input\day_2.txt)";
  const auto inputData = readFromFile<int, std::string>(inputFile);

  partTwo(inputData);
}
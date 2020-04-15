/*
 *   Copyright (c) 2020 Jackson Cougar Wiebe
 *   All rights reserved.
 */

#include <fstream>
#include <string>
#include <utility>

#include "driver.h"
#include "tokens.h"

using namespace std::literals::string_literals;

struct ProgramException : public std::exception {
  explicit ProgramException(std::string message)
      : message(std::move(message)) {}
  std::string message;
  [[nodiscard]] const char *what() const noexcept override {
    return message.c_str();
  }
};

int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      throw ProgramException{
          "You must pass the pathname of an input file to scan as the first "
          "program argument."};
    }
    if (argc > 2) {
      throw ProgramException{
          "This program must accept exactly one command-line argument: the "
          "pathname of an input file."};
    }

    std::ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
      throw ProgramException{"Could not open input file '" +
                             std::string(argv[1]) + "'"};
    }

    yy::Driver driver;
    driver.streamname = argv[1]; // for printing errors
    driver.parse_stream(ifs);

    // semantic checking...
    // SemanticChecker sc;
    // sc.process(driver.root.get());

  } catch (const char *e) {
    error(e);
    exit(1);
  } catch (const std::string &e) {
    error(e);
    exit(1);
  }

  return 0;
}
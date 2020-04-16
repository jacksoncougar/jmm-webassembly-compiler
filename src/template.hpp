//
// Created by Jackson Cougar Wiebe on 3/25/2020.
//

#ifndef SCANNER_TEMPLATE_HPP
#define SCANNER_TEMPLATE_HPP

#include <numeric>
#include <string>
#include <utility>
#include <vector>

struct Template
{
  std::string template_string;

  Template(std::string t) : template_string(std::move(t)){};

  Template(std::string t, std::initializer_list<std::string> args) : template_string(std::move(t))
  {

    for (const auto &param : args)
    {
      auto start = template_string.find('{');
      auto end = template_string.find('}', start);
      template_string = template_string.replace(start, end - start + 1, param);
    }
  };

  Template &operator<<(std::string arg)
  {
    auto start = template_string.find("{");
    auto end = template_string.find("}", start);
    template_string = template_string.replace(start, end - start + 1, arg);
    return *this;
  }

  Template &operator<<(std::vector<std::string> pack)
  {
    auto param_list = std::accumulate(
            pack.begin(), pack.end(), std::string(),
            [](const std::string &a, const std::string &b) -> std::string {
              return a + (a.length() > 0 ? "," : "") + b;
            });
    return *this << param_list;
  }

  friend std::ostream &operator<<(std::ostream &out, Template &&aTemplate)
  {
    return out << aTemplate.template_string;
  }

  operator std::string() const { return template_string; }
};
#endif// SCANNER_TEMPLATE_HPP

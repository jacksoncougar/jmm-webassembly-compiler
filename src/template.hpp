//
// Created by Jackson Cougar Wiebe on 3/25/2020.
//

#ifndef SCANNER_TEMPLATE_HPP
#define SCANNER_TEMPLATE_HPP

#include <string>
#include <numeric>
#include <vector>

struct Template {
    std::string t;

    Template(std::string t) : t(std::move(t)) {};

    Template &operator<<(std::string arg) {
        auto start = t.find("{");
        auto end = t.find("}", start);
        t = t.replace(start, end - start + 1, arg);
        return *this;
    }

    Template &operator<<(std::vector<std::string> pack) {
        auto param_list = std::accumulate(pack.begin(), pack.end(), std::string(),
                                          [](const std::string &a,
                                             const std::string &b) -> std::string {
                                              return a + (a.length() > 0 ? "," : "") + b;
                                          });
        return *this << param_list;
    }

    friend std::ostream& operator<<(std::ostream& out, Template& $template) {
        return out << static_cast<std::string>($template);
    }

    operator std::string() { return t; }
};
#endif //SCANNER_TEMPLATE_HPP

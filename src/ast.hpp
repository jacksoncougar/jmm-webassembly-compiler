/*
 *   Copyright (c) 2020 Jackson Cougar Wiebe
 *   All rights reserved.
 */

#ifndef AST_H
#define AST_H

#include <memory>
#include <utility>
#include <vector>
#include <initializer_list>
#include <iostream>

static int tab = 0;

std::ostream &operator<<(std::ostream &out, const class ASTNodeBase &node);

class ASTNodeBase {
protected:
    std::vector<std::unique_ptr<ASTNodeBase>> m_children;

public:
    std::string name;

    [[nodiscard]] const std::vector<std::unique_ptr<ASTNodeBase>> &children() const {

        return m_children;
    }

    // adds the node as a child.
    void add(ASTNodeBase *node);

    // prints this node,its attributes, and its child nodes.
    virtual std::ostream &print(std::ostream &out) const = 0;

    ASTNodeBase(
        std::string name, std::initializer_list<ASTNodeBase *> children = {}
    ) : name(std::move(name)) {

        for (auto child : children) {
            m_children.emplace_back(std::unique_ptr<ASTNodeBase>(child));
        }
    }
};

template<typename T>
struct ASTNodeAttribute {
    std::string label;
    T value;

    friend std::ostream &operator<<(std::ostream &out, const ASTNodeAttribute &node) {

        out << node.label << ": " << node.value;
        return out;
    }
};

template<typename... As>
class ASTNode : public ASTNodeBase {
public:
    std::tuple<As...> attributes;

    explicit ASTNode(
        std::string name, std::initializer_list<ASTNodeBase *> children = {}, As... attributes
    ) : ASTNodeBase(name, children), attributes(attributes...) {}

    std::ostream &print(std::ostream &out) const override {

        out << std::string(tab, ' ') << "(" << name;


        out << " (attributes (";
        std::apply(
            [&out](auto &&... values) {
                auto n = 0;
                ((out << values << (++n != sizeof...(As) ? ", " : "")), ...);
            }, attributes
        );
        out << "))";

        out << ")\n";
        tab++;

        auto &children = this->children();
        if (!children.empty()) {
            for (auto &n : children) {
                if (n)
                    out << *n;
            }
        }
        tab--;
        return out;
    }
};

template<>
class ASTNode<> : public ASTNodeBase {
public:
    explicit ASTNode(
        std::string name, std::initializer_list<ASTNodeBase *> children = {}
    ) : ASTNodeBase(std::move(name), children) {}

    std::ostream &print(std::ostream &out) const override {

        out << std::string(tab, ' ') << "(" << name;
        out << ")\n";
        tab++;

        auto &children = this->children();
        if (!children.empty()) {
            for (auto &n : children) {
                if (n)
                    out << *n;
            }
        }
        tab--;
        return out;
    }
};

class ASTIntNode : public ASTNode<int> {
public:
    ASTIntNode(
        int value, std::initializer_list<ASTNodeBase *> children = {}
    ) : ASTNode<int>("int", children, value) {}
};

#endif //AST_H
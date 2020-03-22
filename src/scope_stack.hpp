//
// Created by Jackson Cougar Wiebe on 3/19/2020.
//

#ifndef SCANNER_SCOPESTACK_HPP
#define SCANNER_SCOPESTACK_HPP

#include <vector>
#include <map>
#include <memory>

struct Identifier {
    int type;
};

namespace std {
    template<>
    struct less<Identifier> {
        bool operator()(const Identifier &lhs, const Identifier &rhs) const {

            return lhs.type < rhs.type;
        }
    };
}

struct SymbolTableEntry {

};

class ScopeStack {
    std::vector<std::unique_ptr<SymbolTableEntry>> entries;
    std::vector<std::map<Identifier, SymbolTableEntry *>> scopes;
public:
    void open_new_scope() {

        scopes.emplace_back(); // push back an empty map
    }

    void close_top_scope() {

        if (!scopes.empty()) {
            scopes.pop_back();
        }
    }

    SymbolTableEntry *define(Identifier anIdentifier) {

        auto ptr = entries.emplace_back(std::make_unique<SymbolTableEntry>()).get();
        scopes.back().emplace(anIdentifier, ptr); // add an empty table entry for this
        return ptr;
    }

    SymbolTableEntry *lookup(Identifier anIdentifier) {

        for (auto &scope : scopes) {
            auto it = scope.find(anIdentifier);
            if (it != scope.end()) {
                return it->second;
            }
        } //error here...
    }

};


#endif //SCANNER_SCOPESTACK_HPP

#pragma once

#include <Spec.h>
#include <Spec/Snowhouse.h>
#include <Spec/Types/SpecApp.h>

using namespace Spec;
using namespace snowhouse;

std::shared_ptr<Spec::Types::SpecApp> SpecApp(std::function<void()> body = []() {}) {
    auto app = Spec::Types::SpecApp::CreateDefault();
    app->Reporters.clear();
    Types::SpecDiscovery::UsingRegistry(app->Registry, body);
    return app;
}

#include <regex>

class MatchesRegexMatcher {
    std::vector<std::string> _patterns;

public:
    template <typename... Args>
    MatchesRegexMatcher(std::string pattern, Args... args) : _patterns({pattern, args...}) {}

    const std::vector<std::string>& GetPatterns() const { return _patterns; }

    bool Matches(const std::string& text) const {
        for (const auto& pattern : _patterns) {
            if (!std::regex_search(text, std::regex(pattern, std::regex_constants::icase))) {
                return false;
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const MatchesRegexMatcher& matcher) {
        if (matcher._patterns.size() == 1) {
            return os << "match regular expression /" << matcher._patterns[0] << "/";
        } else {
            os << "match regular expressions:";
            for (const auto& pattern : matcher._patterns) {
                os << " /" << pattern << "/";
            }
            return os;
        }
    }
};

#define MatchesRegex(...) Fulfills(MatchesRegexMatcher(__VA_ARGS__))

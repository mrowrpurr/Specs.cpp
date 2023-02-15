#pragma once

#include <any>
#include <functional>
#include <future>
#include <optional>
#include <unordered_map>
#include <vector>

namespace Spec {

    class SpecGroup;

    /** Represents an individual "spec" or "test" */
    class SpecTest {
        std::string                                                _description;
        std::shared_ptr<SpecGroup>                                 _parent;
        std::function<void(SpecTest&)>                             _body;
        std::shared_ptr<std::promise<bool>>                        _promise;
        std::unordered_map<std::string, std::any>                  _metadata;
        std::shared_ptr<std::unordered_map<std::string, std::any>> _data;

    public:
        SpecTest(
            const std::string& description, const std::shared_ptr<SpecGroup>& parent,
            const std::function<void(SpecTest&)>& body
        )
            : _description(description),
              _parent(parent),
              _body(body),
              _promise(std::make_shared<std::promise<bool>>()),
              _data(std::make_shared<std::unordered_map<std::string, std::any>>()) {}

        const std::string&                GetDescription() const { return _description; }
        const std::shared_ptr<SpecGroup>& GetGroup() const { return _parent; }

        void Pass() { _promise->set_value(true); }
        void Fail() { _promise->set_value(false); }
        void Reset() { _promise = std::make_shared<std::promise<bool>>(); }

        std::any Get(const std::string& key) { return _data->at(key); }

        template <typename T>
        T Get(const std::string& key) {
            return std::any_cast<T>(_data->at(key));
        }

        std::any Get(const std::string& key, const std::any& defaultValue) {
            auto it = _data->find(key);
            if (it == _data->end()) {
                return defaultValue;
            }
            return it->second;
        }

        template <typename T>
        T Get(const std::string& key, const T& defaultValue) {
            auto it = _data->find(key);
            if (it == _data->end()) {
                return defaultValue;
            }
            return std::any_cast<T>(it->second);
        }

        void Set(const std::string& key, const std::any& value) { _data->insert_or_assign(key, value); }

        template <typename T>
        void Set(const std::string& key, const T& value) {
            _data->insert_or_assign(key, value);
        }

        std::any GetMeta_data(const std::string& key) { return _metadata.at(key); }

        template <typename T>
        T GetMeta_data(const std::string& key) {
            return std::any_cast<T>(_metadata.at(key));
        }
    };
}
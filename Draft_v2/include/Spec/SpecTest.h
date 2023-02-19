#pragma once

#include <any>
#include <functional>
#include <future>
#include <optional>
#include <unordered_map>
#include <vector>

namespace Specs {

    class SpecGroup;

    /** Represents an individual "spec" or "test" */
    class SpecTest {
        std::string                                                _description;
        std::shared_ptr<SpecGroup>                                 _parent;
        std::optional<std::function<void(SpecTest&)>>              _body;
        std::shared_ptr<std::promise<bool>>                        _promise;
        std::unordered_map<std::string, std::any>                  _metadata;
        std::shared_ptr<std::unordered_map<std::string, std::any>> _data;
        bool _todo                       = false;
        bool _automaticPromiseResolution = true;
        bool _complete                   = false;

    public:
        SpecTest(
            const std::shared_ptr<SpecGroup>&     parent,
            const std::function<void(SpecTest&)>& body
        )
            : _parent(parent), _body(body), _todo(false) {}

        SpecTest(
            const std::string&                description,
            const std::shared_ptr<SpecGroup>& parent
        )
            : _description(description), _parent(parent), _todo(true) {}

        SpecTest(
            const std::string&                    description,
            const std::shared_ptr<SpecGroup>&     parent,
            const std::function<void(SpecTest&)>& body, bool isAsync = false
        )
            : _description(description),
              _parent(parent),
              _body(body),
              _promise(std::make_shared<std::promise<bool>>()),
              _data(std::make_shared<std::unordered_map<std::string, std::any>>(
              )),
              _automaticPromiseResolution(!isAsync) {}

        void Run() {
            if (_body) _body.value()(*this);
        }

        bool RunAndWait(
            std::future<bool>&               future,
            std::chrono::duration<long long> timeout = std::chrono::seconds(0)
        ) {
            if (_body) _body.value()(*this);
            future      = _promise->get_future();
            auto result = future.wait_for(timeout);
            if (result == std::future_status::timeout) {
                Fail();
                return false;
            }
            return true;
        }

        std::shared_ptr<SpecGroup>& GetGroup() { return _parent; }
        std::string                 GetDescription() { return _description; }
        std::string                 GetFullDescription();

        bool IsComplete() { return _complete; }
        void Complete() { _complete = true; }

        void Pass() {
            if (!_complete) _promise->set_value(true);
            Complete();
        }
        void Fail() {
            if (!_complete) _promise->set_value(false);
            Complete();
        }
        void Fail(std::exception_ptr exception) {
            if (!_complete) _promise->set_exception(exception);
            Complete();
        }
        void Fail(const std::string& message) {
            if (!_complete)
                _promise->set_exception(
                    std::make_exception_ptr(std::runtime_error(message))
                );
            Complete();
        }
        void Reset() {
            _promise  = std::make_shared<std::promise<bool>>();
            _complete = false;
        }

        bool HasBody() { return _body.has_value(); }

        bool IsTodo() { return _todo; }
        void SetTodo(bool todo = true) { _todo = todo; }

        bool IsAutomaticPromiseResolution() {
            return _automaticPromiseResolution;
        }
        void SetAutomaticPromiseResolution(
            bool automaticPromiseResolution = true
        ) {
            _automaticPromiseResolution = automaticPromiseResolution;
        }
        void SetManualPromiseResolution() {
            _automaticPromiseResolution = false;
        }
        bool IsManualPromiseResolution() {
            return !_automaticPromiseResolution;
        }
        bool IsAsync() { return IsManualPromiseResolution(); }

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

        void Set(const std::string& key, const std::any& value) {
            _data->insert_or_assign(key, value);
        }

        template <typename T>
        void Set(const std::string& key, const T& value) {
            _data->insert_or_assign(key, value);
        }

        std::any GetMeta_data(const std::string& key) {
            return _metadata.at(key);
        }

        template <typename T>
        T GetMeta_data(const std::string& key) {
            return std::any_cast<T>(_metadata.at(key));
        }
    };
}
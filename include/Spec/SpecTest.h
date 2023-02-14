#pragma once

#include <any>
#include <functional>
#include <future>
#include <optional>
#include <unordered_map>
#include <vector>

namespace Spec {

    /** Represents an individual "spec" or "test" */
    class SpecTest {
    public:
        /** The description of this test (does not include description from parent group(s)) */
        std::string description;

        // Maybe weak_ptr parent? <-- (so we can get to its description, but siblings/etc would be cool)
        /** All  */
        // std::vector<std::string> parentDescription;

        /** The promise which this test is expected to resolve (when using an async test interface)
         *
         * Note: if not using an async test interface, the satisfaction of this promise will be handled automatically.
         *
         * Also, the promise is automatically satisfied when the test throws an exception.
         */
        std::shared_ptr<std::promise<bool>> promise;

        /** Body of this test.
         *
         * Depending on the DSL interface used to create the test, you can optionally accept a SpecTest& argument
         * which references this test. This allows you to access the metadata and data of this test.
         */
        std::function<void(SpecTest&)> body;

        /** Metadata of this test definition, e.g. tags */
        std::unordered_map<std::string, std::any> metadata;

        /** The test data is a map of std::any which is shared between the test as well as any
         * setup and teardown functions which are run before or after the test.
         *
         * Its lifetime lasts for one individual test run.
         */
        std::shared_ptr<std::unordered_map<std::string, std::any>> data;

        void pass() { promise->set_value(true); }
        void fail() { promise->set_value(false); }
        void done() { pass(); }
        void fail(std::string message) {
            // TODO - set message
            fail();
        }

        std::any Get(const std::string& key) { return data->at(key); }

        template <typename T>
        T Get(const std::string& key) {
            return std::any_cast<T>(data->at(key));
        }

        std::any Get(const std::string& key, const std::any& defaultValue) {
            auto it = data->find(key);
            if (it == data->end()) {
                return defaultValue;
            }
            return it->second;
        }

        template <typename T>
        T Get(const std::string& key, const T& defaultValue) {
            auto it = data->find(key);
            if (it == data->end()) {
                return defaultValue;
            }
            return std::any_cast<T>(it->second);
        }

        void Set(const std::string& key, const std::any& value) { data->insert_or_assign(key, value); }

        template <typename T>
        void Set(const std::string& key, const T& value) {
            data->insert_or_assign(key, value);
        }
    };
}
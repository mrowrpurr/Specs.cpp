#pragma once

#include <any>
#include <functional>
#include <future>
#include <optional>
#include <unordered_map>

namespace Spec {

    /** Represents an individual "spec" or "test" */
    struct SpecTest {
        /** The description of this test (does not include description from parent group(s)) */
        std::string description;

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
    };
}
#pragma once

#include <Specs/API.h>
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <dlfcn.h>
#endif
#include <collections.h>

#include <filesystem>
#include <string>
#include <string_view>

namespace SpecsCpp {

    class LibraryLoader {
        ISpecEnvironment* _globalSpecEnvironment = nullptr;

#ifdef _WIN32
        using LibraryPtr = HMODULE;
#else
        using LibraryPtr = void*;
#endif

        using LOAD_FUNCTION_SIGNATURE = ISpecGroup* (*)(ISpecEnvironment*);

        static constexpr auto LOAD_FUNCTION_NAME = "SpecsCpp_Load";

        collections_map<std::string, LibraryPtr> _loadedLibraries;

    public:
        LibraryLoader(ISpecEnvironment* globalSpecEnvironment)
            : _globalSpecEnvironment(globalSpecEnvironment) {}

        ~LibraryLoader() { unload_all(); }

        ISpecGroup* load(std::string_view libraryFilePath) {
            if (!std::filesystem::exists(libraryFilePath))
                throw std::runtime_error("File does not exist: " + std::string(libraryFilePath));

#ifdef _WIN32
            auto libraryHandle = LoadLibraryA(libraryFilePath.data());
#else
            auto libraryHandle = dlopen(libraryFilePath.data(), RTLD_LAZY);
#endif

            if (!libraryHandle)
                throw std::runtime_error("Failed to load library: " + std::string(libraryFilePath));

#ifdef _WIN32
            auto loadFunctionAddress = GetProcAddress(libraryHandle, LOAD_FUNCTION_NAME);
#else
            auto loadFunctionAddress = dlsym(libraryHandle, LOAD_FUNCTION_NAME);
#endif
            if (!loadFunctionAddress)
                throw std::runtime_error(
                    "Failed to get load function address: " + std::string(LOAD_FUNCTION_NAME)
                );

            auto loadFunction = reinterpret_cast<LOAD_FUNCTION_SIGNATURE>(loadFunctionAddress);

            if (auto* group = loadFunction(_globalSpecEnvironment)) {
                _loadedLibraries.emplace(libraryFilePath, libraryHandle);
                return group;
            } else {
#ifdef _WIN32
                FreeLibrary(libraryHandle);
#else
                dlclose(libraryHandle);
#endif
                throw std::runtime_error(
                    "Failed to load group from library: " + std::string(libraryFilePath)
                );
            }
        }

        bool unload(std::string_view libraryFilePath) {
            if (auto it = _loadedLibraries.find(libraryFilePath.data());
                it != _loadedLibraries.end()) {
#ifdef _WIN32
                FreeLibrary(it->second);
#else
                dlclose(it->second);
#endif

                _loadedLibraries.erase(it);
                return true;
            }
            return false;
        }

        void unload_all() {
            for (auto& [libraryFilePath, libraryHandle] : _loadedLibraries)
#ifdef _WIN32
                FreeLibrary(libraryHandle);
#else
                dlclose(libraryHandle);
#endif
            _loadedLibraries.clear();
        }
    };
}

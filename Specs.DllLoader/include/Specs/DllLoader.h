#pragma once

#include <Specs/API.h>
#include <Windows.h>
#include <collections.h>

#include <filesystem>
#include <string>
#include <string_view>

namespace SpecsCpp {

    class DllLoader {
        ISpecEnvironment* _globalSpecEnvironment = nullptr;

        using LOAD_FUNCTION_SIGNATURE = ISpecGroup* (*)(ISpecEnvironment*);

        static constexpr auto LOAD_FUNCTION_NAME = "SpecsCpp_Load";

        collections_map<std::string, HMODULE> _loadedDlls;

    public:
        DllLoader(ISpecEnvironment* globalSpecEnvironment)
            : _globalSpecEnvironment(globalSpecEnvironment) {}

        ~DllLoader() { unload_all(); }

        ISpecGroup* load(std::string_view dllFilePath) {
            if (!std::filesystem::exists(dllFilePath))
                throw std::runtime_error("DLL file does not exist: " + std::string(dllFilePath));

            auto dllHandle = LoadLibraryA(dllFilePath.data());
            if (!dllHandle)
                throw std::runtime_error("Failed to load DLL: " + std::string(dllFilePath));

            auto loadFunctionAddress = GetProcAddress(dllHandle, LOAD_FUNCTION_NAME);
            if (!loadFunctionAddress)
                throw std::runtime_error(
                    "Failed to get load function address: " + std::string(LOAD_FUNCTION_NAME)
                );

            auto loadFunction = reinterpret_cast<LOAD_FUNCTION_SIGNATURE>(loadFunctionAddress);

            if (auto* group = loadFunction(_globalSpecEnvironment)) {
                _loadedDlls.emplace(dllFilePath, dllHandle);
                return group;
            } else {
                FreeLibrary(dllHandle);
                throw std::runtime_error(
                    "Failed to load group from DLL: " + std::string(dllFilePath)
                );
            }
        }

        bool unload(std::string_view dllFilePath) {
            if (auto it = _loadedDlls.find(dllFilePath.data()); it != _loadedDlls.end()) {
                FreeLibrary(it->second);
                _loadedDlls.erase(it);
                return true;
            }
            return false;
        }

        void unload_all() {
            for (auto& [dllFilePath, dllHandle] : _loadedDlls) FreeLibrary(dllHandle);
            _loadedDlls.clear();
        }
    };
}

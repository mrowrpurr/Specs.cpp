#pragma once

#include <Specs/API.h>

#include <string>

namespace SpecsCpp {

    class SpecDataValue : public ISpecDataValue {
        std::string       _asString = "";
        std::string       _key;
        SpecDataValueType _type;
        IVoidPointer*     _value          = nullptr;
        void*             _unmanagedValue = nullptr;

    public:
        SpecDataValue(const char* key, SpecDataValueType type, IVoidPointer* value)
            : _key(key), _type(type), _value(value) {}

        SpecDataValue(const char* key, SpecDataValueType type, void* value)
            : _key(key), _type(type), _unmanagedValue(value) {}

        SpecDataValue(const char* key, SpecDataValueType type, bool value)
            : _key(key), _type(type), _value(new VoidPointer<bool>(new bool(value))) {}

        SpecDataValue(const char* key, SpecDataValueType type, int value)
            : _key(key), _type(type), _value(new VoidPointer<int>(new int(value))) {}

        SpecDataValue(const char* key, SpecDataValueType type, unsigned int value)
            : _key(key),
              _type(type),
              _value(new VoidPointer<unsigned int>(new unsigned int(value))) {}

        SpecDataValue(const char* key, SpecDataValueType type, double value)
            : _key(key), _type(type), _value(new VoidPointer<double>(new double(value))) {}

        SpecDataValue(const char* key, SpecDataValueType type, const char* value)
            : _key(key),
              _type(type),
              _value(new VoidPointer<std::string>(new std::string(value))) {}

        ~SpecDataValue() override {
            if (_value) delete _value;
        }

        SpecDataValueType type() const override { return _type; }

        const char* key() const override { return _key.c_str(); }
        void        key(const char* key) override { _key = key; }

        bool bool_value() const override {
            if (_type != SpecDataValueType::Boolean) return false;
            return _value->as<bool>();
        }

        void bool_value(bool value) override {
            _type  = SpecDataValueType::Boolean;
            _value = new VoidPointer<bool>(new bool(value));
        }

        int int_value() const override {
            if (_type != SpecDataValueType::Integer) return 0;
            return _value->as<int>();
        }

        void int_value(int value) override {
            _type  = SpecDataValueType::Integer;
            _value = new VoidPointer<int>(new int(value));
        }

        unsigned int unsigned_int_value() const override {
            if (_type != SpecDataValueType::UnsignedInteger) return 0;
            return _value->as<unsigned int>();
        }

        void unsigned_int_value(unsigned int value) override {
            _type  = SpecDataValueType::UnsignedInteger;
            _value = new VoidPointer<unsigned int>(new unsigned int(value));
        }

        double float_value() const override {
            if (_type != SpecDataValueType::Float) return 0;
            return _value->as<double>();
        }

        void float_value(double value) override {
            _type  = SpecDataValueType::Float;
            _value = new VoidPointer<double>(new double(value));
        }

        const char* string_value() const override {
            if (_type != SpecDataValueType::String) return nullptr;
            // TODO whaaaaa this isn't safe!
            return _value->as<std::string*>()->c_str();
        }

        void string_value(const char* value) override {
            _type  = SpecDataValueType::String;
            _value = new VoidPointer<std::string>(new std::string(value));
        }

        void* pointer_value() const override {
            if (_type != SpecDataValueType::Pointer) return nullptr;
            return _unmanagedValue ? _unmanagedValue : _value->void_ptr();
        }

        void pointer_value(void* value) override {
            _type           = SpecDataValueType::Pointer;
            _unmanagedValue = value;
        }

        void pointer_value(IVoidPointer* value) override {
            _type  = SpecDataValueType::Pointer;
            _value = value;
        }

        bool is_bool() const override { return _type == SpecDataValueType::Boolean; }
        bool is_int() const override { return _type == SpecDataValueType::Integer; }
        bool is_unsigned_int() const override {
            return _type == SpecDataValueType::UnsignedInteger;
        }
        bool is_float() const override { return _type == SpecDataValueType::Float; }
        bool is_string() const override { return _type == SpecDataValueType::String; }
        bool is_pointer() const override { return _type == SpecDataValueType::Pointer; }

        const char* to_string() override {
            switch (_type) {
                case SpecDataValueType::Boolean:
                    _asString = bool_value() ? "true" : "false";
                    break;
                case SpecDataValueType::Integer:
                    _asString = std::to_string(int_value());
                    break;
                case SpecDataValueType::UnsignedInteger:
                    _asString = std::to_string(unsigned_int_value());
                    break;
                case SpecDataValueType::Float:
                    _asString = std::to_string(float_value());
                    break;
                case SpecDataValueType::String:
                    _asString = string_value();
                    break;
                case SpecDataValueType::Pointer:
                    _asString = "(pointer)";
                    break;
            }
            return _asString.c_str();
        }

        static ISpecDataValue* create_bool(const char* key, bool value) {
            return new SpecDataValue(key, SpecDataValueType::Boolean, value);
        }
        static ISpecDataValue* create_int(const char* key, int value) {
            return new SpecDataValue(key, SpecDataValueType::Integer, value);
        }
        static ISpecDataValue* create_unsigned_int(const char* key, unsigned int value) {
            return new SpecDataValue(key, SpecDataValueType::UnsignedInteger, value);
        }
        static ISpecDataValue* create_float(const char* key, double value) {
            return new SpecDataValue(key, SpecDataValueType::Float, value);
        }
        static ISpecDataValue* create_string(const char* key, const char* value) {
            return new SpecDataValue(key, SpecDataValueType::String, value);
        }
        static ISpecDataValue* create_pointer(const char* key, void* value) {
            return new SpecDataValue(key, SpecDataValueType::Pointer, value);
        }
        static ISpecDataValue* create_pointer(const char* key, IVoidPointer* value) {
            return new SpecDataValue(key, SpecDataValueType::Pointer, value);
        }

        static ISpecDataValue* create(const char* key, bool value) {
            return create_bool(key, value);
        }
        static ISpecDataValue* create(const char* key, int value) { return create_int(key, value); }
        static ISpecDataValue* create(const char* key, unsigned int value) {
            return create_unsigned_int(key, value);
        }
        static ISpecDataValue* create(const char* key, double value) {
            return create_float(key, value);
        }
        static ISpecDataValue* create(const char* key, const char* value) {
            return create_string(key, value);
        }
        static ISpecDataValue* create(const char* key, void* value) {
            return create_pointer(key, value);
        }
        static ISpecDataValue* create(const char* key, IVoidPointer* value) {
            return create_pointer(key, value);
        }
    };
}

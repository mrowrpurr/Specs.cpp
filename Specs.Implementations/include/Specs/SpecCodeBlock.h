#pragma once

#include <Specs/API.h>
#include <_Log_.h>

#include <future>
#include <memory>
#include <string>

#include "GlobalSpecEnvironment.h"  // <--- Global is gross, but - better way? Works for now.
#include "SpecDone.h"
#include "SpecRunResult.h"

namespace SpecsCpp {

    class SpecCodeBlock : public ISpecCodeBlock {
        ISpecComponent* _component  = nullptr;
        bool            _async      = false;
        std::uint32_t   _timeout_ms = 0;

        SpecCodeBlockBodyFn* _unmanagedBody = nullptr;

        std::unique_ptr<std::promise<void>> _asyncDonePromise = nullptr;

        std::unique_ptr<IFunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>
            _managedBody = nullptr;

        bool                                _exceptionHandled = false;
        std::unique_ptr<std::exception_ptr> _currentExceptionPtr;
        std::string                         _currentExceptionMessage;

        void mark_async_promise_done() {
            if (_asyncDonePromise) _asyncDonePromise->set_value();
        }

        FunctionPointer<void()> _markAsyncPromiseDoneFn =
            function_pointer(this, &SpecCodeBlock::mark_async_promise_done);

        void store_current_exception_message(
            ILocalSpecExceptionHandler::IExceptionMessage* exceptionMessage
        ) {
            if (_exceptionHandled) return;
            if (exceptionMessage)
                if (auto* message = exceptionMessage->message())
                    _currentExceptionMessage = exceptionMessage->message();
        }

        FunctionPointer<void(ILocalSpecExceptionHandler::IExceptionMessage*)>
            _storeCurrentExceptionMessageFn =
                function_pointer(this, &SpecCodeBlock::store_current_exception_message);

        void foreach_exception_handler(ILocalSpecExceptionHandler* handler) {
            if (_exceptionHandled) return;
            if (handler->handle_exception(
                    _currentExceptionPtr.get(), &_storeCurrentExceptionMessageFn
                ))
                _exceptionHandled = true;
        }

        FunctionPointer<void(ILocalSpecExceptionHandler*)> _forEachExceptionHandlerFn =
            function_pointer(this, &SpecCodeBlock::foreach_exception_handler);

    public:
        SpecCodeBlock(std::unique_ptr<
                      IFunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>
                          managedBody)
            : _managedBody(std::move(managedBody)) {}

        SpecCodeBlock(FunctionPointer<void()> body)
            : _managedBody(
                  std::make_unique<
                      FunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                      [body](
                          ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone
                      ) { body.invoke(); }
                  )
              ) {}

        SpecCodeBlock(FunctionPointer<void(SpecDone)> body)
            : _managedBody(
                  std::make_unique<
                      FunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                      [body](
                          ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone
                      ) { body.invoke(SpecDone{asyncDone}); }
                  )
              ) {
            mark_async();
        }

        SpecCodeBlock(FunctionPointer<void(ISpec*)> body)
            : _managedBody(
                  std::make_unique<
                      FunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                      [body](
                          ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone
                      ) { body.invoke(spec); }
                  )
              ) {}

        SpecCodeBlock(FunctionPointer<void(ISpecGroup*)> body)
            : _managedBody(std::make_unique<FunctionPointer<
                               void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                  [body](ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone) {
                      // If 'self' is a group, invoke the body with it, otherwise invoke with the
                      // group() of self, if any
                      if (auto* group = dynamic_cast<ISpecGroup*>(self)) body.invoke(group);
                      else if (auto* group = self->group()) _Log_("AFTER");
                      ;
                  }
              )) {}

        SpecCodeBlock(FunctionPointer<void(ISpecGroup*, SpecDone)> body)
            : _managedBody(
                  std::make_unique<
                      FunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                      [body](
                          ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone
                      ) { body.invoke(self->group(), SpecDone{asyncDone}); }
                  )
              ) {
            mark_async();
        }

        SpecCodeBlock(FunctionPointer<void(ISpec*, SpecDone)> body)
            : _managedBody(
                  std::make_unique<
                      FunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                      [body](
                          ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone
                      ) { body.invoke(spec, SpecDone{asyncDone}); }
                  )
              ) {
            mark_async();
        }

        SpecCodeBlock(FunctionPointer<void(ISpecComponent*, ISpec*)> body)
            : _managedBody(
                  std::make_unique<
                      FunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                      [body](
                          ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone
                      ) { body.invoke(self, spec); }
                  )
              ) {}

        SpecCodeBlock(FunctionPointer<void(ISpecGroup*, ISpec*)> body)
            : _managedBody(
                  std::make_unique<
                      FunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                      [body](
                          ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone
                      ) { body.invoke(self->group(), spec); }
                  )
              ) {}

        SpecCodeBlock(FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*)> body)
            : _managedBody(
                  std::make_unique<
                      FunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                      [body](
                          ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone
                      ) { body.invoke(self->group(), self, spec); }
                  )
              ) {}

        SpecCodeBlock(FunctionPointer<void(ISpecGroup*, ISpec*, SpecDone)> body)
            : _managedBody(
                  std::make_unique<
                      FunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                      [body](
                          ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone
                      ) { body.invoke(self->group(), spec, SpecDone{asyncDone}); }
                  )
              ) {
            mark_async();
        }

        SpecCodeBlock(FunctionPointer<void(ISpecComponent*, ISpec*, SpecDone)> body)
            : _managedBody(
                  std::make_unique<
                      FunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                      [body](
                          ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone
                      ) { body.invoke(self, spec, SpecDone{asyncDone}); }
                  )
              ) {
            mark_async();
        }

        SpecCodeBlock(FunctionPointer<void(ISpecGroup*, ISpecComponent*, ISpec*, SpecDone)> body)
            : _managedBody(
                  std::make_unique<
                      FunctionPointer<void(ISpecComponent*, ISpec*, SpecCodeBlockAsyncDoneFn*)>>(
                      [body](
                          ISpecComponent* self, ISpec* spec, SpecCodeBlockAsyncDoneFn* asyncDone
                      ) { body.invoke(self->group(), self, spec, SpecDone{asyncDone}); }
                  )
              ) {
            mark_async();
        }

        bool is_async() const override { return _async; }
        void mark_async(bool async = true) override { _async = async; }

        std::uint32_t get_timeout_ms() const override { return _timeout_ms; }
        void set_timeout_ms(std::uint32_t timeout_ms) override { _timeout_ms = timeout_ms; }

        SpecCodeBlockBodyFn* body() const override {
            return _unmanagedBody ? _unmanagedBody : _managedBody.get();
        }

        void set_body(SpecCodeBlockBodyFn* body) override { _unmanagedBody = body; }

        void run(ISpecComponent* self, ISpec* spec, ISpecRunResultCallbackFn* resultCallback)
            override {
            try {
                if (is_async()) {
                    _asyncDonePromise = std::make_unique<std::promise<void>>();
                    body()->invoke(self, spec, &_markAsyncPromiseDoneFn);

                    auto asyncDoneFuture = _asyncDonePromise->get_future();
                    if (get_timeout_ms() > 0) {
                        if (asyncDoneFuture.wait_for(std::chrono::milliseconds(get_timeout_ms())) ==
                            std::future_status::timeout) {
                            if (resultCallback) {
                                auto result = SpecRunResult::timeout(self, spec);
                                resultCallback->invoke(result.get());
                                return;
                            } else {
                                _Log_("Code block timed out");
                            }
                        }
                    }

                    asyncDoneFuture.get();

                } else {
                    body()->invoke(self, spec, nullptr);
                }

                if (!resultCallback) return;
                auto result = SpecRunResult::passed(self, spec);
                resultCallback->invoke(result.get());
            } catch (...) {
                _exceptionHandled = false;

                // ...
                if (_asyncDonePromise) _asyncDonePromise->set_exception(std::current_exception());

                if (auto* currentlyRunningSpecEnvironment = global_spec_environment().get()) {
                    if (auto* exceptionHandlers =
                            currentlyRunningSpecEnvironment->local_exception_handlers()) {
                        _currentExceptionMessage.clear();
                        _currentExceptionPtr =
                            std::make_unique<std::exception_ptr>(std::current_exception());
                        exceptionHandlers->foreach_exception_handler(&_forEachExceptionHandlerFn);
                        if (_exceptionHandled) {
                            if (resultCallback) {
                                auto result = SpecRunResult::failed(
                                    self, spec, _currentExceptionMessage.c_str()
                                );
                                resultCallback->invoke(result.get());
                            } else {
                                _Log_("Code block error: {}", _currentExceptionMessage);
                            }
                        } else {
                            if (resultCallback) {
                                auto result =
                                    SpecRunResult::failed(self, spec, "Unknown exception");
                                resultCallback->invoke(result.get());

                            } else {
                                _Log_("Code block error: Unhandled exception");
                            }
                        }
                    } else {
                        _Log_("No exception handlers registered");
                    }
                } else {
                    _Log_("No currently running spec environment");
                }
            }
        }
    };
}

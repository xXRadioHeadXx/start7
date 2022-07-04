#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "../src/template/SingletonTemplate.h"
#include "../src/template/AfterConstructInitialization.h"
#include "../src/ctpl/ctpl_stl.h"


class ThreadPool : public ctpl::thread_pool, public AfterConstructInitialization, public SingletonTemplate<ThreadPool>
{
    void afterConstructInitializationImpl() override {
        this->resize(std::thread::hardware_concurrency());
    };
public:
};

#endif // THREADPOOL_H

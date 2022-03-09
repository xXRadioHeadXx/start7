#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "template/SingletonTemplate.h"
#include "template/AfterConstructInitialization.h"
#include "ctpl_stl.h"


class ThreadPool : public ctpl::thread_pool, public AfterConstructInitialization, public SingletonTemplate<ThreadPool>
{
    void afterConstructInitializationImpl() override {
        this->resize(std::thread::hardware_concurrency());
    };
public:
};

#endif // THREADPOOL_H

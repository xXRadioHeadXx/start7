//
// Created by gavrilin on 04.06.2021.
//


#ifndef SINGLETONTEMPLATE_H
#define SINGLETONTEMPLATE_H
//#include <QDebug>

#include "AfterConstructInitialization.h"

template<typename T>
class SingletonTemplate {
public:
    static T& instance(){
        static T instance;
        const auto& iAfterConstructInitialization = dynamic_cast<AfterConstructInitialization *>(&instance);
        if (nullptr != iAfterConstructInitialization)
        {
            iAfterConstructInitialization->afterConstructInitialization();
        }
        return instance;
    }

    SingletonTemplate(const SingletonTemplate&) = delete;
    SingletonTemplate(SingletonTemplate&&) = delete;
    SingletonTemplate & operator=(const SingletonTemplate&) = delete;
    SingletonTemplate& operator=(SingletonTemplate&&) = delete;

    virtual ~SingletonTemplate() {}

protected:
    SingletonTemplate() {}
};
#endif //SINGLETONTEMPLATE_H

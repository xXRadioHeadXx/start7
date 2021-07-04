//
// Created by gavrilin on 04.06.2021.
//

#ifndef ABONENT_SIMULATOR_SINGLETONTEMPLATE_H
#define ABONENT_SIMULATOR_SINGLETONTEMPLATE_H
template<typename T>
class SingletonTemplate {
public:
    static T& instance(){
        static T instance;
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
#endif //ABONENT_SIMULATOR_SINGLETONTEMPLATE_H

#ifndef AFTERCONSTRUCTINITIALIZATION_H
#define AFTERCONSTRUCTINITIALIZATION_H


class AfterConstructInitialization
{
    bool wasAfterConstructInitialization = false;

    virtual void afterConstructInitializationImpl() = 0;
public:
    AfterConstructInitialization() {};

    void afterConstructInitialization() {
        if(!wasAfterConstructInitialization) {
            wasAfterConstructInitialization = true;
            afterConstructInitializationImpl();
        }
    }

};

#endif // AFTERCONSTRUCTINITIALIZATION_H

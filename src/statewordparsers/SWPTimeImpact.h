#ifndef SWPTIMEIMPACT_H
#define SWPTIMEIMPACT_H

template <typename T>
class SWPTimeImpact {
public:
    virtual ~SWPTimeImpact() {}
    virtual T timeImpact() const = 0;
};

#endif // SWPTIMEIMPACT_H

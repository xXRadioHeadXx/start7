#ifndef SSOI_MANAGER_H
#define SSOI_MANAGER_H


struct SSOI_PORT
{
int SsoiM_PortNum;
int SsoiM_Interval;
int SsoiM_Interval_;
int SsoiM_MaxErrCnt;


public:
int getSsoiM_PortNum() const;
void setSsoiM_PortNum(int value);
int getSsoiM_Interval() const;
void setSsoiM_Interval(int value);
int getSsoiM_MaxErrCnt() const;
void setSsoiM_MaxErrCnt(int value);
int getSsoiM_Interval_() const;
void setSsoiM_Interval_(int value);
};

class SSOI_manager
{
private:

    int Version;

    SSOI_PORT SSOI_PORTS[4];



int SsoiAutoDkUse;
int SsoiMOprosVariant;
int SsoiFixNewWarning;
int SsoiM_PortSpeed;

public:
    SSOI_manager();




    int getSsoiAutoDkUse() const;
    void setSsoiAutoDkUse(int value);
    int getSsoiMOprosVariant() const;
    void setSsoiMOprosVariant(int value);
    int getSsoiFixNewWarning() const;
    void setSsoiFixNewWarning(int value);
    int getSsoiM_PortSpeed() const;
    void setSsoiM_PortSpeed(int value);

    int getSsoiM_PortNum(int SSOI_PORT) const;
    void setSsoiM_PortNum(int SSOI_PORT,int value);
    int getSsoiM_Interval(int SSOI_PORT) const;
    void setSsoiM_Interval(int SSOI_PORT,int value);
    int getSsoiM_MaxErrCnt(int SSOI_PORT) const;
    void setSsoiM_MaxErrCnt(int SSOI_PORT,int value);
    int getSsoiM_Interval_(int SSOI_PORT) const;
    void setSsoiM_Interval_(int SSOI_PORT,int value);

    void show();
};




#endif // SSOI_MANAGER_H

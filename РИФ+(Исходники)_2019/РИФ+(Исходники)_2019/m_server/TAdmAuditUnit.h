#ifndef TAdmAuditUnitH
#define TAdmAuditUnitH
class TAdmAudit
{
public:
   double Version;           
   TDateTime CreateDt;       
   double Crc;               

   bool Load( AnsiString fn );
   bool Save( AnsiString fn );
};
#endif

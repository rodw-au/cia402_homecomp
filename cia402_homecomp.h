// cia402_homecomp.h

//CIA Control Word
typedef union
{
  struct
  {
    unsigned char SwitchOn        : 1;  // 00
    unsigned char EnableVoltage   : 1;  // 01
    unsigned char QuickStop       : 1;  // 02
    unsigned char EnableOperation : 1;  // 03
    unsigned char StartHome       : 1;  // 04 not used in CSP or homing
    unsigned char bit5            : 1;  // 05 not used in CSP or homing
    unsigned char bit6            : 1;  // 06 not used in CSP or homing
    unsigned char Faultreset      : 1;  // 07
    unsigned char Timeout         : 1;  // 08
    unsigned char bit9            : 1;  // 09 not used in any mode
    unsigned char keep            : 6;  // 10-15 not used in any mode
  }b;
    unsigned int Word;
}Control_t;

//CIA Status Word
typedef union
{
  struct
  {
    unsigned char ReadyToSwitchOn  : 1;  // 00
    unsigned char SwitchOn         : 1;  // 01
    unsigned char OperationEnabled : 1;  // 02
    unsigned char Fault            : 1;  // 03
    unsigned char VoltageEnabled   : 1;  // 04
    unsigned char QuickStop        : 1;  // 05
    unsigned char SwitchOnDisabled : 1;  // 06
    unsigned char Warning          : 1;  // 07
    unsigned char keep1            : 1;  // 08
    unsigned char Remote           : 1;  // 09
    unsigned char TargetReached    : 1;  // 10
    unsigned char bit11            : 1;  // 11
    unsigned char bit12            : 1;  // 12
    unsigned char keep2            : 3;  // 13-15
  }b;
    hal_u32_t Word;
}Status_t;

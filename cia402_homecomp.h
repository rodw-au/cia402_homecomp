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

typedef struct {
  bool request_custom_homing;
  bool is_custom_homing;
  bool custom_homing_finished;
  // CIA402 pins
  unsigned statusword;       // IN  - Drives CiA402 Statusword, index 0x6041
  signed opmode_display;      // IN  - Drives Modes of Operation feedback register, index 0x6061
  signed drv_actual_position; // IN  - Drives actual Position, index 0x6064
  signed drv_actual_velocity; // IN  - Drives actual Velocity, index 0x606C 
  hal_u32_t controlword;      // OUT - Drives CIA402 Controlword, index 0x6040
  signed opmode;              // OUT - Drives Modes of Operation Input, index 0x6060
  signed drv_target_position; // OUT - Position command to the drive, index 0x607A
  signed drv_target_velocity; // OUT - Velocity command to the drive, index 0x60FF  
  //Homing IOs
  hal_bit_t cia_home;         // IO  - true starts the Drives internal home procedure
  hal_bit_t stat_homed;  	  // OUT - true indicates that the Drive is internaly homed
  hal_bit_t stat_homing; 	  // OUT - true indicates that the Drives homing procedure is running
  hal_bit_t enable;     		// IN - true enables the Drive
  float pos_cmd;  			// IN - target Position, from Motion or PID
  float velocity_cmd;         // IN - target Velocity, from Motion or PID
  float pos_fb;               // OUT - Position feedback, scaled
  float velocity_fb;          // OUT - Velocity feedback scaled
  hal_bit_t drv_fault;        // OUT - true indicates an Drive Error
  Status_t     Status;  	  // IN  - CIA Status Word with bitmap (not a pin)
  Control_t    Control; 	  // OUT - CIA Control Word with bitmap (not a pin)   
} custom_home_local_data;

// data for per-joint custom-homing-specific hal pins:
typedef struct {
  hal_bit_t *request_custom_homing;   // output requests homing (connect to cia402.n.home)
  hal_bit_t *is_custom_homing;        // input verifies custom homing (connect to cia402.n.stat_homing)
  hal_bit_t *custom_homing_finished;  // input from servo drive after homing (connect to cia402.n.stat_homed)
  hal_u32_t *statusword;       // IN  - Drives CiA402 Statusword, index 0x6041
  signed *opmode_display;      // IN  - Drives Modes of Operation feedback register, index 0x6061
  signed *drv_actual_position; // IN  - Drives actual Position, index 0x6064
  signed *drv_actual_velocity; // IN  - Drives actual Velocity, index 0x606C 
  unsigned *controlword;       // OUT - Drives CIA402 Controlword, index 0x6040
  signed *opmode;              // OUT - Drives Modes of Operation Input, index 0x6060
  signed *drv_target_position; // OUT - Position command to the drive, index 0x607A
  signed *drv_target_velocity; // OUT - Velocity command to the drive, index 0x60FF
  hal_bit_t *cia_enable;       // IN - true enables the Drive
  float *cia_pos_cmd;  		   // IN - target Position, from Motion or PID
  float *cia_velocity_cmd;     // IN - target Velocity, from Motion or PID
  float *cia_pos_fb;           // OUT - Position feedback, scaled
  float *cia_velocity_fb;      // OUT - Velocity feedback scaled
  hal_bit_t *cia_drv_fault;    // OUT - true indicates an Drive Error   
  //Homing IOs
  hal_bit_t *cia_home;   	   // IO  - true starts the Drives internal home procedure
  hal_bit_t *stat_homed; 	   // OUT - true indicates that the Drive is internaly homed
  hal_bit_t *stat_homing;	   // OUT - true indicates that the Drives homing procedure is running
  // Inluded for compatibility with homing.c
  int pause_timer;
  double       *home_final_vel;       // intfc
  double       *home_search_vel;      // intfc
  double       *home_latch_vel;       // intfc
} custom_one_joint_home_data_t;

typedef struct {
  custom_one_joint_home_data_t custom_jhd[EMCMOT_MAX_JOINTS];
} custom_all_joints_home_data_t;

typedef enum {
    HOME_WAIT      = 0,
    HOME_BEGIN     = 1,
    HOME_INIT      = 2,
    HOME_RUNNING   = 3,
	HOME_FINISH  = 4
} custom_home_state_t;

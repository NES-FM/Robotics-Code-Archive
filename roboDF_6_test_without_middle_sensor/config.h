//Light Calibration
#define CalLeft ((559 + 526) / 2 - 5) //547
#define CalMid ((452 + 489) / 2 - 5) //559
#define CalRight ((550 + 526) / 2 - 5) //550
//-----------------

//----Mux Ports 0-3
#define template1 0
#define template2 1
#define template3 2
#define template4 3
//-----------------

//--Deactivatet Mux
#define Touch 4
//-----------------

//--Light Ports 0-2
#define left 0
#define mid 1
#define right 2
//-----------------

//-----Motor Speeds
/*
#define ff 24
#define bf -26
*/
/*
#define ff 35
#define bf -26
*/
int ff = 40;
int bf = -20;
#define fm 25
#define bm -10
#define fs 30
#define bs 10
#define drive 28

#define obs_l 15
#define obs_r 50
//-----------------

//----------Arduino
#define arduino_delay 1
//-----------------

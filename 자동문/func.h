#ifndef __FUNC_H__
#define __FUNC_H__

void ActionMotor(int angle);
void ActionSpeed(int aspd);

int AscToInt();
int AscToHex();

void SetPosition(int pos);
void SetSpeed(int aspd);

void SendDeg_ToPc();
void SendSpeed_ToPc();

char GetHex(int in, int pos);
unsigned char GetCheckSum(char * inst, int len);

void init();

extern volatile int head;
extern volatile char Input[3];

extern char Move[9];
extern char Speed[9];

#endif	/* __FUNC_H__ */

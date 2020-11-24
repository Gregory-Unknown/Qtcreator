#ifndef UDPSTRUCT_H
#define UDPSTRUCT_H
#include <QString>
enum DBQuery {INIT_DB = 0x0000, GET_NEXT_TASK = 0x0001, ADD_NEW_TASK = 0x0002, ADD_USER = 0x0003, GET_NEXT_USER = 0x0004,
            AUTORIZATION = 0x0005, ADMIN_MODE = 0x0006, USER_MODE = 0x0007, UPDATE_TASK = 0x0008, USER_TASK_NEXT = 0x0009,
            UPDATE_USER_TASK = 0x000A, UPDATE_REPORT = 0x000B, READ_TASK = 0x000C};
struct UDPTask
{
   union{
       struct {
           DBQuery taskUDP;
           unsigned int amountTask;
           bool correctTask;
           unsigned int progress;
           unsigned int idtask;
           unsigned pos;

           char task[1024];
           char describe[8192];
           char adminpass[128];
           char pass[128];
           char s_data[16];
           char e_data[16];
           char fio[64];
           char login[64];
           char usertask[4096];
           char userreport[4096];
       }udp;
       char bytes[sizeof udp];
   };
   UDPTask()
   {
       memset(bytes, 0, sizeof bytes);
   }
};
#endif // UDPSTRUCT_H

/*
tao bang lenh gom co: ten lenh, dia chi ham thuc thi, info
viet ham cmd_line_parser de tach cmd, thuc hien lenh tuong ung voi cmd
*/
#include<stdint.h>
#include<string.h>
#define MAX_SIZE_OF_CMD 20

typedef void (*fp_cmd)(uint8_t* argv);

typedef struct{
    const int8_t* command;
    fp_cmd cmd_func;
    const int8_t* info;
}cmd_line_table;
typedef enum{
    CMD_NOT_FOUND,
    CMD_TABLE_NOT_FOUND,
    CMD_SUCCESS,
    CMD_TOO_LONG,
} cmd_status;
cmd_status cmd_line_parser(int8_t* command, cmd_line_table *cmd_table){
    char command_tempt[MAX_SIZE_OF_CMD];
    int8_t *p_cmd=command;
    int8_t i=0;
    int8_t cmd_table_i=0;
    if(cmd_table==NULL){
        return CMD_TABLE_NOT_FOUND;
    }
    else{//get cmd
        while(*p_cmd!=' '&&*p_cmd!='\n'){
            command_tempt[i]=*(char*)p_cmd;
            p_cmd++;
            i++;
        }
        command_tempt[i]='\0';
        while(cmd_table[cmd_table_i].command!=0){
            if(strcmp((char*)cmd_table[cmd_table_i].command,(char*)command_tempt)==0){
                cmd_table[cmd_table_i].cmd_func(command);
                return CMD_SUCCESS;
            }
            else if(cmd_table[cmd_table_i].command==0){
                return CMD_NOT_FOUND;
            }
            else if(cmd_table_i>=MAX_SIZE_OF_CMD){
                return CMD_TOO_LONG;
            }
            cmd_table_i++;
        }
    }
    return CMD_TABLE_NOT_FOUND;
}

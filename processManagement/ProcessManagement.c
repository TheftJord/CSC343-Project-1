/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include "processManagement.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int processTimerInterrupt(processStructure* ps) {
    int current=ps->runningProcess;
    int next=(current+1)%PROCESS_MAX;
    bool runnableProcessFound=false;
    int originalNext=next;
    do{
        if(ps->processes[next].state==READY||ps->processes[next].state==BLOCKED){
            runnableProcessFound=true;
            break;
        }
        next=(next+1)%PROCESS_MAX;
    }while(next!=originalNext);
    if(runnableProcessFound){
        ps->runningProcess=next;
        ps->processes[current].state=BLOCKED;
        ps->processes[next].state=RUNNING;
        return next;
    }
    else{
        return current;
    }
}
void processScheduleInitialize(processStructure* ps)  {
    ps->processCount=0;
    ps->runningProcess=-1;
    for(int i=0;i<PROCESS_MAX;i++){
        ps->processes[i].pid=0;
        ps->processes[i].state=UNUSED;
    }
}
int processAdd(processStructure*ps, int parent){
    if(ps->processCount>=PROCESS_MAX){
        return 0;
    }
    else if(ps->processCount==0){
        ps->processes[0].pid=0;
        ps->processes[0].parent=parent;
        ps->processes[0].state=RUNNING;
        ps->processCount=1;
        ps->runningProcess=0;
        return 0;
    }
    else{
        for(int i=0;i<ps->processCount+1;i++){
            if(ps->processes[i].state==UNUSED){
                ps->processes[i].pid=i;
                ps->processes[i].parent=parent;
                ps->processes[i].state=EMBRYO;
                ps->processCount=i+1;
                if(ps->runningProcess==-1){
                    ps->runningProcess=i;
                    ps->processes[i].state=RUNNING;
                }
                else{
                    ps->processes[i].state=RUNNABLE;
                }
                return i;
            }
        }
    }
}
int processGetRunningPID(processStructure* ps){
    return ps->runningProcess;
}
int processIORequest(processStructure* ps){
    processStructure* processSystem=(processStructure*)ps;
    int currentProcessID=processGetRunningPID(ps);
    int waitingProcessID=-1;
    if(currentProcessID!=-1){
        for(int i=0;i<processSystem->processCount;i++){
            if(processSystem->processes[i].pid==currentProcessID){
                processSystem->processes[i].state=READY;
                fprintf(stdout,"%d is now READY",processSystem->processes[i].pid);
                break;
            }
        }
    }
    for(int i=0;i<processSystem->processCount;i++){
        if(processSystem->processes[i].state==BLOCKED){
            waitingProcessID=1;
            break;
        }
    }
    if(waitingProcessID!=-1){
        ps->runningProcess=waitingProcessID;
        ps->processes[waitingProcessID].state=RUNNING;
    }
    else{
        int nextProcessID=processTimerInterrupt(ps);
        if(nextProcessID!=-1){
            ps->processes[ps->runningProcess].state=BLOCKED;
        }
    }
    return 0;
}
int processIODone(processStructure* ps, int processID){
    if(processID>=0&&processID<PROCESS_MAX&&ps->processes[processID].state==BLOCKED){
        ps->processes[processID].state=READY;
    }
    return -1;
}
int processWaitFor(processStructure* ps, int processID){
    if(ps->runningProcess!=-1){
        if(processID>=0&&processID<PROCESS_MAX&&ps->processes[processID].state!=UNUSED){
            ps->processes[ps->runningProcess].state=BLOCKED;
            processTimerInterrupt(ps);
            return 0;
        }
    }
    return -1;
}
int processExit(processStructure* ps, int processID) {
    if(processID>=0&&processID<PROCESS_MAX){
        ps->processes[processID].state=ZOMBIE;
        if(ps->runningProcess==processID){
            processTimerInterrupt(ps);
        }
        return 0;
    }
    return -1;
}
processState getProcessStatus(processStructure* ps, int processID) {
    fprintf(stdout,"\n number: %d",processID);
    return ps->processes[processID].state;
}

/* Copyright (C) 
* 2021 - doitnowman
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
* 
*/
#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <unistd.h>
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/wait.h>
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <iostream>
#include <sstream>
#include <time.h>

#define SEMA_NAME "pSem"

class SemaPhore
{
private:
    sem_t *sem = nullptr;         /*      synch semaphore         */
    unsigned int value = 1;       /*      semaphore value         */
    struct timespec tm;           /*      semaphore timeout       */
    time_t timeout;               /*      timeout value           */
    std::string sema_name;

public:
    SemaPhore(time_t timeout_ = 60)
        :timeout(timeout_)
    {
#ifdef __WIN32__
#else
        extern char* __progname;
        sema_name = __progname;
#endif
        if(false == CheckProcessDuplication(sema_name)) {
            /* unlink prevents the semaphore existing forever */
            sem_unlink(sema_name.c_str());
            sem = sem_open(sema_name.c_str(), O_CREAT, 0644, value); 
        } else {
            /* initialize semaphores for shared processes */
            sem = sem_open(sema_name.c_str(), O_EXCL, 0644, value); 
        }
    }

    ~SemaPhore() = default;

    bool CheckProcessDuplication(std::string program)
    {
        FILE *fp = nullptr;
        std::string pid;
        char cpid[64] = {0, };
        uint32_t run_cnt = 0;

        std::ostringstream oss;
#ifdef __WIN32__
#else
        oss << "ps -ef | grep " << program << " | grep -v grep | awk -F' ' '{print $2}'";
        if (nullptr != (fp = popen(oss.str().c_str(), "r"))) {
            while(fgets(cpid , 64, fp)) {
                run_cnt++;
            }
            pclose(fp);
        }

        return (run_cnt >= 2);
#endif
    }
    bool Lock() 
    {
        if (sem) {
            /* P operation */
            clock_gettime(CLOCK_REALTIME, &tm);
            tm.tv_sec += timeout;

            if (!sem_timedwait(sem, &tm)) {
                return true;
            }
        }
        return false; 
    }

    bool Unlock()
    {
        if (sem) {
            /* V operation */
            if (!sem_post(sem)) {
                return true;
            }
        }
        return false;
    }
};

int main(int argc, char* argv[]) 
{
    SemaPhore sema;
    while(1) {
        if (true == sema.Lock()) {
            std::cout << " in critical section" << std::endl;
            sleep (5);
            sema.Unlock();
        }
        std::cout << " after critical section" << std::endl;
        sleep (1);
    }

}
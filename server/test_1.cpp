#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <sys/timerfd.h>

static timer_t tid;
static timer_t tid2;
struct sigaction sigact;
struct sigaction sa;
time_t curr;
void SignalHandler(int);
void SignalHandler1(int);
timer_t SetTimer(int, int);

void init(struct sigaction,int);

int main(int argc, char *argv[]) {

    int key = 1;
    init(sigact,key);    

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SignalHandler1;
    // set up sigaction to catch signal
    if (sigaction(2, &sa, NULL) == -1) {
        perror("sa failed");
        exit( EXIT_FAILURE );
    }


    // Establish a handler to catch CTRL+c and use it for exiting.
   // sigaction(SIGINT, &sigact, NULL);
    tid=SetTimer(key, 20);
    curr = time(NULL);    
    // Establish a handler to catch CTRL+c and use it for exiting.   // sigaction(SIGINT, &sa, NULL);
    tid2 = SetTimer(2,10);
    
    for(;;);
    return 0;
}

void init(struct sigaction timeup, int key)
{
    sigemptyset(&timeup.sa_mask);
    timeup.sa_handler = SignalHandler;
    // set up sigaction to catch signal
    if (sigaction(key, &timeup, NULL) == -1) {
        perror("sigaction failed");
        exit( EXIT_FAILURE );
    }
}

void SignalHandler(int signo)
{
        double diff = difftime(time(NULL),curr);
	printf("Command Caller has ticked. Time elapsed = %.f\n",diff);
	
	//if (signo == SIGINT) {
        //	perror("Crtl+c cached!");
        //	exit(1);  // exit if CRTL/C is issued
    	//}
}

void SignalHandler1(int signo)
{
    printf("Data Caller has ticked\n");
    //if (signo == SIGINT) {
    //    perror("Crtl+c cached!");
    //    exit(1);  // exit if CRTL/C is issued
    //}
}

timer_t SetTimer(int signo, int sec)
{
    static struct sigevent sigev;
    static timer_t tid;
    static struct itimerspec itval;
    static struct itimerspec oitval;

    // Create the POSIX timer to generate signo
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = signo;
    sigev.sigev_value.sival_ptr = &tid;

    if (timer_create(CLOCK_REALTIME, &sigev, &tid) == 0) {
        itval.it_value.tv_sec = sec;
        itval.it_value.tv_nsec = 0;

        itval.it_interval.tv_sec = 0;
        itval.it_interval.tv_nsec = 0;

        if (timer_settime(tid, 0, &itval, &oitval) != 0) {
            perror("time_settime error!");
        }
    }
    else {
        perror("timer_create error!");
        return NULL;
    }
    return tid;
}

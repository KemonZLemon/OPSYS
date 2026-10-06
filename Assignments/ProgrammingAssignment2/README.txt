Programming Assignment 2: Multi-Core Lottery Scheduler

Build and run
-------------
Run these commands on the course Linux VM with kernel headers matching the
running kernel. The scheduler is a kernel module, so it should be tested in
the VM rather than on a regular workstation.

    cd ProgrammingAssignment2
    sudo bash run_lottery.sh

The script builds lottery.ko and the app, loads the module, launches the
20-worker experiment, collects the status and migration logs, and unloads
the module. Save the complete output below after running it.

Test results
------------
Tested on kevin-VMware-Virtual-Platform, Linux kernel 7.0.0-test, with 8
online CPUs, using:

    sudo bash run_lottery.sh

The module and user application built successfully, loaded, completed the
20-process Lucas(47) workload, and unloaded. The build printed clock-skew
warnings for generated files on the shared folder, but completed successfully.

Total steady-state execution time reported by the script: 44.434 seconds.
The script starts this timer after its 3-second registration settling period,
so it can be shorter than the longest individual worker time.

Worker completion times from this run (seconds):

    200 tickets: 15.13
    150 tickets: 14.69, 17.84
    100 tickets: 15.14, 22.68
     60 tickets: 23.23, 23.25, 25.34, 26.49, 27.27
     30 tickets: 27.82, 29.06, 30.09, 30.65, 32.77
     10 tickets: 35.50, 37.07, 38.21, 45.87, 47.59

The results show an overall ticket-weight trend: the 10-ticket workers were
slowest, while the 150- and 200-ticket workers were among the fastest. Some
overlap between neighboring weights occurred, as expected with randomized
scheduling. The kernel log contained queue status snapshots for CPUs 0-7
and 11 load-balancer migration events. Queue totals changed as workers
completed and unregistered.

Migration events reported by the harness:

    PID 6064 (30 tickets): CPU 5 -> CPU 1
    PID 6076 (60 tickets): CPU 6 -> CPU 4
    PID 6052 (10 tickets): CPU 2 -> CPU 7
    PID 6054 (10 tickets): CPU 5 -> CPU 7
    PID 6068 (30 tickets): CPU 2 -> CPU 7
    PID 6062 (30 tickets): CPU 3 -> CPU 5
    PID 6072 (60 tickets): CPU 2 -> CPU 6
    PID 6050 (10 tickets): CPU 0 -> CPU 1
    PID 6056 (10 tickets): CPU 3 -> CPU 5
    PID 6070 (30 tickets): CPU 3 -> CPU 4
    PID 6059 (10 tickets): CPU 6 -> CPU 3

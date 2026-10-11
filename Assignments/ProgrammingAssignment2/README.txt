=========================================
 Starting Multi-Core Experiment (20 Tasks)
 Target: lucas(47) across 20 processes
 Ticket Distribution: 10 to 200 tickets
=========================================

Spawning 20 processes...
  [Process 01] PID: 6050 | Tickets: 10
  [Process 02] PID: 6052 | Tickets: 10
  [Process 03] PID: 6054 | Tickets: 10
  [Process 04] PID: 6056 | Tickets: 10
  [Process 05] PID: 6059 | Tickets: 10
  [Process 06] PID: 6062 | Tickets: 30
  [Process 07] PID: 6064 | Tickets: 30
  [Process 08] PID: 6066 | Tickets: 30
  [Process 09] PID: 6068 | Tickets: 30
  [Process 10] PID: 6070 | Tickets: 30
  [Process 11] PID: 6072 | Tickets: 60
  [Process 12] PID: 6076 | Tickets: 60
  [Process 13] PID: 6078 | Tickets: 60
  [Process 14] PID: 6080 | Tickets: 60
  [Process 15] PID: 6082 | Tickets: 60
  [Process 16] PID: 6084 | Tickets: 100
  [Process 17] PID: 6086 | Tickets: 100
  [Process 18] PID: 6088 | Tickets: 150
  [Process 19] PID: 6090 | Tickets: 150
  [Process 20] PID: 6092 | Tickets: 200

All 20 processes launched.
Waiting 3 seconds for initial process registration to settle...
--------------------------------------------------------
Capturing Steady-State Load Balancing Metrics...
--------------------------------------------------------
pid 6090, with 150 tickets: computing lucas(47) took 14.69 seconds.
pid 6092, with 200 tickets: computing lucas(47) took 15.13 seconds.
pid 6084, with 100 tickets: computing lucas(47) took 15.14 seconds.
pid 6088, with 150 tickets: computing lucas(47) took 17.84 seconds.
pid 6086, with 100 tickets: computing lucas(47) took 22.68 seconds.
pid 6076, with 60 tickets: computing lucas(47) took 23.23 seconds.
pid 6080, with 60 tickets: computing lucas(47) took 23.25 seconds.
pid 6078, with 60 tickets: computing lucas(47) took 25.34 seconds.
pid 6082, with 60 tickets: computing lucas(47) took 26.49 seconds.
pid 6072, with 60 tickets: computing lucas(47) took 27.27 seconds.
pid 6064, with 30 tickets: computing lucas(47) took 27.82 seconds.
pid 6062, with 30 tickets: computing lucas(47) took 29.06 seconds.
pid 6066, with 30 tickets: computing lucas(47) took 30.09 seconds.
pid 6070, with 30 tickets: computing lucas(47) took 30.65 seconds.
pid 6068, with 30 tickets: computing lucas(47) took 32.77 seconds.
pid 6059, with 10 tickets: computing lucas(47) took 35.50 seconds.
pid 6050, with 10 tickets: computing lucas(47) took 37.07 seconds.
pid 6056, with 10 tickets: computing lucas(47) took 38.21 seconds.
pid 6054, with 10 tickets: computing lucas(47) took 45.87 seconds.
pid 6052, with 10 tickets: computing lucas(47) took 47.59 seconds.

=========================================
 Total Steady-State Execution Time: 44.434159882s
=========================================
=========================================
 Steady-State Migration Events
=========================================
[  506.603114] [LOTTERY] Load Balance: Migrated PID 6064 (30 tix) CPU 5 -> CPU 1
[  506.654653] [LOTTERY] Load Balance: Migrated PID 6076 (60 tix) CPU 6 -> CPU 4
[  506.706206] [LOTTERY] Load Balance: Migrated PID 6052 (10 tix) CPU 2 -> CPU 7
[  506.757548] [LOTTERY] Load Balance: Migrated PID 6054 (10 tix) CPU 5 -> CPU 7
[  506.808490] [LOTTERY] Load Balance: Migrated PID 6068 (30 tix) CPU 2 -> CPU 7
[  509.282387] [LOTTERY] Load Balance: Migrated PID 6062 (30 tix) CPU 3 -> CPU 5
[  514.127910] [LOTTERY] Load Balance: Migrated PID 6072 (60 tix) CPU 2 -> CPU 6
[  514.179433] [LOTTERY] Load Balance: Migrated PID 6050 (10 tix) CPU 0 -> CPU 1
[  514.231332] [LOTTERY] Load Balance: Migrated PID 6056 (10 tix) CPU 3 -> CPU 5
[  514.696589] [LOTTERY] Load Balance: Migrated PID 6070 (30 tix) CPU 3 -> CPU 4
[  516.808755] [LOTTERY] Load Balance: Migrated PID 6059 (10 tix) CPU 6 -> CPU 3

Total Steady-State Migrations: 11

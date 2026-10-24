========================================
Cleaning up previous module
========================================

========================================
Building the experiment
========================================
make: Nothing to be done for 'all'.

========================================
Loading kernel module
========================================

========================================
Running readFile
========================================
readFile process started: PID 29673
PID: 29673
Read 4096 bytes
User buffer virtual address: 0x63e54add3000
First 16 bytes: e4 d8 8f 68 5e ea dd 2a f2 78 6f 1a 5b 66 74 21
Waiting for kernel-module test...

========================================
Verifying readFile
========================================
    PID    PPID S COMMAND
  29673   29662 S readFile

readFile PID:     29673
User buffer:      0x63e54add3000

========================================
Running kernel-module test
========================================

========================================
Kernel output
========================================
[ 2065.615168] pagecache_test: file page 0 is not in the page cache
[ 2065.835846] pagecache_test: unloaded
[ 2118.739328] pagecache_test: loaded
[ 2118.739333] Use /proc/pagecache_test to run the experiment
[ 2118.893868] pagecache_test: file page 0 is not in the page cache
[ 2119.114769] pagecache_test: unloaded
[ 2196.394957] pagecache_test: loaded
[ 2196.394962] Use /proc/pagecache_test to run the experiment
[ 2245.093348] pagecache_test: unloaded
[ 2247.123736] pagecache_test: loaded
[ 2247.123744] Use /proc/pagecache_test to run the experiment
[ 2247.169945] ========================================
[ 2247.169950] Page Cache vs User Buffer Experiment
[ 2247.169951] ========================================
[ 2247.169952] PID:              29586
[ 2247.169954] User virtual addr: 0x5ff06d713000
[ 2247.169955] File:             data.bin

[ 2247.169957] USER BUFFER:
[ 2247.169958]   virtual address = 0x5ff06d713000
[ 2247.169959]   PFN              = 1669951
[ 2247.169960]   physical address = 0x197b3f000
[ 2247.169962]   first 16 bytes   = e4 d8 8f 68 5e ea dd 2a f2 78 6f 1a 5b 66 74 21

[ 2247.169978] PAGE CACHE:
[ 2247.169979]   file offset      = 0
[ 2247.169980]   PFN              = 2448126
[ 2247.169981]   physical address = 0x255afe000
[ 2247.169983]   first 16 bytes   = e4 d8 8f 68 5e ea dd 2a f2 78 6f 1a 5b 66 74 21

[ 2247.170371] memcmp(PAGE_SIZE) = 0
[ 2247.170373] ========================================
[ 2247.414507] pagecache_test: unloaded
[ 2321.871291] pagecache_test: loaded
[ 2321.871299] Use /proc/pagecache_test to run the experiment
[ 2321.915924] ========================================
[ 2321.915932] Page Cache vs User Buffer Experiment
[ 2321.915933] ========================================
[ 2321.915935] PID:              29628
[ 2321.915937] User virtual addr: 0x5c9ba05f1000
[ 2321.915939] File:             data.bin

[ 2321.915940] USER BUFFER:
[ 2321.915941]   virtual address = 0x5c9ba05f1000
[ 2321.915943]   PFN              = 2352191
[ 2321.915944]   physical address = 0x23e43f000
[ 2321.915945]   first 16 bytes   = e4 d8 8f 68 5e ea dd 2a f2 78 6f 1a 5b 66 74 21

[ 2321.915961] PAGE CACHE:
[ 2321.915962]   file offset      = 0
[ 2321.915963]   PFN              = 2448126
[ 2321.915965]   physical address = 0x255afe000
[ 2321.915966]   first 16 bytes   = e4 d8 8f 68 5e ea dd 2a f2 78 6f 1a 5b 66 74 21

[ 2321.915983] memcmp(PAGE_SIZE) = 0
[ 2321.915984] ========================================
[ 2322.159363] pagecache_test: unloaded
[ 2407.329376] pagecache_test: loaded
[ 2407.329380] Use /proc/pagecache_test to run the experiment
[ 2407.387036] ========================================
[ 2407.387039] Page Cache vs User Buffer Experiment
[ 2407.387041] ========================================
[ 2407.387042] PID:              29673
[ 2407.387044] User virtual addr: 0x63e54add3000
[ 2407.387046] File:             data.bin

[ 2407.387047] USER BUFFER:
[ 2407.387048]   virtual address = 0x63e54add3000
[ 2407.387050]   PFN              = 1900225
[ 2407.387051]   physical address = 0x1cfec1000
[ 2407.387052]   first 16 bytes   = e4 d8 8f 68 5e ea dd 2a f2 78 6f 1a 5b 66 74 21

[ 2407.387071] PAGE CACHE:
[ 2407.387072]   file offset      = 0
[ 2407.387073]   PFN              = 2448126
[ 2407.387074]   physical address = 0x255afe000
[ 2407.387075]   first 16 bytes   = e4 d8 8f 68 5e ea dd 2a f2 78 6f 1a 5b 66 74 21

[ 2407.387091] memcmp(PAGE_SIZE) = 0
[ 2407.387696] ========================================

========================================
Experiment complete
========================================

========================================
Cleaning up
========================================
Stopping readFile (PID 29673)...
Removing pagecacheTest...

# **Producer-Consumer Problem Solution**
## By, Jason Abounader

**Producer-Consumer Problem written in C.**

Producer generates items and put items onto table. Consumer will pick up items. The table can only hold 2 items at the same time. When the table is full, producer will wait. When there are no items, consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use pthreadsin producer program and consumer program. Shared memory is used for “table”.

**Compiled and executed using GCC Compiler with the following commands:**

gcc producer.c -pthread -o producer -Irt

gcc consumer.c -pthread -o consumer -Irt

./producer & ./consumer & 

**Example Output:**

Producer enters the critical section and places items onto buffer represented as 1's until "full". Producer exits critical section and consumer enters turning 1's into 0's to represent picing up the items until "empty". For demonstration purposes, the procedure iterates 10 times. See the output below for reference as well as the code provided in the repository. 

![image](https://user-images.githubusercontent.com/86804265/139169924-0330ec5a-766e-442d-befe-e2a16cd7d2e2.png)

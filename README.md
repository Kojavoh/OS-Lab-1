# OS Lab 1: The Producer-Consumer Problem
Producer-Consumer assignment for Operating Systems course:
## About <a name = "about"></a>
Producer generates items and put items onto table. Consumer will pick up items. The table can only hold 2 items at the same time. When the table is full, producer will wait. When there are no items, consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use pthreads in producer program and consumer program. Shared memory is used for “table”.

## Getting Started <a name = "getting_started"></a>
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
gcc and pthread library.
Compiled on Ubuntu 22.04.1

Test for gcc version
```
gcc --version
```
Installing gcc if not already installed
```
sudo apt update
sudo apt install build-essential
```
Confirming gcc installation
```
gcc --version
```

### Installing
1. Clone the Repository

```
git clone https://github.com/Kojavoh/OS-Lab-1.git
```
2. Compile and run the program

```
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
./producer & ./consumer &
```
3. Exit the program after receiving results

```
Type ^C or Enter
```

## Usage <a name="usage"></a>
This project is an implementation of a solution to the producer consumer problem using semaphores and shared memory.

### Example Output

![ExampleOutput](https://user-images.githubusercontent.com/90359108/139364242-21476c10-9e37-457a-a6c1-3c1562c1445a.png)

### Special Notes:
Due to the use of rand() designated sleep() duration, output log will vary.  Also, yes, as can be seen in my example output screenshot, the account I used in my VirtualBox VM for this assignment was left as the default "vboxuser".  I didn't want to have to think about unecessary things when I was already stressed as it was.  Additionally, I have come to the conclusion that terminating the processes using ^C introduces unpredictable behavior due to the sem_ and shm_ files not getting closed properly.  If you choose to terminate this program using the ^C hotkey, it is highly recommended that you execute the following lines of code to "clear your cache", so-to-speak, before running the processes again:
```
sudo killall -9 consumer producer
rm /dev/shm/sem.* /dev/shm/table
```

# OS Lab 1: The Producer-Consumer Problem
Producer-Consumer assignment for Operating Systems course:
## About <a name = "about"></a>
The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

## Getting Started <a name = "getting_started"></a>
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
gcc and pthread library.
Compiled in Ubuntu 22.04.1

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
Additionally, <a href="https://github.blog/2020-12-15-token-authentication-requirements-for-git-operations">as of August 13, 2021, password authentication is no longer supported</a>.  This means that you must either <a href="https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token">create a personal access token</a> for use with HTML, use an OAuth or GitHub App installation token, or use an SSH Key.

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
This project is an implementation of a solution to the Producer-Consumer problem using semaphores and shared memory.

### Example Output

![Example Output](https://user-images.githubusercontent.com/114598688/199409155-e43b9155-89ab-4b95-a307-fa93b4e62f05.png)


### Special Notes:
Due to the use of rand()-designated sleep() duration, output log will vary.  Also, yes, as can be seen in my example output screenshot, the account I used in my VirtualBox VM for this assignment was left as the default "vboxuser".  I didn't want to have to think about unecessary things when I was already stressed as it was.  Additionally, I have come to the conclusion that terminating the processes using ^C introduces unpredictable behavior due to the sem_ and shm_ files not getting closed properly.  If you choose to terminate this program using the ^C hotkey, it is highly recommended that you execute the following lines of code to "clear your cache", so-to-speak, before running the processes again:
```
sudo killall -9 consumer producer
rm /dev/shm/sem.* /dev/shm/table
```

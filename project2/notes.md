
Project 2—Linux Kernel Module for Listing Tasks
Only Part I is required. However, for each process, the info of its ancestor process must also be shown. The format is
name, state, pid
parent name, parent state, parent pid
grandparent name, grandparent state, grandparent pid
and so on

Due Feb. 14, 2PM.
Submit at http://hucs.dynu.net/lij/courses/submit_hw.html





# Notes
* Each process is represented in OS by its PCB
* A process not in execution is in waiting queue
* Major Classes of queues:
>    * IO request queues 
	 * Ready queues : all processes that are ready to execute and are waiting for CPU

* Long term scheduling : Selection of processes allowed to contend for CPU (influenced by resource allocation)
* Short term scheduling: selection of process from ready queue

* OS provides mechanism for parent to create child processes
>   Parent may wait for its children to terminate before proceeding or both can execute concurrently (if the process must share information, computation speedup, modularity and conveniece). Coopertating process require an IPC mechanism: Shared Memory(communicting processes must share variables to communicate), Message passing.  
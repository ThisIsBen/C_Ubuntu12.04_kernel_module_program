# C_Ubuntu12.04_kernel_module_program
 Objectives:  
 Writing kernel modules  
 Passing parameters to a kernel module  
 Accessing /proc file  
 Using for_each_process  
 Using task_struct
 
I wrote a pair of programs (a kernel module and a user program)  
-Pass command argument(s) when install kernel module
  For instance,  $sudo insmod hello.ko command="showall"  
-After installing this module, a proc file will be created (you may name the proc file whatever you want)   
-Run user program to read the proc file and print the content in console (content in /proc file depends on the command )  
-showall: list all process id  
-parentchild: Pass a process id as command argument and list its parent and children process name . 
(user has to pass 2 commands, command and process id)  
ex：Query process id=485 parent and children process name
   For instance,  $sudo insmod hello.ko command="parentchild" pid ="485"  


-Environment: Ubuntu 12.04


-How to run this program:
make
sudo insmod klhello.ko command="" pid=""
./a.out

-How to delete module on terminal:
sudo rmmod moduleName

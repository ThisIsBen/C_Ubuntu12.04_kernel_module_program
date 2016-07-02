#include <linux/seq_file.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/init.h>


#include <asm/uaccess.h>
//#include <string.h>

//store parameter :command 
static char *command = "blah";
module_param(command, charp, 0000);
MODULE_PARM_DESC(command, "A character string");

//store parameter :process id.
static int pid ;
module_param(pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(pid, "An integer");



static int hello_proc_execution(struct seq_file *m, void *v) {
 
  //store each pid and processname
  char buf[100];
  
  struct task_struct *task_list ,*child;
  struct list_head *list;
  
   //if command is "parentchild"
  if(strcmp(command,"parentchild")==0 )
  {
    

      //traverse all the processes
      for_each_process(task_list) 
     {
        //stop at the process whose id equals the entered process id.
        if(task_list->pid==pid)
        {
           
                //get parents
                sprintf(buf,"\nProcess with id %d has   parent process: %s, parent process id: %d\n",pid, task_list->parent->comm, task_list->parent->pid);
                
                //This is the printf equivalent for seq_file implementations
                seq_printf(m,buf);//print the found parent process to seq_file.
                memset(buf,0,sizeof(buf));


///////////////////////////////////////////////////////////////////
            //get children
            
           //traverse all the children of the process which is pointed by task_list.
            list_for_each(list, &task_list->children) 
            {
                
              
                child = list_entry(list, struct task_struct, sibling);
                /* child now points to one of task_list's children */
            
                sprintf(buf,"\nProcess with id %d has   child process: %s, child process id: %d\n",pid, child->comm, child->pid);
                
                //This is the printf equivalent for seq_file implementations
                seq_printf(m,buf);//print the found child process to seq_file.
                memset(buf,0,sizeof(buf));
               



            }
            
//////////////////////////////////////////////////////
        }
         
     }



  }
  //if command is "showall"
  if(strcmp(command,"showall")==0)
  {
    //traverse all the processes
    for_each_process(task_list) 
     {

         sprintf(buf, "\n Process name: %s , Process id:%d \n",task_list->comm,task_list->pid);
         seq_printf(m,buf);//print the traversed process to seq_file.
         memset(buf,0,sizeof(buf));
      }
  }
  
  
  return 0;
}

//call hello_proc_execution to deal with showall and parentchild command.
static int hello_proc_open(struct inode *inode, struct  file *file) {
  return single_open(file, hello_proc_execution, NULL);
}

//file operation
static const struct file_operations hello_proc_fops = {
  .owner = THIS_MODULE,
  .open = hello_proc_open,
  .read = seq_read,
  .llseek = seq_lseek,
  .release = single_release,
};

static int __init hello_proc_init(void) {
  //create a file called ps_list under /proc
  proc_create("ps_list", 0, NULL, &hello_proc_fops);
  return 0;
}

static void __exit hello_proc_exit(void) {
  //remove a file called ps_list under /proc
  remove_proc_entry("ps_list", NULL);
}
module_init(hello_proc_init);//call function hello_proc_init when installing module.
module_exit(hello_proc_exit);//call function hello_proc_exit when removing module.










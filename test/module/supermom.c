#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include<linux/syscalls.h>
#include<linux/rcupdate.h>
#include<linux/sched.h>
#include<linux/uidgid.h>
#include<linux/cred.h>
#include<linux/types.h>
#include<asm/uaccess.h>

/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

long supermom(pid_t pid, uid_t *uid)
{
	
	pid_t pid_true;
	rcu_read_lock();
	pid_true = task_tgid_vnr(rcu_dereference(current->real_parent));
	rcu_read_unlock();
	
	uid_t uid_true;
	uid_true = from_kuid_munged(current_user_ns(), current_euid());

	if (pid != pid_true){
		return -EINVAL;
	}

	if (uid != NULL) 
		copy_to_user(uid, &uid_true, sizeof(uid_t));

	if (uid_true == 0)
	{
		return 0;
	} else {
		return -EACCES;
	}
	

}

EXPORT_SYMBOL(supermom);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Supermom");
MODULE_AUTHOR("wp2191");


#include<linux/syscalls.h>
#include<linux/rcupdate.h>
#include<linux/sched.h>
#include<linux/uidgid.h>
#include<linux/cred.h>
#include<linux/types.h>
#include<asm/uaccess.h>
SYSCALL_DEFINE2(supermom, pid_t, pid, uid_t *, uid)
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

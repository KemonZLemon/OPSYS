#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xdc50aae2, "__ref_stack_chk_guard" },
	{ 0x96848186, "scnprintf" },
	{ 0xb19a5453, "__per_cpu_offset" },
	{ 0xc67e1059, "_raw_spin_lock_irqsave" },
	{ 0x52e94aa9, "_raw_spin_unlock_irqrestore" },
	{ 0x017de3d5, "nr_cpu_ids" },
	{ 0x5a5a2271, "__cpu_online_mask" },
	{ 0x53a1e8d9, "_find_next_bit" },
	{ 0x122c3a7e, "_printk" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x87801d9f, "pcpu_alloc_noprof" },
	{ 0x9e683f75, "__cpu_possible_mask" },
	{ 0x27821391, "misc_register" },
	{ 0xc6f178ad, "hrtimer_setup" },
	{ 0xdbfbb9c1, "hrtimer_start_range_ns" },
	{ 0x8554eded, "__num_online_cpus" },
	{ 0xc9ec4e21, "free_percpu" },
	{ 0xb6c4379f, "system_percpu_wq" },
	{ 0xc5b6f236, "queue_work_on" },
	{ 0x315bfc73, "hrtimer_cb_get_time" },
	{ 0x739f986f, "hrtimer_forward" },
	{ 0x42005d30, "misc_deregister" },
	{ 0x81a4ceb2, "mutex_lock" },
	{ 0xeb5546a2, "mutex_unlock" },
	{ 0xd465145b, "hrtimer_cancel" },
	{ 0x03c12dfe, "cancel_work_sync" },
	{ 0x037a0cba, "kfree" },
	{ 0xa670bcc2, "send_sig_info" },
	{ 0x94160518, "__put_task_struct_rcu_cb" },
	{ 0x28aa6a67, "call_rcu" },
	{ 0x950eb34e, "__list_del_entry_valid_or_report" },
	{ 0x5d16eed4, "refcount_warn_saturate" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0xa5b63e67, "find_get_pid" },
	{ 0xe9179a07, "get_pid_task" },
	{ 0xb7750f25, "put_pid" },
	{ 0x4c03a563, "random_kmalloc_seed" },
	{ 0x0c011510, "kmalloc_caches" },
	{ 0x490f8f90, "__kmalloc_cache_noprof" },
	{ 0x8810754a, "_find_first_bit" },
	{ 0x01c12c32, "cpu_bit_bitmap" },
	{ 0x74e1628a, "set_cpus_allowed_ptr" },
	{ 0x7696f8c7, "__list_add_valid_or_report" },
	{ 0x41ed3709, "get_random_bytes" },
	{ 0xc30cae9a, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xbdfb6dbb,
	0xdc50aae2,
	0x96848186,
	0xb19a5453,
	0xc67e1059,
	0x52e94aa9,
	0x017de3d5,
	0x5a5a2271,
	0x53a1e8d9,
	0x122c3a7e,
	0xf0fdf6cb,
	0x87801d9f,
	0x9e683f75,
	0x27821391,
	0xc6f178ad,
	0xdbfbb9c1,
	0x8554eded,
	0xc9ec4e21,
	0xb6c4379f,
	0xc5b6f236,
	0x315bfc73,
	0x739f986f,
	0x42005d30,
	0x81a4ceb2,
	0xeb5546a2,
	0xd465145b,
	0x03c12dfe,
	0x037a0cba,
	0xa670bcc2,
	0x94160518,
	0x28aa6a67,
	0x950eb34e,
	0x5d16eed4,
	0x13c49cc2,
	0xa5b63e67,
	0xe9179a07,
	0xb7750f25,
	0x4c03a563,
	0x0c011510,
	0x490f8f90,
	0x8810754a,
	0x01c12c32,
	0x74e1628a,
	0x7696f8c7,
	0x41ed3709,
	0xc30cae9a,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__fentry__\0"
	"__ref_stack_chk_guard\0"
	"scnprintf\0"
	"__per_cpu_offset\0"
	"_raw_spin_lock_irqsave\0"
	"_raw_spin_unlock_irqrestore\0"
	"nr_cpu_ids\0"
	"__cpu_online_mask\0"
	"_find_next_bit\0"
	"_printk\0"
	"__stack_chk_fail\0"
	"pcpu_alloc_noprof\0"
	"__cpu_possible_mask\0"
	"misc_register\0"
	"hrtimer_setup\0"
	"hrtimer_start_range_ns\0"
	"__num_online_cpus\0"
	"free_percpu\0"
	"system_percpu_wq\0"
	"queue_work_on\0"
	"hrtimer_cb_get_time\0"
	"hrtimer_forward\0"
	"misc_deregister\0"
	"mutex_lock\0"
	"mutex_unlock\0"
	"hrtimer_cancel\0"
	"cancel_work_sync\0"
	"kfree\0"
	"send_sig_info\0"
	"__put_task_struct_rcu_cb\0"
	"call_rcu\0"
	"__list_del_entry_valid_or_report\0"
	"refcount_warn_saturate\0"
	"_copy_from_user\0"
	"find_get_pid\0"
	"get_pid_task\0"
	"put_pid\0"
	"random_kmalloc_seed\0"
	"kmalloc_caches\0"
	"__kmalloc_cache_noprof\0"
	"_find_first_bit\0"
	"cpu_bit_bitmap\0"
	"set_cpus_allowed_ptr\0"
	"__list_add_valid_or_report\0"
	"get_random_bytes\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "68772674C276BA6B4115A9C");

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
	{ 0xb19a5453, "__per_cpu_offset" },
	{ 0xc67e1059, "_raw_spin_lock_irqsave" },
	{ 0x52e94aa9, "_raw_spin_unlock_irqrestore" },
	{ 0x96848186, "scnprintf" },
	{ 0x017de3d5, "nr_cpu_ids" },
	{ 0x5a5a2271, "__cpu_online_mask" },
	{ 0x53a1e8d9, "_find_next_bit" },
	{ 0x122c3a7e, "_printk" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x87801d9f, "pcpu_alloc_noprof" },
	{ 0x9e683f75, "__cpu_possible_mask" },
	{ 0x27821391, "misc_register" },
	{ 0xffeedf6a, "delayed_work_timer_fn" },
	{ 0xf9ddb5d9, "timer_init_key" },
	{ 0xb6c4379f, "system_percpu_wq" },
	{ 0xb2fcb56d, "queue_delayed_work_on" },
	{ 0x8554eded, "__num_online_cpus" },
	{ 0xc9ec4e21, "free_percpu" },
	{ 0x9fa7184a, "cancel_delayed_work_sync" },
	{ 0x42005d30, "misc_deregister" },
	{ 0x037a0cba, "kfree" },
	{ 0x09f2313c, "send_sig" },
	{ 0x94160518, "__put_task_struct_rcu_cb" },
	{ 0x28aa6a67, "call_rcu" },
	{ 0x950eb34e, "__list_del_entry_valid_or_report" },
	{ 0x5d16eed4, "refcount_warn_saturate" },
	{ 0x01c12c32, "cpu_bit_bitmap" },
	{ 0x74e1628a, "set_cpus_allowed_ptr" },
	{ 0x6a5cc518, "__kmalloc_noprof" },
	{ 0x41ed3709, "get_random_bytes" },
	{ 0x7696f8c7, "__list_add_valid_or_report" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x381109a2, "const_current_task" },
	{ 0x4c03a563, "random_kmalloc_seed" },
	{ 0x0c011510, "kmalloc_caches" },
	{ 0x490f8f90, "__kmalloc_cache_noprof" },
	{ 0xa5b63e67, "find_get_pid" },
	{ 0xe9179a07, "get_pid_task" },
	{ 0xb7750f25, "put_pid" },
	{ 0xc30cae9a, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xbdfb6dbb,
	0xdc50aae2,
	0xb19a5453,
	0xc67e1059,
	0x52e94aa9,
	0x96848186,
	0x017de3d5,
	0x5a5a2271,
	0x53a1e8d9,
	0x122c3a7e,
	0xf0fdf6cb,
	0x87801d9f,
	0x9e683f75,
	0x27821391,
	0xffeedf6a,
	0xf9ddb5d9,
	0xb6c4379f,
	0xb2fcb56d,
	0x8554eded,
	0xc9ec4e21,
	0x9fa7184a,
	0x42005d30,
	0x037a0cba,
	0x09f2313c,
	0x94160518,
	0x28aa6a67,
	0x950eb34e,
	0x5d16eed4,
	0x01c12c32,
	0x74e1628a,
	0x6a5cc518,
	0x41ed3709,
	0x7696f8c7,
	0x13c49cc2,
	0x381109a2,
	0x4c03a563,
	0x0c011510,
	0x490f8f90,
	0xa5b63e67,
	0xe9179a07,
	0xb7750f25,
	0xc30cae9a,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__fentry__\0"
	"__ref_stack_chk_guard\0"
	"__per_cpu_offset\0"
	"_raw_spin_lock_irqsave\0"
	"_raw_spin_unlock_irqrestore\0"
	"scnprintf\0"
	"nr_cpu_ids\0"
	"__cpu_online_mask\0"
	"_find_next_bit\0"
	"_printk\0"
	"__stack_chk_fail\0"
	"pcpu_alloc_noprof\0"
	"__cpu_possible_mask\0"
	"misc_register\0"
	"delayed_work_timer_fn\0"
	"timer_init_key\0"
	"system_percpu_wq\0"
	"queue_delayed_work_on\0"
	"__num_online_cpus\0"
	"free_percpu\0"
	"cancel_delayed_work_sync\0"
	"misc_deregister\0"
	"kfree\0"
	"send_sig\0"
	"__put_task_struct_rcu_cb\0"
	"call_rcu\0"
	"__list_del_entry_valid_or_report\0"
	"refcount_warn_saturate\0"
	"cpu_bit_bitmap\0"
	"set_cpus_allowed_ptr\0"
	"__kmalloc_noprof\0"
	"get_random_bytes\0"
	"__list_add_valid_or_report\0"
	"_copy_from_user\0"
	"const_current_task\0"
	"random_kmalloc_seed\0"
	"kmalloc_caches\0"
	"__kmalloc_cache_noprof\0"
	"find_get_pid\0"
	"get_pid_task\0"
	"put_pid\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "10C3EA891903141B719625D");

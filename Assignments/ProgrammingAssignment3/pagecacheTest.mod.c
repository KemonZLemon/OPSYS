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
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xce279400, "remove_proc_entry" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0x5cb46e6d, "validate_usercopy_range" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0x173ec8da, "sscanf" },
	{ 0xf452b537, "find_get_pid" },
	{ 0xab4517db, "get_pid_task" },
	{ 0xcf59ca29, "put_pid" },
	{ 0x976c74cb, "get_task_mm" },
	{ 0xe6cc5085, "__tracepoint_mmap_lock_start_locking" },
	{ 0x8efcc8cd, "down_read" },
	{ 0xe6cc5085, "__tracepoint_mmap_lock_acquire_returned" },
	{ 0x81a11b4b, "get_user_pages_remote" },
	{ 0xe6cc5085, "__tracepoint_mmap_lock_released" },
	{ 0x8efcc8cd, "up_read" },
	{ 0x70e9fdd0, "filp_open" },
	{ 0x03760204, "pagecache_get_page" },
	{ 0xbd03ed67, "vmemmap_base" },
	{ 0xbd03ed67, "page_offset_base" },
	{ 0x402db74e, "memcmp" },
	{ 0xe5179ac5, "hugetlb_optimize_vmemmap_key" },
	{ 0xf19f3c24, "filp_close" },
	{ 0x35283b01, "mmput" },
	{ 0xff0106da, "refcount_warn_saturate" },
	{ 0xe78e4943, "__mmap_lock_do_trace_start_locking" },
	{ 0xe78e4943, "__mmap_lock_do_trace_released" },
	{ 0x790053b1, "__mmap_lock_do_trace_acquire_returned" },
	{ 0x1cf09ab5, "__put_task_struct_rcu_cb" },
	{ 0xb9fcd065, "call_rcu" },
	{ 0x1285fd2a, "__folio_put" },
	{ 0x90a48d82, "__ubsan_handle_out_of_bounds" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0xd272d446, "__fentry__" },
	{ 0x6b01a33d, "proc_create" },
	{ 0xe8213e80, "_printk" },
	{ 0xd954c786, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0xce279400,
	0xbd03ed67,
	0x5cb46e6d,
	0xa61fd7aa,
	0x092a35a2,
	0x173ec8da,
	0xf452b537,
	0xab4517db,
	0xcf59ca29,
	0x976c74cb,
	0xe6cc5085,
	0x8efcc8cd,
	0xe6cc5085,
	0x81a11b4b,
	0xe6cc5085,
	0x8efcc8cd,
	0x70e9fdd0,
	0x03760204,
	0xbd03ed67,
	0xbd03ed67,
	0x402db74e,
	0xe5179ac5,
	0xf19f3c24,
	0x35283b01,
	0xff0106da,
	0xe78e4943,
	0xe78e4943,
	0x790053b1,
	0x1cf09ab5,
	0xb9fcd065,
	0x1285fd2a,
	0x90a48d82,
	0xd272d446,
	0xd272d446,
	0x6b01a33d,
	0xe8213e80,
	0xd954c786,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__x86_return_thunk\0"
	"remove_proc_entry\0"
	"__ref_stack_chk_guard\0"
	"validate_usercopy_range\0"
	"__check_object_size\0"
	"_copy_from_user\0"
	"sscanf\0"
	"find_get_pid\0"
	"get_pid_task\0"
	"put_pid\0"
	"get_task_mm\0"
	"__tracepoint_mmap_lock_start_locking\0"
	"down_read\0"
	"__tracepoint_mmap_lock_acquire_returned\0"
	"get_user_pages_remote\0"
	"__tracepoint_mmap_lock_released\0"
	"up_read\0"
	"filp_open\0"
	"pagecache_get_page\0"
	"vmemmap_base\0"
	"page_offset_base\0"
	"memcmp\0"
	"hugetlb_optimize_vmemmap_key\0"
	"filp_close\0"
	"mmput\0"
	"refcount_warn_saturate\0"
	"__mmap_lock_do_trace_start_locking\0"
	"__mmap_lock_do_trace_released\0"
	"__mmap_lock_do_trace_acquire_returned\0"
	"__put_task_struct_rcu_cb\0"
	"call_rcu\0"
	"__folio_put\0"
	"__ubsan_handle_out_of_bounds\0"
	"__stack_chk_fail\0"
	"__fentry__\0"
	"proc_create\0"
	"_printk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "306B60AC2016192D4793928");

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
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0xbd069841, "kstrtoull" },
	{ 0x90a48d82, "__ubsan_handle_out_of_bounds" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x33c78c8a, "remove_proc_entry" },
	{ 0x092a35a2, "_copy_to_user" },
	{ 0x4d40f3a6, "const_pcpu_hot" },
	{ 0x40a621c5, "snprintf" },
	{ 0xf296206e, "pgdir_shift" },
	{ 0xb1ad3f2f, "boot_cpu_data" },
	{ 0xb3f8c2e9, "pv_ops" },
	{ 0xd272d446, "BUG_func" },
	{ 0x095159b2, "physical_mask" },
	{ 0xf296206e, "ptrs_per_p4d" },
	{ 0xbd03ed67, "page_offset_base" },
	{ 0x82fd7238, "__ubsan_handle_shift_out_of_bounds" },
	{ 0xd272d446, "__fentry__" },
	{ 0x82c6f73b, "proc_create" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xba157484, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xa61fd7aa,
	0x092a35a2,
	0xbd069841,
	0x90a48d82,
	0xd272d446,
	0x33c78c8a,
	0x092a35a2,
	0x4d40f3a6,
	0x40a621c5,
	0xf296206e,
	0xb1ad3f2f,
	0xb3f8c2e9,
	0xd272d446,
	0x095159b2,
	0xf296206e,
	0xbd03ed67,
	0x82fd7238,
	0xd272d446,
	0x82c6f73b,
	0xe8213e80,
	0xd272d446,
	0xba157484,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__check_object_size\0"
	"_copy_from_user\0"
	"kstrtoull\0"
	"__ubsan_handle_out_of_bounds\0"
	"__stack_chk_fail\0"
	"remove_proc_entry\0"
	"_copy_to_user\0"
	"const_pcpu_hot\0"
	"snprintf\0"
	"pgdir_shift\0"
	"boot_cpu_data\0"
	"pv_ops\0"
	"BUG_func\0"
	"physical_mask\0"
	"ptrs_per_p4d\0"
	"page_offset_base\0"
	"__ubsan_handle_shift_out_of_bounds\0"
	"__fentry__\0"
	"proc_create\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "0A7F27FA3C40A639E191750");

/*
 * Copyright (c) 2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <realm/rmi.h>
#include <realm/rmi_lib.h>

u_register_t realm_version(void)
{
	smc_args args = { RMI_RMM_REQ_VERSION };
	smc_ret_values ret;

	ret = tftf_smc(&args);
	return ret.ret0;
}

u_register_t realm_granule_delegate(u_register_t add)
{
	smc_args args = { 0 };
	smc_ret_values ret;

	args.fid = SMC_RMM_GRANULE_DELEGATE;
	args.arg1 = add;

	ret = tftf_smc(&args);
	return ret.ret0;
}

u_register_t realm_granule_undelegate(u_register_t add)
{
	smc_args args = { 0 };
	smc_ret_values ret;

	args.fid = SMC_RMM_GRANULE_UNDELEGATE;
	args.arg1 = add;

	ret = tftf_smc(&args);
	return ret.ret0;
}

smc_ret_values realm_vm_create()
{
	smc_args args = { 0 };
	smc_ret_values ret;

	args.fid = SMC_RMM_VM_CREATE;

	ret = tftf_smc(&args);
	return ret;
}

smc_ret_values realm_vm_run(u_register_t vm, u_register_t vcpu)
{
	smc_args args = { 0 };
	smc_ret_values ret;

	args.fid = SMC_RMM_VM_RUN;
	args.arg1 = vm;
	args.arg2 = vcpu;

	ret = tftf_smc(&args);
	return ret;
}

#if 0
u_register_t realm_vm_resume(void)
{
	smc_args args = { 0 };
	smc_ret_values ret;

	args.fid = SMC_RMM_VM_RESUME;

	ret = tftf_smc(&args);
	return ret.ret0;
}
#endif

u_register_t realm_vm_destroy(u_register_t vm)
{
	smc_args args = { 0 };
	smc_ret_values ret;

	args.fid = SMC_RMM_VM_DESTROY;
	args.arg1 = vm;

	ret = tftf_smc(&args);
	return ret.ret0;
}

u_register_t realm_vm_map_memory(u_register_t vm, u_register_t guest,
		u_register_t phys, u_register_t size, u_register_t prot)
{
	smc_args args = { 0 };
	smc_ret_values ret;

	args.fid = SMC_RMM_VM_MAP_MEMORY;
	args.arg1 = vm;
	args.arg2 = guest;
	args.arg3 = phys;
	args.arg4 = size;
	args.arg5 = prot;

	ret = tftf_smc(&args);
	return ret.ret0;
}

u_register_t realm_vm_unmap_memory(u_register_t vm, u_register_t guest,
		u_register_t size)
{
	smc_args args = { 0 };
	smc_ret_values ret;

	args.fid = SMC_RMM_VM_UNMAP_MEMORY;
	args.arg1 = vm;
	args.arg2 = guest;
	args.arg3 = size;

	ret = tftf_smc(&args);
	return ret.ret0;
}

u_register_t realm_vm_set_reg(u_register_t vm, u_register_t guest,
		u_register_t reg, u_register_t value)
{
	smc_args args = { 0 };
	smc_ret_values ret;

	args.fid = SMC_RMM_VM_SET_REG;
	args.arg1 = vm;
	args.arg2 = guest;
	args.arg3 = reg;
	args.arg4 = value;

	ret = tftf_smc(&args);
	return ret.ret0;
}

smc_ret_values realm_vm_get_reg(u_register_t vm, u_register_t guest,
		u_register_t reg)
{
	smc_args args = { 0 };
	smc_ret_values ret;

	args.fid = SMC_RMM_VM_GET_REG;
	args.arg1 = vm;
	args.arg2 = guest;
	args.arg3 = reg;

	ret = tftf_smc(&args);
	return ret;
}

smc_ret_values realm_vcpu_create(u_register_t vmid)
{
	smc_args args = { 0 };
	smc_ret_values ret;

	args.fid = SMC_RMM_VCPU_CREATE;
	args.arg1 = vmid;

	ret = tftf_smc(&args);
	return ret;
}

/*
 * Copyright (c) 2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __RMI_H__
#define __RMI_H__

#include <linux/types.h>
#include <vdso/const.h>
#define u_register_t uint64_t

#if defined(__LINKER__) || defined(__ASSEMBLY__)
# define   U(_x)    (_x)
//# define  UL(_x)    (_x)
//# define ULL(_x)    (_x)
//# define   L(_x)    (_x)
//# define  LL(_x)    (_x)
#else
# define   U(_x)    (_x##U)
//# define  UL(_x)    (_x##UL)
//# define ULL(_x)    (_x##ULL)
//# define   L(_x)    (_x##L)
//# define  LL(_x)    (_x##LL)
#endif

/*
 * SMC calls take a function identifier and up to 7 arguments.
 * Additionally, few SMC calls that originate from EL2 leverage the seventh
 * argument explicitly. Given that TFTF runs in EL2, we need to be able to
 * specify it.
 */
typedef struct {
	/* Function identifier. Identifies which function is being invoked. */
	uint32_t	fid;

	u_register_t	arg1;
	u_register_t	arg2;
	u_register_t	arg3;
	u_register_t	arg4;
	u_register_t	arg5;
	u_register_t	arg6;
	u_register_t	arg7;
} smc_args;

/* SMC calls can return up to 8 register values */
typedef struct {
	u_register_t	ret0;
	u_register_t	ret1;
	u_register_t	ret2;
	u_register_t	ret3;
	u_register_t	ret4;
	u_register_t	ret5;
	u_register_t	ret6;
	u_register_t	ret7;
} smc_ret_values;

#define RET_SUCCESS                     U(257)
#define RET_FAIL                        U(256)
#define RET_PAGE_FAULT                  U(1)

u_register_t realm_version(void);
u_register_t realm_granule_delegate(u_register_t);
u_register_t realm_granule_undelegate(u_register_t);

smc_ret_values realm_vm_create(void);
u_register_t realm_vm_switch(u_register_t, u_register_t);
u_register_t realm_vm_resume(void);
u_register_t realm_vm_destroy(u_register_t);
u_register_t realm_vm_map_memory(u_register_t, u_register_t, u_register_t,
		u_register_t, u_register_t);
u_register_t realm_vm_unmap_memory(u_register_t, u_register_t, u_register_t);
u_register_t realm_vm_set_reg(u_register_t, u_register_t, u_register_t,
		u_register_t);
smc_ret_values realm_vm_get_reg(u_register_t, u_register_t, u_register_t);
smc_ret_values realm_vm_run(u_register_t, u_register_t);
smc_ret_values realm_vcpu_create(u_register_t);

/* Just to avoid compile error with kvm nvhe */
#if 0
u_register_t __kvm_nvhe_realm_vm_set_reg(u_register_t, u_register_t, u_register_t,
		u_register_t);
smc_ret_values __kvm_nvhe_realm_vm_get_reg(u_register_t, u_register_t, u_register_t);
u_register_t __kvm_nvhe_realm_vm_set_reg(u_register_t r1,
                                    u_register_t r2, u_register_t r3, u_register_t r4)
{
    return 0x0;
};

smc_ret_values __kvm_nvhe_realm_vm_get_reg(u_register_t r1,
                                        u_register_t r2, u_register_t r3)
{
    smc_ret_values ret;
    ret.ret0 = 0;
    return ret;
};
#endif
#endif /* __RMI_H__ */

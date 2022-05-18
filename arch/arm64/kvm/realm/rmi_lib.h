/*
 * Copyright (c) 2018-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __TFTF_LIB_H__
#define __TFTF_LIB_H__

#include "smccc.h"
//#include <tftf_lib.h>

#if defined(__LINKER__) || defined(__ASSEMBLY__)
# define   U(_x)    (_x)
# define  UL(_x)    (_x)
# define ULL(_x)    (_x)
# define   L(_x)    (_x)
# define  LL(_x)    (_x)
#else
# define   U(_x)    (_x##U)
# define  UL(_x)    (_x##UL)
# define ULL(_x)    (_x##ULL)
# define   L(_x)    (_x##L)
# define  LL(_x)    (_x##LL)
#endif

#define RMI_FNUM_MIN_VALUE	U(0x00)
#define RMI_FNUM_MAX_VALUE	U(0x20)

/* Get RMI fastcall std FID from function number */
#define RMI_FID(smc_cc, func_num)			\
	((SMC_TYPE_FAST << FUNCID_TYPE_SHIFT)	|	\
	((smc_cc) << FUNCID_CC_SHIFT)		|	\
	(OEN_ARM_START << FUNCID_OEN_SHIFT)	|	\
	((func_num) << FUNCID_NUM_SHIFT))

/*
 * SMC_RMM_INIT_COMPLETE is the only function in the RMI that originates from
 * the Realm world and is handled by the RMMD. The remaining functions are
 * always invoked by the Normal world, forwarded by RMMD and handled by the
 * RMM
 */
#define RMI_FNUM_VERSION_REQ		U(0)

#define RMI_FNUM_GRAN_NS_REALM		U(1)
#define RMI_FNUM_GRAN_REALM_NS		U(2)

#define RMI_FNUM_VM_CREATE              U(3)
#define RMI_FNUM_VM_SWITCH              U(4)
#define RMI_FNUM_VM_RESUME              U(5)
#define RMI_FNUM_VM_DESTROY             U(6)
#define RMI_FNUM_VM_MAP_MEMORY          U(7)
#define RMI_FNUM_VM_UNMAP_MEMORY        U(8)
#define RMI_FNUM_VM_SET_REG             U(9)
#define RMI_FNUM_VM_GET_REG             U(10)
#define RMI_FNUM_VM_RUN                 U(11)
#define RMI_FNUM_VCPU_CREATE            U(12)

//#define RET_SUCCESS                     U(0)
//#define RET_FAIL                        U(256)
//#define RET_PAGE_FAULT                  U(1)

/********************************************************************************/


/* RMI SMC64 FIDs handled by the RMMD */
#define RMI_RMM_REQ_VERSION		RMI_FID(SMC_64, RMI_FNUM_VERSION_REQ)

#define SMC_RMM_GRANULE_DELEGATE	RMI_FID(SMC_64, RMI_FNUM_GRAN_NS_REALM)
#define SMC_RMM_GRANULE_UNDELEGATE	RMI_FID(SMC_64, RMI_FNUM_GRAN_REALM_NS)

#define SMC_RMM_VM_CREATE               RMI_FID(SMC_64, RMI_FNUM_VM_CREATE)
#define SMC_RMM_VM_SWITCH               RMI_FID(SMC_64, RMI_FNUM_VM_SWITCH)
#define SMC_RMM_VM_RESUME               RMI_FID(SMC_64, RMI_FNUM_VM_RESUME)
#define SMC_RMM_VM_DESTROY              RMI_FID(SMC_64, RMI_FNUM_VM_DESTROY)
#define SMC_RMM_VM_MAP_MEMORY           RMI_FID(SMC_64, RMI_FNUM_VM_MAP_MEMORY)
#define SMC_RMM_VM_UNMAP_MEMORY         RMI_FID(SMC_64, RMI_FNUM_VM_UNMAP_MEMORY)
#define SMC_RMM_VM_SET_REG              RMI_FID(SMC_64, RMI_FNUM_VM_SET_REG)
#define SMC_RMM_VM_GET_REG              RMI_FID(SMC_64, RMI_FNUM_VM_GET_REG)
#define SMC_RMM_VM_RUN                  RMI_FID(SMC_64, RMI_FNUM_VM_RUN)
#define SMC_RMM_VCPU_CREATE             RMI_FID(SMC_64, RMI_FNUM_VCPU_CREATE)

#define RMI_ABI_VERSION_GET_MAJOR(_version) ((_version) >> 16)
#define RMI_ABI_VERSION_GET_MINOR(_version) ((_version) & 0xFFFF)

#define NUM_GRANULES			5
#define NUM_RANDOM_ITERATIONS		7
#define GRANULE_SIZE			4096

#define B_DELEGATED			0
#define B_UNDELEGATED			1

#define NUM_CPU_DED_SPM			PLATFORM_CORE_COUNT / 2


/*
 * Possible error codes for signaling the result of a test
 * TEST_RESULT_MIN and TEST_RESULT_MAX are only used as bounds in the enum.
 */
typedef enum {
	/*
	 * NA = Not applicable.
	 * Initial value for a test result.
	 * Used for CPUs that don't participate in the test.
	 */
	TEST_RESULT_NA		= -1,

	TEST_RESULT_MIN		= 0,
	TEST_RESULT_SKIPPED	= TEST_RESULT_MIN,
	TEST_RESULT_SUCCESS,
	TEST_RESULT_FAIL,
	TEST_RESULT_CRASHED,

	TEST_RESULT_MAX
} test_result_t;

#define TEST_RESULT_IS_VALID(result) \
	((result >= TEST_RESULT_MIN) && (result < TEST_RESULT_MAX))


/*
 * Trigger an SMC call.
 */
smc_ret_values asm_tftf_smc64(uint32_t fid,
                  u_register_t arg1,
                  u_register_t arg2,
                  u_register_t arg3,
                  u_register_t arg4,
                  u_register_t arg5,
                  u_register_t arg6,
                  u_register_t arg7);
 
smc_ret_values tftf_smc(const smc_args *args)
{
    return asm_tftf_smc64(args->fid,
                  args->arg1,
                  args->arg2,
                  args->arg3,
                  args->arg4,
                  args->arg5,
                  args->arg6,
                  args->arg7);
}

#endif /* __TFTF_LIB_H__ */

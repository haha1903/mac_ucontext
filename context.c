/* Copyright (c) 2005-2006 Russ Cox, MIT; see COPYRIGHT */

#include "mac-ucontext.h"

#define NEEDAMD64MAKECONTEXT
#define NEEDSWAPCONTEXT

#ifdef NEEDAMD64MAKECONTEXT
void
makecontext(ucontext_t *ucp, void (*func)(void), int argc, ...)
{
	long *sp;
	va_list va;

	memset(&ucp->uc_mcontext, 0, sizeof ucp->uc_mcontext);
	if(argc != 2)
		*(volatile int*)0 = 0;
	va_start(va, argc);
	ucp->uc_mcontext.mc_rdi = va_arg(va, int);
	ucp->uc_mcontext.mc_rsi = va_arg(va, int);
	va_end(va);
	sp = (long*)ucp->uc_stack.ss_sp+ucp->uc_stack.ss_size/sizeof(long);
	sp -= argc;
	sp = (void*)((uintptr_t)sp - (uintptr_t)sp%16);	/* 16-align for OS X */
	*--sp = 0;	/* return address */
	ucp->uc_mcontext.mc_rip = (long)func;
	ucp->uc_mcontext.mc_rsp = (long)sp;
}
#endif

#ifdef NEEDSWAPCONTEXT
int
swapcontext(ucontext_t *oucp, const ucontext_t *ucp)
{
	if(getcontext(oucp) == 0)
		setcontext(ucp);
	return 0;
}
#endif


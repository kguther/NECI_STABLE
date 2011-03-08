#define LogAlloc(ERR,NAME,LEN,SIZE,TAG) CALL LogMemAlloc(NAME,LEN,SIZE,this_routine,TAG)
#define LogDealloc(TAG) CALL LogMemDealloc(this_routine,TAG)
#define IsNullDet(nI) (nI(1).eq.0)

! Is the specified orbital occupied or not?
! TODO: Use ilut_int/ilut_off here?
#define IsOcc(ilut,orb) btest(ilut((orb-1)/bits_n_int), mod(orb-1,bits_n_int))
#define IsNotOcc(ilut,orb) (.not.IsOcc(ilut,orb))

! Is the specified orbital alpha or beta? Generate the appropriate pair.
#define is_beta(orb) btest(orb, 0)
#define is_alpha(orb) (.not.is_beta(orb))
#define is_one_alpha_beta(orb1,orb2) (btest(orb1,0) .neqv. btest(orb2,0)) 
#define ab_pair(orb) (ieor(orb-1,1)+1)
#define get_beta(orb) (ibclr(orb-1,0)+1)
#define get_alpha(orb) (ibset(orb-1,0)+1)

! The spin where 1=alpha, 2=beta
#define get_spin(orb) (1+iand(orb,1))

! Is the specified orbital part of a doubly occupied pair?
#define IsDoub(ilut,orb) (IsOcc(ilut,orb).and.IsOcc(ilut,ab_pair(orb)))

! Are the two orbitals specified (may be the same orbital) from the same
! spatial orbital?
#define is_in_pair(orb1,orb2) (ibclr(orb1-1,0) == ibclr(orb2-1,0))

! Set or clear orbitals in a bit representation
#define ilut_int(orb) ((orb - 1) / bits_n_int)
#define ilut_off(orb) mod(orb-1, bits_n_int)
#define set_orb(ilut, orb) ilut(ilut_int(orb)) = ibset(ilut(ilut_int(orb)), ilut_off(orb))
#define clr_orb(ilut, orb) ilut(ilut_int(orb)) = ibclr(ilut(ilut_int(orb)), ilut_off(orb))

! Useful for fixing things. Requires this_routine to be defined
#ifdef __DEBUG
#define ASSERT(x) \
if (.not. (x)) then; \
 call stop_all (this_routine, "Assertation failed: "//"x"); \
endif
#define ASSERTROOT(x) \
if ((iProcIndex.eq.Root).and.(.not. (x))) then; \
 call stop_all (this_routine, "Assertation failed: "//"x"); \
endif
! Do some debugging if X>=Y
#define IFDEBUG(PrintLevel,ThisLevel) if (PrintLevel>=ThisLevel)
#define IFDEBUGEQ(PrintLevel,ThisLevel) if (PrintLevel==ThisLevel)
#define IFDEBUGEQTHEN(PrintLevel,ThisLevel) if (PrintLevel==ThisLevel) then
#define IFDEBUGTHEN(PrintLevel,ThisLevel) if (PrintLevel>=ThisLevel) then
#define ENDIFDEBUG endif
#else
#define ASSERT(x)
#define ASSERTROOT(x)
#define IFDEBUG(PrintLevel,ThisLevel) if(.false.)
#define IFDEBUGEQ(PrintLevel,ThisLevel) if(.false.)
#define IFDEBUGEQTHEN(PrintLevel,ThisLevel) if(.false.) then
#define IFDEBUGTHEN(PrintLevel,ThisLevel) if(.false.) then
#define ENDIFDEBUG endif
#endif

! Write out from the root node (concisely)
#define root_write if (iProcIndex == 0) write
#define root_print root_write (6, *) 

! Make Re / Cplx builds easier
#ifdef __CMPLX
#define ARR_RE_OR_CPLX(arr) cmplx(arr(1), arr(2), dp)
#define ARR_ABS(arr) abs(cmplx(arr(1), arr(2), dp))
#else
#define ARR_RE_OR_CPLX(arr) real(arr(1), dp)
#define ARR_ABS(arr) abs(arr(1))
#endif

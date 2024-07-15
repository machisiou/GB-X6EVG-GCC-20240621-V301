#ifndef __RTK_common_dbc_H__
#define __RTK_common_dbc_H__

#ifndef	RTK_NASSERT

//extern void onAssert__(char const *file, unsigned line);

#define RTK_DEFINE_THIS_FILE static const char THIS_FILE__[] = __FILE__

#define RTK_ASSERT(test_)	\
		if(test_) {	\
		}			\
		else onAssert__(THIS_FILE__,__LINE__)

#define RTK_REQUIRE(test_)		RTK_ASSERT(test_)
#define RTK_ENSURE(test_)		RTK_ASSERT(test_)
#define RTK_INVARIANT(test_)	RTK_ASSERT(test_)
#define RTK_ALLEGE(test_)		RTK_ASSERT(test_)

#else

#endif

#endif

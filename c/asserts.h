/*
 ============================================================================
 Name        : asserts.h
 Author      : borgr
 Version     : 1
 Copyright   :
 Description : adds asserts to c++ for debugging
 ============================================================================
 */
#ifndef ASSERTS
	using namespace std;
	#define ASSERTS
	#ifdef NDEBUG
		#define ASSERT_PRINT(text) ((void)0)
	#else
		#define ASSERT_PRINT(text) cout << text << endl
	#endif
#endif
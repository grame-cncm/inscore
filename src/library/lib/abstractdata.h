#ifndef ABSTRACTDATA
#define ABSTRACTDATA

/*!
 * A simple structure for arbitrary binary data.
 */
typedef struct abstractdata {
		const char * data;
		int size;
		unsigned long version;
} AbstractData;

#endif // ABSTRACTDATA


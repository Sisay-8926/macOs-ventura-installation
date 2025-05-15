#include <mach/mach_time.h>
#include <sys/time.h>

int gettimeofday(struct timeval *tv, void *tz) {
    if (tv) {
        // Get current time from Mach absolute time
        uint64_t now = mach_absolute_time();
        
        // Convert Mach time to nanoseconds
        mach_timebase_info_data_t timebase;
        mach_timebase_info(&timebase);
        uint64_t nanos = now * timebase.numer / timebase.denom;
        
        // Convert to timeval
        tv->tv_sec = nanos / NSEC_PER_SEC;
        tv->tv_usec = (nanos % NSEC_PER_SEC) / 1000;
    }
    
    // macOS ignores the timezone parameter
    if (tz) {
        // On macOS, this would typically be set to NULL
    }
    
    return 0;
}


